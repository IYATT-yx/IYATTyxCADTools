#include "StdAfx.h"
#include "DimensionLock.hpp"
#include "Common.hpp"

Types::CallbackReturnStatus DimensionLock::cbLock(AcDbEntity* ent)
{
	AcDbDimension* dim = Common::entityToDimension(ent);
	if (!dim)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	// ��ȡ��ע�ַ��� 
	AcString dimensionString;
	dim->dimensionText(dimensionString);

	// �ߴ�ֵ���ַ���
	AcString measureValueString;
	// �ߴ�ֵ
	double measureValue;
	dim->measurement(measureValue);

	if (dim->isA() == AcDb2LineAngularDimension::desc()) // �Ƕȱ�ע
	{
		int precision = dim->dimadec(); // �Ƕȱ�ע����
		Common::doubnleToStringWithPrecision(measureValue, measureValueString, precision, true);
		measureValueString += L"%%d";
	}
	else
	{
		int precision = dim->dimdec(); // ���Ա�ע����
		Common::doubnleToStringWithPrecision(measureValue, measureValueString, precision);
		if (dim->isA() == AcDbDiametricDimension::desc()) // ֱ����ע
		{
			measureValueString = L"%%c" + measureValueString;
		}
		else if (dim->isA() == AcDbRadialDimension::desc()) // �뾶��ע
		{
			measureValueString = L"R" + measureValueString;
		}
	}

	if (dimensionString.length() == 0) // ��ע�ַ���Ϊ�գ�ԭʼ�ߴ������ı�ע
	{
		dim->setDimensionText(measureValueString.kACharPtr());
		acutPrintf(L"����ֵ��%lf�����ñ�ע����Ϊ��%s\n", measureValue, measureValueString.kACharPtr());
	}
	else
	{
		if (Common::dimensionStringInsertValue(dimensionString, measureValueString))
		{
			dim->setDimensionText(dimensionString.kACharPtr());
			acutPrintf(L"����ֵ��%lf�����ñ�ע����Ϊ��%s\n", measureValue, dimensionString.kACharPtr());
		}
		else
		{
			acutPrintf(L"���ı���ע:%s����������\n", dimensionString.kACharPtr());
			return Types::CallbackReturnStatus::CONTINUE;
		}
	}

	return Types::CallbackReturnStatus::SUCCESS;
}

Types::CallbackReturnStatus DimensionLock::cbReset(AcDbEntity* ent)
{
	AcDbDimension* dim = Common::entityToDimension(ent);
	if (!dim)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}
	dim->setDimensionText(L"");
	return Types::CallbackReturnStatus::SUCCESS;
}
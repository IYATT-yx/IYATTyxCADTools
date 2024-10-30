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

	// 获取标注字符串 
	AcString dimensionString;
	dim->dimensionText(dimensionString);

	// 尺寸值的字符串
	AcString measureValueString;
	// 尺寸值
	double measureValue;
	dim->measurement(measureValue);

	if (dim->isA() == AcDb2LineAngularDimension::desc()) // 角度标注
	{
		int precision = dim->dimadec(); // 角度标注精度
		Common::doubnleToStringWithPrecision(measureValue, measureValueString, precision, true);
		measureValueString += L"%%d";
	}
	else
	{
		int precision = dim->dimdec(); // 线性标注精度
		Common::doubnleToStringWithPrecision(measureValue, measureValueString, precision);
		if (dim->isA() == AcDbDiametricDimension::desc()) // 直径标注
		{
			measureValueString = L"%%c" + measureValueString;
		}
		else if (dim->isA() == AcDbRadialDimension::desc()) // 半径标注
		{
			measureValueString = L"R" + measureValueString;
		}
	}

	if (dimensionString.length() == 0) // 标注字符串为空，原始尺寸驱动的标注
	{
		dim->setDimensionText(measureValueString.kACharPtr());
		acutPrintf(L"测量值：%lf，设置标注内容为：%s\n", measureValue, measureValueString.kACharPtr());
	}
	else
	{
		if (Common::dimensionStringInsertValue(dimensionString, measureValueString))
		{
			dim->setDimensionText(dimensionString.kACharPtr());
			acutPrintf(L"测量值：%lf，设置标注内容为：%s\n", measureValue, dimensionString.kACharPtr());
		}
		else
		{
			acutPrintf(L"纯文本标注:%s，不做处理。\n", dimensionString.kACharPtr());
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
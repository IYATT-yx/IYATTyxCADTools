#include "StdAfx.h"
#include "Common.hpp"
#include <sstream>
#include <iomanip>

void Common::doubnleToStringWithPrecision(double inDouble, AcString& outString, const int& precision, bool isRadianValue)
{
	if (isRadianValue)
	{
		inDouble = inDouble / PI * 180;
	}

	std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << inDouble;
	outString = oss.str().c_str();
}

bool Common::dimensionStringInsertValue(AcString& dimensionString, AcString& measureValueString)
{
	Adesk::Int32 pos = dimensionString.find(dimensionPlaceHolder);
	if (pos != -1)
	{
		dimensionString = dimensionString.substr(pos) + measureValueString + dimensionString.mid(pos + dimensionPlaceHolderLength);
		return true;
	}
	else
	{
		return false;
	}
}

AcDbDimension* Common::entityToDimension(AcDbEntity* entity)
{
	if (entity->isKindOf(AcDbDimension::desc()))
	{
		return AcDbDimension::cast(entity);
	}
	return nullptr;
}

AcDbMText* Common::entityToMText(AcDbEntity* entity)
{
	if (entity->isKindOf(AcDbMText::desc()))
	{
		return AcDbMText::cast(entity);
	}
	return nullptr;
}
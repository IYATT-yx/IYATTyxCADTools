#include "StdAfx.h"
#include "IYATTyxCADTools.hpp"
#include "DimensionLock.hpp"
#include "Select.hpp"
#include "Types.hpp"
#include "Symbol.hpp"
#include <map>

void IYATTyxCADTools::cmdLockDimension()
{
	const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction> classFunctionPairs = { { AcDbDimension::desc(), DimensionLock::cbLock } };
	Select::selectSetForeach(classFunctionPairs);
}

void IYATTyxCADTools::cmdResetDimension()
{
	const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction> classFunctionPairs = { { AcDbDimension::desc(), DimensionLock::cbReset } };
	Select::selectSetForeach(classFunctionPairs);
}

void IYATTyxCADTools::cmdSetReferenceDimension()
{
	const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction> classFunctionPairs = { { AcDbDimension::desc(), Symbol::cbAddParentheses } };
	Select::selectExecute(classFunctionPairs);
}

void IYATTyxCADTools::cmdCancelReferenceDimension()
{
	const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction> classFunctionPairs = { { AcDbDimension::desc(), Symbol::cbRemoveParaenthess } };
	Select::selectExecute(classFunctionPairs);
}

void IYATTyxCADTools::cmdAddCustomSymbol()
{
	const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction> classFunctionPairs =
	{
		{ AcDbDimension::desc(), Symbol::cbAddCustomSymbolDimension },
		{ AcDbMText::desc(), Symbol::cbAddCustomSymbolMText }
	};
	Select::selectExecute(classFunctionPairs);
}

void IYATTyxCADTools::cmdRemoveCustomSymbol()
{
	const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction> classFunctionPairs =
	{
		{ AcDbDimension::desc(), Symbol::cbRemoveCustomSymbolDimension },
		{ AcDbMText::desc(), Symbol::cbRemoveCustomSymbolMText }
	};
	Select::selectExecute(classFunctionPairs);
}

void IYATTyxCADTools::cmdIYATTyxCADToolsInfo()
{
	acutPrintf(L"%s\n", INFO);
}

void IYATTyxCADTools::init()
{
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"LD", L"LD", ACRX_CMD_MODAL, IYATTyxCADTools::cmdLockDimension);
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"RD", L"RD", ACRX_CMD_MODAL, IYATTyxCADTools::cmdResetDimension);
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"SRD", L"SRD", ACRX_CMD_MODAL, IYATTyxCADTools::cmdSetReferenceDimension);
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"CRD", L"CRD", ACRX_CMD_MODAL, IYATTyxCADTools::cmdCancelReferenceDimension);
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"ACS", L"ACS", ACRX_CMD_MODAL, IYATTyxCADTools::cmdAddCustomSymbol);
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"RCS", L"RCS", ACRX_CMD_MODAL, IYATTyxCADTools::cmdRemoveCustomSymbol);
	acedRegCmds->addCommand(L"IYATTyxCADTools", L"IYATTyxCADToolsInfo", L"IYATTyxCADToolsInfo", ACRX_CMD_MODAL, IYATTyxCADTools::cmdIYATTyxCADToolsInfo);
}

void IYATTyxCADTools::unload()
{
	acedRegCmds->removeGroup(L"IYATTyxCADTools");
}
/**
 * @file DimensionTools.hpp
 * @brief IYATT-yx CAD 工具
 */
#pragma once

#define charStringToWideCharString(s)           L##s
#define CSTWCS(s)                               charStringToWideCharString(s)
#define WDATE                                   CSTWCS(__DATE__)
#define WTIME                                   CSTWCS(__TIME__)

#define VERSION									L"v0.0.1"
#define INFO									L"* IYATT-yx iyatt@iyatt.com" L"\n* 版本：" VERSION L"\n* 程序构建时间："  WDATE L" " WTIME

class IYATTyxCADTools
{
private:
	static void cmdLockDimension();
	static void cmdResetDimension();
	static void cmdSetReferenceDimension();
	static void cmdCancelReferenceDimension();
	static void cmdAddCustomSymbol();
	static void cmdRemoveCustomSymbol();
	static void cmdIYATTyxCADToolsInfo();

public:
	static void init();
	static void unload();
};


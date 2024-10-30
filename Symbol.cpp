#include "StdAfx.h"
#include "Symbol.hpp"
#include "Common.hpp"

Types::CallbackReturnStatus Symbol::cbAddParentheses(AcDbEntity* ent)
{
	AcDbDimension* dim = Common::entityToDimension(ent);
	if (!dim)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	AcString dimensionString;
	dim->dimensionText(dimensionString);

	if (dimensionString.empty())
	{
		dimensionString = L"(<>)";
	}
	else
	{
		dimensionString = L"(" + dimensionString + L")";
	}
	acutPrintf(L"设置内容：%s\n", dimensionString.kACharPtr());
	dim->setDimensionText(dimensionString.kACharPtr());
	return Types::CallbackReturnStatus::SUCCESS;
}

Types::CallbackReturnStatus Symbol::cbRemoveParaenthess(AcDbEntity* ent)
{
	AcDbDimension* dim = Common::entityToDimension(ent);
	if (!dim)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	AcString dimensionString;
	dim->dimensionText(dimensionString);

	if (!dimensionString.empty() &&
		dimensionString[0] == L'(' &&
		dimensionString[dimensionString.length() - 1] == L')')
	{
		dimensionString = dimensionString.mid(1, dimensionString.length() - 2);
		dim->setDimensionText(dimensionString);
	}
	return Types::CallbackReturnStatus::SUCCESS;
}

AcString Symbol::customSymbolPosition = "";
AcString Symbol::customSymbolString = "";

bool Symbol::customSymbolUserInput()
{
	if (Symbol::customSymbolPosition.length() == 0)
	{
		acedGetString(Adesk::kTrue, L"在首（B）或尾（E）？B", Symbol::customSymbolPosition);
		Symbol::customSymbolPosition.makeUpper();
		if (Symbol::customSymbolPosition.length() == 0 || Symbol::customSymbolPosition != L"E")
		{
			Symbol::customSymbolPosition = L"B";
		}

		acutPrintf(L"常用内置符号：%%%%C Φ；%%%%D °；%%%%P ±\n注：在多行文本中输入会转换成符号本身，直径符号会显示为空集符号\n");
		acedGetString(Adesk::kTrue, L"输入自定义符号：", Symbol::customSymbolString);
		if (Symbol::customSymbolString.length() == 0)
		{
			acutPrintf(L"未输入自定义符号，取消命令。");
			return false;
		}
	}
	acutPrintf(L"位置：%s，插入符号：%s\n", Symbol::customSymbolPosition.kACharPtr(), Symbol::customSymbolString.kACharPtr());
	return true;
}

Types::CallbackReturnStatus Symbol::cbAddCustomSymbolDimension(AcDbEntity* ent)
{
	if (!Symbol::customSymbolUserInput())
	{
		return Types::CallbackReturnStatus::CANCELED;
	}

	AcDbDimension* dim = Common::entityToDimension(ent);
	if (!dim)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	AcString dimensionString;
	dim->dimensionText(dimensionString);

	// 纯尺寸标注的标注字符串为空，需要插入占位符
	if (dimensionString.length() == 0)
	{
		dimensionString = dimensionPlaceHolder;
	}

	if (Symbol::customSymbolPosition == L"B")
	{
		dimensionString = Symbol::customSymbolString + dimensionString;
	}
	else
	{
		dimensionString += Symbol::customSymbolString;
	}

	dim->setDimensionText(dimensionString);

	return Types::CallbackReturnStatus::SUCCESS;
}

Types::CallbackReturnStatus Symbol::cbAddCustomSymbolMText(AcDbEntity* ent)
{
	if (!Symbol::customSymbolUserInput())
	{
		return Types::CallbackReturnStatus::CANCELED;
	}

	AcDbMText* mt = Common::entityToMText(ent);
	if (!mt)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	AcString mtextString = mt->text();

	if (Symbol::customSymbolPosition == L"B")
	{
		mtextString = Symbol::customSymbolString + mtextString;
	}
	else
	{
		mtextString += Symbol::customSymbolString;
	}

	mt->setContents(mtextString.kACharPtr());

	return Types::CallbackReturnStatus::SUCCESS;
}

bool Symbol::removeSymbolFromString(AcString& str)
{
	if (str.length() == 0)
	{
		acutPrintf(L"无文本内容，不需要移除符号\n");
		return false;
	}

	if (Symbol::customSymbolPosition == L"B")
	{
		if (str.substr(0, Symbol::customSymbolString.length()) == Symbol::customSymbolString)
		{
			acutPrintf(L"在首移除符号：%s\n", Symbol::customSymbolString.kACharPtr());
			str = str.mid(Symbol::customSymbolString.length());
		}
		else
		{
			acutPrintf(L"没有在首匹配到符号：%s\n", Symbol::customSymbolString.kACharPtr());
			return false;
		}
	}
	else
	{
		if (str.mid(str.length() - Symbol::customSymbolString.length()) == Symbol::customSymbolString)
		{
			acutPrintf(L"在尾移除符号：%s\n", Symbol::customSymbolString.kACharPtr());
			str = str.substr(0, str.length() - Symbol::customSymbolString.length());
		}
		else
		{
			acutPrintf(L"没有在尾匹配到符号：%s\n", Symbol::customSymbolString.kACharPtr());
			return false;
		}
	}
	return true;
}

Types::CallbackReturnStatus Symbol::cbRemoveCustomSymbolDimension(AcDbEntity* ent)
{
	if (!Symbol::customSymbolUserInput())
	{
		return Types::CallbackReturnStatus::CANCELED;
	}

	AcDbDimension* dim = Common::entityToDimension(ent);
	if (!dim)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	AcString dimensionString;
	dim->dimensionText(dimensionString);

	if (!Symbol::removeSymbolFromString(dimensionString))
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	dim->setDimensionText(dimensionString);

	return Types::CallbackReturnStatus::SUCCESS;
}

Types::CallbackReturnStatus Symbol::cbRemoveCustomSymbolMText(AcDbEntity* ent)
{
	if (!Symbol::customSymbolUserInput())
	{
		return Types::CallbackReturnStatus::CANCELED;
	}

	AcDbMText* mt = Common::entityToMText(ent);
	if (!mt)
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	AcString mtextString = mt->text();

	if (!Symbol::removeSymbolFromString(mtextString))
	{
		return Types::CallbackReturnStatus::CONTINUE;
	}

	mt->setContents(mtextString.kACharPtr());

	return Types::CallbackReturnStatus::SUCCESS;
}

void Symbol::customSymbolClear()
{
	Symbol::customSymbolPosition = "";
	Symbol::customSymbolString = "";
}
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
	acutPrintf(L"�������ݣ�%s\n", dimensionString.kACharPtr());
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
		acedGetString(Adesk::kTrue, L"���ף�B����β��E����B", Symbol::customSymbolPosition);
		Symbol::customSymbolPosition.makeUpper();
		if (Symbol::customSymbolPosition.length() == 0 || Symbol::customSymbolPosition != L"E")
		{
			Symbol::customSymbolPosition = L"B";
		}

		acutPrintf(L"�������÷��ţ�%%%%C ����%%%%D �㣻%%%%P ��\nע���ڶ����ı��������ת���ɷ��ű���ֱ�����Ż���ʾΪ�ռ�����\n");
		acedGetString(Adesk::kTrue, L"�����Զ�����ţ�", Symbol::customSymbolString);
		if (Symbol::customSymbolString.length() == 0)
		{
			acutPrintf(L"δ�����Զ�����ţ�ȡ�����");
			return false;
		}
	}
	acutPrintf(L"λ�ã�%s��������ţ�%s\n", Symbol::customSymbolPosition.kACharPtr(), Symbol::customSymbolString.kACharPtr());
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

	// ���ߴ��ע�ı�ע�ַ���Ϊ�գ���Ҫ����ռλ��
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
		acutPrintf(L"���ı����ݣ�����Ҫ�Ƴ�����\n");
		return false;
	}

	if (Symbol::customSymbolPosition == L"B")
	{
		if (str.substr(0, Symbol::customSymbolString.length()) == Symbol::customSymbolString)
		{
			acutPrintf(L"�����Ƴ����ţ�%s\n", Symbol::customSymbolString.kACharPtr());
			str = str.mid(Symbol::customSymbolString.length());
		}
		else
		{
			acutPrintf(L"û������ƥ�䵽���ţ�%s\n", Symbol::customSymbolString.kACharPtr());
			return false;
		}
	}
	else
	{
		if (str.mid(str.length() - Symbol::customSymbolString.length()) == Symbol::customSymbolString)
		{
			acutPrintf(L"��β�Ƴ����ţ�%s\n", Symbol::customSymbolString.kACharPtr());
			str = str.substr(0, str.length() - Symbol::customSymbolString.length());
		}
		else
		{
			acutPrintf(L"û����βƥ�䵽���ţ�%s\n", Symbol::customSymbolString.kACharPtr());
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
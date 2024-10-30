#include "StdAfx.h"
#include "Select.hpp"
#include "Types.hpp"
#include "Symbol.hpp"


void Select::selectSetForeach(const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction>& classFunctionPairs)
{
	ads_name ss;
	if (acedSSGet(nullptr, nullptr, nullptr, nullptr, ss) != RTNORM)
	{
		acutPrintf(L"%s：获取选择集失败！\n", __FUNCTION__);
		return;
	}

	Adesk::Int32 len = 0;
	if (acedSSLength(ss, &len) != RTNORM)
	{
		acutPrintf(L"%s：获取选择集长度失败！\n", __FUNCTION__);
		return;
	}

	for (Adesk::Int32 i = 0; i < len; ++i)
	{
		ads_name name;
		if (acedSSName(ss, i, name) != RTNORM)
		{
			acutPrintf(L"%s：获取选择集对象失败！\n", __FUNCTION__);
			return;
		}

		AcDbObjectId id;
		if (acdbGetObjectId(id, name) != Acad::eOk)
		{
			acutPrintf(L"%s：获取选择集对象ID失败！\n", __FUNCTION__);
			return;
		}

		AcDbEntity* pEntity = nullptr;
		if (acdbOpenObject(pEntity, id, AcDb::kForWrite) != Acad::eOk)
		{
			continue;
		}

		for (std::pair<AcRxClass*, Types::EntityOperatorCallbackFunction> pair : classFunctionPairs)
		{
			if (pEntity->isKindOf(pair.first))
			{
				switch (pair.second(pEntity))
				{
					case Types::CallbackReturnStatus::SUCCESS:
					{
						goto END_FOR1;
					}
					case Types::CallbackReturnStatus::CONTINUE:
					{
						goto END_FOR1;
					}
					case Types::CallbackReturnStatus::CANCELED:
					{
						acutPrintf(L"%s: 回调函数内取消命令\n", __FUNCTION__);
						goto END_FOR2;
					}
				}
			}
		}
		END_FOR1:
		pEntity->close();
		acedSSFree(name);
	}
	END_FOR2:
	acedSSFree(ss);
}

void Select::selectExecute(const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction>& classFunctionPairs)
{
	ads_name ent;
	ads_point pt;
	AcDbObjectId objId;
	AcDbEntity* pEntity = nullptr;

	while (true)
	{
		if (acedEntSel(L"选择一个对象：\n", ent, pt) != RTNORM)
		{
			acutPrintf(L"取消命令\n");
			break;
		}

		if (acdbGetObjectId(objId, ent) != Acad::eOk)
		{
			acutPrintf(L"%s: 获取对象ID失败\n", __FUNCTION__);
			continue;
		}

		if (acdbOpenObject(pEntity, objId, AcDb::kForWrite) != Acad::eOk)
		{
			acutPrintf(L"%s: 打开对象失败\n", __FUNCTION__);
			continue;
		}

		for (std::pair<AcRxClass*, Types::EntityOperatorCallbackFunction> pair : classFunctionPairs)
		{
			if (pEntity->isKindOf(pair.first))
			{
				switch (pair.second(pEntity))
				{
					case Types::CallbackReturnStatus::SUCCESS:
					{
						goto END_FOR3;
					}
					case Types::CallbackReturnStatus::CONTINUE:
					{
						goto END_FOR3;
					}
					case Types::CallbackReturnStatus::CANCELED:
					{
						acutPrintf(L"%s: 回调函数内取消命令\n", __FUNCTION__);
						goto END_FOR4;
					}
				}
			}
		}
		END_FOR3:
		pEntity->close();
		acedSSFree(ent);
	}
	Symbol::customSymbolClear();
	return;
	END_FOR4:
	Symbol::customSymbolClear();
	pEntity->close();
	acedSSFree(ent);
}
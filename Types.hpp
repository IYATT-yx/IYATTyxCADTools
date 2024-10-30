/**
 * @file Types.hpp
 * @breaf 类型定义
 */
#pragma once
#include "StdAfx.h"

class Types
{
public:
	enum CallbackReturnStatus // 回调函数返回状态
	{
		SUCCESS, // 正常结束
		CONTINUE, // 跳过本次执行
		CANCELED // 取消执行
	};

	typedef Types::CallbackReturnStatus (*EntityOperatorCallbackFunction)(AcDbEntity*); // 操作实体的回调函数
};
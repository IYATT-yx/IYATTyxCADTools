/**
 * @file DimensionLock.hpp
 * @brief 标注固化
 */
#pragma once
#include "Types.hpp"

class DimensionLock
{
public:
	/**
	 * @brief 固化标注内容
	 * @param ent 要固化的标注对象
	 */
	static Types::CallbackReturnStatus cbLock(AcDbEntity* ent);

	/**
	 * @brief 重置标注内容
	 * @param ent 要重置的标注对象
	 */
	static Types::CallbackReturnStatus cbReset(AcDbEntity* ent);
};
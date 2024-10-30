/**
 * @file Select.hpp
 * @brief 选择类，用于选择对象
 */
#pragma once
#include "Types.hpp"
#include <map>

class Select
{
public:
	/**
	 * @brief 遍历选中的对象，对指定对象类型执行指定操作
	 * @param 
	 */
	static void selectSetForeach(const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction>& classFunctionPairs);

	/**
	 * @brief 选择执行，点击一个对象执行一次
	 * @param 
	 */
	static void selectExecute(const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction>& classFunctionPairs);
};
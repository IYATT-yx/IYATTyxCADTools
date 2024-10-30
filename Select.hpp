/**
 * @file Select.hpp
 * @brief ѡ���࣬����ѡ�����
 */
#pragma once
#include "Types.hpp"
#include <map>

class Select
{
public:
	/**
	 * @brief ����ѡ�еĶ��󣬶�ָ����������ִ��ָ������
	 * @param 
	 */
	static void selectSetForeach(const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction>& classFunctionPairs);

	/**
	 * @brief ѡ��ִ�У����һ������ִ��һ��
	 * @param 
	 */
	static void selectExecute(const std::map<AcRxClass*, Types::EntityOperatorCallbackFunction>& classFunctionPairs);
};
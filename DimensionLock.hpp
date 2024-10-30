/**
 * @file DimensionLock.hpp
 * @brief ��ע�̻�
 */
#pragma once
#include "Types.hpp"

class DimensionLock
{
public:
	/**
	 * @brief �̻���ע����
	 * @param ent Ҫ�̻��ı�ע����
	 */
	static Types::CallbackReturnStatus cbLock(AcDbEntity* ent);

	/**
	 * @brief ���ñ�ע����
	 * @param ent Ҫ���õı�ע����
	 */
	static Types::CallbackReturnStatus cbReset(AcDbEntity* ent);
};
/**
 * @file Types.hpp
 * @breaf ���Ͷ���
 */
#pragma once
#include "StdAfx.h"

class Types
{
public:
	enum CallbackReturnStatus // �ص���������״̬
	{
		SUCCESS, // ��������
		CONTINUE, // ��������ִ��
		CANCELED // ȡ��ִ��
	};

	typedef Types::CallbackReturnStatus (*EntityOperatorCallbackFunction)(AcDbEntity*); // ����ʵ��Ļص�����
};
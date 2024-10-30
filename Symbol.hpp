/**
 * @file Symbol.hpp
 * @brief ���Ź���
 */
#pragma once
#include "Types.hpp"

class Symbol
{
private:
	static AcString customSymbolPosition;
	static AcString customSymbolString;

private:
	/**
	 * @brief ��ȡ�û�������Զ������Ҫ��
	 * @return true �ɹ���false ʧ��
	 */
	static bool customSymbolUserInput();

	/**
	 * @brief �Ƴ��ַ����еķ���
	 * @param str ��Ҫ������ַ�������
	 * @return true ִ���˲�����û��ִ�в���
	 */
	static bool removeSymbolFromString(AcString& str);

public:
	/**
	 * @brief Ϊ��ע���С����
	 * @param ent Ҫ���С���ŵı�ע����
	 * @return ״̬����: SUCCESS �ɹ�ִ�У�CONTINUE �ڲ�����ִ�У�ָʾ���ֻص�������CANCELED ȡ������
	 */
	static Types::CallbackReturnStatus cbAddParentheses(AcDbEntity* ent);

	/**
	 * @brief �Ƴ���ע��С����
	 * @param ent Ҫ�Ƴ�С���ŵı�ע
	 * @return ״̬����: SUCCESS �ɹ�ִ�У�CONTINUE �ڲ�����ִ�У�ָʾ���ֻص�������CANCELED ȡ������
	 */
	static Types::CallbackReturnStatus cbRemoveParaenthess(AcDbEntity* ent);

	/**
	 * @brief �ڱ�ע���׻�β����Զ������
	 * @param ent Ҫ��ӷ��ŵı�ע����
	 * @return ״̬����: SUCCESS �ɹ�ִ�У�CONTINUE �ڲ�����ִ�У�ָʾ���ֻص�������CANCELED ȡ������
	 */
	static Types::CallbackReturnStatus cbAddCustomSymbolDimension(AcDbEntity* ent);

	/**
	 * @brief �ڶ����ı����׻�β����Զ������
	 * @param ent Ҫ��ӷ��ŵĶ����ı�����
	 * @return ״̬����: SUCCESS �ɹ�ִ�У�CONTINUE �ڲ�����ִ�У�ָʾ���ֻص�������CANCELED ȡ������
	 */
	static Types::CallbackReturnStatus cbAddCustomSymbolMText(AcDbEntity* ent);

	/**
	 * @brief �ڱ�ע���׻�β�Ƴ��Զ������
	 * @param ent Ҫ�Ƴ����ŵı�ע����
	 * @return ״̬����: SUCCESS �ɹ�ִ�У�CONTINUE �ڲ�����ִ�У�ָʾ���ֻص�������CANCELED ȡ������
	 */
	static Types::CallbackReturnStatus cbRemoveCustomSymbolDimension(AcDbEntity* ent);


	/**
	 * @brief �ڶ����ı����׻�β�Ƴ��Զ������
	 * @param ent Ҫ�Ƴ����ŵĶ����ı�����
	 * @return ״̬����: SUCCESS �ɹ�ִ�У�CONTINUE �ڲ�����ִ�У�ָʾ���ֻص�������CANCELED ȡ������
	 */
	static Types::CallbackReturnStatus cbRemoveCustomSymbolMText(AcDbEntity* ent);

	/**
	 * @brief ����û�������Զ������Ҫ��
	 */
	static void customSymbolClear();
};
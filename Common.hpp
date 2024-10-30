/**
 * @file Common.hpp
 * @brief ������
 */
#pragma once


constexpr double PI = 3.14159265358979323846;
constexpr ACHAR* dimensionPlaceHolder = L"<>"; // �ߴ��ע�����е�ռλ��
constexpr size_t dimensionPlaceHolderLength = 2; // ռλ������

class Common
{
public:
	/**
	 * @brief ��������תΪָ�����ȵ�С���ַ���������ǻ���ֵ��תΪ�Ƕ�ֵ
	 * @param inDouble ����ĸ�����
	 * @param outString �����С���ַ���
	 * @param precision Ҫ��ľ���
	 * @param isRadianValue �Ƿ�Ϊ������
	 */
	static void doubnleToStringWithPrecision(double inDouble, AcString& outString, const int& precision, bool isRadianValue = false);

	/**
	 * @brief ����ע������ַ�����ֵ
	 * @param dimensionString �ӱ�ע�����ȡ���ַ���
	 * @param valueString �������ֵ
	 * @return true �����˲�ֵ������false δ�ҵ�ռλ����δ���в�ֵ����
	 */
	static bool dimensionStringInsertValue(AcString& dimensionString, AcString& measureValueString);

	/**
	 * @brief ʵ��ת��ע����
	 * @param entity ʵ�����
	 * @return ��ע���󣬷Ǳ�ע���󷵻� nullptr
	 */
	static AcDbDimension* entityToDimension(AcDbEntity* entity);

	/**
	 * @brief ʵ��ת�����ı�����
	 * @param entity ʵ�����
	 * @return �����ı����󣬷Ƕ����ı����󷵻� nullptr
	 */
	static AcDbMText* entityToMText(AcDbEntity* entity);
};
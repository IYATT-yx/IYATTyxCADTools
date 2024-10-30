/**
 * @file Common.hpp
 * @brief 公共类
 */
#pragma once


constexpr double PI = 3.14159265358979323846;
constexpr ACHAR* dimensionPlaceHolder = L"<>"; // 尺寸标注对象中的占位符
constexpr size_t dimensionPlaceHolderLength = 2; // 占位符长度

class Common
{
public:
	/**
	 * @brief 将浮点数转为指定精度的小数字符串，如果是弧度值则转为角度值
	 * @param inDouble 输入的浮点数
	 * @param outString 输出的小数字符串
	 * @param precision 要求的精度
	 * @param isRadianValue 是否为弧度制
	 */
	static void doubnleToStringWithPrecision(double inDouble, AcString& outString, const int& precision, bool isRadianValue = false);

	/**
	 * @brief 给标注对象的字符串插值
	 * @param dimensionString 从标注对象获取的字符串
	 * @param valueString 待插入的值
	 * @return true 进行了插值操作；false 未找到占位符，未进行插值操作
	 */
	static bool dimensionStringInsertValue(AcString& dimensionString, AcString& measureValueString);

	/**
	 * @brief 实体转标注对象
	 * @param entity 实体对象
	 * @return 标注对象，非标注对象返回 nullptr
	 */
	static AcDbDimension* entityToDimension(AcDbEntity* entity);

	/**
	 * @brief 实体转多行文本对象
	 * @param entity 实体对象
	 * @return 多行文本对象，非多行文本对象返回 nullptr
	 */
	static AcDbMText* entityToMText(AcDbEntity* entity);
};
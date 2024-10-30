/**
 * @file Symbol.hpp
 * @brief 符号工具
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
	 * @brief 读取用户输入的自定义符号要求
	 * @return true 成功，false 失败
	 */
	static bool customSymbolUserInput();

	/**
	 * @brief 移除字符串中的符号
	 * @param str 需要处理的字符串对象
	 * @return true 执行了操作；没有执行操作
	 */
	static bool removeSymbolFromString(AcString& str);

public:
	/**
	 * @brief 为标注添加小括号
	 * @param ent 要添加小括号的标注对象
	 * @return 状态返回: SUCCESS 成功执行；CONTINUE 内部结束执行，指示本轮回调结束；CANCELED 取消命令
	 */
	static Types::CallbackReturnStatus cbAddParentheses(AcDbEntity* ent);

	/**
	 * @brief 移除标注的小括号
	 * @param ent 要移除小括号的标注
	 * @return 状态返回: SUCCESS 成功执行；CONTINUE 内部结束执行，指示本轮回调结束；CANCELED 取消命令
	 */
	static Types::CallbackReturnStatus cbRemoveParaenthess(AcDbEntity* ent);

	/**
	 * @brief 在标注的首或尾添加自定义符号
	 * @param ent 要添加符号的标注对象
	 * @return 状态返回: SUCCESS 成功执行；CONTINUE 内部结束执行，指示本轮回调结束；CANCELED 取消命令
	 */
	static Types::CallbackReturnStatus cbAddCustomSymbolDimension(AcDbEntity* ent);

	/**
	 * @brief 在多行文本的首或尾添加自定义符号
	 * @param ent 要添加符号的多行文本对象
	 * @return 状态返回: SUCCESS 成功执行；CONTINUE 内部结束执行，指示本轮回调结束；CANCELED 取消命令
	 */
	static Types::CallbackReturnStatus cbAddCustomSymbolMText(AcDbEntity* ent);

	/**
	 * @brief 在标注的首或尾移除自定义符号
	 * @param ent 要移除符号的标注对象
	 * @return 状态返回: SUCCESS 成功执行；CONTINUE 内部结束执行，指示本轮回调结束；CANCELED 取消命令
	 */
	static Types::CallbackReturnStatus cbRemoveCustomSymbolDimension(AcDbEntity* ent);


	/**
	 * @brief 在多行文本的首或尾移除自定义符号
	 * @param ent 要移除符号的多行文本对象
	 * @return 状态返回: SUCCESS 成功执行；CONTINUE 内部结束执行，指示本轮回调结束；CANCELED 取消命令
	 */
	static Types::CallbackReturnStatus cbRemoveCustomSymbolMText(AcDbEntity* ent);

	/**
	 * @brief 清空用户输入的自定义符号要求
	 */
	static void customSymbolClear();
};
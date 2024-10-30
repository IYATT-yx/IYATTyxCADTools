# IYATT-yx 的 CAD 工具

## 测试环境

* Visual Studio 2022
* ObjectARX 2025
* AutoCAD Mechanical 2025

## 使用

在 CAD 处于图纸编辑状态时，执行 APPLOAD 命令，然后选择扩展程序文件 IYATTyxIYATTyxCADTools.arx，完成加载。

## 功能命令

* LD - lock dimension 固化标注，将标注内容设定为常量值，不再跟随实体尺寸变化
* RD - reset dimension 重置标注，删除标注的文本内容，标注显示内容跟随实体尺寸变化，但会丢失标注中自定义添加的符号、极限偏差等内容
---
* SRD - set reference dimension 设置参考标注，会给标注添加小括号
* CRD - cancel reference dimension 取消参考标注，删除标注中最外围的小括号
---
* ACS - add custom symbol 添加自定义符号，可以在多行文本或标注的首或尾添加自定义的字符串，可点选连续添加
* RCS - remove custom symbol 移除自定义符号，可以在多行文本或标注的首或尾删除自定义符号，可点选连续删除
---
* IYATTyxCADToolsInfo 显示软件信息
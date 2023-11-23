# cloudgamefix

#### 介绍
一个用于网易云游戏云电脑的库，基于C++开发提供了Windows Notification调用，日志系统，事件系统，Windows部分原生API封装
同时提供了ini文件解析器的实现

#### 引用的第三方库
rapidjson: 用于解析json数据
libcurl: 用于获取文件和json数据
boost-stacktrace: 用于实现诊断，检查程序调用栈

#### 关于cloudgamefix的开发
此库是我个人开发的，全部由我自己测试，这个库的开发非常消耗精力，尤其是cloudgamefix.hpp这个文件
这个库是在7月中旬启动的项目

关于这个项目，它的前身是
https://gitee.com/eGlhb2p1emk/test
这个仓库

虽然没有源代码，但是我保证那个的代码是最混乱的，因为在那个版本测试了许多特性，接口很混乱
而我在整理WinToast代码的时候有注意到WRL的命名空间
WRL我觉得很整洁，很多接口都用命名空间存储起来

因此，一个分支诞生了

在这个库中，有一部分实现其实就是上个版本的
比如loadFunFromLib函数

并且在这个新版本中，有WinToast的重写，SetWindowsHookEx的封装，Windows部分API的封装，以及关于抽象工厂模式的实现，还有ini解析器和事件总线的实现

它不仅是一个里程碑，也是一个句号
这个库只会进行短期维护，随后停止更新
因为网易云游戏即将跑路了！

#### 安装

你需要Visual Studio 2022来编译这个项目，并且标准必须是C++20
并且需要安装引用的第三方库
当然，Visual Studio 2019或许也行，只要标准是C++20就行
仅支持MSVC编译器编译，Clion或DevC++使用的gnu编译器提供的库因为不支持WRL，因此无法使用

#### 关于许可证

如果你想使用也没关系，我的许可证是MIT许可证，你只需要留个许可证声明就行了


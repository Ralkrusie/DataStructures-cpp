#pragma once
// 在 main() 之前自动将 Windows 控制台输出代码页设为 UTF-8，
// 与 /utf-8 编译选项保持一致，一劳永逸解决 cout 中文乱码。
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
namespace {
struct _ConsoleUtf8Init {
    _ConsoleUtf8Init() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    }
};
inline _ConsoleUtf8Init _consoleUtf8InitInstance;
}
#endif

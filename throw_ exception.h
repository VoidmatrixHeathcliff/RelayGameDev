#ifndef _THROW_EXCEPTION_H_
#define _THROW_EXCEPTION_H_

#include <windows.h>

//抛出错误的窗口

//第一个参数用于判断对错
//第二个参数用于写错误的原因

inline void Throw_Exception_Window(bool flag,const wchar_t* error)
{
    if (flag)return;

    int result = MessageBox(NULL,error,L"报错位置",MB_OK | MB_ICONINFORMATION);
    
    if (result == IDOK)exit(-1);
}

#endif // !_THROW_EXCEPTION_H_

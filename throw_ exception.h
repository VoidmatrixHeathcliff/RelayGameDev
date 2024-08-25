#ifndef _THROW_EXCEPTION_H_
#define _THROW_EXCEPTION_H_

#include <windows.h>

//�׳�����Ĵ���

//��һ�����������ж϶Դ�
//�ڶ�����������д�����ԭ��

inline void Throw_Exception_Window(bool flag,const wchar_t* error)
{
    if (flag)return;

    int result = MessageBox(NULL,error,L"����λ��",MB_OK | MB_ICONINFORMATION);
    
    if (result == IDOK)exit(-1);
}

#endif // !_THROW_EXCEPTION_H_

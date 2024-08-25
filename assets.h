#ifndef _ASSETS_H_
#define _ASSETS_H_

#include"easyx.h"//easyx��
#include <iostream>
#include <string>
#include"throw_ exception.h"

//��������ͼ���࣬�ṩ������ͼƬ��Դ���ع���
//�Լ���ȡ���Ϳ�
//��Ҫ�µķ������Բ���

class PAssets
{
public:

	PAssets(std::wstring wstr)
	{
		img = new IMAGE();
		loadimage(img,wstr.c_str(), 0, 0);
	}

	PAssets(std::wstring wstr,const wchar_t* error)//�ṩһ���жϴ���ķ���
	{
		img = new IMAGE();
		loadimage(img, wstr.c_str(), 0, 0);

		bool check_img = ((img->getheight() == 0) && (img->getwidth() == 0));//����ʧ�ܵ�����

		Throw_Exception_Window(!check_img, error);
	}

	~PAssets()
	{
		delete img;
	}

	int GetImgW()
	{
		return img->getwidth();
	}

	int GetImgH()
	{
		return img->getheight();
	}

	IMAGE* GetImg()
	{
		return img;
	}

private:
	IMAGE* img = nullptr;
};

#endif // !_ASSETS_H_
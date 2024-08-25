#ifndef _NEW_ANIMATION_H_
#define _NEW_ANIMATION_H_

#include"timer.h"
#include"assets.h"
#include<vector>
#include<iostream>
//����������ṩ���¶�����
//������µĶ������в�û���ṩ�и��ͼƬ����
//�����µĶ�����

class PNAnimation
{
public:
	PNAnimation() = default;

	~PNAnimation() = default;

	void load_img_from_file(std::wstring img,const wchar_t* error = nullptr)//���뵥��ͼƬ
	{
		PAssets* img_temp = new PAssets(img,error);
		assets_list.push_back(img_temp);
	}

	//���������������ص��ͼƬ
	//���磺player_0.png��player_1.png
	//����˵������һ����ͼƬ�������ڶ�����ͼƬ��ͬӵ�е��ַ������������ļ���׺��
	void load_img_from_file(int n ,std::wstring img,std::wstring suffix, const wchar_t* error = nullptr)
	{
		std::wstring cur = img;
		std::wstring cur_suffix = suffix;
		wchar_t buffer[256];
		for (int i = 0; i < n; i++)
		{
			swprintf_s(buffer, 256, L"%ls%d%ls", cur.c_str(), i, cur_suffix.c_str());
			PAssets temp(buffer);
			assets_list.push_back(&temp);
		}
		assets_nums = assets_list.size();
	}

	void on_update(double val)//ʵʱ����
	{
		//Throw_Exception_Window(assets_nums <= 1, L"����Ϊһ֡");

		timer.on_update(val);
		bool frame_index_check = timer.get_is_shotted();
		
		if (frame_index_check)
		{
			frame_idx++;
			frame_idx %= assets_nums;
		}
	}

	void on_draw()//��Ⱦ
	{
		putimage(v2.x, v2.y, assets_list[frame_idx]->GetImg());
	}

	void set_point(int x,int y)//��������
	{
		v2.x = x;
		v2.y = y;
	}

	void set_assets_nums(int val)//����ͼ����
	{
		assets_nums = val;
	}

private:
	std::vector<PAssets*>assets_list;//ͼ����
	Timer timer;//��ʱ��
	POINT v2 = { 0,0 };//����

	int frame_idx = 0;//ͼ������
	int assets_nums = 0;//ͼ������������õĶ�ͼƬ������ôͼ�����͵���ͼ����Ĵ�С
	
};

#endif // !_NEW_ANIMATION_H_

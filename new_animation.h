#ifndef _NEW_ANIMATION_H_
#define _NEW_ANIMATION_H_

#include"timer.h"
#include"assets.h"
#include<vector>
#include<iostream>
//？这个是我提供的新动画类
//在这个新的动画类中并没有提供切割单个图片功能
//这是新的动画类

class PNAnimation
{
public:
	PNAnimation() = default;

	~PNAnimation() = default;

	void load_img_from_file(std::wstring img,const wchar_t* error = nullptr)//插入单个图片
	{
		PAssets* img_temp = new PAssets(img,error);
		assets_list.push_back(img_temp);
	}

	//插入多个具有相似特点的图片
	//例如：player_0.png、player_1.png
	//参数说明：第一个是图片个数，第二个是图片共同拥有的字符，第三个是文件后缀名
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

	void on_update(double val)//实时更新
	{
		//Throw_Exception_Window(assets_nums <= 1, L"动画为一帧");

		timer.on_update(val);
		bool frame_index_check = timer.get_is_shotted();
		
		if (frame_index_check)
		{
			frame_idx++;
			frame_idx %= assets_nums;
		}
	}

	void on_draw()//渲染
	{
		putimage(v2.x, v2.y, assets_list[frame_idx]->GetImg());
	}

	void set_point(int x,int y)//设置坐标
	{
		v2.x = x;
		v2.y = y;
	}

	void set_assets_nums(int val)//设置图集数
	{
		assets_nums = val;
	}

private:
	std::vector<PAssets*>assets_list;//图集表
	Timer timer;//计时器
	POINT v2 = { 0,0 };//坐标

	int frame_idx = 0;//图集索引
	int assets_nums = 0;//图集数，如果是用的多图片加载那么图集数就等于图集表的大小
	
};

#endif // !_NEW_ANIMATION_H_

#pragma once
#include<vector>
#include <graphics.h>
class Statusbar
{
public:
	Statusbar() = default;

	~Statusbar() = default;

	void set_acatar(IMAGE* img) {
		img_avatar.push_back(img);
	}
	void on_draw() {

	}
private:
	std::vector<int> IdFrame;//��Ʒ����

	std::vector<IMAGE*> img_avatar;//�������Ʒ�ķ��õ������ͼƬָ��
};


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
	std::vector<int> IdFrame;//物品栏？

	std::vector<IMAGE*> img_avatar;//这个是物品的放置的所需的图片指针
};


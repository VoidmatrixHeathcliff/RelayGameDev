#pragma once
#include"content.h"
#include<vector>
class Inventory
{
public:
	Inventory()
	{
		contents.resize(row * column);
	}
	~Inventory() = default;
	void On_Message(const ExMessage& msg)
	{
		int single_length = 40;
		int up = (480 - (single_length * 9)) / 2;
		int left = (640 - (single_length * 9)) / 2;
		int x = msg.x;
		int y = msg.y;
		int pos = (y - up) / single_length * column + (x - left) / single_length;
		switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (pos < 0 && pos >= row * column)
				{
					current_choice = -1;
					break;
				}
				if (contents[pos] && current_choice<0)
					current_choice = pos;
				else if (contents[pos] && current_choice >= 0)
				{
					std::swap(contents[pos], contents[current_choice]);
					current_choice = -1;
				}
				break;
			case WM_RBUTTONDOWN:
				current_choice = -1;
				break;
		case WM_MOUSEMOVE:
			mouse_pos.x = msg.x;
			mouse_pos.y = msg.y;
			break;
		}
	}
	bool Erase(PContent* thing)
	{
		for (auto& e : contents)
		{
			if (e == thing)
			{
				delete e;
				e = nullptr;
				return true;
			}
		}
		return false;
	}
	bool Erase(int pos)
	{
		if (pos >= contents.size())
			return false;
		delete contents[pos];
		contents[pos] = nullptr;
		return true;
	}
	void On_Draw()
	{
		setfillcolor(RGB(255, 255, 204));
		setlinecolor(RGB(0, 0, 0));
		double single_length = 40;
		double up = (480 - (single_length * 9)) / 2;
		double left= (640 - (single_length * 9)) / 2;
		for(int i=0;i<row;i++)
		{
			for (int j = 0; j < column; j++)
			{
				int y = up + i * single_length;
				int x = left + j * single_length;
				fillrectangle(x, y, x + single_length, y + single_length);
				if (i * 9 + j == current_choice)
				{
					continue;
				}
				if(contents[i * 9 + j])
				{
					contents[i * 9 + j]->On_Show(x, y);
					outtextxy(x+10, y+10, contents[i * 9 + j]->Get_Num());
				}
			}

		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				int y = up + i * single_length;
				int x = left + j * single_length;
				if (i * 9 + j == current_choice)
				{
					x = mouse_pos.x;
					y = mouse_pos.y;
					settextcolor(RGB(0, 0, 0));
					contents[i * 9 + j]->On_Show(x, y);
					outtextxy(x + 10, y + 10, contents[i * 9 + j]->Get_Num()+'0');
					TCHAR tex[100] = { 0 };
					std::string buffer = contents[i * 9 + j]->Get_Name();
					for (int i = 0; i < buffer.size(); i++)
					{
						tex[i] = buffer[i];
					}
					outtextxy(x - 20, y - 20,tex);
					break;
				}
			}

		}
	}
protected:
	//contents in beg
	std::vector<PContent*>contents;
	int row=9;
	int column=9;
	bool is_show = false;
	int current_choice = -1;
	POINT mouse_pos = { 0 };
};
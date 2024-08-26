#pragma once
#include"content.h"
#include<vector>
#include"Hand.h"
class Beg
{
public:
	Beg()
	{
		contents.resize(row * column+inventory_size);
		//inventory.resize(inventory_size);
	}
	~Beg() = default;
	bool Can_Add()
	{
		for (auto& e : contents)
			if (e == nullptr)
			{
				return true;
			}
		return false;
	}
	bool Add(PContent* thing)
	{
		for(auto&e:contents)
			if (e == nullptr)
			{
				e = thing;
				return true;
			}
		return false;
	}
	void On_Message(const ExMessage& msg)
	{
		int single_length = 40;
		int up = (480 - (single_length * 9)) / 2;
		int left = (640 - (single_length * 9)) / 2;
		int x = msg.x;
		int y = msg.y;
		int pos = (y - up) / single_length * column + (x - left) / single_length;
		switch (msg.message) {
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
				case 0x30:
					on_hand = 9;
					break;
				case 0x31:
					on_hand = 0;
					break;
				case 0x32:
					on_hand = 1;
					break;
				case 0x33:
					on_hand = 2;
					break;
				case 0x34:
					on_hand = 3;
					break;
				case 0x35:
					on_hand = 4;
					break;
				case 0x36:
					on_hand = 5;
					break;
				case 0x37:
					on_hand = 6;
					break;
				case 0x38:
					on_hand = 7;
					break;
				case 0x39:
					on_hand = 8;
					break;
				case 66:
					Set_Show(!Is_Show());
					break;
			}
			break;
		case WM_LBUTTONDOWN:
			if (pos >= 0 && pos < row * column);
			else if (pos > 0 && (y >= 480 - single_length && x <= inventory_size * single_length))
			{
				pos = row * column + (x / single_length);
			}
			else
			{
				current_choice = -1;
				break;
			}
			if (contents[pos] && current_choice < 0)
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
	bool Is_Show()
	{
		return is_show;
	}
	bool Set_Show(bool flag)
	{
		is_show = flag;
		return flag;
	}
	void On_Draw()
	{
		setfillcolor(RGB(255, 255, 204));
		setlinecolor(RGB(0, 0, 0));
		double single_length = 35;
		double up = (480 - (single_length * 9)) / 2;
		double left= (640 - (single_length * 9)) / 2;

		for (int i = row*column; i < contents.size(); i++)
		{
			int x = (i - row * column) * single_length;
			int y =480 - single_length;
			if (i - row * column == on_hand)
			{
				setlinecolor(RGB(255, 102, 178));
			}
			fillrectangle(x, y, x + single_length, y + single_length);
			if (i-row*column == on_hand)
			{
				setlinecolor(RGB(0,0,0));
			}
			if (contents[i])
			{
				contents[i]->On_Show(x, y);
				outtextxy(x + 10, y + 10, contents[i]->Get_Num());
			}
		}
		if (is_show == false)
			return;
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
					TCHAR tex[256] = { 0 };
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
	PContent* Get_On_Hand()
	{
		if (contents[on_hand] == nullptr)
			return &Singleton<Hand>::instance();
		return contents[on_hand];
	}
protected:
	//contents in beg
	std::vector<PContent*>contents;
	//std::vector<PContent*>inventory;
	int row=9;
	int column=9;
	int inventory_size = 10;
	bool is_show = false;
	int current_choice = -1;
	int on_hand = 0;
	POINT mouse_pos = { 0 };
};

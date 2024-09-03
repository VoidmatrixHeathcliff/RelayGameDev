#pragma once
#include"../gui/GUIObject.h"
#include"../entity/Player.h"
//content in bag
class PContent :public PGUIObject
{
public:
	PContent() = default;
	~PContent() = default;
	//left click
	virtual bool On_Left_Click()
	{
		return false;
	}
	//right click
	virtual bool On_Right_Click()
	{
		return false;
	}
	//the image you show in bag
	virtual void On_Show(double x, double y)
	{

	}
	//if it is the current content on your hand,use it
	virtual void On_Hand()
	{

	}
	//draw the content you catch
	virtual void OnDraw()
	{

	}
	int Get_Num()
	{
		return num;
	}
	std::string Set_Name(std::string N)
	{
		name = N;
		return N;
	}
	std::string Get_Name()
	{
		return name;
	}
protected:
	//how many
	int num = 1;
	std::string name;
};
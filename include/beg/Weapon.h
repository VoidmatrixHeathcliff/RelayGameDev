#pragma once
#include"Content.h"
//content belongs to weapon
class PWeapon :public PContent
{
public:
	PWeapon() = default;
	~PWeapon() = default;
protected:
	int damage = 1;
	virtual void On_Attack()
	{

	}
};
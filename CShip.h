#pragma once
#include "CGameObject.h"

class CShip : public CGameObject
{
public:
	CShip(Point top_l = Point(340, 770), Point bot_r = Point(460, 800), int lives = 3);
	~CShip();
};


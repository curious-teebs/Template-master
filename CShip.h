#pragma once
#include "CGameObject.h"

class CShip : public CGameObject
{
public:
	CShip(Point top_l = Point(450, 30), Point bot_r = Point(550, 0), int lives = 3);
	~CShip();
};


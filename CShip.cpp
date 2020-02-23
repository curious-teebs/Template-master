#include "stdafx.h"
#include "CShip.h"


CShip::CShip(Point top_l, Point bot_r, int lives)
{
	set_lives(lives);
	_shape.SetRect(top_l.x, top_l.y, bot_r.x, bot_r.y);
}

CShip::~CShip()
{
}

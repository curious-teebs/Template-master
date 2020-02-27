#include "stdafx.h"
#include "CInvader.h"

CInvader::CInvader(Point top_l, Point bot_r, int lives)
{
	_shape.SetRect(top_l.x, top_l.y, bot_r.x, bot_r.y);
	_lives = lives;
	_velocity = Point(6, 10);
	_position = top_l;
}

CInvader::~CInvader()
{
}

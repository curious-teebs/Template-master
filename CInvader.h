#pragma once
#include "CGameObject.h"
class CInvader : public CGameObject
{
public:
	CInvader(Point top_l, Point bot_r, int lives = 1);
	~CInvader();
};


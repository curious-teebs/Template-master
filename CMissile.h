#pragma once
#include "CGameObject.h"
#include <atltypes.h>
class CMissile : public CGameObject
{
public:
	CMissile(int vel_dir, Point pos, int lives = 1);
	~CMissile();
};


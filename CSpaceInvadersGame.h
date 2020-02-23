#pragma once
#include "CBase4618.h"
#include "CInvader.h"
#include "CMissile.h"
#include "CShip.h"
#include <atltypes.h>
class CSpaceInvadersGame : public CBase4618
{
private:
	CShip _ship;
	std::vector<CMissile> _missile;
	std::vector<CInvader> _invaders;
	void update();
	void draw();
	void set_invaders();
	Size _dim = Size(400, 400);
public:
	CSpaceInvadersGame(Size dim = Size(800, 800), int port = 5);
	~CSpaceInvadersGame();
};


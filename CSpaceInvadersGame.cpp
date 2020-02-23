#include "stdafx.h"
#include "CSpaceInvadersGame.h"
#include "CInvader.h"
#include "CMissile.h"
#include "CShip.h"
#include <atltypes.h>

CSpaceInvadersGame::CSpaceInvadersGame(Size dim, int port)
{
	_canvas = Mat::zeros(Size(dim), CV_8UC3);
	sketch_contr.init_com(port);
	set_invaders();
	imshow("image", _canvas);
}

CSpaceInvadersGame::~CSpaceInvadersGame()
{
}

void CSpaceInvadersGame::update()
{
}

void CSpaceInvadersGame::draw()
{
	_canvas = Mat::zeros(_canvas.size(), CV_8UC3);
	for (int num_of_inv = (_invaders.size() - 1); num_of_inv >= 0; num_of_inv--)
		_invaders[num_of_inv].draw(_canvas);
	imshow("image", _canvas);
}

void CSpaceInvadersGame::set_invaders()
{
	int num_in_row = 9;
	Point top_l = Point(50, 20);
	Point bot_r = Point(110, 70);
	for (int num_of_inv = 45; num_of_inv > 0; num_of_inv--)
	{
		if (num_in_row <= 0)
		{
			top_l.y += 70;
			top_l.x = 50;
			bot_r.y += 70;
			bot_r.x = 110;
			num_in_row = 9;
		}
		_invaders.push_back(CInvader(top_l, bot_r));
		top_l.x += 80;
		bot_r.x += 80;
		num_in_row--;
	}
}

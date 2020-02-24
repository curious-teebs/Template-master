#pragma once
#include "CBase4618.h"
#include "CInvader.h"
#include "CMissile.h"
#include "CShip.h"
#include <atltypes.h>

class CSpaceInvadersGame : public CBase4618
{
private:
	int _dbl_bounce = 1;
	int _bounce = 4;
	Size _dim = Size(800, 800);
	int _score = 0;
	CShip _ship;
	std::vector<CMissile> _missile;
	std::vector<CInvader> _invaders;
	void update();
	void draw();
	void set_invaders();
	void check_butt(int butt);
	int _not_held = 0;
	//Size _dim = Size(400, 400);
	int _ship_pos = 340;
	int _ship_max_a = 300;
	int _ship_v;
	int _x_joy_per;
	int _done = 1;
	Point _ship_offset = Point(0, 25);
	double _butt_1_time = getTickCount();
	double _butt_2_time = getTickCount();
	//time variables for movemoent calculations
	double _last_time = getTickCount();///< Last time of paddle 1 position update
	double _current_time;///< Current time of paddle 1 update
	double _delta_time = 0.0333;///< Difference between current paddle 1 update and last paddle 1 update
	double _freq = getTickFrequency();
public:
	CSpaceInvadersGame(Size dim = Size(800, 800), int port = 5);
	~CSpaceInvadersGame();
};


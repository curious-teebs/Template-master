#pragma once
#include "CBase4618.h"
#include "CInvader.h"
#include "CMissile.h"
#include "CShip.h"
#include <atltypes.h>

class CSpaceInvadersGame : public CBase4618
{
private:
	//strings
	int _font_scale = 1;
	Scalar _white = Scalar(255, 255, 255);
	int _pos;
	Point _lives_pt = Point(100, 30);
	Point _score_pt = Point(600, 30);
	std::string _score_s = "Score: ";
	std::string _live_s = "Lives: ";
	std::string _space = " ";
	int chnc_missile;
	//timing for invader velocity increase
	double _now;
	double _last_wall_coll = getTickCount();
	//invader dimensions
	int dis_to_top = 50;
	int dis_to_wall = 60;
	int inv_width = 50;
	int inv_height = 50;
	int inbtwn_invs = 30;
	int _dbl_bounce = 1;
	int _bounce = 2;
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


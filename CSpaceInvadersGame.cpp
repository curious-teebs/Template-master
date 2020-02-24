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
	if (_done)
	{
		//checks for collision between player missile and invader
		for (int num_of_inv = (_invaders.size() - 1); num_of_inv >= 0; num_of_inv--)
		{
			for (int num_of_mis = (_missile.size() - 1); num_of_mis >= 0; num_of_mis--)
				_missile[num_of_mis].collide(_invaders[num_of_inv]);
		}
		//checks collision between missiles and ship and ends game if ship has 0 lives
		for (int num_of_mis = (_missile.size() - 1); num_of_mis >= 0; num_of_mis--)
			_missile[num_of_mis].collide(_ship);
		if (_ship.get_lives() <= 0)
		{
			_done = 0;
		}
		for (int num_of_mis = (_missile.size() - 1); num_of_mis >= 0; num_of_mis--)
			_missile[num_of_mis].collide_wall(_dim);
		//erases missiles and invaders with 0 lives
		for (int num_of_inv = (_invaders.size() - 1); num_of_inv >= 0; num_of_inv--)
		{
			if (_invaders[num_of_inv].get_lives() <= 0)
			{
				_invaders.erase(_invaders.begin() + num_of_inv);
				_score += 10;
			}
		}
		for (int num_of_mis = (_missile.size() - 1); num_of_mis >= 0; num_of_mis--)
		{
			if (_missile[num_of_mis].get_lives() <= 0)
			{
				_missile.erase(_missile.begin() + num_of_mis);
			}
		}
		//check invaders collision with wall and reverses velocity
		for (int num_of_inv = (_invaders.size() - 1); num_of_inv >= 0; num_of_inv--)
		{
			if (_invaders[num_of_inv].collide_wall(_dim) && _dbl_bounce)
			{
				for (int num_of_inv = (_invaders.size() - 1); num_of_inv >= 0; num_of_inv--)
				{
					Point cur_vel = _invaders[num_of_inv].get_vel();
					cur_vel.x = cur_vel.x * -1;
					_invaders[num_of_inv].set_vel(cur_vel);
				}
				_bounce--;
				_dbl_bounce = 0;
			}
		}
		_dbl_bounce = 1;
		if (_bounce == 0)
		{
			for (int num_of_mis = (_invaders.size() - 1); num_of_mis >= 0; num_of_mis--)
				_invaders[num_of_mis].move(invader_y, _invaders[num_of_mis].get_top_left().y);
			_bounce = 4;
		}
		//checks for button push and creates player missile
		check_butt(BUTT_1);
		//gets delta time for velocity and acceleration equations
		
		//moves missiles
		for (int num_of_mis = (_missile.size() - 1); num_of_mis >= 0; num_of_mis--)
			_missile[num_of_mis].move(missile);
		//moves invaders side to side
		for (int num_of_mis = (_invaders.size() - 1); num_of_mis >= 0; num_of_mis--)
		{
			Point new_pos = _invaders[num_of_mis].get_pos();
			//new_pos.x += (_invaders[num_of_mis].get_vel().x * _delta_time);
			_invaders[num_of_mis].move(invader_x, new_pos.x);
			_invaders[num_of_mis].set_pos(_invaders[num_of_mis].get_top_left());
		}
		//gets joystick position as a percentage
		sketch_contr.get_data(ANALOG, 15, _x_joy_per);
		_x_joy_per = ((_x_joy_per * 100) / 1024) - 50;
		//gets delta time for velocity and acceleration equations
		//_current_time = getTickCount();
		//_delta_time = (_current_time - _last_time) / _freq;
		_ship_v += _ship_max_a * _delta_time;
		//relates joystick position to paddle velocity
		if (_x_joy_per > 10 || _x_joy_per < -10)
		{
			_ship_v += (_x_joy_per * _ship_max_a) * _delta_time;
			_ship_pos = _ship.get_top_left().x;
			_ship_pos += _ship_v * _delta_time;
			//edge dectection
			if (_ship_pos > 690)
			{
				_ship_pos = 690;
			}
			else if (_ship_pos < 0)
			{
				_ship_pos = 0;
			}
		}
		//puts new paddle positons into paddle objects
		_ship.move(ship, _ship_pos);
		//resets paddle velocity so it doeesn't move faster and faster
		_ship_v = 0;
		_last_time = getTickCount();
	}
}

void CSpaceInvadersGame::draw()
{
	_canvas = Mat::zeros(_canvas.size(), CV_8UC3);
	_ship.draw(_canvas);
	for (int num_of_inv = (_invaders.size() - 1); num_of_inv >= 0; num_of_inv--)
		_invaders[num_of_inv].draw(_canvas);
	for (int num_of_mis = (_missile.size() - 1); num_of_mis >= 0; num_of_mis--)
		_missile[num_of_mis].draw(_canvas);
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

void CSpaceInvadersGame::check_butt(int butt)
{
	//checks button position and resets game if button is pushed
	int pushed;
	switch (butt)
	{
	case BUTT_1:
		sketch_contr.get_butt(pushed, butt);
		if (pushed && (((getTickCount() - _butt_1_time) / getTickFrequency()) > 0.2))
		{
			_not_held = 1;
		}
		if (!pushed && (((getTickCount() - _butt_1_time) / getTickFrequency()) > 0.2))
		{
			if (_not_held)
			{
				_butt_1_time = getTickCount();
				_missile.push_back(CMissile(-1, (_ship.get_center() - _ship_offset)));
				_not_held = 0;
			}
		}
		break;
	case BUTT_2:
		sketch_contr.get_butt(pushed, butt);
		if (pushed && (((getTickCount() - _butt_2_time) / getTickFrequency()) > 0.2))
		{
			_not_held = 1;
		}
		if (!pushed && (((getTickCount() - _butt_2_time) / getTickFrequency()) > 0.2))
		{
			if (_not_held)
			{
				_butt_2_time = getTickCount();
				_done = 1;
				_not_held = 0;
			}
		}
		break;
	}
	sketch_contr.get_butt(pushed, butt);
	if (pushed && (((getTickCount() - _butt_2_time) / getTickFrequency()) > 0.2))
	{
		_not_held = 1;
	}
	if (!pushed && (((getTickCount() - _butt_2_time) / getTickFrequency()) > 0.2))
	{
		if (_not_held)
		{
			_butt_2_time = getTickCount();
			_done = 1;
			_not_held = 0;
		}
	}
}

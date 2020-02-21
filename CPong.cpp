#include "stdafx.h"
#include "CPong.h"

void CPong::chng_score()
{
	int pos = 0;
	while ((pos = _plyr_2.find(" ")) != std::string::npos)
	{
		_plyr_2.erase(pos, _plyr_2.length());
	}
	_plyr_2 += _space;
	_plyr_2 += std::to_string(_score[_plyr_2_scor]);
}

void CPong::new_set()
{
	background();
	_pad1_pos = Point(0, 325);
	_pad2_pos = Point(990, 325);
	_padd_1 = Rect(_pad1_pos.x, _pad1_pos.y, _pad_w, _pad_h);
	_padd_2 = Rect(_pad2_pos.x, _pad2_pos.y, _pad_w, _pad_h);
	_ball_p = Point(500, 400);
	_ball_v0 = Point(7, 7);
	_angle = (40 + (rand() % 11)) - (90 * (rand() % 2));
}

void CPong::background()
{
	putText(_canvas, _plyr_1, _plyr_1_origin, FONT_HERSHEY_SIMPLEX, _font_scale, _white);
	putText(_canvas, _plyr_2, _plyr_2_origin, FONT_HERSHEY_SIMPLEX, _font_scale, _white);
	line(_canvas, _mid_line_top, _mid_line_bot, _white);
	//rectangle(_canvas, padd_1, white, -10, 1);
	//rectangle(_canvas, padd_2, white, -10, 1);
}

void CPong::check_pos()
{
	_this_coll = getTickCount();
	if (((_this_coll - _last_ply1_coll) / _freq) > 3)
	{
		int pad_top = _pad1_pos.y - 5;
		int pad_bot = _pad1_pos.y + 155;
		if ((_ball_p.y > pad_top) && (_ball_p.y < pad_bot))
		{
			_ball_v0.x = _ball_v0.x * -1;
		}
		else
		{
			_plyr_2_scor += 1;
			if (_plyr_2_scor == 5)
			{
				chng_score();
				_canvas = Mat::zeros(_canvas.size(), CV_8UC3);
				background();
				putText(_canvas, _over_s, _over_or, FONT_HERSHEY_SIMPLEX, _ovr_font_sz, _white);
				//putText(_canvas, plyr_2, plyr_2_origin, FONT_HERSHEY_SIMPLEX, font_scale, white);
				imshow("image", _canvas);
				_done = 0;
			}
			else
			{
				chng_score();
				new_set();
			}
		}
		_last_ply1_coll = getTickCount();
	}

}

CPong::CPong(Size dim, int port)
{
	_canvas = Mat::zeros(Size(dim), CV_8UC3);
	sketch_contr.init_com(port);
	background();
	imshow("image", _canvas);
}

CPong::~CPong()
{
}

void CPong::draw()
{
	//resets the game
	sketch_contr.get_butt(_reset, BUTT_2);
	if (_reset && (((getTickCount() - _butt_2) / getTickFrequency()) > 0.2))
	{
		_not_held = 1;
	}
	if (!_reset && (((getTickCount() - _butt_2) / getTickFrequency()) > 0.2))
	{
		if (_not_held)
		{
			_butt_2 = getTickCount();
			_plyr_2_scor = 0;
			chng_score();
			new_set();
			_done = 1;
			_not_held = 0;
		}
	}
	//if statement stops game from refreshing when score of 5 reached and done becomes 0
	if (_done)
	{
		//frame per second measurement and display
		_cur_frame = getTickCount();
		_frames = _sec / ((_cur_frame - _last_frame) / _freq);
		_frames = round(_frames);
		_frame_s += std::to_string(_frames);
		_frame_s.erase(9, _frame_s.length());
		putText(_canvas, _frame_s, _fram_origin, FONT_HERSHEY_SIMPLEX, _font_scale, _white);
		//ball position
		_ball_p.x += _ball_v0.x * cos((_angle * PI) / 180);
		_ball_p.y += _ball_v0.y * sin((_angle * PI) / 180);
		//ball top and bottom collison detection
		int top_edge = _ball_p.y - _radius;
		int bot_edge = _ball_p.y + _radius;
		_this_wall_col = getTickCount();
		if ((bot_edge > 800 || top_edge < 0) && ((_this_wall_col - _last_wall_col) / _freq) > 2)
		{
			_ball_v0.y = _ball_v0.y * -1;
			_last_wall_col = getTickCount();
		}
		//ball computer paddle collison detection
		if (_ball_p.x > (_canvas.size().width - _radius - _pad_w))
		{
			_ball_v0.x = _ball_v0.x * -1;
		}
		//computer paddle edge detection
		_pad2_pos.y = _ball_p.y - 75;
		if (_pad2_pos.y > 650)
		{
			_pad2_pos.y = 650;
		}
		if (_pad2_pos.y < 0)
		{
			_pad2_pos.y = 0;
		}
		//player paddle vs ball collision
		if (_ball_p.x < 15)
		{
			check_pos();
		}
		//draws paddle and ball position
		_padd_2 = Rect(_pad2_pos.x, _pad2_pos.y, _pad_w, _pad_h);
		_padd_1 = Rect(_pad1_pos.x, _pad1_pos.y, _pad_w, _pad_h);
		rectangle(_canvas, _padd_1, _white, -10, 1);
		rectangle(_canvas, _padd_2, _white, -10, 1);
		circle(_canvas, _ball_p, _radius, _white, -1);
		imshow("image", _canvas);
		//blanks the screen
		_canvas = Mat::zeros(_canvas.size(), CV_8UC3);
		//time for frame count
		_last_frame = getTickCount();
		//draws new player score and midcount
		background();
		//clears frame string of previous fps
		int _pos = 0;
		while ((_pos = _frame_s.find(" ")) != std::string::npos)
		{
			_frame_s.erase(_pos, _frame_s.length());
		}
		_frame_s += _space;
	}
}

void CPong::update()
{
	//gets delta time for velocity and acceleration equations
	_current_time = getTickCount();
	_delta_time = (_current_time - _last_time) / _freq;
	//gets joystick posion
	sketch_contr.get_data(ANALOG, 9, _y_joy_per);
	_y_joy_per = 50 - ((_y_joy_per * 100) / 1024);
	_padd_v += _padd_max_a * _delta_time;
	//relates joystick position to paddle velocity
	if (_y_joy_per > 10 || _y_joy_per < -10)
	{
		_padd_v += (_y_joy_per * _padd_max_a) * _delta_time;
		_pad1_pos.y += _padd_v.y * _delta_time;
		//edge dectection
		if (_pad1_pos.y > 650)
		{
			_pad1_pos.y = 650;
		}
		else if (_pad1_pos.y < 0)
		{
			_pad1_pos.y = 0;
		}
	}
	//resets paddle velocity so it doeesn't move faster and faster
	_padd_v = Point(0, 0);
	_last_time = getTickCount();
}
#pragma once
#include "CBase4618.h"
#include <math.h>       /* cos */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>  

constexpr auto PI = 3.14159265;
using namespace cv;
class CPong : public CBase4618
{
private:
	//button reset
	double _butt_2 = getTickCount();
	int _reset;
	int _not_held = 1;
	//wall collision
	double _last_wall_col = getTickCount();
	double _this_wall_col;
	//30 fps control
	double _cur_frame;
	double _freq = getTickFrequency();
	double _last_frame = getTickCount();
	double _frames;
	double _sec = 1;
	//display strings
	std::string _space = " ";
	std::string _frame_s = "FPS: ";
	std::string _plyr_1 = "Player_1: 0";
	std::string _plyr_2 = "Player_2: 0";
	int _plyr_2_scor = 0;
	int _score[6] = { 0,1,2,3,4,5 };
	//score display origin points
	Point _fram_origin = Point(10, 30);
	Point _plyr_1_origin = Point(200, 30);
	Point _plyr_2_origin = Point(650, 30);
	double _font_scale = 1;
	Scalar _white = Scalar(255, 255, 255);
	//paddle positions and size
	int _pad_w = 10;
	int _pad_h = 150;
	Point _pad1_pos = Point(0, 325);
	Point _pad2_pos = Point(990, 325);
	Rect _padd_1 = Rect(_pad1_pos.x, _pad1_pos.y, _pad_w, _pad_h);
	Rect _padd_2 = Rect(_pad2_pos.x, _pad2_pos.y, _pad_w, _pad_h);
	//midline display
	Point _mid_line_top = Point(500, 0);
	Point _mid_line_bot = Point(500, 800);
	//player paddle control variables
	int _y_joy_per = 50;
	Point _padd_max_a = Point(0, 300);
	Point _padd_v;
	void new_set();
	//time variables fro movemoent calculations
	double _last_time = getTickCount();
	double _current_time;
	double _delta_time;
	//circle
	Point _ball_p = Point(500, 400);
	int _angle = (40 + rand() % 11) - (90 * (rand() % 2));
	Point _ball_v0 = Point(7, 7);
	int _radius = 5;
	//checks collision between player 1 and ball
	double _last_ply1_coll = getTickCount();
	double _this_coll;
	//game over
	std::string _over_s = "GAME OVER";
	Point _over_or = Point(320, 460);
	double _ovr_font_sz = 2;
	int _done = 1;
	void check_pos();
	void background();
	void chng_score();
public:
	CPong(Size dim = Size(1000, 800), int port = 5);
	~CPong();
	void draw();
	void update();
};

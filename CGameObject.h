#pragma once
#include "CBase4618.h"
#include <stdlib.h>         
#include <stdio.h> 
#include "opencv.hpp"
#include <atltypes.h>

using namespace cv;
enum { ship = 0, missile, invader_x, invader_y };

class CGameObject
{
protected:
	Point _position;
	Point _velocity;
	CRect _shape;
	int _lives;
public:
	void move(int obj, int new_pos = 0);
	bool collide_ship(CGameObject& obj);
	bool collide_inv(CGameObject& obj);
	bool collide_bot(CGameObject& obj);
	bool collide_wall(Size board);
	void hit();
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(Point pos) { _position = pos; }
	Point get_pos() { return _position; }
	Point get_vel() { return _velocity; }
	void set_vel(Point vel) { _velocity = vel; }
	void draw(Mat& im);
	Point get_top_left();
	Point get_center();
};


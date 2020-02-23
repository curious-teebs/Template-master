#pragma once
#include "CBase4618.h"
#include <stdlib.h>         
#include <stdio.h> 
#include "opencv.hpp"
#include <atltypes.h>

using namespace cv;

class CGameObject
{
protected:
	Point _position;
	Point _velocity;
	CRect _shape;
	int _lives;
public:
	void move();
	bool collide(CGameObject& obj);
	bool collide_wall(Size board);
	void hit();
	int get_lives() { return _lives; }
	void set_lives(int lives) { _lives = lives; }
	void set_pos(Point2f pos) { _position = pos; }
	Point2f get_pos() { return _position; }
	Point2f get_vel() { return _velocity; }
	void set_vel(Point2f vel) { _velocity = vel; }
	void draw(Mat& im);
};


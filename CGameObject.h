#pragma once
#include "CBase4618.h"
#include <stdlib.h>         
#include <stdio.h> 
#include "opencv.hpp"
#include <atltypes.h>

using namespace cv;
enum { ship = 0, missile, invader_x, invader_y };
/**
*
*@brief Holds variables and base functions for all game objects
*
*Holds shape, velocity, position, and lives of game objects, and allows you to read and alter those values
*
*@author Stephen Cyr
*
*/
class CGameObject
{
protected:
	Point _position;///< Top left corner of object
	Point _velocity;///< Pixels object moves every frame
	CRect _shape;///< Dimensions of object
	int _lives;///< Lives of object
public:

	/** @brief Increments object postion by its velocity
	*
	* @param Int specify which type of object is being moved, int specifying object's starting position
	* @return nothing
	*/
	void move(int obj, int new_pos = 0);

	/** @brief Checks collision between downward missile and object
	*
	* @param Object to be checked against the missile that called the function
	* @return boolean value, returns true when collsion occurs
	*/
	bool collide_ship(CGameObject& obj);

	/** @brief Checks collision between upward missile and object
	*
	* @param Object to be checked against the missile that called the function
	* @return boolean value, returns true when collsion occurs
	*/
	bool collide_inv(CGameObject& obj);

	/** @brief Checks for collsion between two objects, invaders and ship
	*
	* @param Ship object
	* @return boolean value, True when collsion occurs
	*/
	bool collide_bot(CGameObject& obj);

	/** @brief Checks for collsion between side of image and object
	*
	* @param Size of image
	* @return boolean value, True when collsion occurs
	*/
	bool collide_wall(Size board);

	/** @brief Decreases object's lives by one
	*
	* @param none
	* @return nothing
	*/
	void hit();

	/** @brief Returns the amount of lives the object has left
	*
	* @param none
	* @return int representing amount of lives remaining
	*/
	int get_lives() { return _lives; }

	/** @brief Sets the object's lives
	*
	* @param int representing the amount of lives
	* @return nothing
	*/
	void set_lives(int lives) { _lives = lives; }

	/** @brief Sets the postion of object
	*
	* @param Point represting the top left corner of the object
	* @return nothing
	*/
	void set_pos(Point pos) { _position = pos; }

	/** @brief Returns the current position of the object
	*
	* @param none
	* @return Point of the top left corner of the object
	*/
	Point get_pos() { return _position; }

	/** @brief Returns the current velocity of the object
	*
	* @param none
	* @return Point of the object's current velocity
	*/
	Point get_vel() { return _velocity; }

	/** @brief Sets the objects velocity
	*
	* @param Point holding velocity to be set
	* @return nothing
	*/
	void set_vel(Point vel) { _velocity = vel; }

	/** @brief Draws the object
	*
	* @param Mat image to been drawn on
	* @return nothing
	*/
	void draw(Mat& im, Scalar colour);

	/** @brief Gets the position of the top left corner
	*
	* @param none
	* @return Point containing the position of the top left corner
	*/
	Point get_top_left();

	/** @brief Gets the position of the center of the object
	*
	* @param none
	* @return Point containing the position of the center of the object
	*/
	Point get_center();
};


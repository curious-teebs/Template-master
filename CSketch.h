#pragma once
#include "CBase4618.h"
#include "opencv.hpp"
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")
/**
*
*@brief Draws different coloured lines on _canvas image
*
*Initializes serial comunication with msp board and sets sizes of _canvas
*takes position data from msp joystick to draw line on _canvas image
*
*@author Stephen Cyr
*
*/
using namespace cv;
enum {BLUE = 37, GREEN, RED};
enum { LOW = 0, HIGH };

class CSketch : public CBase4618
{
private:
	Point2d p1 = Point2d(250,250);
	Point2d p2 = Point2d(250,250);
	double incr = 5;
	Scalar colour = Scalar(0, 0, 255);
	double butt_2 = getTickCount();
	double butt_1 = getTickCount();
	int chan_col = 1;
	/** @brief variable to hold joystick y position
	*/
	int _y_pos = 250;
	/** @brief variable to hold joystick x position
	*/
	int _x_pos = 250;
	int clear;
	int cur_colour = RED;
	void change_col();
public:
	/** @brief method draws a line in a direction on _canvas depending on x and y values from update
	*
	* @param none
	* @return nothing
	*/
	void draw();
	/** @brief method update reads data from com port and updates the x and y positions
	*
	* @param none
	* @return nothing
	*/
	void update();
	/** @brief Contructor creates _canvas window and initializes serial communication
	*
	* @param size of object and int for com port number
	* @return nothing
	*/
	CSketch(Size dim = Size(500,500), int port = 5);
	/** @brief CSketch deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CSketch();
};


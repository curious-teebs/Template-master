#pragma once
#include "CBase4618.h"
#include <math.h>       
#include <stdlib.h>     
#include <time.h>       
#include <stdio.h>  
#include <chrono>
#include <thread>
#include <mutex>

constexpr auto PI = 3.14159265;
using namespace cv;
/**
*
*@brief Runs the game pong
*
*Runs simple physics engine to update ball and paddle positons and prints them to screen. Takes serial communication from potentiometer to control paddle velocity. Measures frame rate of the display 
*
*@author Stephen Cyr
*
*/
class CPong : 
	public CBase4618
{
private:

	std::mutex esc_condition;///< Allows threads escape condition to be changed in main thread

	bool _esc = true;///< Escape variable to exit program
	
	//button reset
	double _butt_2 = getTickCount();///< Time of last button push
	int _reset;///< The result from polling push button
	int _not_held = 1;///< Signifies when the push butto is released

	//timing of wall collsions
	double _last_wall_col = getTickCount();///< Time of last wall collision
	double _this_wall_col;///< Time at current wall collision

	//30 fps control
	double _cur_frame;///< Time at current frame
	double _freq = getTickFrequency();///< frequency
	double _last_frame = getTickCount();///< Time of last drawn frame
	double _frames;///< Amount of frames per second
	double _sec = 1;///< 1 second for frames per second calculation

	//display strings
	std::string _space = " ";///< Space string
	std::string _frame_s = "FPS: ";///< frames per second string
	std::string _plyr_1 = "Player_1: 0";///< Player 1 score string
	std::string _plyr_2 = "Player_2: 0";///< Player 2 score string
	int _plyr_2_scor = 0;///< Current player 2 score
	int _score[6] = { 0,1,2,3,4,5 };///< Array of possible scores

	//score display origin points
	Point _fram_origin = Point(10, 30);///< Point origin for FPS string
	Point _plyr_1_origin = Point(200, 30);///< Point origin for player 1 score string
	Point _plyr_2_origin = Point(650, 30);///< Point origin for player 2 score string
	double _font_scale = 1;///< Size multiplying for font
	Scalar _white = Scalar(255, 255, 255);///< Scalar object for the colour white

	//paddle positions and size
	int _pad_w = 10;///< paddle width
	int _pad_h = 150;///< paddle height
	Point _pad1_pos = Point(0, 325);///< Paddle 1 starting position
	Point _pad2_pos = Point(990, 325);///< Paddle 2 starting position
	Rect _padd_1 = Rect(_pad1_pos.x, _pad1_pos.y, _pad_w, _pad_h);///< Rect object for paddle 1
	Rect _padd_2 = Rect(_pad2_pos.x, _pad2_pos.y, _pad_w, _pad_h);///< Rect object for paddle 2

	//midline display
	Point _mid_line_top = Point(500, 0);///< Top point of mid line
	Point _mid_line_bot = Point(500, 800);///< Bottom point of mid line

	//player paddle control variables
	int _y_joy_per = 50;///< Joystick position as a percentage
	Point _padd_max_a = Point(0, 300);///< Fastest acceleration of paddle 1
	Point _padd_v;///< Paddle 1 velocity

	//time variables for movemoent calculations
	double _last_time = getTickCount();///< Last time of paddle 1 position update
	double _current_time;///< Current time of paddle 1 update
	double _delta_time;///< Difference between current paddle 1 update and last paddle 1 update

	//circle
	Point _ball_p = Point(500, 400);///< Starting point of ball
	int _angle = (40 + rand() % 11) - (90 * (rand() % 2));///< Random initial angle of ball velocity
	Point _ball_v0 = Point(8, 8);///< Ball velocity
	int _radius = 5;///< Radius of ball

	//checks collision between player 1 and ball
	double _last_ply1_coll = getTickCount();///< Time of last collision between ball and paddle 1
	double _this_coll;///< Time at current collision between ball and paddle 1

	//game over
	std::string _over_s = "GAME OVER";///< Game over string
	Point _over_or = Point(320, 460);///< Starting point of game over text
	double _ovr_font_sz = 2;///< Size of game over text
	int _done = 1;///< marks the end of a game 

	/** @brief Resets starting parameters after a point or push from reset button
	*
	* @param none
	* @return nothing
	*/
	void new_set();

	/** @brief Checks positon of paddle 1 vs the ball and calls chng_score or reverses balls velocity
	*
	* @param none
	* @return nothing
	*/
	void check_pos();

	/** @brief Draws the scores and center line
	*
	* @param none
	* @return nothing
	*/
	void background();

	/** @brief Increments the score and changes the "done" condition when score of 5 is reached
	*
	* @param none
	* @return nothing
	*/
	void chng_score();

	/** @brief Runs update in a loop until 'q' is pushed
	*
	* @param none
	* @return nothing
	*/
	void update_thread();

	/** @brief Runs draw in a loop until 'q' is pushed
	*
	* @param none
	* @return nothing
	*/
	void draw_thread();

public:

	/** @brief CPong constructor
	*
	* @param Size object for canvas, Int for port to open communitcation with
	* @return nothing
	*/
	CPong(Size dim = Size(1000, 800), int port = 5);

	/** @brief CPong deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CPong();

	/** @brief Draws new paddles and ball position and frames per second, and calls background for midline and scores
	*
	* @param none
	* @return nothing
	*/
	void draw();

	/** @brief Updates the position paddles and ball
	*
	* @param none
	* @return nothing
	*/
	void update();

	/** @brief Starts seperate threads for update_thread and draw_thread and waits for a 'q' to end Pong game
	*
	* @param none
	* @return nothing
	*/
	void start();
};

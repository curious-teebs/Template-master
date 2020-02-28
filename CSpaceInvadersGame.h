#pragma once
#include "CBase4618.h"
#include "CInvader.h"
#include "CMissile.h"
#include "CShip.h"
#include <atltypes.h>
/**
*
*@brief Runs the game pong
*
*Runs simple physics engine to update ball and paddle positons and prints them to screen. Takes serial communication from potentiometer to control paddle velocity. Measures frame rate of the display
*
*@author Stephen Cyr
*
*/
class CSpaceInvadersGame : public CBase4618
{
private:

	int _level_up = 3;

	int _per_of_missile = 1;///< percent of missile creation
	int _chnc_missile;///< Holds random number between 0-1000

	int _done = 1;///< Game end codition

	//Colour variables
	Scalar _red = Scalar(0, 0, 255);///< Red scalar
	Scalar _white = Scalar(255, 255, 255);///< White scalar
	Scalar _green = Scalar(0, 255, 0);///< Green scalar

	//Score and life string
	int _font_scale = 1;///< Size of font
	int _pos;///< Current position in string
	Point _lives_pt = Point(100, 30);///< Starting point of life string
	Point _score_pt = Point(600, 30);///< Starting point of the score string
	std::string _score_s = "Score: ";///< Score string
	std::string _live_s = "Lives: ";///< Life string
	std::string _space = " ";///< Space string
	int _score = 0;///< Int to hold the current score

	//invader dimensions
	int _dis_to_top = 50;///< Distance between top of screen and first row of invaders
	int _dis_to_wall = 60;///< Starting point of first invader from wall
	int _inv_width = 50;///< Width of the invaders
	int _inv_height = 50;///< Height of the invaders
	int _inbtwn_invs = 30;///< Distance inbetween invaders
	Point _ship_offset = Point(0, 25);///< distance from center of ship to edge for missile creation

	//Collision variables
	int _dbl_bounce = 1;///< Int to prevent invaders from double bouncing off wall
	int _bounce = 2;///< Amount of times the invaders will bounce off the ball
	Size _dim = Size(800, 800);///< Dimensions of the screen

	//CGameObject initializations
	CShip _ship;///< Initializing a CShip object
	std::vector<CMissile> _missile;///< Vector of CMissile objects
	std::vector<CInvader> _invaders;///< Vector of CInvader objects

	//Pushbutton variables
	int _not_held_1 = 0;///< Marks when button one is being held
	int _not_held_2 = 0;///< Marks when button two is being held
	double _butt_1_time = getTickCount();///< Last time button one was pushed
	double _butt_2_time = getTickCount();///< Last time button two was pushed

	//Ship movement variables
	int _ship_pos = 340;///< Ships starting position
	int _ship_max_v = 300;///< Ships maximum velocity
	int _ship_v;///< Ships current velocity
	int _x_joy_per;///< Contains joysticks relative position, contains 50>int>-50
	

	//time variables for movemoent calculations
	double _last_time = getTickCount();///< Last time of paddle 1 position update
	double _current_time;///< Current time of paddle 1 update
	double _delta_time = 0.0333;///< Difference between current paddle 1 update and last paddle 1 update
	double _freq = getTickFrequency();///< Clock frequency

	/** @brief Checks collsions between CGameObjects, erases ones with 0 lives, and calculates new postions
	*
	* @param none
	* @return nothing
	*/
	void update();

	/** @brief Clears display, draws CGameObjects and strings, and prints new images
	*
	* @param none
	* @return nothing
	*/
	void draw();

	/** @brief Fills Invader vector with 45 invader objects at their starting locations
	*
	* @param none
	* @return nothing
	*/
	void set_invaders();

	/** @brief Checks output of button and creates missile or resets game variables to starting value depending on which button is pressed
	*
	* @param int representing which button to check
	* @return nothing
	*/
	void check_butt(int butt);

public:

	/** @brief CSpaceInvadersGame constructor initializes serial point, creates blank image for game, and calls set_invaders function
	*
	* @param Size variable for size of game screen, int for which comm port to initializes 
	* @return nothing
	*/
	CSpaceInvadersGame(Size dim = Size(800, 800), int port = 5);

	/** @brief CSpaceInvadersGame deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CSpaceInvadersGame();
};


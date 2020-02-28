#pragma once
#include "CGameObject.h"
/**
*
*@brief CShip object controls the position and velocity of ship
*
*Initializes the size, position, and lives of CGameobject
*
*@author Stephen Cyr
*
*/
class CShip : public CGameObject
{
public:

	/** @brief CSpaceInvadersGame Constructor
	*
	* @param Point of top left starting position, Point of the bottom right starting position, int containing amount of lives
	* @return nothing
	*/
	CShip(Point top_l = Point(370, 770), Point bot_r = Point(430, 800), int lives = 3);

	/** @brief CShip deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CShip();
};


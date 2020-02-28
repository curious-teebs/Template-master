#pragma once
#include "CGameObject.h"
/**
*
*@brief Initializes GameObject as a CInvader
*
*Initializes CInvader of a specified at a size at a specified point with one life
*
*@author Stephen Cyr
*
*/
class CInvader : public CGameObject
{
public:

	/** @brief CInvader constructor 
	*
	* @param Point of top left corner of object, Point of bottom right corner of object
	* @return nothing
	*/
	CInvader(Point top_l, Point bot_r, int lives = 1);

	/** @brief CInvader deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CInvader();
};


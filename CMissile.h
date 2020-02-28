#pragma once
#include "CGameObject.h"
#include <atltypes.h>
/**
*
*@brief Creates CMissile specific GameObject
*
*Initializes Game object with a certain size at a specified position with one life
*
*@author Stephen Cyr
*
*/
class CMissile : public CGameObject
{
public:

	/** @brief CMissile deconstructor
	*
	* @param int describing velocity of object, 1 = down and -1 = up, Point of the starting top left corner of object
	* @return nothing
	*/
	CMissile(int vel_dir, Point pos, int lives = 1);

	/** @brief CMissile deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CMissile();
};


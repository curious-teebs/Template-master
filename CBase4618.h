#pragma once
#include "CControl.h"
#include "opencv.hpp"
/**
*
*@brief initializes Mat and CControl objects
*
*Initializes Mat and CControl objects and creates function decriptors for update and draw, and then run runs them on a loop
*
*@author Stephen Cyr
*
*/
class CBase4618
{
public:
	/** @brief Contructor creates
	*
	* @param none
	* @return nothing
	*/
	CBase4618();
	/** @brief CBase4618 deconstructor
	*
	* @param none
	* @return nothing
	*/
	~CBase4618();
	/** @brief calls udpdate and draw on a loop until until it receivs q key
	*
	* @param none
	* @return nothing
	*/
	void run();
protected:

	/** @brief Mat object to create drawing window
	*/
	cv::Mat _canvas;
	/** @brief CControl opject to get data from com port
	*/
	CControl sketch_contr;
	/** @brief virtual method update reads data from com port and updates the x and y positions
	*
	* @param none
	* @return nothing
	*/
	virtual void update()=0;
	/** @brief virtual method draws a line in a direction on _canvas depending on x and y values from update
	*
	* @param none
	* @return nothing
	*/
	virtual void draw()=0;
};



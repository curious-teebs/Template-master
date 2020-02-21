#include "stdafx.h"
#include "CColour.h"

void CColour::get_colour(int cur_col,int& _blue, int& _red, int& _green)
{
	switch (cur_col)
	{
	case 1:
		_blue = 255;
		_red = 0;
		_green = 0;
		break;
	case 2:
		_blue = 0;
		_red = 0;
		_green = 255;
		break;
	case 3:
		_blue = 0;
		_red = 255;
		_green = 0;
		break;
	}
}

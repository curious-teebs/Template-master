#include "stdafx.h"
#include "CGameObject.h"
#include <atltypes.h>

void CGameObject::move()
{
	_position += _velocity;
}

bool CGameObject::collide(CGameObject& obj)
{
	return false;
}

bool CGameObject::collide_wall(Size board)
{
	return false;
}

void CGameObject::hit()
{
	_lives -= 1;
}

void CGameObject::draw(Mat& im)
{
	CPoint topleft = _shape.TopLeft();
	CPoint botright = _shape.BottomRight();
	int width = botright.x - topleft.x;
	int height = botright.y - topleft.y;
	Rect shape = Rect(topleft.x, topleft.y, width, height);
	cv::rectangle(im, shape, Scalar(255, 255, 255), -10, 1);
}

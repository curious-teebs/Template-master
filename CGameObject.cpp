#include "stdafx.h"
#include "CGameObject.h"
#include <atltypes.h>

void CGameObject::move(int obj, int new_pos)
{
	switch (obj)
	{
	case ship:
		_shape.MoveToX(new_pos);
		break;
	case missile:
		new_pos = _velocity.y + get_top_left().y;
		_shape.MoveToY(new_pos);
		break;
	case invader_x:
		new_pos += _velocity.x;
		_shape.MoveToX(new_pos);
		break;
	case invader_y:
		new_pos += _velocity.y;
		if (new_pos > 750)
		{
			new_pos = 745;
		}
		_shape.MoveToY(new_pos);
		break;
	}
}

bool CGameObject::collide_inv(CGameObject& obj)
{
	CPoint topleft = _shape.TopLeft();
	CPoint topright = topleft + CPoint(4, 0);
	CPoint botright = _shape.BottomRight();
	CPoint botleft = botright - CPoint(4, 0);
	if ((_velocity.y < 0) && (obj._shape.PtInRect(topleft) || obj._shape.PtInRect(topright) || obj._shape.PtInRect(botleft) || obj._shape.PtInRect(botright)))
	{
		hit();
		obj.hit();
	}
	return false;
}
bool CGameObject::collide_bot(CGameObject& obj)
{
	CPoint topleft = _shape.TopLeft();
	CPoint topright = topleft + CPoint(50, 0);
	CPoint botright = _shape.BottomRight();
	CPoint botleft = botright - CPoint(50, 0);
	if (obj._shape.PtInRect(topleft) || obj._shape.PtInRect(topright) || obj._shape.PtInRect(botleft) || obj._shape.PtInRect(botright))
	{
		obj._lives = 0;
	}
	return false;
}

bool CGameObject::collide_ship(CGameObject& obj)
{
	CPoint topleft = _shape.TopLeft();
	CPoint topright = topleft + CPoint(4, 0);
	CPoint botright = _shape.BottomRight();
	CPoint botleft = botright - CPoint(4, 0);
	if ((_velocity.y > 0) && (obj._shape.PtInRect(topleft) || obj._shape.PtInRect(topright) || obj._shape.PtInRect(botleft) || obj._shape.PtInRect(botright)))
	{
		hit();
		obj.hit();
	}
	return false;
}

bool CGameObject::collide_wall(Size board)
{
	if (_shape.TopLeft().y <= 0 || _shape.BottomRight().y >= 800)
	{
		hit();
	}
	if ((_shape.BottomRight().x >= 800 && _velocity.x > 0) || (_shape.TopLeft().x <= 0 && _velocity.x < 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CGameObject::hit()
{
	_lives -= 1;
}

void CGameObject::draw(Mat& im, Scalar colour)
{
	CPoint topleft = _shape.TopLeft();
	CPoint botright = _shape.BottomRight();
	int width = botright.x - topleft.x;
	int height = botright.y - topleft.y;
	Rect shape = Rect(topleft.x, topleft.y, width, height);
	cv::rectangle(im, shape, colour, -10, 1);
}

Point CGameObject::get_top_left()
{
	CPoint topleft = _shape.TopLeft();
	int x_pos = topleft.x;
	int y_pos = topleft.y;
	return Point(x_pos, y_pos);
}

Point CGameObject::get_center()
{
	CPoint center = _shape.CenterPoint();
	int x_pos = center.x;
	int y_pos = center.y;
	return Point(x_pos, y_pos);
}

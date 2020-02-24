#include "stdafx.h"
#include "CMissile.h"

CMissile::CMissile(int vel_dir, Point pos, int lives)
{
	set_lives(1);
	_position = pos;
	Point top_l = Point((pos.x - 2), (pos.y - 4));
	Point bot_r = Point((pos.x + 2), (pos.y + 4));
	_shape.SetRect(top_l.x, top_l.y, bot_r.x, bot_r.y);
	_velocity = (Point2f(0, 10)) * vel_dir;
}

CMissile::~CMissile()
{
}

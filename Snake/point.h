#pragma once
//Class Point -  Point representation in two-dimensional space
class point {
public:
	int x;
	int y;
	point() { x = 0; y = 0; }
	point(int _x, int _y) { x = _x; y = _y; }
	bool operator ==(point p) {
		if (this->x == p.x&&this->y == p.y)
			return true;
		return false;
	}
};

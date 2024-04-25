#ifndef COORD_H
#define COORD_H

struct Coord{
        int x,y;
        Coord();
        Coord(int x, int y);
        Coord operator+(const Coord &addition);
	void operator+=(const Coord &addition);
        Coord operator-(const Coord &subtract);
	void operator-=(const Coord &subtract);
	bool operator==(const Coord &comparison);
	bool operator!=(const Coord &comparison);
};

#endif //COORD_H


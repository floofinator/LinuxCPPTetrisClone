#include "coord.h"

Coord::Coord(){
        x=0;
        y=0;
}
Coord::Coord(int x, int y){
        this->x = x;
        this->y = y;
}
Coord Coord::operator+(const Coord &addition){
	return Coord(x+addition.x,y+addition.y);
}
void Coord::operator+=(const Coord &addition){
        x = x+addition.x;
	y = y+addition.y;
}
Coord Coord::operator-(const Coord &subtract){
        return Coord(x-subtract.x,y-subtract.y);
}
void Coord::operator-=(const Coord &subtract){
        x = x-subtract.x;
        y = y-subtract.y;
}
bool Coord::operator==(const Coord &comparison) {
	return (x==comparison.x && y==comparison.y);
}
bool Coord::operator!=(const Coord &comparison) {
	return (y!=comparison.y || y!=comparison.y);
}

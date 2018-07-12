#pragma once
#include <deque>
#include <vector>
#include <map>
using namespace std;


struct Point {
	int x;
	int y;
};


class SearchOfWay
{
	int width, height;
	int ** field;
	Point first;
	Point last;
	bool bestWay = false;
	int bestPos;
	deque<deque<Point>> allWays;
	void choosePoint(int &, Point, Point);
	void countSteps();
	int checkDistance(Point, Point);

public:
	SearchOfWay(char[]) throw(char);
	~SearchOfWay();
	void readPoint(char [], Point &);
	void printField();
	void chooseWay();

};


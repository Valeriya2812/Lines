#include "stdafx.h"
#include "SearchOfWay.h"
#include <iostream>
#include <deque>
#include <fstream>
using namespace std;





SearchOfWay::SearchOfWay(char path []) throw (char)
{
	
	int i, j=0, k=0;
	ifstream fin(path); 
	char buff[100];
	if (!fin.is_open()) 
		cout << "File can not open!\n"; 
	else {
		fin.getline(buff, 100);
		height = atoi(buff);
		fin.getline(buff, 100);
		width = atoi(buff);

		field = new int * [height];
		for (i = 0; i < height; i++)
		{
			field[i] = new int [width];
		}
		
		fin.getline(buff, 100);
		readPoint(buff, first);
		fin.getline(buff, 100);
		readPoint(buff, last);
		if (first.x < 0 || first.x >= height || first.y < 0 || first.y >= width || last.x < 0  || last.x >= height || last.y < 0 || last.y >= width)
			throw "One of your point is out of field";

		while (!fin.eof())
		{
			fin.getline(buff, 100);
			for (i = 0; i < width * 2 - 1; i++)
			{
				if (buff[i] == '1')
				{
					field[j][k] = 1;
					k++;
					
				}
				else if (buff[i] == '0')
				{
					field[j][k] = 0;
					k++;
				}
				else if (buff[i] = ' ')
					continue;
				else {
					cout << "The file contains an invalid character!";
					exit(0);
				}
			}
			
			j++; 
			k = 0;
			}
		fin.close();
	}	
	
	allWays.resize(30);
	allWays[0].push_back(first);

}


void SearchOfWay::readPoint(char buff [], Point & p) {
	int i = 0, k = 0;
	while (buff[i] != ')')
	{
		if (buff[i] == ',')
		{
			p.x = k-1;
			k = 0;
		}
		if ((buff[i] >= 0x30) && (buff[i] <= 0x39))
		{
			k *= 10;
			k += buff[i] - 0x30;
		}
		i++;
	}
	p.y = k-1;
}

void SearchOfWay::printField() {
	
	int i, j;
	for (j = 0; j < width*2; j++)
	cout << "_";

	cout << endl;
	cout << endl;
	for (i = 0; i < height;i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i  == first.x) && (j  == first.y))
				cout << "O" << " ";
			else if ((i  == last.x) && (j  == last.y))
				cout << "F" << " ";
			else if(field[i][j]==1)
				cout << "O ";
			else if(field[i][j]==0)
				cout << "X ";
		}
		cout << endl;
	}
	for (j = 0; j < width*2; j++)
		cout << "_";


	cout << endl;
	cout << endl;

}


int SearchOfWay::checkDistance(Point p, Point nextP) {
	int diffX, diffY;
	int nextDiffX, nextDiffY, prevDiffX, prevDiffY, prevNextDiffX, prevNextDiffY;
	diffX = abs(p.x - last.x);
	diffY = abs(p.y - last.y);
	nextDiffX = abs(nextP.x - last.x);
	nextDiffY = abs(nextP.y - last.y);
	
	if (nextDiffX < diffX)
		return 2;
	else if (nextDiffY < diffY)
		return 3;
	else {
		prevNextDiffX = abs(nextP.x - first.x);
		prevNextDiffY = abs(nextP.y - first.y);
		prevDiffX = abs(p.x - first.x);
		prevDiffY = abs(p.y - first.y);
		if ((prevNextDiffX > prevDiffX) || (prevNextDiffY > prevDiffY))
			return 1;
		else return 0;
	}
		
		
}






void SearchOfWay::chooseWay() {

	int j, i, beg, end, pos = 0;
	Point prev;
	prev.x = -1;
	prev.y = -1;
	bool f1 = false;
	bool f2 = false;

	if (first.x < last.x)
	{
		beg = first.x;
		end = last.x;
	}
	else {
		beg = last.x;
		end = first.x;
	}
	if (beg != end && beg+1!=end) {
		for (i = beg + 1; i < end; i++)
		{
			if (!f1)
			{
				for (j = 0; j < width; j++)
					if (field[i][j] == 0)
					{
						f1 = true;
						break;
					}
			}
			else break;
		}
	}
	else f1 = true;
	if (first.y < last.y)
	{
		beg = first.y;
		end = last.y;
	}
	else {
		beg = last.y;
		end = first.y;
	}
	if (beg != end && beg + 1 != end) {
		for (i = 0; i < height; i++)
		{
			if (!f2)
			{
				for (j = beg + 1; j < end; j++)
				{
					if (field[i][j] == 0)
					{
						f2 = true;
						break;
					}
				}
			}
			else break;
		}
	}
	else f2 = true;
	if (!f1 || !f2)
		countSteps();
	else
	{
		choosePoint(pos, first, prev);
		countSteps();
	}


}



void SearchOfWay::choosePoint(int & pos, Point p, Point previous) {
		int k, i, max;
		deque<Point>pdeq = allWays[pos];
		map<int, Point> priority;
		map<int, Point>::iterator it;
		
		Point newP;
		bool f = false;
		

		if ((p.x + 1 < width) && (field[p.x + 1][p.y] == 0) && (p.x + 1 != previous.x))
		{
			newP.x = p.x + 1;
			newP.y = p.y;
			f = true;
			k = checkDistance(p, newP);
			priority[k] = newP;
		}

		if ((p.x - 1 >= 0) && (field[p.x - 1][p.y] == 0) && (p.x - 1 != previous.x))
		{
			newP.x = p.x - 1;
			newP.y = p.y;
			f = true;
			k = checkDistance(p, newP);
			priority[k] = newP;
		}

		if ((p.y + 1 < height) && (field[p.x][p.y + 1] == 0) && (p.y + 1 != previous.y))
		{
			newP.x = p.x;
			newP.y = p.y + 1;
			f = true;
			k = checkDistance(p, newP);
			priority[k] = newP;
		}

		if ((p.y - 1 >= 0) && (field[p.x][p.y - 1] == 0) && (p.y - 1 != previous.y))
		{
			newP.x = p.x;
			newP.y = p.y - 1;
			f = true;
			k = checkDistance(p, newP);
			priority[k] = newP;
		}
		 max = 3;

		while (max != -1 && bestWay==false) {
	
				if (priority.find(max) != priority.end())
				{
					allWays[++pos] = pdeq;
					newP.x = priority[max].x;
					newP.y = priority[max].y;
					if ((newP.x == last.x) && (newP.y == last.y))
					{
						allWays[pos].push_back(priority[max]);
						bestWay = true;
						bestPos = pos;
						break;
					}
					else {

						allWays[pos].push_back(priority[max]);
						choosePoint(pos, newP, p);
					}
				}
				max--;
	
		}

		if (!f)
			allWays[++pos] = pdeq;
	
	allWays.pop_front();
}




void SearchOfWay::countSteps() {
	int i;
	deque<Point> temp;
	if (bestWay) {
		for (i = 0; i < allWays.size(); i++)
		{
			 if (allWays[i].size() == bestPos + 1)
			{
				temp = allWays[i];
				break;
			}
		}

		for (i = 0; i < temp.size() - 1; i++)
		{
			if (temp[i].x < temp[i + 1].x)
				cout << "D ";
			else if (temp[i].x > temp[i + 1].x)
				cout << "U ";
			else if (temp[i].y < temp[i + 1].y)
				cout << "R ";
			else if (temp[i].y > temp[i + 1].y)
				cout << "L ";
		}

		cout << endl;
		cout << "Count of steps	= " << bestPos << endl;
	}
	else cout << "There is no path" <<  endl;
}



SearchOfWay::~SearchOfWay()
{
	for (int i = 0; i < height; i++)
		delete [] field[i];
}

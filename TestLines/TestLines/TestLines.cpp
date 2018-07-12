// TestLines.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SearchOfWay.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	try {
		//eSearchOfWay ob("lines1.txt");
		SearchOfWay ob("lines.txt");
		ob.printField();
		ob.chooseWay();

	}
	catch (char mess)
	{
		cout << mess << endl;
	}
	system("pause");
    return 0;
}


#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
// pow(x,3) + 2*pow(x,2) + 5
#define graphic(x) (pow(x,3) + 2*pow(x,2) + 5) //график который будет строится
#define lagranjGraph(x) (polinomLangranja(x))

int interval[2];
double intervalLength;
double divInterval[100];
double intervalValues[100];
int degree;

void getInterval()
{
	cout << "Input an interval: ";
	cin >> interval[0] >> interval[1];
	cout << "Input polynomial degree: ";
	cin >> degree;

	intervalLength = interval[1] - interval[0] + 1;
	double step = (intervalLength - 1) / degree;

	for (int i = 0; i < degree + 1; i++)
	{
		double temp = i;
		divInterval[i] = interval[0] + temp * step;
		intervalValues[i] = graphic(divInterval[i]);
	}
	intervalLength = degree + 1;

	system("pause");
}


float polinomLangranja(double x)
{
	int n = intervalLength;
	float finalRes = 0;

	for (int i = 0; i < n; i++)
	{
		double res = 1;

		for (int j = 0; j < n; j++)
		{
			if (j != i)
			{
				res *= (x - divInterval[j]) / (divInterval[i] - divInterval[j]);
			}
		}

		finalRes += intervalValues[i] * res;
	}

	return finalRes;
}


void buildGraphic()
{
	float point;
	float finterval[2] = { interval[0], interval[1] };

	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	MoveToEx(hDC, 0, 200, NULL);
	LineTo(hDC, 200, 200);
	MoveToEx(hDC, 100, 0, NULL);
	LineTo(hDC, 100, 370);

	for (point = finterval[0]; point <= interval[1]; point += 0.01f) // O(100,200) - center
	{
		MoveToEx(hDC, 10 * point + 100, -10 * lagranjGraph(point) + 200, NULL);//10 - scale
		LineTo(hDC, 10 * point + 100, -10 * lagranjGraph(point) + 200);
	}

	HDC hDC2 = GetDC(GetConsoleWindow());
	HPEN Pen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hDC2, Pen2);

	for (point = finterval[0]; point <= interval[1]; point += 0.1f) // O(100,200) - center
	{
		MoveToEx(hDC2, 10 * point + 100, -10 * graphic(point) + 200, NULL);//10 - scale
		LineTo(hDC2, 10 * point + 100, -10 * graphic(point) + 200);
	}
	
}

int main(void)
{
	getInterval();
	system("cls");
	buildGraphic();

	system("pause");
	return 0;
}
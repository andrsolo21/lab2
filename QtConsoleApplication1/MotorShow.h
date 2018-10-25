#pragma once
#include "Car.h"
#include <fstream> 
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class MotorShow
{
	
public:
	struct Rect {
		Rect * next, *last;
		Car *data;
	};
	MotorShow();
	MotorShow(Car * addData[], int addCount, float addGabarits[]);
	MotorShow(const MotorShow & addData);
	MotorShow(std::string f);
	~MotorShow();

	void addElement(const Car element);
	void deleteElement(int i);	
	void deleteAll();
	void printToFile(std::string f);

	Car getElement(int i) const;

	int getCount() const;
	float getGabarits(int i) const;


private:
	float _gabarits[2];
	Rect *_head, *_tail, *_gen;
	int _count;
	void grow(int i);
	void grow10();
	bool checkCar(const Car carToCheck);
	int linear(int X[], int A[], int B[]);
	
};


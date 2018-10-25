#include "MotorShow.h"
#include <fstream> 
#include <string>
#include <cstdio>
MotorShow::MotorShow()
{
	_head = NULL;
	_tail = NULL;
	_gen = NULL;
	_gabarits[0] = 10;
	_gabarits[1] = 10;
	_count = 0;
}

MotorShow::MotorShow(Car * addData[], int addCount, float addGabarits[]) {
	_head = NULL;
	_tail = NULL;
	_gen = NULL;
	_count = addCount;
	if (addGabarits[0] > 0 && addGabarits[1] > 0) {
		_gabarits[0] = addGabarits[0];
		_gabarits[1] = addGabarits[1];
	}

	for (int i = 0; i < addCount; i++) {
		if (checkCar(*addData[i])) {
			grow10();

			_tail->data = new Car(*addData[i]);
			_tail->data->calculate();
			_tail = _tail->next;
		}
	}
}

MotorShow::MotorShow(const MotorShow & addData) {
	_head = NULL;
	_tail = NULL;
	_gen = NULL;
	_count = addData.getCount();
	_gabarits[0] = addData.getGabarits(0);
	_gabarits[1] = addData.getGabarits(1);
	for (int i = 0; i < _count; i++) {
		grow10();
		
		_tail->data = new Car(addData.getElement(i));	
		_tail->data->calculate();
		_tail = _tail->next;
	}
}

MotorShow::MotorShow(std::string name) {
	_head = NULL;
	_tail = NULL;
	_gen = NULL;
	ifstream file(name);
	if (file.is_open())
	{
		file >> _gabarits[0];
		file >> _gabarits[1];
		std::string s;
		float size[2], coord[2], angle;
		Car * tempCar;
		for (file >> s; !file.eof(); file >> s) {
			file >> size[0] >> size[1] >> angle >> coord[0] >> coord[1];
			tempCar = new Car(s, angle, size, coord);
			if (checkCar(*tempCar)) {
				grow10();
				_tail->data = new Car(*tempCar);
				_tail->data->calculate();
				_tail = _tail->next;
			}
			delete tempCar;

		}
	}
	file.close();
}

int MotorShow::getCount() const {
	return _count;
}

float MotorShow::getGabarits(int i) const {
	return _gabarits[i % 2];
}

Car MotorShow::getElement(int c) const {
	if (c < _count) {
		Rect * uk = _head;
		for (int i = 0; i < c; i++)
			uk = uk->next;
		return *(uk->data);
	}

}

void MotorShow::addElement(Car element) {
	if (checkCar(element)) {
		grow10();
		
		_tail->data = new Car(element);
		_tail->data->calculate();
		_tail = _tail->next;
		_count++;
	}

}

void MotorShow::deleteElement(int c) {
	if (c < _count) {
		Rect * uk = _head;
		for (int i = 0; i < c; i++)
			uk = uk->next;

		if (uk == _head && uk == _tail) {
			_head = NULL;
			_tail = NULL;
		}
		else
			if (uk == _head) {
				uk->next->last = NULL;
				_head = uk->next;
			}else
				if (uk == _tail) {
					uk->last->next = NULL;
					_tail = uk->last;
				}else
					if (uk != _head && uk != _tail)
					{
						uk->next->last = uk->last;
						uk->last->next = uk->next;
					}
		_count--;
		delete uk->data;
	}
}

void MotorShow::deleteAll() {
	Rect *uk, * uk1 = _head;
	while (uk) {
		uk = uk1->next;
		//delete uk1->data;
		uk1 = uk;
	}
	_head = NULL;
	_tail = NULL;
	_gen = NULL;
	_count = 0;
}

void MotorShow::printToFile(std::string f) {
	ofstream fout(f, ios_base::out | ios_base::trunc);	
	fout << _gabarits[0] << ' ';
	fout << _gabarits[1] ;
	Car * tempCar;
	Rect * uk = _head;
	for (int i = 0; i<_count; i++) {
		fout <<endl<< uk->data->getName() << endl;
		fout << uk->data->getSize(0) << ' ' << uk->data->getSize(1) << ' ' << uk->data->getAngle()<<
			' '<< uk->data->getCoord(0) << ' '<< uk->data->getCoord(1);
		uk = uk->next;
	}
	fout.close();
}

int MotorShow::linear(int X[], int A[], int B[]) {
	return ((X[0] / (B[0] - A[0])) - (X[1] / (B[1] - A[1])) - (A[0] / (B[0] - A[0])) + (A[1] / (B[1] - A[1])));
}

bool MotorShow::checkCar(const Car carToCheck) {
	/*Rect *uk = _head;
	float d;
	for (int i = 0; i < _count; i++) {
		uk->data->getRBig();
		d = sqrt((uk->data->getCoord(0) - carToCheck.getCoord(0)) * (uk->data->getCoord(0) - carToCheck.getCoord(0)) +
			(uk->data->getCoord(1) - carToCheck.getCoord(1)) * (uk->data->getCoord(1) - carToCheck.getCoord(1)));
		if (uk->data->getRSmall + carToCheck.getRSmall < d)
			return false;
		if (uk->data->getRBig + carToCheck.getRBig > d) {
			float A1[2], A2[2], B1[2], B2[2], C1[2], C2[2], D1[2], D2[2];
			for (int i = 0; i < 2; i++) {
				A1[i] = carToCheck.getA(i);
				B1[i] = carToCheck.getB(i);
				C1[i] = carToCheck.getC(i);
				D1[i] = carToCheck.getD(i);
				A2[i] = uk->data->getA(i);
				B2[i] = uk->data->getB(i);
				C2[i] = uk->data->getC(i);
				D2[i] = uk->data->getD(i);
			}

			//TODO
		}
		uk = uk->next;
	}*/
	return true;
}

void MotorShow::grow10() {
	if (_gen ==_tail) {
		int startNum = 0;
		Rect * add = new Rect [10];
		if (_head == NULL) {
			_head = &add[0];
			_gen = &add[0];
			_tail = &add[0];
			startNum = 1;
			_gen->last = NULL;
		}
		for (int i = startNum; i < 10; i++) {
			_gen->next = &add[i];
			add[i].last = _gen;
			_gen = &add[i];
		}
		_gen->next = NULL;
	}
}

void MotorShow::grow(int c) {
	if (c > 0) {
		Rect * add;
			if (_tail) {
				for (int i = 0; i < c; i++) {
					add = new Rect;
					_gen->next = add;
					add->last = _gen;
					_gen = add;
					_gen->next = NULL;
				}
			}
			else {
				add = new Rect;
				_tail = add;
				_tail->last = NULL;
				_gen = _tail;
				_gen->next = NULL;

				for (int i = 1; i < c; i++) {
					add = new Rect;
					_gen->next = add;
					add->last = _gen;
					_gen = add;
					_gen->next = NULL;
				}
			}	
	}
}

MotorShow::~MotorShow()
{
}
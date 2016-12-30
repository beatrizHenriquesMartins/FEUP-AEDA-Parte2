/*
 * Taxi.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef TAXI_H_
#define TAXI_H_

#include <string>
#include <iostream>
#include "Hora.h"

using namespace std;

class Taxi {
	static int ultinumeroTaxi;
	int numeroTaxi;
	float rentabilidade;
	Hora horaIn;
	Hora horaOff;
	float dispo;

public:
	Taxi();
	Taxi(Hora horI, Hora horO);
	Taxi(int n, float r, Hora horI, Hora horO);

	~Taxi();

	int getNumeroTaxi() const;
	//bool getDisponivel(Hora hi, Hora hf);
	float getRentabilidade();
	Hora getHoraIn();
	Hora getHoraOff();
	float getdispo() const;

	void setRentabilidade(float n);

	void changeDispo(float n);

	bool operator <(const Taxi t);
	friend ostream & operator <<(ostream & os, Taxi t);
};

class TaxisIndisponiveis {
	string razao;
public:
	TaxisIndisponiveis(string r) {
		razao = r;
	}
	;
	string getRazao() {
		return razao;
	}
	;
};

#endif /* TAXI_H_ */

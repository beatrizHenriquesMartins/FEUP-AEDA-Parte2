/*
 * Hora.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef HORA_H_
#define HORA_H_

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Hora{
	int hora;
	int minutos;
	int segundos;

public:
	Hora();
	Hora(int h, int m, int s);

	int getHora() const;
	int getMinutos() const;
	int getSegundos() const;

	Hora somaHoras(int min);

	bool operator <(Hora h2);
	bool operator <=(Hora h2);

	string toString();
	friend ostream & operator <<(ostream & os, Hora h);
};

class HoraInvalida {
	string razao;
public:
	HoraInvalida(string r) {
		razao = r;
	}
	;

	string getRazao() {
		return razao;
	}
	;
};

#endif /* HORA_H_ */

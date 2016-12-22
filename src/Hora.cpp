/*
 * Hora.cpp
 *
 *  Created on: 08/11/2016
 *      Author: Pedro Silva
 */

#include "Hora.h"

Hora::Hora() {

	time_t now;
	time(&now);

	tm *ltm = localtime(&now);

	hora = ltm->tm_hour;
	minutos = ltm->tm_min;
	segundos = ltm->tm_sec;

}

Hora::Hora(int h, int m, int s) {

	if (h < 0 || h > 23)
		throw HoraInvalida("Hora nao permitida");
	if (m < 0 || m > 59)
		throw HoraInvalida("Minutos nao permitidos");
	if (s < 0 || s > 59)
		throw HoraInvalida("Segundos nao permitidos");

	hora = h;
	minutos = m;
	segundos = s;

}

int Hora::getHora() const {
	return hora;
}

int Hora::getMinutos() const {
	return minutos;
}

int Hora::getSegundos() const {
	return segundos;
}

Hora Hora::somaHoras(int min) {
	int minfinal;

	minfinal = this->minutos + min;

	if (minfinal / 60 > 0) {
		if (hora + 1 == 24) {
			Hora h = Hora(0, 0, 0);
			return h;
		}
	}

	int hor = this->hora + 1;
	int minu = this->minutos + minfinal % 60;
	int sec = this->segundos;

	Hora h = Hora(hor, minu, sec);
	return h;
}

//
string Hora::toString() {
	stringstream ss;
	ss << this->getHora() << ":" << this->getMinutos() << ":"
			<< this->getSegundos() << "h";
	return ss.str();
}
//

bool Hora::operator <(Hora h2) {

	if (hora < h2.getHora())
		return true;
	else if (hora == h2.getHora() && minutos < h2.getMinutos())
		return true;
	else if (hora == h2.getHora() && minutos == h2.getMinutos()
			&& segundos < h2.getSegundos())
		return true;
	else
		return false;

}

bool Hora::operator <=(Hora h2) {

	if (hora <= h2.getHora())
		return true;
	else if (hora == h2.getHora() && minutos <= h2.getMinutos())
		return true;
	else if (hora == h2.getHora() && minutos == h2.getMinutos()
			&& segundos <= h2.getSegundos())
		return true;
	else
		return false;

}

ostream & operator <<(ostream & os, Hora h) {

	os << h.getHora() << ":" << h.getMinutos() << ":" << h.getSegundos() << "h";
	return os;

}


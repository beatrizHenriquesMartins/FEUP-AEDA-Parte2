/*
 * Taxi.cpp
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#include "Taxi.h"

int Taxi::ultinumeroTaxi = 1;

Taxi::Taxi() {

}

Taxi::Taxi(Hora horI, Hora horO) {
	horaIn = horI;
	horaOff = horO;
	rentabilidade = 0;
	numeroTaxi = ultinumeroTaxi++;
	dispo = 0;
}

Taxi::Taxi(int n, float r, Hora horI, Hora horO) {
	horaIn = horI;
	horaOff = horO;
	rentabilidade = r;
	numeroTaxi = n;
	ultinumeroTaxi = ++n;
	dispo = 0;
}

Taxi::~Taxi() {

}
//;

int Taxi::getNumeroTaxi() const {
	return numeroTaxi;
}

/*bool Taxi::getDisponivel(Hora hi, Hora hf) {
 if (hf <= horaOff && horaIn <= hi)
 return true;
 else
 return false;
 }*/

float Taxi::getRentabilidade() {
	return rentabilidade;
}

Hora Taxi::getHoraIn() {
	return horaIn;
}

Hora Taxi::getHoraOff() {
	return horaOff;
}

float Taxi::getdispo() const {
	return dispo;
}

void Taxi::setRentabilidade(float n) {
	rentabilidade += n;
}

void Taxi::changeDispo(float n) {
	dispo += n;
}

bool Taxi::operator <(const Taxi t) {
	return dispo > t.getdispo();
}

ostream & operator <<(ostream & os, Taxi t) {

	os << "Taxi numero " << t.getNumeroTaxi() << " ; "
			<< " Rentabilidade Atual: " << t.getRentabilidade() << " ; "
			<< " Disponivel entre:" << t.getHoraIn() << " e as "
			<< t.getHoraOff();
	return os;
}

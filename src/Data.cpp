/*
 * Data.cpp
 *
 *  Created on: 01/11/2016
 *      Author: Diogo Pereira
 */

#include "Data.h"
#include <time.h>

Data::Data() {

	time_t now;
	time(&now);

	tm *ltm = localtime(&now);

	dia = ltm->tm_mday;
	mes = ltm->tm_mon+1;
	ano = ltm->tm_year+1900;


}

Data::Data(int d, int m, int a) {
	if (m > 12 || m < 1)
		throw DataInvalida();
	if (m == 2) {
		if (d > 29)
			throw DataInvalida();
	}
	if (m == 4 || m == 6 || m == 9 || m == 11) {
		if (d < 1 || d > 30)
			throw DataInvalida();
	} else if (d < 1 || d > 31)
		throw DataInvalida();

	dia = d;
	mes = m;
	ano = a;
}

int Data::getDia() const {
	return dia;
}

int Data::getMes() const {
	return mes;
}

int Data::getAno() const {
	return ano;
}

void Data::setDia(int d) {
	dia = d;
}

void Data::setMes(int m) {
	mes = m;
}

void Data::setAno(int a) {
	ano = a;
}

//
string Data::toString() {
	stringstream ss;
	ss << this->getDia() << "/" << this->getMes() << "/" << this->getAno();
	return ss.str();
}
//

ostream & operator <<(ostream os, Data d) {

	os << d.getDia() << "/" << d.getMes() << "/" << d.getAno();
	return os;

}

/////

bool Data::operator <(const Data d) {

	if (ano < d.getAno())
		return true;
	else if (ano == d.getAno() && mes < d.getMes())
		return true;
	else if (ano == d.getAno() && mes == d.getMes() && dia < d.getDia())
		return true;
	else
		return false;
}


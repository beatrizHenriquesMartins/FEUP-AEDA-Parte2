/*
 * Viagem.cpp
 *
 *  Created on: 01/11/2016
 *      Author: Diogo Pereira
 */

#include "Viagem.h"

#include "Data.h"
#include "Percurso.h"

//MUDEI 2
Viagem::Viagem(Data dia, Hora horaIn, Percurso p1, string cli) {
	this->data = dia;
	this->horaIn = horaIn;
	this->deslocacao = p1;
	this->pago = false;
	this->custo = 0;
	this->cliente = cli;
}

//MUDEI 2
Viagem::Viagem(Data dia, Hora horaIn, Hora horaOut, Percurso p1, float c, string cli) {
	this->data = dia;
	this->horaIn = horaIn;
	this->horaOut = horaOut;
	this->deslocacao = p1;
	this->pago = true;
	this->custo = c;
	this->cliente = cli;
}

Viagem::~Viagem() {
}
;

Data Viagem::getData() const {
	return data;
}

/*void Viagem::setData(int d, int m, int a) {
 Data d1 = Data(d, m, a);
 this->data = d1;
 }*/

Hora Viagem::getHoraIn() const {
	return horaIn;
}

void Viagem::setHoraIn(Hora hora) {
	horaIn = hora;
}

Hora Viagem::getHoraOut() const {
	return horaOut;
}

void Viagem::setHoraOut(Hora hora) {
	horaOut = hora;
}

string Viagem::getPartida() const {
	return deslocacao.getLocalPartida();
}

void Viagem::setPartida(string localP, int dist1) {
	deslocacao.setLocalPartida(localP, dist1);
}

string Viagem::getDestino() const {
	return deslocacao.getLocalDestino();
}

void Viagem::setDestino(string localD, int dist2) {
	deslocacao.setLocalDestino(localD, dist2);
}

float Viagem::horaFinal() {

	float tempo = 1.15 * deslocacao.getDistancia();
	Hora t1(7, 15, 0), t2(9, 0, 0), t3(18, 0, 0), t4(20, 15, 0);

	if ((horaIn < t2 && t1 < horaIn) || (horaIn < t4 && t3 < horaIn))
		tempo = tempo * 1.3;

	int temp = floor(tempo);

	horaOut = horaIn.somaHoras(temp);
	return tempo;

}

float Viagem::pagarViagem() {

	float tempo = this->horaFinal();

	custo = tempo * 0.6;
	this->pago = true;

	return custo;
}

Percurso Viagem::getDeslocacao() {
	return deslocacao;
}

float Viagem::getCustoViagem() const {
	return custo;
}

string Viagem::getCliente() const {
	return cliente;

}

void Viagem::modificaCusto(float per) {
	custo = custo * per;
}

//MUDEI 2

/*bool Viagem::operator <(const Viagem v) {

	if (this->getCliente() < v.getCliente()) {
		return true;
	} else if (this->getCliente() == v.getCliente()
			&& this->getData() < v.getData()) {

		return true;
	}

	return false;
}*/
bool operator <(const Viagem v1, Viagem v2) {

	if (v1.getCliente() < v2.getCliente()) {
		return true;
	} else if (v1.getCliente() == v2.getCliente()
			&& v1.getData() < v2.getData()) {

		return true;
	}

	return false;
}


string Viagem::toString() {
	stringstream ss;
	ss << "Data: " << this->getData().toString() << " Hora Inicial: " << horaIn
			<< " Hora Final: " << horaOut << " " << deslocacao.toString()
			<< " Custo: " << this->getCustoViagem() << " Cliente: "
			<< this->getCliente();
	return ss.str();
}

ostream & operator<<(ostream & os, Viagem &v) {
	os << "Data: " << v.getData().toString() << " Hora Inicial: "
			<< v.getHoraIn() << " Hora Final: " << v.getHoraOut() << " "
			<< v.getDeslocacao().toString() << " Custo: " << v.getCustoViagem()
			<< " Cliente: " << v.getCliente();
	return os;
}

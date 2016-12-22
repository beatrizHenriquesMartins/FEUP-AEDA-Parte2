/*
 * Viagem.cpp
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#include "Viagem.h"

Viagem::Viagem() {

}

Viagem::Viagem(Data dia, Hora horaIn, Percurso p1) {
	this->data = dia;
	this->horaIn = horaIn;
	this->deslocacao = p1;
	this->pago = false;
	this->custo = 0;
}

Viagem::Viagem(Data dia, Hora horaIn, Hora horaOut, Percurso p1, float c) {
	this->data = dia;
	this->horaIn = horaIn;
	this->horaOut = horaOut;
	this->deslocacao = p1;
	this->pago = true;
	this->custo = c;
}

Viagem::~Viagem() {
}
;

Data Viagem::getData() const {
	return data;
}

Hora Viagem::getHoraIn() const {
	return horaIn;
}

Hora Viagem::getHoraOut() const {
	return horaOut;
}

string Viagem::getPartida() const {
	return deslocacao.getLocalPartida();
}

string Viagem::getDestino() const {
	return deslocacao.getLocalDestino();
}

float Viagem::getCustoViagem() const {
	return custo;
}

Percurso Viagem::getDeslocacao() {
	return deslocacao;
}

string Viagem::getCliente() const {
	return cliente;

}

void Viagem::setData(int d, int m, int a) {
	Data d1 = Data(d, m, a);
	this->data = d1;
}

void Viagem::setHoraIn(Hora hora) {
	horaIn = hora;
}

void Viagem::setHoraOut(Hora hora) {
	horaOut = hora;
}

void Viagem::setPartida(string localP, int dist1) {
	deslocacao.setLocalPartida(localP, dist1);
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

void Viagem::modificaCusto(float per) {
	custo = custo * per;
}

bool Viagem::operator <(const Viagem v) {

	if (this->getCliente() < v.getCliente()) {
		return true;
	} else if (this->getCliente() == v.getCliente()
			&& this->getData() < v.getData()) {

		return true;
	}

	return false;
}

string Viagem::toString() {
	stringstream ss;
	ss << "Data: " << this->getData().toString() << " Hora Inicial: " << horaIn
			<< " Hora Final: " << horaOut << " " << deslocacao.toString()
			<< " Custo: " << this->getCustoViagem();
	return ss.str();
}

ostream & operator<<(ostream & os, Viagem &v) {
	os << "Data: " << v.getData().toString() << " Hora Inicial: "
			<< v.getHoraIn() << " Hora Final: " << v.getHoraOut() << " "
			<< v.getDeslocacao().toString() << " Custo: " << v.getCustoViagem();
	return os;
}

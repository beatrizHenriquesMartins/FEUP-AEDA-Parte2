/*
 * Percurso.cpp
 *
 *  Created on: 01/11/2016
 *      Author: Diogo
 */

#include "Percurso.h"

Percurso::Percurso() {

}

Percurso::Percurso(string localPart, string localDest, int distancia) {
	this->localPartida = localPart;
	this->localDestino = localDest;
	this->distancia = distancia;
}

string Percurso::getLocalPartida() const {
	return localPartida;
}

string Percurso::getLocalDestino() const {
	return localDestino;
}

int Percurso::getDistancia() const {
	return distancia;
}

void Percurso::setLocalPartida(string localPart, int dist) {
	this->localPartida = localPart;
	this->distancia = distancia;
}

void Percurso::setLocalDestino(string localDest, int dist) {
	this->localDestino = localDest;
	this->distancia = distancia;
}

void Percurso::setDistancia(int distancia) {
	this->distancia = distancia;
}


string Percurso::toString() {
	stringstream ss;
	ss << "Percurso: " << localPartida << "-" << localDestino
				<< " Distancia: " << distancia;
	return ss.str();
}

ostream & operator <<(ostream os, Percurso p) {

	os << "Percurso: " << p.getLocalPartida() << "-" << p.getLocalDestino()
			<< " Distancia: " << p.getDistancia();
	return os;
}

/*
 * Percurso.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef PERCURSO_H_
#define PERCURSO_H_

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Percurso {
private:
	string localPartida;
	string localDestino;
	int distancia;
public:
	Percurso();
	Percurso(string localPart, string localDest, int distancia);

	string getLocalPartida() const;
	string getLocalDestino() const;
	int getDistancia() const;

	void setLocalPartida(string localPart, int dist);
	void setLocalDestino(string localDest, int dist);
	void setDistancia(int distancia);

	string toString();
	friend ostream & operator <<(ostream os, Percurso p);
};



#endif /* PERCURSO_H_ */

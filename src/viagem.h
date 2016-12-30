/*
 * Viagem.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef VIAGEM_H_
#define VIAGEM_H_

#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>

#include "Hora.h"
#include "Data.h"
#include "Percurso.h"

using namespace std;

class Viagem {
private:
	Data data;
	Hora horaIn;
	Hora horaOut;
	Percurso deslocacao;
	float custo;
	bool pago;
	string cliente; /////

public:
	Viagem();
	Viagem(Data dia, Hora horaIn, Percurso p1);
	Viagem(Data dia, Hora horaIn, Hora horaOut, Percurso p1, float c);

	~Viagem();

	Data getData() const;
	Hora getHoraIn() const;
	Hora getHoraOut() const;
	string getPartida() const;
	string getDestino() const;
	float getCustoViagem() const;
	Percurso getDeslocacao();
	string getCliente() const;

	void setData(int d, int m, int a);
	void setHoraIn(Hora hora);
	void setHoraOut(Hora hora);
	void setPartida(string localP, int dist1);
	void setDestino(string localD, int dist2);

	float horaFinal();

	float pagarViagem();

	void modificaCusto(float per);

	bool operator <(const Viagem v);

	string toString();
	friend ostream & operator <<(ostream & os, Viagem &v);
};

#endif /* VIAGEM_H_ */

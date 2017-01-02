/*
 * Taxi.h
 *
 *  Created on: 30/10/2016
 *      Author: Beatriz de Henriques Martins
 */

#ifndef SRC_TAXI_H_
#define SRC_TAXI_H_

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
	/**
	 * @brief construtor da classe Taxi sem parametros
	 */
	Taxi();

	/**
	 * @brief construtor da classe Taxi com parametros
	 * @param horI - hora inicio
	 * @param horO - hora final
	 */
	Taxi(Hora horI, Hora horO);

	/**
	 * @brief construtor da classe Taxi com parametros
	 * @param n - número taxi
	 * @param r - rentabilidade
	 * @param horI - hora inicio
	 * @param horO - hora final
	 */
	//Rodas
	Taxi(int n, float r, Hora horI, Hora horO, float dis);

	/**
	 * @brief função destrutora de taxi
	 */
	~Taxi();

	/**
	 * @brief função para obter número do taxi
	 * @return retorna número do taxi
	 */
	int getNumeroTaxi() const;

	/**
	 * @brief função para obter disponibilidade
	 * @return retorna disponibilidade
	 */
	bool inHorario(Hora hi, Hora hf);

	/**
	 * @brief função para obter Rentabilidade
	 * @return retorna Rentabilidade
	 */
	float getRentabilidade();

	/**
	 * @brief função para actulizar rentabilidade
	 * @param n - rentabilidade
	 */
	void setRentabilidade(float n);

	/**
	 * @brief função para obter hora de inicio
	 * @return retorna hora de inicio
	 */
	Hora getHoraIn();

	/**
	 * @brief função para obter hora final
	 * @return retorna hora final
	 */
	Hora getHoraOff();

	/**
	 * @brief função operador<< impressão para taxi com formatação especifica
	 * @param os - ostream
	 * @param t -taxi
	 * @return string taxi
	 */
	friend ostream & operator <<(ostream & os, Taxi t);

	/**
	 * @brief função para obter a disponibilidade do taxi
	 * @return float dispo - disponibilidade
	 */
	float getdispo() const;

	/**
	 * @brief função que permite mudar a disponibilidade do Taxi
	 * @param float n - valor
	 */
	void changeDispo(float n);

	/**
	 * @brief operador menor
	 * @param t - Taxi
	 * @return bool, true se o taxi tiver rendimentos menores do que o outro, false se se verificar o ontrário
	 */
	bool operator <(const Taxi t);

};

class Taxipointer {
	Taxi* tp;
public:
	/**
	 * @brief contrutor classe de pointer para Taxi
	 * @param t - Taxi* que lhe deu origem
	 */
	Taxipointer(Taxi* t){
		tp= t;
	}
	;


	/**
	 * @brief função para obter um Taxi* atrav�s da classe Taxipointer
	 * @return tp -Taxi*
	 */

	 Taxi* getTaxipointer()const {
			return tp;
		}
		;

	/**
	 * @brief operador menor
	 * @param ta - Taxipointer
	 * @return bool, true se o taxi apontado por Taxipointer tiver rendimentos menores do que o outro, false se se verificar o ontrário
	 */
	bool operator <(const Taxipointer & t2) const
	{

		return tp->getdispo() > t2.getTaxipointer()->getdispo();

	}
};




class TaxisIndisponiveis {
	string razao;
public:
	/**
	 * @brief contrutor classe excessão de Taxi
	 * @param r - razao da excessão
	 */
	TaxisIndisponiveis(string r) {
		razao = r;
	}
	;

	/**
	 * @brief função para obter r que provocou excessão
	 * @return r -razão
	 */
	string getRazao() {
		return razao;
	}
	;
};

#endif /* SRC_TAXI_H_ */

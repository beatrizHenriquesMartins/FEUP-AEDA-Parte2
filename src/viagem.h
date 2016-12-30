/*
 * Viagem.h
 *
 *  Created on: 01/11/2016
 *      Author: Diogo Pereira
 */

#ifndef SRC_VIAGEM_H_
#define SRC_VIAGEM_H_

#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>

#include "Hora.h"
#include "Data.h"
#include "Percurso.h"
#include "Cliente.h"

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

	/**
	 * @brief fun√ß√£o construtor Viagem
	 * @param dia - data
	 * @param horaIn - hora inicio
	 * @param p1 - percurso
	 */
	Viagem(Data dia, Hora horaIn, Percurso p1);

	/**
	 * @brief fun√ß√£o construtor Viagem
	 * @param dia - data
	 * @param horaIn - hora inicio
	 * @param horaOut - hora fim
	 * @param p1 - percurso
	 * @param c - custo
	 */
	Viagem(Data dia, Hora horaIn, Hora horaOut, Percurso p1, float c);

	/**
	 * @brief fun√ß√£o destrutora de viagem
	 */
	~Viagem();

	/**
	 * @brief fun√ß√£o para obter data
	 * @return data
	 */
	Data getData() const;

	/**
	 * @brief fun√ß√£o que actualiza data
	 * @param data - data
	 */
	void setData(int d, int m, int a);

	/**
	 * @brief fun√ß√£o para obter hora de inicio
	 * @return hora de inicio
	 */
	Hora getHoraIn() const;

	/**
	 * @brief fun√ß√£o que actualiza hora de inicio
	 * @param hora - hora de inicio
	 */
	void setHoraIn(Hora hora);

	/**
	 * @brief fun√ß√£o para obter hora de fim
	 * @return hora de fim
	 */
	Hora getHoraOut() const;

	/**
	 * @brief fun√ß√£o que actualiza hora de fim
	 * @param hora - hora de fim
	 */
	void setHoraOut(Hora hora);

	/**
	 * @brief fun√ß√£o para obter partida
	 * @return partida
	 */
	string getPartida() const;

	/**
	 * @brief fun√ß√£o que actualiza partida
	 * @param localP - local partida
	 * @param dist1 - distancia
	 */
	void setPartida(string localP, int dist1);

	/**
	 * @brief fun√ß√£o para obter destino
	 * @return destino
	 */
	string getDestino() const;

	/**
	 * @brief fun√ß√£o que actualiza partida
	 * @param localD - local destino
	 * @param dist2 - distancia
	 */
	void setDestino(string localD, int dist2);

	/**
	 * @brief fun√ß√£o que calcula a hora final da viagem
	 * @return hora final
	 */
	float horaFinal();

	/**
	 * @brief fun√ß√£o que calcula o custo da viagem
	 * @return custo
	 */
	float pagarViagem();

	/**
	 * @brief fun√ß√£o para obter custo viagem
	 * @return custo viagem
	 */
	float getCustoViagem() const;

	/**
	 * @brief fun√ß√£o para obter o cliente associado a viagem
	 * @return cliente que fez a viagem
	 */
	string getCliente() const;

	/**
	 * @brief fun√ß√£o que calcula custo viagem com desconto
	 * @param per - percentagem
	 */
	void modificaCusto(float per);

	/**
	 * @brief fun√ß√£o para obter percurso
	 * @return percurso
	 */
	Percurso getDeslocacao();
    /**
     * @brief funcao que permite comparar duas viagens atraves do operador menor
     * @return bool indicando true se a viagem for menor com aquela a que est· a ser comparada
     */
    bool operator <(const Viagem v);

	/**
	 * @brief fun√ß√£o para imprimir detalhes viagem com formata√ß√£o especifica
	 * @return string viagem
	 */
	string toString();


	/**
	 * @brief fun√ß√£o operador<< impress√£o para detalhes viagem com formata√ß√£o especifica
	 * @param os - ostream
	 * @param v - viagem
	 * @return string viagem
	 */
	friend ostream & operator <<(ostream & os, Viagem &v);

};

#endif /* SRC_VIAGEM_H_ */

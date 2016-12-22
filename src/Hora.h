/* * Hora.h
 *
 *  Created on: 08/11/2016
 *      Author: Pedro Silva
 */

#ifndef SRC_HORA_H_
#define SRC_HORA_H_

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Hora {
	int hora;
	int minutos;
	int segundos;

public:
	/**
	 * @brief construtor da classe Hora vazio
	 */
	Hora();

	/**
	 * @brief construtor da classe Hora com parametros
	 * @param h - hora
	 * @param m - minuto
	 * @param s - segundo
	 */
	Hora(int h, int m, int s);

	/**
	 * @brief função para obter hora
	 * @return hora
	 */
	int getHora() const;

	/**
	 * @brief função para obter minutos
	 * @return minutos
	 */
	int getMinutos() const;

	/**
	 * @brief função para obter segundos
	 * @return segundos
	 */
	int getSegundos() const;

	/**
	 * @brief função que soma minutos a uma determinada hora
	 * @param min - minutos
	 * @return h - hora
	 */
	Hora somaHoras(int min);

	/**
	 * @brief função para imprimir hora com formatação especifica
	 * @return string hora
	 */
	string toString();

	/**
	* @brief função verifica se uma hora é menor do que a outra
	* @param h2 - 2ºhora
	* @return true - algum caso ocorra, false - caso não ocorra nenhum
	*/
	bool operator <(Hora h2);

	/**
	* @brief função verifica se uma hora é menor ou igual a outra
	* @param h2 - 2ºhora
	* @return true - algum caso ocorra, false - caso não ocorra nenhum
	*/
	bool operator <=(Hora h2);

	/**
	 * @brief função operador<< impressão para hora com formatação especifica
	 * @param os - ostream
	 * @param h - hora
	 * @return string hora
	 */
	friend ostream & operator <<(ostream & os, Hora h);
};

class HoraInvalida {
	string razao;
public:

	/**
	 * @brief contrutor classe excessão de Hora
	 * @param r
	 */
	HoraInvalida(string r) {
		razao = r;
	}
	;

	/**
	 * @brief função para obter r que provocou excessão
	 * @return r
	 */
	string getRazao() {
		return razao;
	}
	;
};

#endif /* SRC_HORA_H_ */

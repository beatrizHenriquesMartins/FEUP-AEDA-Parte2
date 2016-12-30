/*
 * Data.h
 *
 *  Created on: 01/11/2016
 *      Author: Diogo Pereira
 */

#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Data {
	int dia;
	int mes;
	int ano;

public:
	/**
	 * @brief construtor da classe Data vazio
	 */
	Data();

	/**
	 * @brief construtor da classe Data com parametros
	 * @param d - dia
	 * @param m - mes
	 * @param a - ano
	 */
	Data(int d, int m, int a);

	/**
	 * @brief função para obter dia
	 * @return dia
	 */
	int getDia() const;

	/**
	 * @brief função para obter mes
	 * @return mes
	 */
	int getMes() const;

	/**
	 * @brief função para obter ano
	 * @return ano
	 */
	int getAno() const;

	/**
	 * @brief função que actualiza dia
	 * @param d- dia
	 */
	void setDia(int d);

	/**
	 * @brief função que actualiza mes
	 * @param m - mes
	 */
	void setMes(int m);

	/**
	 * @brief função que actualiza ano
	 * @param a - ano
	 */
	void setAno(int a);

	/**
	 * @brief função para imprimir data com formatação especifica
	 * @return string data
	 */
	string toString();

	/**
	 * @brief função operador<< impressão para data com formatação especifica
	 * @param os - ostream
	 * @param d -data
	 * @return string data
	 */
	friend ostream & operator <<(ostream os, Data d);

	/**
	 * @brief funcao que permite comparar duas datas atraves do operador menor
	 * @return bool indicando true se a data for menor com aquela a que está a ser comparada
	 */
	bool operator <(const Data d);
};

class DataInvalida {
public:
	/**
	 * @brief função classe excessão
	 */
	void dataErrada() {
		cout << "Data invalida" << endl;
	}

};
#endif /* SRC_DATA_H_ */

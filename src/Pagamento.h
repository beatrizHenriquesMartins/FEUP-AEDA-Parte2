/*
 * Pagamento.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef PAGAMENTO_H_
#define PAGAMENTO_H_

#include <string>
#include <vector>

using namespace std;

class Pagamento {
private:
	float dinheiro;
	string tipo;

public:
	/**
	 * @brief construtor da classe Pagamento vazio
	 */
	Pagamento();

	/**
	 * @brief construtor da classe Pagamento com parametros
	 * @param t - tipo
	 */
	Pagamento(string t);

	/**
	 * @brief função para obter valor a pagar
	 * @return valor a pagar
	 */
	float getTotal();

	/**
 * @brief função para obter tipo de pagamento
 * @return tipo de pagamento
 */
	string getTipo();

	/**
	 * @brief função que calcula o valor total a pagar
	 * @param n - valor a somar ao total
	 */
	void changeTotal(float n);

	/**
	 * @brief função que altera o tipo de pagamento
	 * @param tipo - novo tipo de pagamento
	 */
	void changeTipo(string t);
};

#endif /* PAGAMENTO_H_ */

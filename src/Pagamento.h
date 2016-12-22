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
	Pagamento();
	Pagamento(string t);

	float getTotal();
	string getTipo();

	void changeTotal(float n);
	void changeTipo(string t);
};

#endif /* PAGAMENTO_H_ */

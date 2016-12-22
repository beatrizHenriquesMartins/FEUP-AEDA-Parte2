/*
 * Pagamento.cpp
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#include "Pagamento.h"

Pagamento::Pagamento() {
	tipo = "indefinido";
	dinheiro = 0;
}

Pagamento::Pagamento(string t) {
	tipo = t;
	dinheiro = 0;
}

float Pagamento::getTotal() {
	return dinheiro;
}

string Pagamento::getTipo() {
	return tipo;
}

void Pagamento::changeTotal(float n) {
	dinheiro += n;
}

void Pagamento::changeTipo(string t) {
	tipo = t;

}

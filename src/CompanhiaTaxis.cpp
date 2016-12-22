/*
 * CompanhiaTaxis.cpp
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#include "CompanhiaTaxis.h"
#include "Cliente.h"

#include <vector>

CompanhiaTaxis::CompanhiaTaxis() {
	this->capital = 0;
}

CompanhiaTaxis::CompanhiaTaxis(string n, float c) {
	this->nome = n;
	this->capital = c;
}

string CompanhiaTaxis::getNome() {
	return nome;
}

float CompanhiaTaxis::getCapital() {
	return capital;
}

void CompanhiaTaxis::somaCapital(float n) {
	capital += n;
}

vector<Cliente *> CompanhiaTaxis::getClientes() const {
	return clientes;
}

vector<Taxi> CompanhiaTaxis::getTaxisTotais() const {
	return taxisTotais;
}

priority_queue<Taxi> CompanhiaTaxis::getTaxis() const {
	return taxis;
}

void CompanhiaTaxis::adicionaTaxi(Hora horI, Hora horO) {
	Taxi t(horI, horO);
	capital -= 500;
	taxis.push(t);
}

void CompanhiaTaxis::setTaxis(priority_queue<Taxi> t) {
	taxis = t;

}

Taxi* CompanhiaTaxis::procuraTaxi(int n) const {
	if (taxis.size() == 0)
		throw TaxisIndisponiveis();

	priority_queue<Taxi> aux = taxis;

	while (!aux.empty()) {

		Taxi t = aux.top();

		if (t.getNumeroTaxi() == n) {
			return t;
		}

		aux.pop();
	}

	throw TaxisIndisponiveis();
}

void CompanhiaTaxis::removeTaxi(int n) {
	Taxi *t;
	t = procuraTaxi(n);

	t->getRentabilidade();

	capital += t->getRentabilidade();

	priority_queue<Taxi> aux;

	while (!taxis.empty()) {

		Taxi t = taxis.top();

		if (t.getNumeroTaxi() == n) {

			taxis.pop();
			continue;
		}

		aux.push(t);
		taxis.pop();
	}

}

void CompanhiaTaxis::setClientes(vector<Cliente*> c) {
	this->clientes = c;
}

void CompanhiaTaxis::concaClientes(vector<Cliente*> c) {

	clientes.insert(clientes.end(), c.begin(), c.end());
}

void CompanhiaTaxis::setPercursos(vector<Percurso*> p) {
	percursosDisponiveis = p;
}

vector<Percurso*> CompanhiaTaxis::getPercursos() const {
	return percursosDisponiveis;

}
void CompanhiaTaxis::adicionaClienteParticular(string nome, string morada,
		string email, int nT, int nif, string tipoPagamento) {
	Cliente *c = new Particular(nome, morada, email, nT, nif, tipoPagamento);
	clientes.push_back(c);
}

void CompanhiaTaxis::adicionaClienteEmpresa(string nome, string morada,
		string email, int nT, int nif, string tipoPagamento,
		int numFuncionarios) {
	Cliente *c = new Empresa(nome, morada, email, nT, nif, tipoPagamento,
			numFuncionarios);
	clientes.push_back(c);
}

bool CompanhiaTaxis::removeCliente(int id) {
	int ind;
	ind = procuraCliente(id);

	if (ind == -1) {
		return false;
	}

	/*
	 vector<Cliente*>::iterator itBegin = clientes.begin();

	 clientes.erase(itBegin + ind);
	 */

	clientes.erase(clientes.begin() + ind);

	return true;
}

int CompanhiaTaxis::procuraCliente(int id) const {
	if (clientes.size() == 0) {
		return -1;
	}

	vector<int> aux;

	for (unsigned int i = 0; i < clientes.size(); i++) {
		aux.push_back(clientes[i]->getID());
	}

	int ind;
	ind = sequentialSearch(aux, id);

	if (ind == -1) {
		return -1;
	}

	return ind;
}

int CompanhiaTaxis::ultimoIDcliente() {
	int ind;
	ind = clientes.size() - 1;

	return clientes[ind]->getID() + 1;
}

void CompanhiaTaxis::fazerViagemOcasional(Data dia, Hora horaIn, Percurso p1) {

	Viagem v(dia, horaIn, p1);
	v.horaFinal();

	Taxi t = taxis.top();
	taxis.pop();

	t.changeDispo(v.horaFinal());

	t.setRentabilidade(v.pagarViagem());
	taxis.push(t);

	return;
	throw TaxisIndisponiveis("Nao existem taxis de momento disponiveis");
}

void CompanhiaTaxis::fazerViagemCliente(int id, Data dia, Hora horaIn,
		Percurso p1, bool disc, float per) {

	Viagem v(dia, horaIn, p1);
	v.horaFinal();
	v.pagarViagem();
	for (unsigned int j = 0; j < clientes.size(); j++) {
		if (clientes[j]->getID() == id) {

			for (unsigned int i = 0; i < taxisTotais.size(); i++) {

				if (taxisTotais[i].getDisponivel(horaIn, v.getHoraOut())) {

					if (disc)
						v.modificaCusto(clientes[j]->giveMonthlyPromotion(per));
					clientes[j]->addViagemHistorico(v);
					clientes[j]->aumentaPontos();
					clientes[j]->addViagemMensal(v);
					if (clientes[j]->getCusto().getTipo() == "fim_do_mes") {
						if (clientes[j]->getPontos() > 50) {
							clientes[j]->resetPontos();
							return;
						}
						return;
					}
					if (clientes[j]->getCusto().getTipo() == "credito") {

						if (clientes[j]->getPontos() > 50) {
							clientes[j]->resetPontos();
							return;
						}
						clientes[j]->changeCustoTotal(v.pagarViagem() * 1.05);
						taxisTotais[i].setRentabilidade(v.pagarViagem() * 1.05);
						return;
					} else {
						v.pagarViagem();
						if (clientes[j]->getPontos() > 50) {
							clientes[j]->resetPontos();
							return;
						}
						clientes[j]->changeCustoTotal(v.pagarViagem());
						taxisTotais[i].setRentabilidade(v.pagarViagem());
						return;
					}
				}

			}
			throw TaxisIndisponiveis(
					"Nao existem taxis de momento disponiveis");
		}
	}

	throw ClienteInexistente(id);

}

void CompanhiaTaxis::cobrarPagamentoMensal() {

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->getCusto().getTipo() == "fim_do_mes")
			capital += clientes[i]->fimdoMes();

		clientes[i]->resetMes();
	}

	for (unsigned int j = 0; j < taxisTotais.size(); j++) {
		capital += taxisTotais[j].getRentabilidade();
		float n = -1 * (taxisTotais[j].getRentabilidade());
		taxisTotais[j].setRentabilidade(n);
	}
}

void CompanhiaTaxis::mostrarClientesPorCapital() {
	vector<Cliente> v;

	for (unsigned int i = 0; i < clientes.size(); i++) {
		v.push_back(*(clientes[i]));
	}

	/*vector<Cliente>::iterator it = v.begin();
	 vector<Cliente>::iterator ite = v.end();
	 sort(it, ite);
	 reverse(it, ite);
	 for (; it != ite; it++) {
	 cout << (*it).mostrarCliente() << endl;
	 }*/

	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());

	for (unsigned int j = 0; j < v.size(); j++) {
		cout << v[j].mostrarCliente() << endl;
	}

}

bool compaID(Cliente c1, Cliente c2) {
	if (c1.getID() < c2.getID())
		return true;
	else
		return false;
}

void CompanhiaTaxis::mostrarClientesPorID() {

	vector<Cliente> v;

	for (unsigned int i = 0; i < clientes.size(); i++) {
		v.push_back(*(clientes[i]));
	}

	/*
	 vector<Cliente>::iterator it = v.begin();
	 vector<Cliente>::iterator ite = v.end();

	 sort(it, ite, compaID);

	 for (; it != ite; it++) {
	 cout << (*it).mostrarCliente() << endl;
	 }
	 */

	sort(v.begin(), v.end(), compaID);

	for (unsigned int j = 0; j < v.size(); j++) {
		cout << v[j].mostrarCliente() << endl;
	}
}

void CompanhiaTaxis::mostrarTaxis() {

	if (taxis.size() == 0)
		throw TaxisIndisponiveis();

	priority_queue<Taxi> aux = taxis;

	while (!aux.empty()) {

		Taxi t = aux.top();

		cout << t << endl;

		aux.pop();
	}
}


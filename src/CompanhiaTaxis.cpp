/*
 * CompanhiaTaxis.cpp
 *
 *  Created on: 17/10/2016
 *      Author: Pedro Silva
 */

#include "CompanhiaTaxis.h"
#include <algorithm>

CompanhiaTaxis::CompanhiaTaxis() {
	capital = 0;
}

CompanhiaTaxis::CompanhiaTaxis(string n, float c) {
	nome = n;
	capital = c;

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

void CompanhiaTaxis::adicionaTaxi(Hora horI, Hora horO) {
	Taxi t(horI, horO);
	capital -= 500;
	taxisTotais.push_back(t);
}

void CompanhiaTaxis::setTaxis(vector<Taxi> t)
{
	taxisTotais=t;

}

int CompanhiaTaxis::procuraTaxi(int n) const {
	if (taxisTotais.size() == 0) {
		return -1;
	}

	vector<int> aux;

	for (unsigned int i = 0; i < taxisTotais.size(); i++) {
		aux.push_back(taxisTotais[i].getNumeroTaxi());
	}

	int ind;
	ind = sequentialSearch(aux, n);

	if (ind == -1) {
		return -1;
	}

	return ind;
}

bool CompanhiaTaxis::removeTaxi(int n) {
	int ind;
	ind = procuraTaxi(n);

	if (ind == -1) {
		return false;
	}

	vector<Taxi>::iterator itBegin = taxisTotais.begin();

	capital += taxisTotais[ind].getRentabilidade();
	taxisTotais.erase(itBegin + ind);

	return true;
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

	vector<Cliente*>::iterator itBegin = clientes.begin();

	clientes.erase(itBegin + ind);

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
	for (unsigned int i = 0; i < taxisTotais.size(); i++) {
		if (taxisTotais[i].getDisponivel(horaIn, v.getHoraOut())) {

			taxisTotais[i].setRentabilidade(v.pagarViagem());
			return;
		}
	}
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

	for (unsigned int i = 0; i < clientes.size(); i++)
		v.push_back(*(clientes[i]));

	vector<Cliente>::iterator it = v.begin();
	vector<Cliente>::iterator ite = v.end();

	sort(it, ite);
	reverse(it, ite);

	for (; it != ite; it++) {
		cout << (*it).mostrarCliente() << endl;
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

	for (unsigned int i = 0; i < clientes.size(); i++)
		v.push_back(*(clientes[i]));

	vector<Cliente>::iterator it = v.begin();
	vector<Cliente>::iterator ite = v.end();

	sort(it, ite, compaID);
	for (; it != ite; it++) {
		cout << (*it).mostrarCliente() << endl;
	}

}

void CompanhiaTaxis::mostrarTaxis() {

	vector<Taxi>::iterator it = taxisTotais.begin();
	vector<Taxi>::iterator ite = taxisTotais.end();

	for (; it != ite; it++) {
		cout << (*it) << endl;
	}
}

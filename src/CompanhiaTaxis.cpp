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
	Viagem null = Viagem(Data(1, 1, 1), Hora(0, 0, 0), Percurso("", "", 0));
	BST<Viagem> viagens(null);
}

CompanhiaTaxis::CompanhiaTaxis(string n, float c) {
	this->nome = n;
	this->capital = c;
	Viagem null = Viagem(Data(1, 1, 1), Hora(0, 0, 0), Percurso("", "", 0));
	BST<Viagem> viagens(null);
}

string CompanhiaTaxis::getNome() {
	return nome;
}

float CompanhiaTaxis::getCapital() {
	return capital;
}

vector<Cliente *> CompanhiaTaxis::getClientes() const {
	return clientes;
}

priority_queue<Taxi> CompanhiaTaxis::getTaxis() const {
	return taxis;
}

vector<Percurso*> CompanhiaTaxis::getPercursos() const {
	return percursosDisponiveis;

}

tabCli CompanhiaTaxis::getInativos() const {
	return this->inativos;
}

void CompanhiaTaxis::setTaxis(priority_queue<Taxi> t) {
	taxis = t;
}

void CompanhiaTaxis::setPercursos(vector<Percurso*> p) {
	percursosDisponiveis = p;
}

void CompanhiaTaxis::setClientes(vector<Cliente*> c) {
	this->clientes = c;
}

void CompanhiaTaxis::somaCapital(float n) {
	capital += n;
}

void CompanhiaTaxis::adicionaTaxi(Hora horI, Hora horO) {
	Taxi t(horI, horO);
	capital -= 500;
	taxis.push(t);
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

bool CompanhiaTaxis::removeTaxi(int n) {
	Taxi *t;
	t = procuraTaxi(n);

	t->getRentabilidade();

	capital += t->getRentabilidade();

	priority_queue<Taxi> aux;

	while (!taxis.empty()) {

		Taxi t = taxis.top();

		if (t.getNumeroTaxi() == n) {

			taxis.pop();
			break;
		}

		aux.push(t);
		taxis.pop();
	}

	while (!aux.empty()) {
		taxis.push(aux.top());
		aux.pop();
	}

	return true;
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

void CompanhiaTaxis::removeClienteTabela(Cliente c) {
	inativos.erase(inativos.find(c), inativos.end()); //erasing by range
}

Taxi* CompanhiaTaxis::procuraTaxi(int n) const {
	if (taxis.size() == 0) {
		throw TaxisIndisponiveis();
	}

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

	Taxi* t = this->proximoTaxi(v);

	t->changeDispo(v.horaFinal());

	t->setRentabilidade(v.pagarViagem());
	taxis.push(*t);

}

void CompanhiaTaxis::fazerViagemCliente(int id, Data dia, Hora horaIn,
		Percurso p1, bool disc, float per, string tipoPag) {
	Viagem v(dia, horaIn, p1);
	v.horaFinal();
	v.pagarViagem();
	for (unsigned int j = 0; j < clientes.size(); j++) {
		if (clientes[j]->getID() == id) {

			Taxi* t = this->proximoTaxi(v);

			if (disc)
				v.modificaCusto(clientes[j]->giveMonthlyPromotion(per));

			clientes[j]->addViagemHistorico(v);
			clientes[j]->aumentaPontos();
			clientes[j]->addViagemMensal(v);
			if (clientes[j]->getCusto().getTipo() == "fim_do_mes") {
				clientes[j]->addViagemMensalFimDoMes(v);
				if (clientes[j]->getPontos() > 50) {
					clientes[j]->resetPontos();
					taxis.push(*t);
					return;
				}
				taxis.push(*t);
				return;
			}
			if (clientes[j]->getCusto().getTipo() == "credito") {

				if (clientes[j]->getPontos() > 50) {
					clientes[j]->resetPontos();
					taxis.push(*t);
					return;
				}
				clientes[j]->changeCustoTotal(v.pagarViagem() * 1.05);
				t->setRentabilidade(v.pagarViagem() * 1.05);
				taxis.push(*t);
				return;
			} else {
				v.pagarViagem();
				if (clientes[j]->getPontos() > 50) {
					clientes[j]->resetPontos();
					taxis.push(*t);
					return;
				}
				clientes[j]->changeCustoTotal(v.pagarViagem());
				t->setRentabilidade(v.pagarViagem());
				taxis.push(*t);
				return;
			}
		}

	}

	throw ClienteInexistente(id);
}

void CompanhiaTaxis::cobrarPagamentoMensal() {
	resetTabelaClientes(); //
	criarTabelaClientes(); //

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->getCusto().getTipo() == "fim_do_mes")
			capital += clientes[i]->fimdoMes();

		clientes[i]->resetMes();
	}

	priority_queue<Taxi> aux;

	while (!taxis.empty()) {

		Taxi t = taxis.top();

		capital += t.getRentabilidade();
		float n = -1 * (t.getRentabilidade());
		t.setRentabilidade(n);

		aux.push(t);
		taxis.pop();
	}

	while (!aux.empty()) {
		taxis.push(aux.top());
		aux.pop();
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

	if (taxis.size() == 0) {
		throw TaxisIndisponiveis();
	}

	priority_queue<Taxi> aux = taxis;

	while (!aux.empty()) {

		Taxi t = aux.top();

		cout << t << endl;

		aux.pop();
	}
}

void CompanhiaTaxis::concaClientes(vector<Cliente*> c) {

	clientes.insert(clientes.end(), c.begin(), c.end());
}

void CompanhiaTaxis::criarTabelaClientes() {
	vector<Cliente*> aux;

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->getViagensMensais().size() == 0) {
			this->inativos.insert(clientes[i]);
			aux.push_back(clientes[i]);
		}
	}

	for (unsigned int k = 0; k < aux.size(); k++) {
		/*for (unsigned int j = 0; j < clientes.size(); j++) {
		 if (aux[k]->getID() == clientes[j]->getID()
		 && aux[k]->getNIF() == clientes[j]->getNIF()
		 && aux[k]->getMorada() == clientes[j]->getMorada()
		 && aux[k]->getMorada() == clientes[j]->getMorada()
		 && aux[k]->getEmail() == clientes[j]->getEmail()
		 && aux[k]->getNumeroTelemovel()
		 == clientes[j]->getNumeroTelemovel()
		 && aux[k]->getNomeC() == clientes[j]->getNomeC()) {
		 clientes.erase(clientes.begin() + j);
		 break;
		 }
		 }*/
		this->removeCliente(aux[k]->getID());
	}
}

void CompanhiaTaxis::resetTabelaClientes() {
	inativos.clear();
}

/*
 bool CompanhiaTaxis::verficaClienteTabela(int id) {
 Cliente* c; //= Cliente(id, "a", "b", "c", -1, -1, -1, "d");
 c->setID(id);

 //typedef unordered_set<Cliente, HashCli, EqualCli>::iterator
 itTabCli = inativos.find(*c);

 if (itTabCli == inativos.end()) {

 }
 }
 */

//////BST////////77
BST<Viagem> CompanhiaTaxis::getViagens() {
	return this->viagens;
}

void CompanhiaTaxis::addViagemBST(Viagem &v) {
	viagens.insert(v);
}

void CompanhiaTaxis::mostrarViagensBST() {
	BSTItrIn<Viagem> it(viagens);
	while (!it.isAtEnd()) {
		cout << it.retrieve() << endl;
		it.advance();
	}
}

Taxi* CompanhiaTaxis::proximoTaxi(Viagem v) {

	Taxi res;
	priority_queue<Taxi> aux;

	while (!taxis.empty()) {

		Taxi t = taxis.top();

		if (t.inHorario(v.getHoraIn(), v.getHoraOut())) {

			taxis.pop();
			res = t;
			break;
		}

		aux.push(t);
		taxis.pop();
	}

	while (!aux.empty()) {
		taxis.push(aux.top());
		aux.pop();
	}

	if (res.getNumeroTaxi() == 0)
		throw TaxisIndisponiveis();
	else
		return res;
}

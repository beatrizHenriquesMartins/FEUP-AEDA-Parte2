/*
 * CompanhiaTaxis.cpp
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#include "CompanhiaTaxis.h"
#include "Cliente.h"

#include <vector>

//MUDEI 2
CompanhiaTaxis::CompanhiaTaxis():viagens(Viagem(Data(1, 1, 1), Hora(0, 0, 0), Percurso("", "", 0), "Ninguem")), viagens_ocasionais(Viagem(Data(1, 1, 1), Hora(0, 0, 0), Percurso("", "", 0), "Ninguem")) {
	this->capital = 0;
}


//MUDEI 2
CompanhiaTaxis::CompanhiaTaxis(string n, float c):viagens(Viagem(Data(1, 1, 1), Hora(0, 0, 0), Percurso("", "", 0), "Ninguem")), viagens_ocasionais(Viagem(Data(1, 1, 1), Hora(0, 0, 0), Percurso("", "", 0), "Ninguem")) {
	this->nome = n;
	this->capital = c;
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

priority_queue<Taxipointer> CompanhiaTaxis::getTaxis() const {
	return taxis;
}

vector<Percurso*> CompanhiaTaxis::getPercursos() const {
	return percursosDisponiveis;

}

tabCli CompanhiaTaxis::getInativos() const {
	return this->inativos;
}

//MUDEI
tabCli CompanhiaTaxis::getAtivos() const {
	return this->ativos;
}

void CompanhiaTaxis::setTaxis(priority_queue<Taxipointer> t) {
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
	Taxi* t = new Taxi(horI, horO);
	capital -= 500;
	Taxipointer ta(t);
	taxis.push(ta);
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

void CompanhiaTaxis::removeTaxi(int n) {
	Taxi *t;
	t = procuraTaxi(n);

	t->getRentabilidade();

	capital += t->getRentabilidade();

	priority_queue<Taxipointer> aux;

	while (!taxis.empty()) {

		Taxipointer t = taxis.top();
		Taxi ta = *(t.getTaxipointer());
		if (ta.getNumeroTaxi() == n) {

			taxis.pop();
			break;
		}

		aux.push(taxis.top());
		taxis.pop();
	}

	while (!aux.empty()) {
		taxis.push(aux.top());
		aux.pop();
	}

	cout << "Taxi Removido" << endl;
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

//MUDEI
void CompanhiaTaxis::removeClienteInativo(Cliente* c) {
	this->inativos.erase(inativos.find(c), inativos.end()); //erasing by range
}

void CompanhiaTaxis::removeClienteAtivo(Cliente* c) {
	this->inativos.erase(inativos.find(c), inativos.end()); //erasing by range
}

Taxi* CompanhiaTaxis::procuraTaxi(int n) const {
	if (taxis.size() == 0) {
		throw TaxisIndisponiveis("Nao existem taxis");
	}

	priority_queue<Taxipointer> aux = taxis;

	while (!aux.empty()) {

		Taxipointer ta = (aux.top());
		Taxi t= *(ta.getTaxipointer());

		if (t.getNumeroTaxi() == n) {
			return ta.getTaxipointer();
		}

		aux.pop();
	}

	throw TaxisIndisponiveis("Taxi nao existe");
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

//MUDEI 2
void CompanhiaTaxis::fazerViagemOcasional(string cli, Data dia, Hora horaIn, Percurso p1) {

	Viagem v(dia, horaIn, p1, cli);
	v.horaFinal();

	Taxi* t = this->proximoTaxi(v);

	t->changeDispo(v.horaFinal());

	t->setRentabilidade(v.pagarViagem());
	Taxipointer ta(t);
	taxis.push(ta);

	this->addViagemBSTOcasionais(v);
}

//MUDEI 2
void CompanhiaTaxis::fazerViagemCliente(int id, Data dia, Hora horaIn,
		Percurso p1, bool disc, float per, string tipoPag) {

	for (unsigned int j = 0; j < clientes.size(); j++) {
		if (clientes[j]->getID() == id) {
			Viagem v(dia, horaIn, p1, clientes[j]->getNomeC());
				v.horaFinal();
				v.pagarViagem();

			Taxi* t = this->proximoTaxi(v);

			if (disc)
				v.modificaCusto(clientes[j]->giveMonthlyPromotion(per));

			clientes[j]->addViagemHistorico(v);
			clientes[j]->aumentaPontos();
			clientes[j]->addViagemMensal(v);
			if (clientes[j]->getCusto().getTipo() == "fim_do_mes") {
				//clientes[j]->addViagemMensalFimDoMes(v);
				if (clientes[j]->getPontos() > 50) {
					clientes[j]->resetPontos();
					taxis.push(t);
					this->addViagemBST(v);
					return;
				}
				taxis.push(t);
				this->addViagemBST(v);
				return;
			}
			if (clientes[j]->getCusto().getTipo() == "credito") {

				if (clientes[j]->getPontos() > 50) {
					clientes[j]->resetPontos();
					taxis.push(t);
					this->addViagemBST(v);
					return;
				}
				clientes[j]->changeCustoTotal(v.pagarViagem() * 1.05);
				t->setRentabilidade(v.pagarViagem() * 1.05);
				taxis.push(t);
				this->addViagemBST(v);
				return;
			} else {
				v.pagarViagem();
				if (clientes[j]->getPontos() > 50) {
					clientes[j]->resetPontos();
					taxis.push(t);
					this->addViagemBST(v);
					return;
				}
				clientes[j]->changeCustoTotal(v.pagarViagem());
				t->setRentabilidade(v.pagarViagem());
				taxis.push(t);
				this->addViagemBST(v);
				return;
			}
		}

	}

	throw ClienteInexistente(id);
}

//MUDEI
void CompanhiaTaxis::cobrarPagamentoMensal() {
	resetTabelasClientes(); //
	criarTabelasClientes(); //

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->getCusto().getTipo() == "fim_do_mes")
			capital += clientes[i]->fimdoMes();

		clientes[i]->resetMes();
	}

	priority_queue<Taxipointer> aux;

	while (!taxis.empty()) {

		Taxipointer to = taxis.top();
		Taxi t = *(to.getTaxipointer());

		capital += t.getRentabilidade();
		float n = -1 * (t.getRentabilidade());
		t.setRentabilidade(n);
		Taxi* ta = new Taxi(t.getNumeroTaxi(), t.getRentabilidade(),
				t.getHoraIn(), t.getHoraOff(), t.getdispo());
		Taxipointer tax(ta);
		aux.push(tax);
		taxis.pop();
	}

	while (!aux.empty()) {
		taxis.push(aux.top());
		aux.pop();
	}
}

bool compaCapital(Cliente* c1, Cliente* c2) {
	if (c1->getCusto().getTotal() < c2->getCusto().getTotal())
		return true;
	else
		return false;
}


void CompanhiaTaxis::mostrarClientesPorCapital() {
	vector<Cliente*> v = clientes;

	sort(v.begin(), v.end(),compaCapital);
	reverse(v.begin(), v.end());

	for (unsigned int j = 0; j < v.size(); j++) {
		cout << v[j]->mostrarCliente() << endl;
	}

}

bool compaID(Cliente* c1, Cliente* c2) {
	if (c1->getID() < c2->getID())
		return true;
	else
		return false;
}

void CompanhiaTaxis::mostrarClientesPorID() {

	vector<Cliente*> v = clientes;

	sort(v.begin(), v.end(), compaID);

	for (unsigned int j = 0; j < v.size(); j++) {
		cout << v[j]->mostrarCliente() << endl <<endl;
	}
}

void CompanhiaTaxis::mostrarTaxis() {

	if (taxis.size() == 0) {
		throw TaxisIndisponiveis("Nao existem taxis");
	}

	priority_queue<Taxipointer> aux = taxis;

	while (!aux.empty()) {

		Taxipointer ta = aux.top();
		Taxi t = *(ta.getTaxipointer());

		cout << t << endl;

		aux.pop();
	}
}

void CompanhiaTaxis::concaClientes(vector<Cliente*> c) {

	clientes.insert(clientes.end(), c.begin(), c.end());
}

//MUDEI
void CompanhiaTaxis::criarTabelasClientes() {

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->getViagensMensais().size() == 0)
			this->inativos.insert(clientes[i]);
		else
			this->ativos.insert(clientes[i]);
	}
}

void CompanhiaTaxis::resetTabelasClientes() {
	inativos.clear();
	ativos.clear();
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

//////BST////////
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


BST<Viagem> CompanhiaTaxis::getViagensOcasionais() {
	return this->viagens_ocasionais;
}

void CompanhiaTaxis::addViagemBSTOcasionais(Viagem &v) {
	viagens_ocasionais.insert(v);
}

void CompanhiaTaxis::mostrarViagensBSTOcasionais() {
	BSTItrIn<Viagem> it(viagens_ocasionais);
	while (!it.isAtEnd()) {
		cout << it.retrieve() << endl;
		it.advance();
	}
}


Taxi* CompanhiaTaxis::proximoTaxi(Viagem v) {

	Taxi *res;
	priority_queue<Taxipointer> aux;

	while (!taxis.empty()) {

		Taxipointer ta = taxis.top();
		Taxi t = *(ta.getTaxipointer());

		if (t.inHorario(v.getHoraIn(), v.getHoraOut())) {

			taxis.pop();
			Taxi* ta = new Taxi(t.getNumeroTaxi(), t.getRentabilidade(),
					t.getHoraIn(), t.getHoraOff(), t.getdispo());
			res = ta;
			break;
		}

		aux.push(taxis.top());
		taxis.pop();
	}

	while (!aux.empty()) {
		taxis.push(aux.top());
		aux.pop();
	}

	if (res->getNumeroTaxi() == 0)
		throw TaxisIndisponiveis("Nao existem taxis");
	else
		return res;
}

/*
 * Cliente.cpp
 *
 *  Created on: 30/10/2016
 *      Author: Beatriz de Henriques Martins
 */

#include "Cliente.h"

//Utente
Utente::Utente(string nome, string tipoPagamento) {
	custo = Pagamento(tipoPagamento);
	nomeC = nome;
}

string Utente::getNomeC() const {
	return nomeC;
}

void Utente::setNomeC(string nC) {
	nomeC = nC;
}

Pagamento Utente::getCusto() {
	return custo;
}

void Utente::changeCustoTotal(float n) {
	custo.changeTotal(n);
}

void Utente::changeCustoTipo(string tipo) {
	custo.changeTipo(tipo);
}

//Ocasionais
Ocasionais::Ocasionais(string nome, string tipoPagamento) :
		Utente(nome, tipoPagamento) {

}

//Cliente
int Cliente::ultidC = 1;

Cliente::Cliente(int id, string nome, string morada, string email,
		int numeroTelemovel, int nif, float cap, string tipoPagamento,
		int pontos) :
		Utente(nome, tipoPagamento) {
	this->id = id;
	ultidC = ++id;
	this->NIF = nif;
	this->custo.changeTotal(cap);
	this->morada = morada;
	this->email = email;
	this->numeroTelemovel = numeroTelemovel;
	cartaoPontos = pontos;
}

Cliente::Cliente(string nC, string m, string mail, int nT, int nif,
		string tipoPagamento) :
		Utente(nC, tipoPagamento) {
	NIF = nif;
	morada = m;
	email = mail;
	numeroTelemovel = nT;
	cartaoPontos = 0;
	id = ultidC++;
}

int Cliente::getID() const {
	return id;
}

int Cliente::getNIF() const {
	return NIF;
}

void Cliente::setNIF(int nif) {
	NIF = nif;
}

string Cliente::getMorada() const {
	return morada;
}

string Cliente::getEmail() const {
	return email;
}

vector<Viagem> Cliente::getHistoricoViagens() {
	return historicoViagens;
}

int Cliente::getNumeroTelemovel() const {
	return numeroTelemovel;
}

int Cliente::getPontos() {
	return cartaoPontos;
}

void Cliente::aumentaPontos() {
	cartaoPontos++;
}

void Cliente::resetPontos() {
	cartaoPontos = 0;
}

void Cliente::setMorada(string m) {
	morada = m;
}

void Cliente::setEmail(string mail) {
	email = mail;
}

void Cliente::setNumeroTelemovel(int nT) {
	numeroTelemovel = nT;
}

void Cliente::addViagemMensal(Viagem v) {
	viagensMensais.push_back(v);

}

void Cliente::addViagemHistorico(Viagem v) {
	historicoViagens.push_back(v);
}

void Cliente::resetMes() {
	vector<Viagem> v;
	viagensMensais = v;
}

float Cliente::giveMonthlyPromotion(float p) {
	return 1;
}  //funcao vazia, seria implementada nas subclasses

float Cliente::fimdoMes() {
	float n = 0;
	for (unsigned int i = 0; i < viagensMensais.size(); i++) {
		viagensMensais[i].pagarViagem();
		n += viagensMensais[i].getCustoViagem();
	}

	n = n * 1.02;
	custo.changeTotal(n);
	return n;

}

string Cliente::mostrarCliente() {
	stringstream ss;
	ss << id << " Nome: " << this->getNomeC() << " Morada: " << morada
			<< " Email: " << email << " Nr Telemovel: " << numeroTelemovel
			<< " NIF: " << NIF << " Total dispendido na Companhia: "
			<< this->getCusto().getTotal() << " Tipo de pagamento: "
			<< this->getCusto().getTipo() << " Nr total de pontos no cartao: "
			<< cartaoPontos;
	return ss.str();
}

bool Cliente::isParticular() {

}



bool Cliente::operator <(Cliente c2) {
	if (custo.getTotal() < c2.getCusto().getTotal())
		return true;
	else {
		if (this->custo.getTotal() == c2.getCusto().getTotal()) {
			if (this->historicoViagens.size() < c2.getHistoricoViagens().size())
				return true;
			else
				return false;
		}
	}
	return false;
}

void Cliente::mostrarViagens() {

	for (unsigned int i = 0; i < historicoViagens.size(); i++) {
		cout << historicoViagens[i].toString() << endl;
	}
}

void Cliente::mostrarViagensmensais() {

	for (unsigned int i = 0; i < viagensMensais.size(); i++) {
		cout << viagensMensais[i].toString() << endl;
	}
}

//Particular
Particular::Particular(int id, string nome, string morada, string email,
		int numeroTelemovel, int nif, float cap, string tipoPagamento,
		int pontos) :
		Cliente(id, nome, morada, email, numeroTelemovel, nif, cap,
				tipoPagamento, pontos) {

}

Particular::Particular(string nC, string m, string mail, int nT, int nif,
		string tipoPagamento) :
		Cliente(nC, m, mail, nT, nif, tipoPagamento) {

}

float Particular::giveMonthlyPromotion(float p) {
	if (custo.getTipo() != "fim_do_mes") {
		if (viagensMensais.size() >= 15) {
			return (1 - p);
		}
	} else {
		if (viagensMensais.size() >= 25) {
			return (1 - p);
		} else {
			return 1;
		}
	}
	return 1;
}

string Particular::mostrarCliente() {
	stringstream ss;
	ss << id << " Nome: " << this->getNomeC() << " Morada: " << morada
			<< " Email: " << email << " Nr Telemovel: " << numeroTelemovel
			<< " NIF: " << NIF << " Total dispendido na Companhia: "
			<< this->getCusto().getTotal() << " Tipo de pagamento: "
			<< this->getCusto().getTipo() << " Nr total de pontos no cartao: "
			<< cartaoPontos;
	return ss.str();
}

bool Particular::isParticular() {
	return true;
}

//Empresa
Empresa::Empresa(int id, string nome, string morada, string email,
		int numeroTelemovel, int nif, float cap, string tipoPagamento,
		int nFuncionarios, int pontos) :
		Cliente(id, nome, morada, email, numeroTelemovel, nif, cap,
				tipoPagamento, pontos) {
	this->numFuncionarios = nFuncionarios;
}

Empresa::Empresa(string nC, string m, string mail, int nT, int nif,
		string tipoPagamento, int numFuncionarios) :
		Cliente(nC, m, mail, nT, nif, tipoPagamento) {
	this->numFuncionarios = numFuncionarios;
}

float Empresa::giveMonthlyPromotion(float p) {
	if (custo.getTipo() != "fim_do_mes") {
		if (viagensMensais.size() / numFuncionarios >= 20) {
			return (1 - p);
		}
	} else {
		if (viagensMensais.size() / numFuncionarios >= 30) {
			return (1 - p);
		} else {
			return 1;
		}
	}
	return 1;
}

string Empresa::mostrarCliente() {
	stringstream ss;
	ss << id << " Nome: " << this->getNomeC() << " Morada: " << morada
			<< " Email: " << email << " Nr Telemovel: " << numeroTelemovel
			<< " NIF: " << NIF << " Total dispendido na Companhia: "
			<< this->getCusto().getTotal() << " Tipo de pagamento: "
			<< this->getCusto().getTipo() << " Nr total de pontos no cartao: "
			<< cartaoPontos << " Nr funcionarios: " << numFuncionarios;
	return ss.str();
}

bool Empresa::isParticular() {
	return false;
}

int Empresa::getNfunc() {
	return numFuncionarios;
}

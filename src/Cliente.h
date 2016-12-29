/*
 * Cliente.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <vector>
#include <string>
#include "Pagamento.h"
#include "Percurso.h"
#include "viagem.h"

using namespace std;

class Utente {
protected:
	string nomeC;
	Pagamento custo;

public:
	Utente(string nome, string tipoPagamento);
	string getNomeC() const;
	void setNomeC(string nome);
	void changeCustoTotal(float n);
	void changeCustoTipo(string tipo);
	Pagamento getCusto();
};

class Ocasionais: public Utente {
public:
	Ocasionais(string nome, string tipo_pagamento);
};

class Cliente: public Utente {
protected:
	static int ultidC;
	int id;
	int NIF;
	string morada;
	string email;
	int numeroTelemovel;
	vector<Viagem> historicoViagens;
	vector<Viagem> viagensMensais;
	vector<Viagem> viagensNaoPagas;
	int cartaoPontos;

public:
	Cliente(int id, string nome, string morada, string email,
			int numeroTelemovel, int nif, float cap, string tipoPagamento,
			int pontos, vector<Viagem> viagensNaoPagas); //
	Cliente(string nC, string m, string mail, int nT, int nif,
			string tipoPagamento);

	virtual ~Cliente() {
	}
	;

	int getID() const;
	int getNIF() const;
	string getMorada() const;
	string getEmail() const;
	vector<Viagem> getHistoricoViagens() const;
	vector<Viagem> getViagensMensais() const; //
	vector<Viagem> getViagensNaoPagas() const; //
	int getNumeroTelemovel() const;
	int getPontos();

	void setNIF(int nif);
	void setMorada(string m);
	void setEmail(string mail);
	void setNumeroTelemovel(int nT);

	void aumentaPontos();
	void resetPontos();

	void addViagemMensal(Viagem v);
	void addViagemHistorico(Viagem v);
	void addViagemMensalFimDoMes(Viagem v);//

	void resetMes();//

	virtual float giveMonthlyPromotion(float p);

	float fimdoMes();//

	virtual string mostrarCliente();

	virtual bool isParticular();

	void mostrarViagens(); //
	void mostrarViagensmensais(); //
	void mostrarViagensNaoPagas(); //

	bool operator <(Cliente c2);
};

class Particular: public Cliente {
public:
	Particular(int id, string nome, string morada, string email,
			int numeroTelemovel, int nif, float cap, string tipoPagamento,
			int pontos, vector<Viagem> viagensNaoPagas);
	Particular(string nC, string m, string mail, int nT, int nif,
			string tipo_pagamento);
	float giveMonthlyPromotion(float p);

	string mostrarCliente();

	virtual bool isParticular();
};

class Empresa: public Cliente {
	int numFuncionarios;
public:
	Empresa(int id, string nome, string morada, string email,
			int numeroTelemovel, int nif, float cap, string tipoPagamento,
			int nFuncionarios, int pontos, vector<Viagem> viagensNaoPagas);
	Empresa(string nC, string m, string mail, int nT, int nif,
			string tipoPagamento, int numFuncionarios);
	int getNfunc();
	float giveMonthlyPromotion(float p);
	string mostrarCliente();
	virtual bool isParticular();

};

class ClienteInexistente {
	int id;
public:
	ClienteInexistente(int n) {
		id = n;
	}
	;
	int getID() {
		return id;
	}
	;

};

#endif /* CLIENTE_H_ */

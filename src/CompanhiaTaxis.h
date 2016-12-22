/*
 * CompanhiaTaxis.h
 *
 *  Created on: 21/12/2016
 *      Author: beatrizHm
 */

#ifndef COMPANHIATAXIS_H_
#define COMPANHIATAXIS_H_

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <algorithm>

//#include "Taxi.h"
#include "Taxi.h"
#include "sequentialSearch.h"
#include "BST.h"
#include "Cliente.h"

using namespace std;

struct EqualCli {
	bool operator()(const Cliente* c1, const Cliente* c2) const {
		return c1->getID() == c2->getID();
	}
};

struct HashCli {
	int operator()(const Cliente* c1) const {
		int v = 0;
		string nome = c1->getNomeC();
		for (unsigned int i = 0; i < nome.size(); i++)
			v = 37 * v + nome[i];

		v += c1->getID();
		return v;
	}
};

typedef unordered_set<Taxi, HashCli, EqualCli> tabCli;

class CompanhiaTaxis {
private:
	string nome;
	float capital;
	vector<Cliente *> clientes;
	vector<Percurso*> percursosDisponiveis;
	vector<Taxi> taxisTotais;
	//////
	tabCli inativos;
	BST<Viagem> viagens;
	priority_queue<Taxi> taxis;
	/////

public:
	CompanhiaTaxis();
	CompanhiaTaxis(string n, float c);
	string getNome();
	float getCapital();
	void somaCapital(float n);
	vector<Cliente *> getClientes() const;
	vector<Taxi> getTaxisTotais() const;
	priority_queue<Taxi> getTaxis() const;
	void adicionaTaxi(Hora horI, Hora horO);
	void setTaxis(priority_queue<Taxi> t);
	void removeTaxi(int id);
	Taxi* procuraTaxi(int n) const;
	void setPercursos(vector<Percurso*> p);
	vector<Percurso*> getPercursos() const;
	void adicionaClienteParticular(string nome, string morada, string email,
			int nT, int nif, string tipoPagamento);
	void adicionaClienteEmpresa(string nome, string morada, string email,
			int nT, int nif, string tipoPagamento, int numFuncionarios);
	bool removeCliente(int id);
	int procuraCliente(int id) const;
	int ultimoIDcliente();
	void fazerViagemOcasional(Data dia, Hora horaIn, Percurso p1);
	void fazerViagemCliente(int id, Data dia, Hora horaIn, Percurso p1,
			bool disc, float per);
	void cobrarPagamentoMensal();
	void mostrarClientesPorCapital();
	void mostrarClientesPorID();
	void mostrarTaxis();
	void setClientes(vector<Cliente*> c);
	void concaClientes(vector<Cliente*> c);
};

#endif /* COMPANHIATAXIS_H_ */

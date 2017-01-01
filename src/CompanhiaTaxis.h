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
		for (unsigned int i = 0; i < nome.size(); i++) {
			v = 37 * v + nome[i];
		}
		v += c1->getID();
		return v;
	}
};

typedef unordered_set<Cliente*, HashCli, EqualCli> tabCli;
typedef unordered_set<Cliente*, HashCli, EqualCli>::iterator itTabCli;

class CompanhiaTaxis {
private:
	string nome;
	float capital;
	vector<Cliente *> clientes;
	vector<Percurso*> percursosDisponiveis;
	//////
	tabCli inativos;
	tabCli ativos;
	BST<Viagem> viagens;
	priority_queue<Taxi*> taxis;
	/////

public:
	CompanhiaTaxis();
	CompanhiaTaxis(string n, float c);

	string getNome();
	float getCapital();
	vector<Cliente *> getClientes() const;
	priority_queue<Taxi*> getTaxis() const;
	vector<Percurso*> getPercursos() const;
	tabCli getInativos() const; //hash
	//MUDEI
	tabCli getAtivos() const; //hash

	void setTaxis(priority_queue<Taxi*> t);
	void setPercursos(vector<Percurso*> p);
	void setClientes(vector<Cliente*> c);

	void somaCapital(float n);

	void adicionaTaxi(Hora horI, Hora horO);
	void adicionaClienteParticular(string nome, string morada, string email,
			int nT, int nif, string tipoPagamento);
	void adicionaClienteEmpresa(string nome, string morada, string email,
			int nT, int nif, string tipoPagamento, int numFuncionarios);

	void removeTaxi(int n);
	bool removeCliente(int id);
	//MUDEI
	void removeClienteInativo(Cliente* c); //hash
	void removeClienteAtivo(Cliente* c); //hash

	Taxi* procuraTaxi(int n) const;
	int procuraCliente(int id) const;

	int ultimoIDcliente();

	void fazerViagemOcasional(Data dia, Hora horaIn, Percurso p1);
	void fazerViagemCliente(int id, Data dia, Hora horaIn, Percurso p1,
			bool disc, float per, string tipoPag);

	void cobrarPagamentoMensal();

	void mostrarClientesPorCapital();
	void mostrarClientesPorID();
	void mostrarTaxis();

	void concaClientes(vector<Cliente*> c);

	//MUDEI
	void criarTabelasClientes(); //hash
	void resetTabelasClientes(); //hash

	BST<Viagem> getViagens(); //BST
	void addViagemBST(Viagem &v); //BST
	void mostrarViagensBST(); //BST

	/**
	 * @brief função que nos permite ter o taxi mais disponivel dentro do Horario da Viagem passada como argumento
	 * @return Taxi que tem as caracteristicas pretendidas
	 */
	Taxi* proximoTaxi(Viagem v);

	//bool verficaClienteTabela(int id);
};

#endif /* COMPANHIATAXIS_H_ */

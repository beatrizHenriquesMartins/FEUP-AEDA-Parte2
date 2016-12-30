/*
 * CompanhiaTaxis.h
 *
 *  Created on: 17/10/2016
 *      Author: Pedro Silva
 */

#ifndef SRC_COMPANHIATAXIS_H_
#define SRC_COMPANHIATAXIS_H_

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <queue>

#include "Taxi.h"
#include "sequentialSearch.h"
#include "BST.h"

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
	//vector<Taxi> taxisTotais;
	//////
	tabCli inativos;
	BST<Viagem> viagens;
	priority_queue<Taxi> taxis;

	/////
	vector<Percurso*> percursosDisponiveis;

public:
	/**
	 * @brief construtor companhia de taxis vazio
	 */
	CompanhiaTaxis();

	/**
	 * @brief construtor companhia de taxis
	 * @param n - nome companhia
	 * @param c - capital companhia
	 */
	CompanhiaTaxis(string n, float c);

	/**
	 * @brief fun��o para obter nome
	 * @return nome
	 */
	string getNome();

	/**
	 * @brief fun��o para obter capital companhia
	 * @return companhia
	 */
	float getCapital();

	/**
	 * @brief fun��o que acumula custo de novas viagens ao capital j� acumulado
	 * @param n - custo
	 */
	void somaCapital(float n);

	/**
	 * @brief fun��o para obter lista de clientes
	 * @return vector de clientes
	 */
	vector<Cliente *> getClientes() const;

	/**
	 * @brief fun��o para obter lista de todos os taxis
	 * @return priority_queue de taxis
	 */
	//vector<Taxi> getTaxisTotais() const;
	priority_queue<Taxi> getTaxis() const;

	/**
	 * @brief fun��o para adicionar taxi � lista de taxis
	 * @param horI - hora inicio
	 * @param horO - hora fim
	 */
	void adicionaTaxi(Hora horI, Hora horO);

	/**
	 * @brief fun��o que actualiza a priority_queue de taxis
	 * @param t - taxis
	 */
	void setTaxis(priority_queue<Taxi> t);

	/**
	 * @brief fun��o para eliminar taxi
	 * @param id - id taxi
	 */
	bool removeTaxi(int id);

	/**
	 * @brief fun��o para procurar taxi
	 * @param id - id taxi
	 */
	Taxi* procuraTaxi(int n) const;

	/**
	 * @brief fun��o que actualiza a lista de percursos
	 * @param p - percurso
	 */
	void setPercursos(vector<Percurso*> p);

	/**
	 * @brief fun��o para obter lista de percursos
	 * @return vector de percursos
	 */
	vector<Percurso*> getPercursos() const;

	/**
	 * @brief fun��o que adiciona um cliente particular � lista de clientes
	 * @param nome
	 * @param morada
	 * @param email
	 * @param nT - n�mero de telem�vel
	 * @param nif - n�mero fiscal
	 * @param tipoPagamento - modo pagamento
	 */
	void adicionaClienteParticular(string nome, string morada, string email,
			int nT, int nif, string tipoPagamento);

	/**
	 * @brief fun��o que adiciona um cliente empresa � lista de clientes
	 * @param nome
	 * @param morada
	 * @param email
	 * @param nT - n�mero de telem�vel
	 * @param nif - n�mero fiscal
	 * @param tipoPagamento - modo pagamento
	 * @param numFuncionarios - n�mero de funcion�rios
	 */
	void adicionaClienteEmpresa(string nome, string morada, string email,
			int nT, int nif, string tipoPagamento, int numFuncionarios);

	/**
	 * @brief fun��o para eliminar cliente
	 * @param id - id cliente
	 */
	bool removeCliente(int id);

	/**
	 * @brief fun��o para procurar cliente
	 * @param id - id cliente
	 */
	int procuraCliente(int id) const;

	/**
	 * @brief fun��o para ultimo id da lista de clientes
	 * @return �ltimo id
	 */
	int ultimoIDcliente();

	/**
	 * @brief fun��o que nos permite ter o taxi mais disponivel dentro do Horario da Viagem passada como argumento
	 * @return Taxi que tem as caracteristicas pretendidas
	 */

	Taxi* proximoTaxi(Viagem v);
	/**
	 * @brief fun��o cria uma viagem de ocasinal
	 * @param dia - data
	 * @param horaIn - hora de inicio
	 * @param p1 -percurso
	 */
	void fazerViagemOcasional(Data dia, Hora horaIn, Percurso p1);

	/**
	 * @brief fun��o cria uma viagem de cliente
	 * @param id - id cliente
	 * @param dia - data
	 * @param horaIn - hora de inicio
	 * @param p1 -percurso
	 * @param disc - desconto
	 * @param per - percentagem de desconto
	 */
	void fazerViagemCliente(int id, Data dia, Hora horaIn, Percurso p1,
			bool disc, float per);

	/**
	 * @brief fun��o que calcula o valor total de todos os cliente que querem pagar no final do m�s
	 */
	void cobrarPagamentoMensal();

	/**
	 * @brief fun��o que imprime todos os clientes por ordem descrescente de total gasto em viagens
	 */
	void mostrarClientesPorCapital();

	/**
	 * @brief fun��o que imprime todos os clientes por ordem crescente de id
	 */
	void mostrarClientesPorID();

	/**
	 * @brief fun��o que imprime todos os taxis da companhia
	 */
	void mostrarTaxis();

	/**
	 * @brief fun��o que actualiza a lista de clientes
	 * @param c - cliente
	 */
	void setClientes(vector<Cliente*> c);

	/**
	 * @brief fun��o usada para concatenar 2 vectores de clientes
	 * @param c - vector de cliente
	 */
	void concaClientes(vector<Cliente*> c);
};

#endif /* SRC_COMPANHIATAXIS_H_ */

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
#include <sstream>
#include "Pagamento.h"
#include "Percurso.h"
#include "Viagem.h"

using namespace std;

class Utente {
protected:
	string nomeC;
	Pagamento custo;

public:
	/**
	 * @brief função construtor de utente
	 * @param nome - nome utente
	 * @param tipoPagamento - tipo de pagamento escolhido pelo utente
	 */
	Utente(string nome, string tipoPagamento);

	/**
	 * @brief função para obter o nome do utente
	 * @return retorna o nome do utente
	 */
	string getNomeC() const;

	/**
	 * @brief função para actulizar o nome do utente
	 * @param nome - nome utente
	 */
	void setNomeC(string nome);

	/**
	 * @brief função que calcula o valor total a pagar pelo utente
	 * @param n - valor a somar ao total
	 */
	void changeCustoTotal(float n);

	/**
	 * @brief função que altera o tipo de pagamento do utente
	 * @param tipo - novo tipo de pagamento
	 */
	void changeCustoTipo(string tipo);

	/**
	* @brief função que calcula o valor a pagar pelo utente
	* @return retorna valor a pagar
	*/
	Pagamento getCusto();
};

class Ocasionais: public Utente {
public:
	/**
	 * @brief função construtor Ocasionais
	 * @param nome - nome de utente ocasional
	 * @param tipoPagamento - tipo de pagamento de ocasional
	 */
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
	//vector<Viagem> viagensNaoPagas;
	int cartaoPontos;

public:
	/**
	* @brief função construtor de utente cliente
	* @param id - id de cliente
	* @param nome - nome de cliente
	* @param morada - morada de cliente
	* @param email - email de cliente
	* @param numeroTelemovel - número de telemóvel de cliente
	* @param nif - número fiscal de cliente
	* @param cap - montante total gasto pelo cliente até ao momento
	* @param tipoPagamento - modo de pagamento escolhido pelo cliente
	* @param pontos - pontos acumulados pelo cliente através das viagens realizadas
	*/
	Cliente(int id, string nome, string morada, string email,
			int numeroTelemovel, int nif, float cap, string tipoPagamento,
			int pontos); //

		/**
	 * @brief função construtor de utente cliente
	 * @param nC - nome de cliente
	 * @param m - morada de cliente
	 * @param mail - email de cliente
	 * @param nT - número de telemóvel de cliente
	 * @param nif - número fiscal de cliente
	 * @param tipoPagamento - modo de pagamento escolhido pelo cliente
	 */
	Cliente(string nC, string m, string mail, int nT, int nif,
			string tipoPagamento);

	/**
	* @brief função destrutora de utente cliente
	*/
	virtual ~Cliente() {
	}
	;

	/**
	 * @brief função para obter o id de utente cliente
	 * @return retorna id correspodente
	 */
	int getID() const;

	/**
	 * @brief função para obter o número fiscal de utente cliente
	 * @return retorna número fical correspondente
	 */
	int getNIF() const;

	/**
	 * @brief função para obter morada de utente cliente
	 * @return retorna morada
	 */
	string getMorada() const;

	/**
 * @brief função para obter email de utente cliente
 * @return retorna email
 */
	string getEmail() const;

	/**
	 * @brief função para obter o histórico de viagens de utente cliente
	 * @return retorna um vector de viagens com todas as viagens realizadas
	 */
	vector<Viagem> getHistoricoViagens() const;

	/**
	 * @brief função para obter o vector de viagens mensais do cliente
	 * @return retorna o vector de viagens mensais do cliente
	 */
	vector<Viagem> getViagensMensais() const; //

	//vector<Viagem> getViagensNaoPagas() const; //

	/**
	 * @brief função para obter o número de telemóvel de utente cliente
	 * @return retorna número telemóvel
	 */
	int getNumeroTelemovel() const;

	/**
	 * @brief função para obter o número de pontos já acumulados pelo utente cliente
	 * @return retorna número pontos
	 */
	int getPontos();

	/**
	 * @brief função para actualizar o número fiscal de utente cliente
	 * @param número fiscal actulizado
	 */
	void setNIF(int nif);

	/**
 * @brief função para actualizar a morada de utente cliente
 * @param nova morada
 */
	void setMorada(string m);

	/**
	 * @brief função para actualizar o email de utente cliente
	 * @param novo email
	 */
	void setEmail(string mail);

	/**
	 * @brief função para actualizar o número telemóvel de utente cliente
	 * @param novo número telemóvel
	 */
	void setNumeroTelemovel(int nT);

	/**
	 * @brief função para actualizar o ID de utente cliente
	 * @param id - novo ID
	 */
	void setID(int id);

	/**
	 * @brief função acumuladora de pontos
	 */
	void aumentaPontos();

	/**
	 * @brief função que coloca o número de pontos a zero
	 */
	void resetPontos();

	/**
	 * @brief função para adicionar viagem ao vector de viagens mensais
	 * @param viagem
	 */
	void addViagemMensal(Viagem v);

	/**
	 * @brief função para adicionar viagem ao vector histórico de viagens
	 * @param viagem
	 */
	void addViagemHistorico(Viagem v);

	//void addViagemMensalFimDoMes(Viagem v); //

	/**
	 * @brief função que coloca o vector de viagens mensais a zero
	 */
	void resetMes(); //

	/**
	 * @brief função que calcula promoção mensal (desconto)
	 * @param p - percntagem desconto
	 * @return valor a pagar menos o desconto
	 */
	virtual float giveMonthlyPromotion(float p);

	/**
 * @brief função calcula o valor total de viagens ainda por pagar
 */
	float fimdoMes(); //

	/**
		 * @brief função imprime os dados do cliente com formatação especifica
		 * @return string com todos os dados
		 */
	virtual string mostrarCliente();

	/**
	 * @brief função diz se cliente é do tipo particular ou empresa
	 * @return true - tipo particular, false - tipo empresa
	 */
	virtual bool isParticular();

	/**
 * @brief função imprime vector de viagens realizadas pelo cliente com formatação especifica
 */
	void mostrarViagens(); //

	/**
	 * @brief função imprime vector de viagens mensais realizadas pelo cliente com formatação especifica
	 */
	void mostrarViagensmensais(); //
	//void mostrarViagensNaoPagas(); //

	/**
	 * @brief Um cliente é menor que outro caso o total gasto seja menor. No caso de seres iguais um cliente é menor do que outro quando o seu histórico de viagens é menor
	 * @param cliente - cliente externo
	 * @return true - um dos 2 casos seja válido, false - nenhum caso válido
	 */
	bool operator <(Cliente c2);
};

class Particular: public Cliente {
public:
	/**
	 * @brief função construtor de utente cliente particular
	 * @param id - id
	 * @param nome - nome
	 * @param morada - morada
	 * @param email - email
	 * @param numeroTelemovel - número de telemóvel
	 * @param nif - número fiscal
	 * @param cap - montante total gasto
	 * @param tipoPagamento - modo de pagamento escolhido
	 * @param pontos - pontos acumulados pelo cliente através das viagens realizadas
	 */
	Particular(int id, string nome, string morada, string email,
			int numeroTelemovel, int nif, float cap, string tipoPagamento,
			int pontos);

			/**
	 * @brief função construtor de utente cliente particular
	 * @param nC - nome
	 * @param m - morada
	 * @param mail - email
	 * @param nT - número de telemóvel
	 * @param nif - número fiscal
	 * @param tipoPagamento - modo de pagamento escolhido pelo cliente
	 */
	Particular(string nC, string m, string mail, int nT, int nif,
			string tipo_pagamento);

			/**
	 * @brief função que calcula promoção mensal (desconto)
	 * @param p - percntagem desconto
	 * @return valor a pagar menos o desconto
	 */
	float giveMonthlyPromotion(float p);

	/**
	 * @brief função imprime dados do cliente com formatação especifica
	 * @return string com todos os dados
	 */
	string mostrarCliente();

	/**
 * @brief função diz se cliente é do tipo particular ou empresa
 * @return true - tipo particular, false - tipo empresa
 */
	virtual bool isParticular();
};

class Empresa: public Cliente {
	int numFuncionarios;
public:
	/**
	 * @brief função construtor de utente cliente particular
	 * @param id - id
	 * @param nome - nome
	 * @param morada - morada
	 * @param email - email
	 * @param numeroTelemovel - número de telemóvel
	 * @param nif - número fiscal
	 * @param cap - montante total gasto
	 * @param tipoPagamento - modo de pagamento escolhido
	 * @param numFuncionarios - número de funcionários da empresa
	 * @param pontos - pontos acumulados pelo cliente através das viagens realizadas
	 */
	Empresa(int id, string nome, string morada, string email,
			int numeroTelemovel, int nif, float cap, string tipoPagamento,
			int nFuncionarios, int pontos);

			/**
	 * @brief função construtor de utente cliente particular
	 * @param nC - nome
	 * @param m - morada
	 * @param mail - email
	 * @param nT - número de telemóvel
	 * @param nif - número fiscal
	 * @param tipoPagamento - modo de pagamento escolhido pelo cliente
	 * @param numFuncionarios - número de funcionários da empresa
	 */
	Empresa(string nC, string m, string mail, int nT, int nif,
			string tipoPagamento, int numFuncionarios);

			/**
	 * @brief função para obter número de funcionários da empresa
	 * @return número de funcionários
	 */
	int getNfunc();

	/**
	 * @brief função que calcula promoção mensal (desconto)
	 * @param p - percntagem desconto
	 * @return valor a pagar menos o desconto
	 */
	float giveMonthlyPromotion(float p);

	/**
	 * @brief função imprime dados do cliente com formatação especifica
	 * @return string com todos os dados
	 */
	string mostrarCliente();

	/**
	 * @brief função diz se cliente é do tipo particular ou empresa
	 * @return true - tipo particular, false - tipo empresa
	 */
	virtual bool isParticular();

};

class ClienteInexistente {
	int id;
public:
	/**
	 * @brief contrutor classe excessão de Cliente
	 * @param id
	 */
	ClienteInexistente(int n) {
		id = n;
	}
	;

	/**
	 * @brief função para obter id que provocou excessão
	 * @return id
	 */
	int getID() {
		return id;
	}
	;

};

#endif /* CLIENTE_H_ */

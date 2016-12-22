/*
 * Percurso.h
 *
 *  Created on: 01/11/2016
 *      Author: Diogo
 */

#ifndef SRC_PERCURSO_H_
#define SRC_PERCURSO_H_

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Percurso {
private:
	string localPartida;
	string localDestino;
	int distancia;
public:
	/**
	 * @brief construtor da classe Percurso vazio
	 */
	Percurso();

	/**
	 * @brief construtor da classe Percurso com parametros
	 * @param localPart - local de partida
	 * @param localDest - local de destino
	 * @param distancia - dist�ncia
	 */
	Percurso(string localPart, string localDest, int distancia);

	/**
	 * @brief fun��o para obter local de partida
	 * @return local de partida
	 */
	string getLocalPartida() const;

	/**
	 * @brief fun��o para obter local de destino
	 * @return local de destino
	 */
	string getLocalDestino() const;

	/**
	 * @brief fun��o para obter dist�ncia
	 * @return dist�ncia
	 */
	int getDistancia() const;

	/**
	 * @brief fun��o que actualiza local de partida
	 * @param localPart - local de partida
	 * @param distancia - dist�ncia
	 */
	void setLocalPartida(string localPart, int dist);

	/**
	 * @brief fun��o que actualiza local de destino
	 * @param localDest - local de destino
	 * @param distancia - dist�ncia
	 */
	void setLocalDestino(string localDest, int dist);

	/**
	 * @brief fun��o que actualiza dist�ncia
	 * @param distancia - dist�ncia
	 */
	void setDistancia(int distancia);

	/**
	 * @brief fun��o para imprimir percurso com formata��o especifica
	 * @return string percurso
	 */
	string toString();

	/**
	 * @brief fun��o operador<< impress�o para percurso com formata��o especifica
	 * @param os - ostream
	 * @param p - percurso
	 * @return string percurso
	 */
	friend ostream & operator <<(ostream os, Percurso p);
};

#endif /* SRC_PERCURSO_H_ */

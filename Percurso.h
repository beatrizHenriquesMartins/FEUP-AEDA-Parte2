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
	 * @param distancia - distância
	 */
	Percurso(string localPart, string localDest, int distancia);

	/**
	 * @brief função para obter local de partida
	 * @return local de partida
	 */
	string getLocalPartida() const;

	/**
	 * @brief função para obter local de destino
	 * @return local de destino
	 */
	string getLocalDestino() const;

	/**
	 * @brief função para obter distância
	 * @return distância
	 */
	int getDistancia() const;

	/**
	 * @brief função que actualiza local de partida
	 * @param localPart - local de partida
	 * @param distancia - distância
	 */
	void setLocalPartida(string localPart, int dist);

	/**
	 * @brief função que actualiza local de destino
	 * @param localDest - local de destino
	 * @param distancia - distância
	 */
	void setLocalDestino(string localDest, int dist);

	/**
	 * @brief função que actualiza distância
	 * @param distancia - distância
	 */
	void setDistancia(int distancia);

	/**
	 * @brief função para imprimir percurso com formatação especifica
	 * @return string percurso
	 */
	string toString();

	/**
	 * @brief função operador<< impressão para percurso com formatação especifica
	 * @param os - ostream
	 * @param p - percurso
	 * @return string percurso
	 */
	friend ostream & operator <<(ostream os, Percurso p);
};

#endif /* SRC_PERCURSO_H_ */

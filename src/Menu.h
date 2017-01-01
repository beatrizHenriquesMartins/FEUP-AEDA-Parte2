/*
 * Menu.h
 *
 *  Created on: 22/12/2016
 *      Author: beatrizHm
 */

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "CompanhiaTaxis.h"
#include "Data.h"

using namespace std;

class Menu {
public:
	Menu();

	void trim(string &str);

	void lerFicheiroClienteParticular(CompanhiaTaxis &comp);
	void lerFicheiroClienteEmpresas(CompanhiaTaxis &comp);
	void lerFicheiroViagens(CompanhiaTaxis &comp);
	void lerFicheiroTaxis(CompanhiaTaxis &comp);
	void lerFicheiroViagensNaoPagasMensais(CompanhiaTaxis &comp);

	Data stringToData(string &s);
	Hora stringToHora(string &s);

	void escreverFicheiroClientesParticulares(CompanhiaTaxis &comp);
	void escreverFicheiroClientesEmpresa(CompanhiaTaxis &comp);
	void escreverFicheiroClientesViagens(CompanhiaTaxis &comp);
	void escreverFicheiroComp(CompanhiaTaxis &comp);
	void escreverFicheiroTaxis(CompanhiaTaxis &comp);
	void escreverFicheiroClientesViagensNaoPagasMensais(CompanhiaTaxis &comp);

	void menuInicio(CompanhiaTaxis &comp);

	void menuEmp(CompanhiaTaxis &comp);

	void menuCompanhia(CompanhiaTaxis &comp);
	void menuNomeCompanhia(CompanhiaTaxis &comp);
	void menuVerClientesPorID(CompanhiaTaxis &comp);
	void menuViagensRealizadas(CompanhiaTaxis &comp);

	void menuClientes(CompanhiaTaxis &comp);
	void menuNovoCliente(CompanhiaTaxis &comp);
	void menuRemoverCliente(CompanhiaTaxis &comp);
	void menuFazerViagem(CompanhiaTaxis &comp);
	void menuMarcarViagem(CompanhiaTaxis &comp);
	void menuVerCliente(CompanhiaTaxis &comp);
	void menuVerHistoricoCliente(CompanhiaTaxis &comp);
	void menuViagensMensaisClientes(CompanhiaTaxis &comp);
	void menuViagensMensaisNaoPagasClientes(CompanhiaTaxis &comp);
	//MUDEI
	void menuMudarCliente(CompanhiaTaxis &comp);

	void menuVerCapital(CompanhiaTaxis &comp);
	void menuPrestarServicoOcasional(CompanhiaTaxis &comp);
	void menuListaClientesMaisLucrativos(CompanhiaTaxis &comp);
	void menuMostrarTodosTaxis(CompanhiaTaxis &comp);
	void menuAplicarDescontoMensal(CompanhiaTaxis &comp);

	void menuTaxis(CompanhiaTaxis &comp);
	void menuComprarTaxi(CompanhiaTaxis &comp);
	void menuRemoverTaxi(CompanhiaTaxis &comp);
	void menuVerTaxi(CompanhiaTaxis &comp);

	void menuCobrarPagamentosMensais(CompanhiaTaxis &comp);

};

class OpcaoErrada {
public:
	int alertaErro() {
		cout << "Opcao errada, tente outra vez" << endl;
		return 1;
	}
	;
};

class ErroInput {
public:
	void alertaErro() {
		cout << "Erro de input, digite tudo outra vez" << endl;

	}
	;
};

#endif /* MENU_H_ */

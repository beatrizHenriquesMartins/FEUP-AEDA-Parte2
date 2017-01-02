/*
 * Menu.cpp
 *
 *  Created on: 22/12/2016
 *      Author: beatrizHm
 */

#include "Menu.h"
//MUDEI 2
#include "Taxi.h"

static bool desconto = false;
static float percentagem = 1;

Menu::Menu() {
	ifstream file("Companhia.txt");

	if (file.is_open()) {

		int n;
		string nome;
		float capital;
		string lixo;

		file >> n;
		getline(file, lixo, '\n');
		getline(file, nome, ';');
		file >> capital;
		getline(file, lixo, '\n');

		CompanhiaTaxis comp = CompanhiaTaxis(nome, capital);
		menuInicio(comp);
	} else {
		cout << endl << "Erro ficheiro Companhia!" << endl;
		return;
	}
}

void Menu::trim(string &str) {
	if (str.size() != 0) {
		size_t first = str.find_first_not_of(" ");
		str = str.substr(first, (str.size() - first));
		size_t last = str.find_last_not_of(" ");
		str = str.substr(0, last + 1);
	}
}

void Menu::lerFicheiroClienteParticular(CompanhiaTaxis &comp) {
	ifstream fileC("clientesParticulares.txt");

	if (fileC.is_open()) {
		string lixo;
		unsigned int total;
		vector<Cliente*> aux;

		fileC >> total;
		getline(fileC, lixo, '\n');

		string line;
		while (getline(fileC, line)) {

			stringstream ss;
			string ids;
			int id;
			string nome;
			string morada;
			string email;
			string ntt;
			int nt;
			string niff;
			int nif;
			string capf;
			float cap;
			string tp;
			string pontof;
			int pontos;

			ss << line;
			getline(ss, ids, ';');
			id = atoi(ids.c_str());
			getline(ss, nome, ';');
			getline(ss, morada, ';');
			getline(ss, email, ';');
			getline(ss, ntt, ';');
			nt = atoi(ntt.c_str());
			getline(ss, niff, ';');
			nif = atoi(niff.c_str());
			getline(ss, capf, ';');
			cap = atof(capf.c_str());
			getline(ss, tp, ';');
			getline(ss, pontof);
			pontos = atoi(pontof.c_str());

			trim(nome);
			trim(morada);
			trim(email);
			trim(tp);

			Cliente* c = new Particular(id, nome, morada, email, nt, nif, cap,
					tp, pontos);

			aux.push_back(c);
		}

		comp.setClientes(aux);
	} else {
		cout << endl << "Nao conseguiu abrir ficheiro de Clientes Particulares"
				<< endl;
	}
}

void Menu::lerFicheiroClienteEmpresas(CompanhiaTaxis &comp) {
	ifstream fileE("clientesEmpresa.txt");

	if (fileE.is_open()) {

		int total;
		string lixo;

		fileE >> total;
		getline(fileE, lixo, '\n');

		vector<Cliente*> aux;
		string line;
		while (getline(fileE, line)) {

			stringstream ss;
			string ids;
			int id;
			string nome;
			string morada;
			string email;
			string ntt;
			int nt;
			string niff;
			int nif;
			string tp;
			string nFuncf;
			int nFunc;
			string capf;
			float cap;
			string pontof;
			int pontos;

			ss << line;
			getline(ss, ids, ';');
			id = atoi(ids.c_str());
			getline(ss, nome, ';');
			getline(ss, morada, ';');
			getline(ss, email, ';');
			getline(ss, ntt, ';');
			nt = atoi(ntt.c_str());
			getline(ss, niff, ';');
			nif = atoi(niff.c_str());
			getline(ss, capf, ';');
			cap = atof(capf.c_str());
			getline(ss, tp, ';');
			getline(ss, nFuncf, ';');
			nFunc = atoi(nFuncf.c_str());
			getline(ss, pontof);
			pontos = atoi(pontof.c_str());

			trim(nome);
			trim(morada);
			trim(email);
			trim(tp);

			Cliente *c = new Empresa(id, nome, morada, email, nt, nif, cap, tp,
					nFunc, pontos);

			aux.push_back(c);
		}

		comp.concaClientes(aux);
	} else {
		cout << endl << "Erro Clientes Empresas" << endl;
	}
}

//MUDEI 2
void Menu::lerFicheiroViagens(CompanhiaTaxis &comp) {
	ifstream file("viagens_clientes.txt");

	if (file.is_open()) {
		int n;
		string lixo;
		vector<int> idAux;
		vector<Viagem> aux;
		file >> n;
		getline(file, lixo, '\n');

		string line;
		while (getline(file, line)) {

			stringstream ss;
			ss << line;

			string idf;
			int id;
			string data;
			string hi;
			string hf;
			string part;
			string dest;
			string distf;
			int dist;
			string custof;
			float custo;
			string cliente;

			ss << line;
			getline(ss, idf, ';');
			id = atoi(idf.c_str());
			getline(ss, data, ';');
			getline(ss, lixo, ':');
			getline(ss, hi, ';');
			getline(ss, lixo, ':');
			getline(ss, hf, ';');
			getline(ss, lixo, ':');
			getline(ss, part, '-');
			getline(ss, dest, 'D');
			getline(ss, lixo, ':');
			getline(ss, distf, ':');
			dist = atoi(distf.c_str());
			getline(ss, lixo, ':');
			getline(ss, custof, ':');
			custo = atoi(custof.c_str());
			getline(ss, lixo, ':');
			getline(ss, cliente);

			Data d = stringToData(data);
			Hora horaIn = stringToHora(hi);
			Hora horaF = stringToHora(hf);
			Percurso p = Percurso(part, dest, dist);
			Viagem v(d, horaIn, horaF, p, custo, cliente);
			idAux.push_back(id);
			aux.push_back(v);
		}

		for (unsigned int i = 0; i < idAux.size(); i++) {
			int index = comp.procuraCliente(idAux[i]);
			if (index == 0) {
				comp.getClientes()[index]->addViagemHistorico(aux[i]);
				comp.addViagemBST(aux[i]); // BST
			}
		}
	} else {
		cout << endl << "Erro Viagens Cientes" << endl;
	}
}

void Menu::lerFicheiroTaxis(CompanhiaTaxis &comp) {
	ifstream file("Taxis.txt");

	cout << "Lerficheirotaxis, inicio" << endl;

	if (file.is_open()) {
		int n;
		string lixo;

		priority_queue<Taxipointer> aux;
		file >> n;
		getline(file, lixo, '\n');

		string line;
		while (getline(file, line)) {

			stringstream ss;
			ss << line;

			string idf;
			int id;
			string hi;
			string hf;
			string rentf;
			float rent;
			string dispof;
			float dispo;

			getline(ss, lixo, 'o');
			getline(ss, idf, ';');
			id = atoi(idf.c_str());
			getline(ss, lixo, ':');
			getline(ss, rentf, ';');
			rent = atoi(rentf.c_str());
			getline(ss, lixo, ':');
			getline(ss, hi, 'e');
			getline(ss, lixo, 's');
			getline(ss, hf, ';');
			getline(ss, lixo, ':');
			getline(ss, dispof, ';');
			dispo = atoi(dispof.c_str());

			Hora horaIn = stringToHora(hi);
			Hora horaF = stringToHora(hf);
			Taxi *t = new Taxi(id, rent, horaIn, horaF, dispo);
			Taxipointer ta(t);
			cout << "Lerficheirotaxis, iteracao" << endl;
			aux.push(ta);
			cout << "Lerficheirotaxis, dps" << endl;
		}
		comp.setTaxis(aux);

	} else {
		cout << endl << "Erro Taxis " << endl;
	}
}

/*void Menu::lerFicheiroViagensNaoPagasMensais(CompanhiaTaxis &comp) {
 ifstream file("viagensNaoPagasClientes.txt");

 if (file.is_open()) {
 int n;
 string lixo;
 vector<int> idAux;
 vector<Viagem> aux;
 file >> n;
 getline(file, lixo, '\n');

 string line;
 while (getline(file, line)) {

 stringstream ss;
 ss << line;

 string idf;
 int id;
 string data;
 string hi;
 string hf;
 string part;
 string dest;
 string distf;
 int dist;
 string custof;
 float custo;

 ss << line;
 getline(ss, idf, ';');
 id = atoi(idf.c_str());
 getline(ss, data, ';');
 getline(ss, lixo, ':');
 getline(ss, hi, ';');
 getline(ss, lixo, ':');
 getline(ss, hf, ';');
 getline(ss, lixo, ':');
 getline(ss, part, '-');
 getline(ss, dest, 'D');
 getline(ss, lixo, ':');
 getline(ss, distf, ':');
 dist = atoi(distf.c_str());
 getline(ss, lixo, ':');
 getline(ss, custof);
 custo = atoi(custof.c_str());

 Data d = stringToData(data);
 Hora horaIn = stringToHora(hi);
 Hora horaF = stringToHora(hf);
 Percurso p = Percurso(part, dest, dist);
 Viagem v(d, horaIn, horaF, p, custo);
 idAux.push_back(id);
 aux.push_back(v);
 }

 for (unsigned int i = 0; i < idAux.size(); i++) {
 int index = comp.procuraCliente(idAux[i]);
 if (index == 0) {
 comp.getClientes()[index]->addViagemMensalFimDoMes(aux[i]);
 }
 }
 } else {
 cout << endl << "Erro Viagens Cientes" << endl;
 }
 }*/

Data Menu::stringToData(string &s) {
	int d;
	int m;
	int a;

	stringstream ss;
	ss.str(s);

	while (!ss.eof()) {
		string lixo;

		ss >> d;
		getline(ss, lixo, '/');
		ss >> m;
		getline(ss, lixo, '/');
		ss >> a;
	}

	Data data = Data(d, m, a);

	return data;
}

Hora Menu::stringToHora(string &s) {
	int hor;
	int min;
	int seg;

	stringstream ss;
	ss.str(s);

	while (!ss.eof()) {
		string lixo;

		ss >> hor;
		getline(ss, lixo, ':');
		ss >> min;
		getline(ss, lixo, ':');
		ss >> seg;
		getline(ss, lixo, 'h');
	}

	Hora hora = Hora(hor, min, seg);

	return hora;
}

void Menu::escreverFicheiroClientesParticulares(CompanhiaTaxis &comp) {

	if (comp.getClientes().size() == 0)
		return;

	ofstream file("clientesParticulares.txt");

	vector<Cliente*> tmpPart;
	for (unsigned int i = 0; i < comp.getClientes().size(); i++) {
		if (comp.getClientes()[i]->isParticular() == true) {
			tmpPart.push_back(comp.getClientes()[i]);
		}
	}

	file << tmpPart.size() << endl;

	for (unsigned int j = 0; j < tmpPart.size(); j++) {
		int id = tmpPart[j]->getID();
		string nome = tmpPart[j]->getNomeC();
		string morada = tmpPart[j]->getMorada();
		string email = tmpPart[j]->getEmail();
		int nt = tmpPart[j]->getNumeroTelemovel();
		int nif = tmpPart[j]->getNIF();
		int cap = tmpPart[j]->getCusto().getTotal();
		string tp = tmpPart[j]->getCusto().getTipo();
		int pontos = tmpPart[j]->getPontos();

		file << id << " ; " << nome << " ; " << morada << " ; " << email
				<< " ; " << nt << " ; " << nif << " ; " << cap << " ; " << tp
				<< " ; " << pontos << endl;
	}

	file.close();
}

void Menu::escreverFicheiroClientesEmpresa(CompanhiaTaxis &comp) {

	if (comp.getClientes().size() == 0)
		return;

	ofstream file("clientesEmpresa.txt");

	vector<Cliente*> tmpEmp;
	for (unsigned int i = 0; i < comp.getClientes().size(); i++) {
		if (comp.getClientes()[i]->isParticular() == false) {
			tmpEmp.push_back(comp.getClientes()[i]);
		}
	}

	file << tmpEmp.size() << endl;

	for (unsigned int j = 0; j < tmpEmp.size(); j++) {
		int id = tmpEmp[j]->getID();
		string nome = tmpEmp[j]->getNomeC();
		string morada = tmpEmp[j]->getMorada();
		string email = tmpEmp[j]->getEmail();
		int nt = tmpEmp[j]->getNumeroTelemovel();
		int nif = tmpEmp[j]->getNIF();
		int cap = tmpEmp[j]->getCusto().getTotal();
		string tp = tmpEmp[j]->getCusto().getTipo();
		Empresa *e = dynamic_cast<Empresa *>(tmpEmp[j]);
		int nFunc = e->getNfunc();
		int pontos = tmpEmp[j]->getPontos();

		file << id << " ; " << nome << " ; " << morada << " ; " << email
				<< " ; " << nt << " ; " << nif << " ; " << cap << " ; " << tp
				<< " ; " << nFunc << " ; " << pontos << endl;
	}

	file.close();
}

void Menu::escreverFicheiroComp(CompanhiaTaxis &comp) {
	ofstream file("Companhia.txt");

	file << 1 << endl;
	file << comp.getNome() << " ; " << comp.getCapital();

	file.close();
}

void Menu::escreverFicheiroClientesViagens(CompanhiaTaxis &comp) {
	if (comp.getClientes().size() == 0)
		return;

	ofstream file("viagens_clientes.txt");

	int total = 0;

	for (unsigned int i = 0; i < comp.getClientes().size(); i++) {
		if (comp.getClientes()[i]->getHistoricoViagens().size() != 0) {
			total = total + comp.getClientes()[i]->getHistoricoViagens().size();
		}
	}

	file << total << endl;

	for (unsigned int i = 0; i < comp.getClientes().size(); i++) {
		if (comp.getClientes()[i]->getHistoricoViagens().size() != 0) {
			for (unsigned int j = 0;
					j < comp.getClientes()[i]->getHistoricoViagens().size();
					j++) {
				int id = comp.getClientes()[i]->getID();
				Data data =
						comp.getClientes()[i]->getHistoricoViagens()[j].getData();
				Hora hi =
						comp.getClientes()[i]->getHistoricoViagens()[j].getHoraIn();
				Hora hf =
						comp.getClientes()[i]->getHistoricoViagens()[j].getHoraOut();
				string part =
						comp.getClientes()[i]->getHistoricoViagens()[j].getPartida();
				string dest =
						comp.getClientes()[i]->getHistoricoViagens()[j].getDestino();
				int dist =
						comp.getClientes()[i]->getHistoricoViagens()[j].getDeslocacao().getDistancia();
				float custo =
						comp.getClientes()[i]->getHistoricoViagens()[j].getCustoViagem();
				string cli =
						comp.getClientes()[i]->getHistoricoViagens()[j].getCliente();
				file << id << " ; " << data.toString() << " ; "
						<< "Hora inicial: " << hi.toString() << " ; "
						<< "Hora final: " << hf.toString() << " ; "
						<< "Percurso: " << part << "-" << dest << " Distancia: "
						<< dist << " ; " << "Custo: " << custo << " ; "
						<< "Cliente: " << cli << endl;

			}
		}
	}

	file.close();
}

void Menu::escreverFicheiroTaxis(CompanhiaTaxis &comp) {
	if (comp.getTaxis().size() == 0)
		return;
	ofstream file("Taxis.txt");

	priority_queue<Taxipointer> vt = comp.getTaxis();

	file << vt.size() << endl;

	while (!vt.empty()) {

		Taxipointer ta = vt.top();
		Taxi t = *(ta.getTaxipointer());
		file << t << endl;
		vt.pop();
	}

	file.close();
}

/*void Menu::escreverFicheiroClientesViagensNaoPagasMensais(
 CompanhiaTaxis &comp) {
 if (comp.getClientes().size() == 0)
 return;

 ofstream file("viagensNaoPagasClientes.txt");

 int total = 0;

 for (unsigned int i = 0; i < comp.getClientes().size(); i++) {
 if (comp.getClientes()[i]->getViagensNaoPagas().size() != 0) {
 total = total + comp.getClientes()[i]->getViagensNaoPagas().size();
 }
 }

 file << total << endl;

 for (unsigned int i = 0; i < comp.getClientes().size(); i++) {
 if (comp.getClientes()[i]->getViagensNaoPagas().size() != 0) {
 for (unsigned int j = 0;
 j < comp.getClientes()[i]->getViagensNaoPagas().size();
 j++) {
 int id = comp.getClientes()[i]->getID();
 Data data =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getData();
 Hora hi =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getHoraIn();
 Hora hf =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getHoraOut();
 string part =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getPartida();
 string dest =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getDestino();
 int dist =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getDeslocacao().getDistancia();
 float custo =
 comp.getClientes()[i]->getViagensNaoPagas()[j].getCustoViagem();
 file << id << " ; " << data.toString() << " ; "
 << "Hora inicial: " << hi.toString() << " ; "
 << "Hora final: " << hf.toString() << " ; "
 << "Percurso: " << part << "-" << dest << " Distancia: "
 << dist << " ; " << "Custo: " << custo << endl;

 }
 }
 }

 file.close();
 }*/

void Menu::menuInicio(CompanhiaTaxis &comp) {
	while (1) {
		cout << "||Menu||" << endl << setw(5) << " " << "Bem vindo" << endl
				<< setw(5) << " " << "1. Entrar" << endl << setw(5) << " "
				<< "2. Sair" << endl;

		int op;
		try {
			cout << setw(5) << " " << "op: ";
			cin >> op;

			if (cin.fail()) {
				throw ErroInput();
			}

			if (op < 1 || op > 2)
				throw OpcaoErrada();

			if (op == 1) {
				menuEmp(comp);
				menuCompanhia(comp);
			} else if (op == 2) {
				escreverFicheiroClientesParticulares(comp);
				escreverFicheiroClientesEmpresa(comp);
				escreverFicheiroClientesViagens(comp);
				escreverFicheiroComp(comp);
				escreverFicheiroTaxis(comp);
				//escreverFicheiroClientesViagensNaoPagasMensais(comp);
				cout << endl << "Terminou" << endl;
				return;
			}

		} catch (OpcaoErrada &x) {
			x.alertaErro();

		} catch (ErroInput &e) {

			e.alertaErro();

		} catch (HoraInvalida &d) {

			cout << d.getRazao() << endl;

		}
	}
}

void Menu::menuEmp(CompanhiaTaxis &comp) {

	lerFicheiroClienteParticular(comp);
	cout << "leu ficheiro clientes" << endl;
	lerFicheiroClienteEmpresas(comp);
	cout << "leu ficheiro clientes emp " << endl;
	lerFicheiroViagens(comp);
	lerFicheiroTaxis(comp);
	//lerFicheiroViagensNaoPagasMensais(comp);
	//lerFicheiroPercurso(comp);

}

void Menu::menuCompanhia(CompanhiaTaxis &comp) {
	while (1) {

		cout << endl << "||Companhia de taxis" << endl << setw(5) << " "
				<< "1. Nome da Companhia" << endl << setw(5) << " "
				<< "2. Ver Clientes por ID" << endl << setw(5) << " "
				<< "3. Gestao de Clientes" << endl << setw(5) << " "
				<< "4. Ver capital" << endl << setw(5) << " "
				<< "5. Prestar servico a utente ocasional" << endl << setw(5)
				<< " " << "6. Lista de clientes mais lucrativos" << endl
				<< setw(5) << " " << "7. Mostrar todos os Taxis " << endl
				<< setw(5) << " " << "8. Aplicar desconto mensal " << endl
				<< setw(5) << " " << "9. Gestao de Taxis " << endl << setw(5)
				<< " " << "10. Cobrar pagamentos mensais" << endl << setw(5)
				<< " " << "11. Mostrar viagens da Companhia" << endl << setw(5)
				<< " " << "12. Sair" << endl;
		int opC;

		try {
			cout << setw(5) << " " << "op: ";
			cin >> opC;

			switch (opC) {
			case 1: {
				menuNomeCompanhia(comp);
				break;
			}
			case 2: {
				menuVerClientesPorID(comp);
				break;
			}
			case 3: {
				menuClientes(comp);
				break;
			}
			case 4: {
				menuVerCapital(comp);
				break;
			}
			case 5: {
				menuPrestarServicoOcasional(comp);
				break;
			}
			case 6: {
				menuListaClientesMaisLucrativos(comp);
				break;
			}
			case 7: {
				menuMostrarTodosTaxis(comp);
				break;
			}
			case 8: {
				menuAplicarDescontoMensal(comp);
				break;
			}

			case 9: {
				menuTaxis(comp);
				break;
			}

			case 10: {
				menuCobrarPagamentosMensais(comp);
				break;
			}
			case 11: {
				menuViagensRealizadas(comp);
				break;
			}
			case 12: {
				return;
			}
			default:
				throw OpcaoErrada();
			}
		} catch (OpcaoErrada &x) {
			x.alertaErro();
		} catch (ErroInput &e) {
			e.alertaErro();
		} catch (TaxisIndisponiveis &t) {
			cout << t.getRazao() << endl;
		}
	}
}

void Menu::menuNomeCompanhia(CompanhiaTaxis &comp) {
	cout << "|Nome Companhia|" << endl << endl;
	cout << comp.getNome() << endl;

}

void Menu::menuVerClientesPorID(CompanhiaTaxis &comp) {
	cout << "|Mostrar Clientes Por ID|" << endl << endl;
	comp.mostrarClientesPorID();

}

void Menu::menuClientes(CompanhiaTaxis &comp) {
	while (1) {

		cout << endl << "||Clientes" << endl << setw(5) << " "
				<< "1. Novo Cliente" << endl << setw(5) << " "
				<< "2. Remover Cliente" << endl << setw(5) << " "
				<< "3. Fazer uma viagem" << endl << setw(5) << " "
				<< "4. Ver Cliente especifico" << endl << setw(5) << " "
				<< "5. Ver historico de viagens de cliente especifico" << endl
				<< setw(5) << " "
				<< "6. Ver viagens do mes atual de cliente especifico" << endl
				<< setw(5) << " " << "7. Marcar uma viagem" << endl << setw(5)
				<< " " << "8. Alterar informacao de Cliente" << endl << setw(5)
				<< " " << "9. Voltar ao Menu da Companhia" << endl;
//MUDEI
		int opC;
		try {
			cout << setw(5) << " " << "op: ";
			cin >> opC;

			switch (opC) {
			case 1: {
				menuNovoCliente(comp);
				break;
			}
			case 2: {
				menuRemoverCliente(comp);
				break;
			}

			case 3: {
				menuFazerViagem(comp);
				break;
			}

			case 4: {
				menuVerCliente(comp);
				break;
			}

			case 5: {
				menuVerHistoricoCliente(comp);
				break;
			}

			case 6: {
				menuViagensMensaisClientes(comp);
				break;
			}
			case 7: {
				menuMarcarViagem(comp);
				//menuViagensMensaisNaoPagasClientes(comp);
				break;
			}
			case 8: {
				menuMudarCliente(comp);
				break;
			}
			case 9: {
				return;
			}
			default:
				throw OpcaoErrada();
			}
		} catch (OpcaoErrada &x) {
			x.alertaErro();
		}catch (TaxisIndisponiveis &t) {
			cout << t.getRazao() << endl;
		}
	}
}

void Menu::menuNovoCliente(CompanhiaTaxis &comp) {
	int emp;

	cout << "|Novo Cliente|" << endl << endl;

	while (1) {
		try {
			cout << "1:Empresa ou 2:Particular? ";
			cin >> emp;
			if (emp == 1 || emp == 2)
				break;
			throw OpcaoErrada();
		} catch (OpcaoErrada &x) {
			x.alertaErro();
		}
	}

	int NIF;
	int numeroTelemovel;
	int op;
	string nome;
	string morada;
	string email;
	string t;

	cin.ignore();
	cout << setw(5) << " " << "Nome: ";
	getline(cin, nome);

	cout << setw(5) << " " << "Morada: ";
	getline(cin, morada);

	cout << setw(5) << " " << "Email: ";
	getline(cin, email);

	//cin.ignore();
	cout << setw(5) << " " << "NIF: ";
	cin >> NIF;

	cout << setw(5) << " " << "Numero Telemovel: ";
	cin >> numeroTelemovel;

	int erro = 1;

	while (erro) {
		cout << setw(5) << " " << "Tipo de pagamento: " << endl;
		cout << "Escolher entre:" << endl;
		cout << "1: Numerario  " << "2: Multibanco  " << "3: Credito  "
				<< "4: Mensal" << endl;
		cin >> op;

		if (cin.fail())
			throw OpcaoErrada();

		switch (op) {
		case 1: {
			t = "numerario";
			erro = 0;
			break;
		}
		case 2: {
			t = "multibanco";
			erro = 0;
			break;
		}
		case 3: {
			t = "credito";
			erro = 0;
			break;
		}
		case 4: {
			t = "fim_do_mes";
			erro = 0;
			break;
		}
		default:
			throw OpcaoErrada();
		}
	}

	if (emp == 1) {
		int num_func;
		cout << setw(5) << " " << "Numero Funcionarios da Empresa: ";
		cin >> num_func;
		comp.adicionaClienteEmpresa(nome, morada, email, numeroTelemovel, NIF,
				t, num_func);
	} else {
		comp.adicionaClienteParticular(nome, morada, email, numeroTelemovel,
				NIF, t);
	}

}

void Menu::menuRemoverCliente(CompanhiaTaxis &comp) {
	int id;

	cout << "|Remover Cliente|" << endl << endl;

	comp.mostrarClientesPorID();

	cout << "ID do cliente que quer remover: ";

	cin >> id;
	bool rem = comp.removeCliente(id);

	if (rem) {
		cout << "Cliente removido" << endl;
	} else {
		cout << "Cliente nao encontrado para remover" << endl;
	}

}

//MUDEI 2
//ESTA FUNCAO NAO ESTA BEM
void Menu::menuMarcarViagem(CompanhiaTaxis &comp) {
	int id;
	int distancia;
	int hi;
	int mi;
	int si;
	int dia;
	int mes;
	int ano;
	string localPartida;
	string localDestino;

	cout << "|Fazer Viagem|" << endl << endl;

	try {
		cout << "Qual e o local de origem da viagem? ";
		cin >> localPartida;
		if (cin.fail())
			throw ErroInput();
		cout << "E de destino? ";
		cin >> localDestino;
		if (cin.fail())
			throw ErroInput();
		cout << "Distancia entre locais: ";
		cin >> distancia;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000);

			//throw ErroInput();
		}
		cout << "Digite as horas a que a viagem comeca:" << endl << "Horas ";
		cin >> hi;
		if (cin.fail())
			throw ErroInput();
		cout << " Minutos: ";
		cin >> mi;
		if (cin.fail())
			throw ErroInput();
		cout << " Segundos: ";
		cin >> si;
		if (cin.fail())
			throw ErroInput();

		Hora h1(hi, mi, si);

		cout << "Digite o dia em que a viagem ocorre:" << endl << "Dia ";
		cin >> dia;
		if (cin.fail())
			throw ErroInput();
		cout << " Mes: ";
		cin >> mes;
		if (cin.fail())
			throw ErroInput();
		cout << " Ano: ";
		cin >> ano;
		if (cin.fail())
			throw ErroInput();

		Data d1(dia, mes, ano);

		comp.mostrarClientesPorID();
		cout << "ID do cliente que quer fazer uma viagem: ";
		cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000);
			throw ErroInput();
		}

		/*Cliente* c;
		 c->setID(id);

		 if (comp.procuraCliente(id) == -1
		 && comp.getInativos().find(c) == comp.getInativos().end())
		 throw ClienteInexistente(id);

		 if (comp.getInativos().find(c) != comp.getInativos().end()) {
		 Cliente*cliente = comp.getInativos().find(c);
		 if (cliente->isParticular() == true) {
		 string n = cliente->getNomeC();
		 string m = cliente->getMorada();
		 string e = cliente->getEmail();
		 int nT = cliente->getNumeroTelemovel();
		 int nif = cliente->getNIF();
		 string c = cliente->getCusto();
		 comp.adicionaClienteParticular(n, m, e, nT, nif, c);
		 } else {
		 string n = cliente->getNomeC();
		 string m = cliente->getMorada();
		 string e = cliente->getEmail();
		 int nT = cliente->getNumeroTelemovel();
		 int nif = cliente->getNIF();
		 string c = cliente->getCusto();
		 int nF = cliente->getNfunc();
		 comp.adicionaClienteEmpresa(n, m, e, nT, nif, c, nF);
		 }
		 comp.removeClienteTabela(cliente);
		 }*/

		int opPag;
		string tipoPag;

		cout << "Tipo de Pagamento: " << endl << "1. Numerario" << endl
				<< "2. Multibanco" << "3. Cartao Credito" << endl
				<< "4. Fim do mes" << endl << "Op: ";
		cin >> opPag;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000);
			throw ErroInput();
		}

		switch (opPag) {
		case 1: {
			tipoPag = "numerario";
		}
		case 2: {
			tipoPag = "multibanco";
		}
		case 3: {
			tipoPag = "credito";
		}
		case 4: {
			tipoPag = "fim_do_mes";
		}
		}

		comp.fazerViagemCliente(id, d1, h1,
				Percurso(localPartida, localDestino, distancia), desconto,
				percentagem, tipoPag);
	} catch (ErroInput &e) {
		e.alertaErro();
	} catch (ClienteInexistente &c) {
		cout << "Cliente numero " << c.getID() << " nao existe" << endl;
	} catch (TaxisIndisponiveis &t) {
		cout << t.getRazao() << endl;
	} catch (HoraInvalida &h) {
		cout << h.getRazao() << endl;
	} catch (DataInvalida &d) {
		d.dataErrada();
	}

	comp.resetTabelasClientes();
	comp.criarTabelasClientes();

}

//MUDEI 2
void Menu::menuFazerViagem(CompanhiaTaxis &comp) {
	int id;
	int distancia;
	int hi;
	int mi;
	int si;
	int dia;
	int mes;
	int ano;
	string localPartida;
	string localDestino;

	cout << "|Marcar Viagem|" << endl << endl;

	try {
		cout << "Qual e o local de origem da viagem? ";
		cin >> localPartida;
		if (cin.fail())
			throw ErroInput();
		cout << "E de destino? ";
		cin >> localDestino;
		if (cin.fail())
			throw ErroInput();
		cout << "Distancia entre locais: ";
		cin >> distancia;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000);

			//throw ErroInput();
		}

		comp.mostrarClientesPorID();
		cout << "ID do cliente que quer fazer uma viagem: ";
		cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000);
			throw ErroInput();
		}

		/*Cliente* c;
		 c->setID(id);

		 if (comp.procuraCliente(id) == -1
		 && comp.getInativos().find(c) == comp.getInativos().end())
		 throw ClienteInexistente(id);

		 if (comp.getInativos().find(c) != comp.getInativos().end()) {
		 Cliente*cliente = comp.getInativos().find(c);
		 if (cliente->isParticular() == true) {
		 string n = cliente->getNomeC();
		 string m = cliente->getMorada();
		 string e = cliente->getEmail();
		 int nT = cliente->getNumeroTelemovel();
		 int nif = cliente->getNIF();
		 string c = cliente->getCusto();
		 comp.adicionaClienteParticular(n, m, e, nT, nif, c);
		 } else {
		 string n = cliente->getNomeC();
		 string m = cliente->getMorada();
		 string e = cliente->getEmail();
		 int nT = cliente->getNumeroTelemovel();
		 int nif = cliente->getNIF();
		 string c = cliente->getCusto();
		 int nF = cliente->getNfunc();
		 comp.adicionaClienteEmpresa(n, m, e, nT, nif, c, nF);
		 }
		 comp.removeClienteTabela(cliente);
		 }*/

		int opPag;
		string tipoPag;

		cout << "Tipo de Pagamento: " << endl << "1. Numerario" << endl
				<< "2. Multibanco" << "3. Cartao Credito" << endl
				<< "4. Fim do mes" << endl << "Op: ";
		cin >> opPag;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000);
			throw ErroInput();
		}

		switch (opPag) {
		case 1: {
			tipoPag = "numerario";
		}
		case 2: {
			tipoPag = "multibanco";
		}
		case 3: {
			tipoPag = "credito";
		}
		case 4: {
			tipoPag = "fim_do_mes";
		}
		}

		comp.fazerViagemCliente(id, Data(), Hora(),
				Percurso(localPartida, localDestino, distancia), desconto,
				percentagem, tipoPag);
	} catch (ErroInput &e) {
		e.alertaErro();
	} catch (ClienteInexistente &c) {
		cout << "Cliente numero " << c.getID() << " nao existe" << endl;
	} catch (TaxisIndisponiveis &t) {
		cout << t.getRazao() << endl;
	} catch (HoraInvalida &h) {
		cout << h.getRazao() << endl;
	} catch (DataInvalida &d) {
		d.dataErrada();
	}

	comp.resetTabelasClientes();
	comp.criarTabelasClientes();

}

void Menu::menuVerCliente(CompanhiaTaxis &comp) {
	int id;
	int i;

	cout << "|Ver Cliente|" << endl << endl;

	try {
		cout << "ID do cliente que quer ver: ";
		cin >> id;
		if (cin.fail())
			throw ErroInput();
	} catch (ErroInput &e) {
		e.alertaErro();

	}

	i = comp.procuraCliente(id);
	if (i == -1) {
		cout << "Cliente numero " << id << " nao existe" << endl;

	}

	vector<Cliente*> vC = comp.getClientes();

	cout << vC[i]->mostrarCliente() << endl;


}

void Menu::menuVerHistoricoCliente(CompanhiaTaxis &comp) {
	int id;
	int i;

	cout << "|Ver Histoico Cliente|" << endl << endl;

	try {
		cout << "ID do cliente que quer ver: ";
		cin >> id;
		if (cin.fail())
			throw ErroInput();
	} catch (ErroInput &e) {
		e.alertaErro();

	}

	i = comp.procuraCliente(id);
	if (i == -1) {
		cout << "Cliente numero " << id << " nao existe" << endl;

	}
	vector<Cliente*> vC = comp.getClientes();

	vC[i]->mostrarViagens();


}

void Menu::menuViagensMensaisClientes(CompanhiaTaxis &comp) {
	int id;
	int i;

	cout << "|Viagens Mensais Cliente|" << endl << endl;

	try {
		cout << "ID do cliente que quer ver: ";
		cin >> id;
		if (cin.fail())
			throw ErroInput();
	} catch (ErroInput &e) {
		e.alertaErro();

	}

	i = comp.procuraCliente(id);
	if (i == -1) {
		cout << "Cliente numero " << id << " nao existe" << endl;

	}
	vector<Cliente*> vC = comp.getClientes();

	vC[i]->mostrarViagensmensais();

}

/*void Menu::menuViagensMensaisNaoPagasClientes(CompanhiaTaxis &comp) {
 int id;
 int i;

 cout << "|Viagens Mensais Nao Pagas Clientes|" << endl << endl;

 try {
 cout << "ID do cliente que quer ver: ";
 cin >> id;
 if (cin.fail())
 throw ErroInput();
 } catch (ErroInput &e) {
 e.alertaErro();
 }

 i = comp.procuraCliente(id);
 if (i == -1) {
 cout << endl << "Cliente numero " << id << " nao existe" << endl;
 break;
 }
 cout << endl;
 vector<Cliente*> vC = comp.getClientes();

 vC[i]->mostrarViagensNaoPagas();

 menuClientes(comp);
 }*/

//MUDEI
void Menu::menuMudarCliente(CompanhiaTaxis &comp) {
	int id;
	int i;

	cout << "|Alterar Cliente|" << endl << endl;

	try {
		cout << "ID do cliente que quer mudar: ";
		cin >> id;
		if (cin.fail())
			throw ErroInput();
	} catch (ErroInput &e) {
		e.alertaErro();

	}

	i = comp.procuraCliente(id);
	if (i == -1) {
		cout << "Cliente numero " << id << " nao existe" << endl;

	}

	vector<Cliente*> vC = comp.getClientes();

	string resposta;
	cout << vC[i]->mostrarCliente() << endl;

	cout << "Mudar NIF?(sim/nao) ";
	cin >> resposta;
	if (resposta == "sim") {
		int nif;
		cout << "NIF: ";
		cin >> nif;
		vC[i]->setNIF(nif);
	}

	cout << "Mudar morada?(sim/nao) ";
	cin >> resposta;
	if (resposta == "sim") {
		string morada;
		cout << "Morada: ";
		cin >> morada;
		vC[i]->setMorada(morada);
	}

	cout << "Mudar email?(sim/nao) ";
	cin >> resposta;
	if (resposta == "sim") {
		string mail;
		cout << "Email: ";
		cin >> mail;
		vC[i]->setEmail(mail);
	}

	cout << "Mudar numero de telemovel?(sim/nao) ";
	cin >> resposta;
	if (resposta == "sim") {
		int num;
		cout << "Num de Telemovel: ";
		cin >> num;
		vC[i]->setNumeroTelemovel(num);
	}

	comp.resetTabelasClientes();
	comp.criarTabelasClientes();

}

void Menu::menuVerCapital(CompanhiaTaxis &comp) {
	cout << "|Ver Capital|" << endl << endl;

	cout << "Capital: " << comp.getCapital() << endl;


}

void Menu::menuPrestarServicoOcasional(CompanhiaTaxis &comp) {
	string nome;
	int t;
	cout << "|Prestar Servico Ocasional|" << endl << endl;

	cin.ignore();
	cout << setw(5) << " " << "Nome: ";
	getline(cin, nome);

	int distancia;

	string localPartida;
	string localDestino;

	try {
		cout << "Qual e o local de origem da viagem? ";
		cin >> localPartida;
		if (cin.fail())
			throw ErroInput();
		cout << "E de destino? ";
		cin >> localDestino;
		if (cin.fail())
			throw ErroInput();
		cout << "Distancia entre locais: ";
		cin >> distancia;
		if (cin.fail())
			throw ErroInput();

		int erro = 1;
		while (erro) {
			try {
				cout << setw(5) << " " << "Tipo de pagamento: " << endl;
				cout << "Escolher entre:" << endl;
				cout << "1: Numerario  " << "2: Multibanco :";
				cin >> t;

				if (cin.fail())
					throw ErroInput();

				if ((t != 2) && (t != 1))
					throw OpcaoErrada();
				else
					erro = 0;

			} catch (OpcaoErrada &x) {
				x.alertaErro();
			}
		}

		comp.fazerViagemOcasional(nome, Data(), Hora(),
				Percurso(localPartida, localDestino, distancia));

	} catch (ErroInput &e) {
		e.alertaErro();
	} catch (TaxisIndisponiveis &t) {
		cout << t.getRazao() << endl;
	} catch (HoraInvalida &h) {
		cout << h.getRazao() << endl;
	} catch (DataInvalida &d) {
		d.dataErrada();
	}


}

void Menu::menuListaClientesMaisLucrativos(CompanhiaTaxis &comp) {
	cout << "|Lista Clientes Mais Lucrativos|" << endl << endl;

	comp.mostrarClientesPorCapital();


}

void Menu::menuMostrarTodosTaxis(CompanhiaTaxis &comp) {
	cout << "|Mostrar Todos os Taxis|" << endl << endl;

	comp.mostrarTaxis();

}

void Menu::menuAplicarDescontoMensal(CompanhiaTaxis &comp) {
	cout << "|Aplicar Desconto Mensal|" << endl << endl;

	desconto = true;
	cout << "Percentagem de desconto:(entre 0 e 1): ";
	cin >> percentagem;
	if (percentagem >= 1 || percentagem <= 0) {
		desconto = false;
		percentagem = 1;
		cout << "Desconto invalido" << endl;
	}

}

void Menu::menuTaxis(CompanhiaTaxis &comp) {
	while (1) {

		cout << endl << "||Taxis" << endl << setw(5) << " "
				<< "1. Compra de Taxi" << endl << setw(5) << " "
				<< "2. Remover Taxi" << endl << setw(5) << " "
				<< "3. Ver Taxi especifico" << " " << endl
				<< "4. Voltar ao Menu da Companhia" << endl;

		int opC;

		try {
			cout << setw(5) << " " << "op: ";
			cin >> opC;

			switch (opC) {
			case 1: {
				menuComprarTaxi(comp);
				break;
			}

			case 2: {
				menuRemoverTaxi(comp);
				break;
			}

			case 3: {
				menuVerTaxi(comp);
				break;
			}

			case 4: {
				return;
			}
			default:
				throw OpcaoErrada();
			}
		} catch (OpcaoErrada &x) {
			x.alertaErro();
		} catch (TaxisIndisponiveis &t) {
			cout << t.getRazao() << endl;
		}
	}
}

void Menu::menuComprarTaxi(CompanhiaTaxis &comp) {
	int hi;
	int mi;
	int si;
	int hf;
	int mf;
	int sf;

	cout << "|Comprar Taxi|" << endl << endl;

	cout << "Digite a hora inicial na qual o Taxi esta disponivel:" << endl
			<< "Horas: ";
	cin >> hi;
	if (cin.fail())
		throw ErroInput();
	cout << " Minutos: ";
	cin >> mi;
	if (cin.fail())
		throw ErroInput();
	cout << " Segundos: ";
	cin >> si;
	if (cin.fail())
		throw ErroInput();

	cout << "E a final:" << endl << "Horas: ";
	cin >> hf;
	if (cin.fail())
		throw ErroInput();
	cout << " Minutos: ";
	cin >> mf;
	if (cin.fail())
		throw ErroInput();
	cout << " Segundos: ";
	cin >> sf;
	if (cin.fail())
		throw ErroInput();

	comp.adicionaTaxi(Hora(hi, mi, si), Hora(hf, mf, sf));


}

//Rodas
void Menu::menuRemoverTaxi(CompanhiaTaxis &comp) {
	int n;

	cout << "|Remover Taxi|" << endl << endl;

	comp.mostrarTaxis();
	cout << "Nr do taxi que quer remover: ";
	cin >> n;

	comp.removeTaxi(n);


}

//Rodas
void Menu::menuVerTaxi(CompanhiaTaxis &comp) {

	int id;

	cout << "|Ver Taxi|" << endl << endl;

	try {
		cout << "Nr do taxi que quer ver: ";
		cin >> id;
		if (cin.fail())
			throw ErroInput();
	} catch (ErroInput &e) {

		e.alertaErro();
	}

	Taxi* t = comp.procuraTaxi(id);

	cout << *t << endl;

}

void Menu::menuCobrarPagamentosMensais(CompanhiaTaxis &comp) {
	cout << "|Cobrar Pagementos Mensais|" << endl << endl;

	comp.cobrarPagamentoMensal();
	desconto = false;
	percentagem = 1;
}

void Menu::menuViagensRealizadas(CompanhiaTaxis &comp) {
	cout << "|Viagens Realizadas|" << endl << endl;
	comp.mostrarViagensBST();
	cout << endl;

}

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node
{
public:
	Node();
	Node(int[9], int);
	void Generate(int[9], int, int, int);
	int verificar_Ganador(int[9]);

	void setGanador(int);
	int getGanador();

	void setGato(int[9]);
	int* getGato();

	void setDificultad(int);
	int getDificultad();

	void setNodos(int*, int);
	vector<Node*> getNodos();

	int determinarTurno(int[9], int);
	int calcularPesos(vector<Node*>);
	int evitarJugada(vector<Node*>);
	int revisarEmpate(int[9]);

	void jugarGato();
	void dibujarGato();
	void imprimirMensajeVictoria(int);
	Node* buscarJugada(vector<Node*> Nodo,int[9]);
	Node* buscarCaminoMasCorto(Node*);
	int compararMatrices(int[9], int[9]);

	static int nivel;

private:

	int gato[9] = { 0,0,0, 0,0,0, 0,0,0 };
	vector<Node*> Nodos = {};
	int dificultad = 0;
	int ganador = 0;
	int peso = 0;

};

Node::Node() {



}

Node::Node(int gato[9], int ganador) {

	setGato(gato);
	setGanador(ganador);

}

void Node::setNodos(int* gato, int ganador) {

	Node* jugada = new Node(gato, ganador);
	this->Nodos.push_back(jugada);

}

void Node::setGanador(int ganador) {

	this->ganador = ganador;

}

int Node::getGanador() {

	return ganador;

}

void Node::setGato(int gato[9]) {

	int gatoRow = 9;

	for (int i = 0; i < gatoRow; i++) {

		this->gato[i] = gato[i];

	}

}

int* Node::getGato() {

	return gato;

}

void Node::setDificultad(int dificultad) {

	this->dificultad = dificultad;

}

int Node::getDificultad() {

	return dificultad;

}

void Node::Generate(int jugadaInicial[9], int jugadorInicial, int contadorRecursivo, int dificultad) {

	int gatoRow = 9;
	int turno;
	int ganador = 0;

	this->setDificultad(dificultad);
	this->setGato(jugadaInicial);

	for (int i = 0; i < gatoRow; i++) {

		if (this->gato[i] != 0) continue;

		turno = determinarTurno(this->gato, jugadorInicial);
		this->gato[i] = turno;
		ganador = verificar_Ganador(this->gato);
		Node* jugada = new Node(this->gato, ganador);
		this->Nodos.push_back(jugada);
		this->gato[i] = 0;

	}

	if (contadorRecursivo < dificultad) {
		for (Node* i : this->Nodos) {
			if (i->ganador != 0) continue;
			i->Generate(i->gato, jugadorInicial,++contadorRecursivo, dificultad);
			--contadorRecursivo;
		}
	}
}

int Node::calcularPesos(vector<Node*> Nodos) {

	int pesoTotal = 0;

	for (Node* i : Nodos) {

		if (i->ganador != 0) {

			i->peso += i->ganador;

		}

	}

	for (Node* i : Nodos) {

		i->peso += calcularPesos(i->Nodos);
		pesoTotal += i->peso;

	}

	return pesoTotal;

}

int Node::determinarTurno(int jugadaActual[9], int jugadorInicial) {

	int gatoRow = 9;
	int ContadorMaquina = 0, ContadorHumano = 0;
	int maquina = 1, humano = 2;

	for (int i = 0; i < gatoRow; i++) {

		if (jugadaActual[i] == 1) ContadorMaquina++;
		else if (jugadaActual[i] == 2) ContadorHumano++;

	}

	//Si el número de X y O es el mismo, se determina que el turno es del jugador que comenzó
	if (ContadorMaquina == ContadorHumano) {

		return jugadorInicial;

	}
	//Si el número de X y O es diferente, se devuelve el número con menores apariciones
	else if (ContadorMaquina > ContadorHumano) {

		return humano;

	}

	else if (ContadorHumano > ContadorMaquina) {

		return maquina;

	}

}

int Node::verificar_Ganador(int jugadaActual[9]) {

	//Si no hay ganador, se regresa un -1 para identificar el caso
	int ganador = 0;
	int maquina = -2;
	int empate = -2;
	int humano = 2;
	int esEmpate = 0;

	// verificar  las filas 
	for (int i = 0; i <= 9;)
	{
		if (jugadaActual[i] == jugadaActual[i + 1] && jugadaActual[i] == jugadaActual[i + 2])
		{
			if (jugadaActual[i] == 1) return maquina;
			else if (jugadaActual[i] == 2) return humano;
		}

		i += 3;
	}
	// verificar ganar por columna
	for (int i = 0; i < 3; i++)
	{
		if (jugadaActual[i] == jugadaActual[i + 3] && jugadaActual[i] == jugadaActual[i + 6])
		{
			if (jugadaActual[i] == 1) return maquina;
			else if (jugadaActual[i] == 2) return humano;
		}

	}
	// verificar por diagonal

	if (jugadaActual[0] == jugadaActual[4] && jugadaActual[0] == jugadaActual[8])
	{
		if (jugadaActual[0] == 1) return maquina;
		else if (jugadaActual[0] == 2) return humano;
	}

	if (jugadaActual[2] == jugadaActual[4] && jugadaActual[2] == jugadaActual[6])
	{
		if (jugadaActual[2] == 1) return maquina;
		else if (jugadaActual[2] == 2) return humano;
	}

	esEmpate = revisarEmpate(jugadaActual);

	if (esEmpate) return empate;

	return ganador;

}

int Node::revisarEmpate(int gatoActual[9]) {

	int numPosiciones = 9;

	for (int i = 0; i < numPosiciones; i++) {

		if (gatoActual[i] == 0) return 0;

	}

	return 1;

}

void Node::jugarGato() {

	int numPosiciones = 9;
	int jugadaGato[9] = { 0 }; 
	int jugadaHumano = -1; //Se inicializa en valor -1 para poder evaluar valores mayores a 0
	int ganador = 0;
	Node* jugadaActual = new Node();

	setGato(jugadaGato);

	dibujarGato();

	for (int i = 0; i < numPosiciones;) {

		while (jugadaHumano < 0 || jugadaHumano > 8) {

			cout << "Elije tu jugada en una posición del 0 al 8" << endl;
			cin >> jugadaHumano;

			if (this->gato[jugadaHumano] != 0) {

				cout << "Elije otra posición" << endl;
				jugadaHumano = -1;

			}

		}

		this->gato[jugadaHumano] = 2;
		jugadaHumano = -1;

		dibujarGato();

		ganador = verificar_Ganador(this->gato);

		if (ganador != 0) {

			imprimirMensajeVictoria(ganador);
			break;

		}

		i++;
		if (i == numPosiciones) break;

		jugadaActual = buscarJugada(Nodos, this->gato);

		jugadaActual = buscarCaminoMasCorto(jugadaActual);

		setGato(jugadaActual->gato);

		dibujarGato();

		ganador = verificar_Ganador(this->gato);

		if (ganador != 0) {

			imprimirMensajeVictoria(ganador);
			break;

		}

		i++;


	}




}

void Node::dibujarGato() {

	vector<char> gatoChar;
	int numPosiciones = 9;
	char humano = 'O';
	char maquina = 'X';
	char espacio = ' ';


	for (int i = 0; i < numPosiciones; i++) {

		if (this->gato[i] == 0) gatoChar.push_back(espacio);
		else if (this->gato[i] == 1) gatoChar.push_back(maquina);
		else if (this->gato[i] == 2) gatoChar.push_back(humano);

	}

	cout << "\n     ######GATO#######\n\n";

	cout << "\t" << gatoChar[0] << " | " << gatoChar[1] << " | " << gatoChar[2] << "\t\t" << "0" << " | " << "1" << " | " << "2" << endl;
	cout << "\t----------\t\t----------" << "\n";
	cout << "\t" << gatoChar[3] << " | " << gatoChar[4] << " | " << gatoChar[5] << "\t\t" << "3" << " | " << "4" << " | " << "5" << endl;
	cout << "\t----------\t\t----------" << "\n";
	cout << "\t" << gatoChar[6] << " | " << gatoChar[7] << " | " << gatoChar[8] << "\t\t" << "6" << " | " << "7" << " | " << "8" << endl;

	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

}

Node* Node::buscarJugada(vector<Node*>Nodo ,int jugadaGato[9]) {

	int iguales = 0;
	Node* aux = new Node();

	for (int i = 0; i < Nodo.size();) {

		iguales = compararMatrices(Nodo[i]->gato, jugadaGato);

		if (iguales == 1) return Nodo[i];

		i++;

	}

	for (Node* i : Nodo) {

		if (i->Nodos.size() > 0) {
			aux = buscarJugada(i->Nodos, jugadaGato);
			if (compararMatrices(aux->gato, jugadaGato)) return aux;
		}
		//if (compararMatrices(aux->gato, jugadaGato)) return aux;

	}

	return aux;

}

int Node::compararMatrices(int matrizNodo[9], int jugadaGato[9]) {

	for (int i = 0; i < 9; i++) {

		if (jugadaGato[i] != matrizNodo[i]) return 0;

	}

	return 1;

}

Node* Node::buscarCaminoMasCorto(Node* jugadaActual) {

	Node* aux = new Node();
	int pesoAux = 999999999;
	int pesoAuxExc = -9999999;
	int rechazarJugada = 0;
	int igualAExc1 = 0;
	int igualAExc2 = 0;

	int excepcion1[9] = {
		2, 0, 0,
		0, 1, 0,
		0, 0, 2
	};

	int excepcion2[9] = {
		0, 0, 2,
		0, 1, 0,
		2, 0, 0
	};

	igualAExc1 = compararMatrices(jugadaActual->gato, excepcion1);
	igualAExc2 = compararMatrices(jugadaActual->gato, excepcion2);

 	for (Node* i : jugadaActual->Nodos) {

		if (i->ganador == -2) {

			aux = i;
			break;

		}

		//if(i->dificultad >= 7) rechazarJugada = evitarJugada(i->Nodos);

		//if (i->peso > pesoAux && rechazarJugada != 1) {
		if (igualAExc1 || igualAExc2) {

			if (i->peso > pesoAuxExc) {

				pesoAuxExc = i->peso;
				aux = i;

			}

		}
		else {

			if (i->peso < pesoAux) {

				pesoAux = i->peso;
				aux = i;

			}

		}

	}

	return aux;

}

void Node::imprimirMensajeVictoria(int ganador) {

	if (ganador == 1) cout << "\n\n\t Victoria para la maquina!" << endl;
	else if (ganador == -1) cout << "\n\n\t Victoria para ti!" << endl;

}

int Node::evitarJugada(vector<Node*>siguienteJugada) {

	for (Node* i : siguienteJugada) {

		if (i->ganador == -1) return 1;

	}

	return 0;

}

vector<Node*> Node::getNodos() {

	return this->Nodos;

}

int Node::nivel = 1;
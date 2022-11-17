#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node
{
public:
	Node();
	Node(int[9]);
	void Generate(int[9], int, int, int);

	void setGato(int[9]);
	int* getGato();

	void setDificultad(int);
	int getDificultad();

	vector<Node*> getNodos();
	int determinarTurno(int[9], int);

	static int nivel;

private:

	int gato[9] = { 0,0,0, 0,0,0, 0,0,0 };
	vector<Node*> Nodos = {};
	int dificultad = 0;

};

Node::Node() {



}

Node::Node(int gato[9]) {

	setGato(gato);

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
	int contadorOffset = contadorRecursivo;

	this->setDificultad(dificultad);
	this->setGato(jugadaInicial);

	for (int i = 0; i < gatoRow; i++) {

		if (this->gato[i] != 0) continue;
		turno = determinarTurno(this->gato, jugadorInicial);
		this->gato[i] = turno;

		Node* jugada = new Node(this->gato);
		this->Nodos.push_back(jugada);
		contadorRecursivo++;

		this->gato[i] = 0;

	}
	
	for (int i = contadorOffset; i + contadorOffset < contadorRecursivo + contadorOffset; i++) {

		if (nivel < dificultad) {

			nivel++;
			this->Generate(this->Nodos[i]->gato, jugadorInicial, this->Nodos.size(), dificultad);
			nivel--;

		}

	}



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
	//Si el número de X y O es diferente, se devuelve el número menor
	else if (ContadorMaquina > ContadorHumano) {

		return humano;

	}

	else if (ContadorHumano > ContadorMaquina) {

		return maquina;

	}

}

vector<Node*> Node::getNodos() {

	return this->Nodos;

}

int Node::nivel = 1;


int main()
{

	int jugadorInicial = 2; //1 equivale a la maquina, 2 equivale al humano
	int dificultad = 0;

	Node gato = Node::Node();

	vector<Node*> Grafo;


	int gatoInicial[9] = {
		0, 0, 0,
		0, 2, 1,
		2, 1, 2
	};

	cout << "Elige la dificultad: " << endl;
	cout << "1.Facil\n2.Dificil\n3.Imposible\n: ";

	cin >> dificultad;

	gato.Generate(gatoInicial, jugadorInicial, 0, dificultad);

	Grafo = gato.getNodos();

	system("pause");

}


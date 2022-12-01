#include "Nodos.h"


int main()
{

	int jugadorInicial = 1; //1 equivale a la maquina, 2 equivale al humano
	int dificultad = 0; //Los niveles de dificultad equivalen a la profundidad del arbol
	int ganador = -1;	//Hay tres estados: -1, no es victoria; 0, victoria para la máquina; 999999 (INFINITY), victoria para el humano
	int peso = 0;

	Node gato = Node::Node();
	Node* aux = new Node();

	vector<Node*> Grafo;
	vector<Node*> Grafo2;


	//int gatoInicialPrueba[9] = {
	//	2, 1, 0,
	//	0, 0, 0,
	//	0, 0, 0
	//};

	int gatoInicial[9] = {
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};

	//Comprobar para el estado inicial si es condición de victoria, y agregarlo al vector de nodos en dicho caso

	ganador = gato.verificar_Ganador(gatoInicial);
	if (ganador != 0) {

		gato.setNodos(gatoInicial, ganador);

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Elige la dificultad: " << endl;
	cout << "1.Facil\n2.Dificil\n3.Imposible\n: ";

	cin >> dificultad;

	//Proceso recursivo para generar todas las posibles jugadas
	gato.Generate(gatoInicial, jugadorInicial, 0, dificultad);
	Grafo = gato.getNodos();
	peso = gato.calcularPesos(Grafo);

	//gato.jugarGato();



	//aux = gato.buscarJugada(Grafo, gatoInicialPrueba);

	system("pause");

}


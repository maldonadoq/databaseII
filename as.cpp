#include <iostream>
#include "src/arbol_d.h"

using namespace std;

int main(int argc, char const *argv[]){

	arbol_d<int> *a = new arbol_d<int>("est");
	a->insertar_orden(7,0);
	a->impresion_lineal();
	delete a;
	return 0;
}
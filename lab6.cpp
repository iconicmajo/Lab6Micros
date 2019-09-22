/*

* UNIVERSIDAD DEL VALLE DE GUATEMALA

* CC3056 - Programacion de Microprocesadores

* Autores: 

* Maria Jose Castro #181202

* Renato Estrada #181099

* Ricardo Valenzuela #18762

* Fecha: 2019/08/29

* ---------------------------------------

* Calcula los números primos en un rango de 10^n

* y escibe en dos archivos

*----------------------------------------

*/


//Librerias necesarias

#include <iostream>

#include <cstdlib>

#include <pthread.h>

#include <stdio.h>

#include <math.h>

#include <fstream> //file processing

#include <cstdlib> //exit function

using namespace std;

/*
Extraido del codigo de ejemplo brindado en clase, del archivo llamado Variables golales compartidas, Autor: JJ Celada
Funcion para saber si un numero es primo o no
*/

int counter = 0, thread_count=6, nuevo=0;
pthread_mutex_t mutex_forvar;
pthread_cond_t cond_var;
pthread_mutex_t nueva_mutex;


/*-----Variables globales compartidas -----*/
void *barrera_condicional(void * arg)
{
	int my_rank = (int)arg;
	//**Barrier**
	pthread_mutex_lock(&mutex_forvar);
	counter++;
	printf("Running Thread : %ld\n",my_rank);

	if(counter == thread_count)
	{
		counter = 0;

		//--Notify all waiting threads--
		pthread_cond_broadcast(&cond_var);
		//...
	}
	else
	{	
		//...
		while(pthread_cond_wait(&cond_var, &mutex_forvar)!= 0);


	}
	//**Release barrier**
	pthread_mutex_unlock(&mutex_forvar);
	printf("Finished thread : %d\n",my_rank);
	nuevo++;
	pthread_exit(0);
	//... 
}

struct parameters {
	int id;
	//string word;
}

string texto;
int cont;
int i;
int conteoG;
/*----- Variables globales compartidas -----*/

void lectura();

int main()
{
	int j;
	lectura();

	
	system("pause");
	return 0;
}

void lectura (){
	int j; 
	int k;
	int h;
	int contSec;
	cont = 0;
	conteoG = 0;
	ifstream archivo;
	archivo.open("FUENTE.txt", ios::in);
	if (archivo.fail()){
		cout<<"No se puede abrir el archivo";
		exit(1);
	}
	while(!archivo.eof())
	{
		getline(archivo,texto);
		cout<<texto<<endl;
	}
	i = texto.size();
	k = i % 8;
	while (k != 8){
		k++;
		cont ++;
	}
	h = i + cont;
	cout<<k<<endl;
	cout<<i<<endl;
	cont = 0;
	k = i / 8;
	char palabra[h];
	string palabraF;
	for (j=0; j<h; j++)
	{
		if (j < i){
			palabra[j] = texto[j];
			cout<<palabra[j]<<endl;
		}else{
			palabra[j] = 8;
			cout<<palabra[j]<<endl;
		}
	}
	contSec = 2;
	char acomodador[8];
	while (cont!= 8){
		if(contSec == 8){
			contSec = 0;
		}
		acomodador[cont] = palabra[contSec];
		cout<<palabra[contSec]<<endl;
		contSec ++;
		cont ++;
	}
	cout<<acomodador<<endl;
	archivo.close();

	return 0;
}
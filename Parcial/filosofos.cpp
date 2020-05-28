#include <iostream>
#include <pthread.h>
#include <vector>
#include<stdio.h>
#include <unistd.h>
#include <ctime>
#include <mutex>
using namespace std;
int estomago=50;
int n;
// se define una cantidad de N filosofos comensales y será ingresada por consola por el usuario, como se pide en el punto b
int lleno=100;
//esta variable lleno nos ayuda a evaluar cuando un filosfo está lleno y por tanto debe dejar de comer, como se pide en el punto f
#define IZQUIERDA(x)	((x) !=0 ? (x)-1 : (n-1)) //Nos retorna asiento en el que se encuentra el comensal de la izquierda de x
#define DERECHA(x)		(((x)+1)%n) //Nos dice el asiento en el que se encuentra el comensal de la derecha de x
vector<bool> tenedores(n);
void comer(vector<bool> tenedores, int id_asiento, int estomago)
{
    //se hará uso del mutex para manejar nuestra seccion critica, ya que nuestros hilos querran entrar todos al mismo tiempo
    mutex m;
    m.lock();
    if(estomago<=lleno){
            //este numero random significa un tiempo random el cual simularemos con un bucle for, punto e
            int num=rand();
            for(int i=0;i<num;i++){}
            if(tenedores[IZQUIERDA(id_asiento)] == 0 && tenedores[DERECHA(id_asiento)]==0){ //evaluamos si el tenedor izquiero y derecho se encuentran disponibles
                    //en caso están disponibles pasa a comer
                    cout<<"Filosofo id: "<<id_asiento<<" tomó los dos tenedores "<<IZQUIERDA(id_asiento)<<" - "<<DERECHA(id_asiento)<<endl;
                    tenedores[IZQUIERDA(id_asiento)]=tenedores[DERECHA(id_asiento)]=1;
                    // cada vez que se come el estomago aumenta, como lo pedido en el punto e
                    estomago+=25;
                    cout<<"y estoy comiendo..., mi estomago tiene"<<estomago<<endl;
                    tenedores[IZQUIERDA(id_asiento)]=tenedores[DERECHA(id_asiento)]=0;
            }
            else{//en caso estén ocupados esperará por estos
                cout<<"Filosfo: "<<id_asiento<<" - Estoy esperando los tenedores..."<<endl;
            }
    }
    else
        usleep(2);
    m.unlock();
}
void pensar(int estomago, int id_asiento)
{
    mutex m;
    m.lock();
    if(estomago>0){//evaluamos si su estomago aun tiene algo
            //este numero random significa un tiempo random el cual simularemos con un bucle for, punto e
            int num=rand();
            for(int i=0;i<num;i++){}
            cout<<"Filosofo id: "<<id_asiento<<", estoy pensando...";
            cout<<" y Mi estomago tiene: "<<estomago<<endl;
            estomago=estomago-25;
            //cada vez que estemos en estado pensando, el estomago disminuira 25 para representar que se tiene hambre, como lo pedido en el punto d
    }
    else
        cout<<"Filosofo: "<<id_asiento<<" murio de hambre :( "<<endl;
    m.unlock();
}
void *filosofo(void * id)
{
    int id_asiento=*((int*)id);

    while(true){
        comer(tenedores,id_asiento,estomago);
        double inicio=clock();
        pensar(estomago, id_asiento);
        double fin=clock();
        double total=(double(fin-inicio)/CLOCKS_PER_SEC);
        if(total>=0.01)//si piensa más de 0.01 segundos significa que estuvo esperando mucho por comer y morirá de hambre, como lo pedido en el punto g
            cout<<"Filosofo: "<<id_asiento<<" Murió de hambre esperando mucho"<<total<<endl;
    }
    pthread_exit(NULL);
}

int main()
{

    cout<<"Ingrese numero de filosofos comensales: ";
    cin>>n;
    pthread_t threads[n];
    for (int i=0;i<n;i++){
        pthread_create(&threads[i], NULL,filosofo,(void *)&i);
        //inicializamos nuestros hilos los cuales son nuestros filosofos comensales, como lo pedido en el punto a
    }
    for(int i=0;i<n;i++)
      pthread_join(threads[i], NULL);
      //Creando los join porqur tenemos que esperar que terminen los demás hilos
    pthread_exit(NULL);
    return 0;
}

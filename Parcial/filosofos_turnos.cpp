#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;
const int N = 10;
// se define una cantidad de N filosofos comensales, como se pide en el punto b
int PENSANDO = 0;
// el filósofo está pensando
int HAMBRIENTO = 1;
// el filósofo tiene hambre y quedrá agarrar los tenedores
int COMIENDO = 2;
// el filosofo está comiendo
int estomago=50;
//definimos una variable estomago como se pide en el punto c
int lleno=100;
//esta variable lleno nos ayuda a evaluar cuando un filosfo está lleno y por tanto debe dejar de comer, como se pide en el punto f
#define IZQUIERDO (i+N-1)%N
// número del vecino izquierdo de i
#define DERECHO (i+1)%N
// número del vecino derecho de i
int estado[N];
 // arreglo que lleva registro del estado de todos
mutex s[N];
// un semáforo por filósofo
//este recurso nos ayudará con el problema del deadlock
void tomar_tenedores(int i);
//definiendo funcion tomar_tenedores
void devolver_tenedores(int i);
//definiendo funcion devolver tenedores
void probar(int i);
//definiendo funcion probar esta funcion probará si podemos tomar los tenedores
void pensar(int i){
    //pensar
}
void comer(int i)
{
    //comer
}
void filosofo(int i)
// i es igual al id del filosofo
{
	while(true){
        // el filosofo vive pensando y comiendo (se repite en forma indefinida)
        double inicio=clock();
		pensar(i);
        double fin=clock();
        double total=(double(fin-inicio)/CLOCKS_PER_SEC);
        if(total>=0.01) cout<<" Filosofo "<<i<<"murio de hambre, esperando mucho"<<endl;                                                                       // el filósofo está pensando
		tomar_tenedores(i);                                                                         // adquiere dos tenedores o se bloquea
		comer(i);                                                                                   // comiendo
		devolver_tenedores(i);                                                                      // poniendo de vuelta ambos tenedores en la mesa
	}
}
void tomar_tenedores(int i)                                                                         // adquiere dos tenedores o se bloquea
{
    cout<<"El filosofo "<<i<<" tomando tenedores"<<endl;
    mutex m;
    m.lock();                                                                                       //para poder probar si puedo tomar tenedores primero debo hacer un lock
	estado[i] = HAMBRIENTO;                                                                         // el filósofo i tiene hambre
	probar(i);                                                                                      // intenta agarrar los dos tenedores
	m.unlock();                                                                                     //quitamos el lock y podemos seguir
	cout<<"El filosofo "<<i<<" Esperando que los tenedores se desocupen"<<endl;
	m.lock();                                                                                       //se bloquea si no se adquirieron los tenedores
}
void devolver_tenedores(int i)//devolvemos los tenedores
{
    //se hará uso del mutex para manejar nuestra seccion critica, ya que nuestros hilos querran entrar todos al mismo tiempo
    mutex m;
    m.lock();
    // hacemos lock para poder trabajar con los tenedores
    if(estomago>0){ //evaluamos si su estomago aun tiene algo
        int num=rand();
        //este numero random significa un tiempo random el cual simularemos con un bucle for, punto e
        for(int i=0;i<num;i++){}
        estado[i] = PENSANDO;
        cout<<"Filosofo: "<<i<<" estoy pensando y mi estomago tiene: "<<estomago<<endl;
        estomago-=25;
        //cada vez que estemos en estado pensando, el estomago disminuira 25 para representar que se tiene hambre, como lo pedido en el punto d
        probar(IZQUIERDO);// verifico si mi vecino izquierdo puede comer
        probar(DERECHO);// verifico si mi vecino derecho puede comer
    }
	else { // en caso de que el estomago sea 0, esto significará que nuetro filosofo murio de hambre, punto g
        cout<<" Filosofo "<<i<<" murio de hambre "<<endl;
	}
	m.unlock();
}
void probar(int i)
{
    //intentar agarrar los tenedores
    cout<<"El filosofo "<<i<<" comprobando que los tenedores esten libres"<<endl;
	if (estado[i] == HAMBRIENTO && estado[IZQUIERDO] != COMIENDO && estado[DERECHO] != COMIENDO) {  //comprobando que los tenedores esten libres para poder comer
        if(estomago<=lleno){ //evaluamos si nuestro filosofo está lleno, como lo pedido en el punto f
            int num=rand();
            //este numero random significa un tiempo random el cual simularemos con un bucle for, punto e
            for(int i=0;i<num;i++){}
            estado[i] = COMIENDO;
            estomago+=25; // cada vez que se come el estomago aumenta, como lo pedido en el punto e
            cout<<"Filosofo "<<i<<" estoy comiendo y mi estomago tiene: "<<estomago<<endl;

        }
        else {
            //en caso de estar lleno le damos un sleep, para que en este tiempo pueda pasar a pensar y bajar el estomago para que tenga hambre de nuevo
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        s[i].unlock();
        // quitamos el lock y podemos seguir (aquí trabajamos con el array)
	}
}
int main()
{
	vector<thread> filosofos_v;
	for(int i = 0; i < 5; i++)
	{
        filosofos_v.push_back(thread( filosofo,i));
        //inicializamos nuestros hilos los cuales son nuestros filosofos comensales, como lo pedido en el punto a
    }
    for(int i = 0; i < 5; i++)
    {
        filosofos_v[i].join();
        //Creando los join porqur tenemos que esperar que terminen los demás hilos
    }
	return 0;
}

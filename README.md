# SO-Ex_Parcial
Archivos del examen parcial

Explicación de la solución al problema de los filósofos comensales
Caso Cíclico
Fue trabajado con C++, hicimos uso de pthreads y de mutex, pero para tal necesitamos la librería #include <unistd.h>, #include <mutex>

Para la solución del problema del caso cíclico, como se vio explicado el filósofo sólo puede comer en su turno, para tal la propuesta 
de nuestra solución fue:
Manejamos los asientos de los filósofos en un vector, para así pasar al siguiente y al siguiente …, siendo de esta manera que pasan 
uno a uno a comer.
Para tal acción de comer, verificamos que ambos tenedores se encuentren disponibles, esto lo manejamos con un vector booleano 
donde nos dice si el tenedor se encuentra disponible o no. Hacemos uso del método sleep para cuando alguno de los dos tenedores 
no se encuentra disponibles entonces tendría que esperar por estos.
El filósofo pasa a pensar después de haber comido, esto le daría hambre y lo representamos disminuyendo una variable estómago. 
Se implementó la función filósofo con un id_asiento y su variable estómago, aquí se representará su vida llamando a las 
funciones comer() y pensar().  Además se tomará el tiempo que le toma pensar, ya que si supera los 0.01 segundos 
lo tomaremos como si hubiera muerto de hambre. Y para nuestras secciones críticas utilizaremos el mutex en las funciones comer
y pensar es aquó donde se dan estas secciones.
En nuestro Main(), se crean los respectivos hilos que nos representará nuestros N filosofos, para ejecutar nuestra función 
filósofo() la cual simula la vida de estos.

Caso Varios turnos

Para tal caso usamos el lenguaje C++, threads y mutex.
Para el manejo de los turnos se creó un arreglo de estados en el cual se verifica si se encuentran comiendo,
pensando o está hambriento y así trabajar con varios filósofos a la vez.
Para evitar el deathlock usamos los semáforos en vez de darle un tiempo por turno ya que nos pareció una solución más óptima.
Al momento de ingresar un turno el filósofo debe agarrar los tenedores (función tomar_tenedores()) en esta función
cambiamos el estado de hambriento del filósofo y probamos si podemos tomar ambos tenedores ( función probar() ) de no 
poder tomarlos se bloquea. Luego de esto tenemos que devolver los tenedores para ello usamos el estado pensando y probamos si 
el filósofo de la izquierda y de la derecha pueden comer (función probar() ).
En el main se creo un vector de filósofos (hilos) y los ejecutamos. 


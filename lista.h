#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>
#include <stdbool.h>


typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

// Crea una lista enlazada.
// Post: devuelve una nueva lista enlazada vacía.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos incertados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista.Este elemento, pasara a ser el primero.
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista. Este elemento, pasara a ser el ultimo
// de la lista.
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene el valor del largo de la lista. Si la lisa tiene elementos,
// se devuelve el valor del largo, si esta vacia se devuelve 0.
// Pre: la lista fue creada.
// Post: se devolvio el valor del largo de la lista. 
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Crea un iterador externo.
// Pre: la lista fue creada.
// Post: devuelve un nuevo iterador externo apuntando al primer elemento de la lista,
// si esta tiene elementos, o apuntando al ultimo elemento de la lista, si esta esta vacia.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador al siguente elemento y devuelve verdadero o falso, dependiendo si se pudo realizar.
// Pre: la lista fue creada y el iterador fue creado. Mientras se utiliza el iterador, no pueden utilizarse
// primitivas de la lista, que la modifiquen.
// Post: Si el iterador esta apuntando al final de la lista, devuelve false.
// Sino, el iterador actual apunta a su siguiente elemento,
// y el anterior apunta a su siguiente, que es el antiguo actual.  
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el valor del elemento de la lista apuntado por el iterador actual.
// Pre: la lista y el iterador fueron creados .Mientras se utiliza el iterador, no pueden utilizarse
// primitivas de la lista, que la modifiquen.
// post: se devolvió el  elemento actual de la lista, cuando no está vacío. 
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero o falso dependiendo si el iterador apunta o no al final de la lista.
// pre: la lista y el iterador fueron creados.Mientras se utiliza el iterador, no pueden utilizarse
// primitivas de la lista, que la modifiquen.
// Post: si el iterador apunta al final de la lista, devuelve true, sino false.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador creado.
// Pre: la lista y el iterador fueron creados. Mientras se utiliza el iterador, no pueden utilizarse
// primitivas de la lista, que la modifiquen.
// Post: se elimino el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento a la lista. Este elemento, pasara a ser actual al que apunta el iterador.
// Devuelve falso en caso de error.
// Pre: la lista y el iterador fueron creados.
// Post: se agregó un nuevo elemento a la lista en la posicion apuntada por el iterador actual.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento apuntado por el iterador actual de la lista. Si la lista tiene elementos, se quita el
// elemento apuntado por el iterador de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista  y el iterador fueron creados.
// Post: se devolvió el valor del elemento eliminado, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_iter_borrar(lista_iter_t *iter);

// Recorre los elementos de la lista y les aplica la funcion visitar siempre y cuando esta devuelva true.Si tiene elementos,
// a cada uno de los elementos de la lista le aplica la funcion visitar, mientras esta devuelva true.
// Pre: la lista fue creada .
// post: se aplico la funcion visitar para cada uno de los elementos de la lista o hasta que visitar devolvio false. 
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);
#endif
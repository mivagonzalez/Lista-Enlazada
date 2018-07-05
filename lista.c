#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include <stdlib.h>

typedef struct nodo{
	void* dato;
	struct nodo* proximo;
} nodo_t;

struct lista {
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;
};

struct lista_iter {
	nodo_t* actual;
	nodo_t* anterior;
	lista_t* lista;
};

lista_t* lista_crear(){
	lista_t* lista = malloc (sizeof(lista_t));
	if(!lista) return NULL;
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == 0 && lista->primero == NULL && lista->ultimo == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo) return false;
	nodo->dato = dato;
	if (lista_esta_vacia(lista)){
		lista->ultimo = nodo;
		nodo->proximo = NULL;
	}else{
		nodo->proximo = lista->primero;
	}
	lista->primero = nodo;
	lista->largo ++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = malloc (sizeof(nodo_t));
	if(!nodo)return false;
	nodo->dato = dato;
	if (lista_esta_vacia(lista)){
		lista->primero = nodo;
	}else{
		lista->ultimo->proximo = nodo;
	}
	lista->ultimo = nodo;
	nodo->proximo = NULL;
	lista->largo ++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista)){
		return NULL;
	}
	nodo_t* aux = lista->primero;
	lista->primero = lista->primero->proximo;
	if (lista->largo == 1) {
		lista->ultimo = NULL;
	}
	void * valor = aux->dato;
	free(aux);
	lista->largo --;
	return valor;
}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->ultimo->dato;
}
size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
 	while (!lista_esta_vacia(lista)){
 		void* aux = lista_borrar_primero(lista);
		if (destruir_dato){
			destruir_dato(aux);
		}
	}
	free (lista);
}


lista_iter_t* lista_iter_crear(lista_t *lista){
	lista_iter_t* nuevo_lista_iter = malloc(sizeof(lista_iter_t));
	if(! nuevo_lista_iter) return NULL;
	nuevo_lista_iter->lista = lista;
	if (nuevo_lista_iter->lista->largo == 0){
		nuevo_lista_iter->actual = NULL;
	}else{
		nuevo_lista_iter->actual = lista->primero;
	}
	nuevo_lista_iter->anterior = NULL;
	return nuevo_lista_iter;
}


bool lista_iter_al_final(const lista_iter_t *iter){
	return((iter->actual == NULL && iter->anterior != NULL) || iter->lista->largo == 0);
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (lista_iter_al_final(iter)) return NULL;
	return iter->actual->dato;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_avanzar(lista_iter_t* iter){
	if(lista_iter_al_final(iter)) return false;
	iter->anterior = iter->actual; 
	iter->actual = iter->actual->proximo;
	return true;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t* nodo = malloc (sizeof (nodo_t));
	if (!nodo) return false;
	nodo->dato = dato;
	if (!iter->anterior){
		iter->lista->primero = nodo;
	}else{
		iter->anterior->proximo = nodo;
	} 
	if (lista_iter_al_final(iter)){
		iter->lista->ultimo = nodo;
	}
	nodo->proximo = iter->actual;
	iter->actual = nodo;
	iter->lista->largo ++;
	return true;
}

void* lista_iter_borrar(lista_iter_t* iter){		
	if(lista_iter_al_final(iter)) return NULL;
	nodo_t* aux = iter->actual;
	if (iter->anterior){
		iter->anterior->proximo = iter->actual->proximo;
	}
	if (iter->actual && ! iter->anterior){
		iter->lista->primero = iter->lista->primero->proximo;
	}
	if (iter->actual == iter->lista->ultimo){
		iter->lista->ultimo = iter->anterior;
	}
	iter->actual = iter->actual->proximo;
	void* valor = aux->dato;
	free (aux);
	iter->lista->largo--;
	return valor;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	if (lista_esta_vacia(lista)) return;
	nodo_t* aux = lista->primero;
	while (aux){
 		if (!visitar(aux->dato, extra)) return;
		aux = aux->proximo;
	}
}
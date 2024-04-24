#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
  int pos = hash(key, map->capacity);
  
  // solveCollision, si hay colisiones avanza hasta encontrar un espacio libre
  while (map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) != 0) {
      pos = (pos + 1) % map->capacity;
}
  Pair* newElem = createPair(key, value);
  map->buckets[pos] = newElem;
  map->size++;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  
  return map;
}

void eraseMap(HashMap * map,  char * key) 
{   
int pos = hash(key, map->capacity);

  // Avanza hasta que las llaves coincidan o llege a una casilla NULL
  while (map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) != 0) 
  {
    pos = (pos + 1) % map->capacity;
  }
  // Si llega a una casilla NULL significa que no esta en la lista, devuelve NULL
  if (map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) == 0) 
  {
        map->buckets[pos]->key = NULL;
        map->size--;
    }
}

Pair * searchMap(HashMap * map,  char * key)
{   
int pos = hash(key, map->capacity);

  // Avanza hasta que las llaves coincidan o llega a una casilla NULL
  while (map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) != 0) 
  {
    pos = (pos + 1) % map->capacity;
  }
  // Si llega a una casilla NULL significa que no esta en la lista, devuelve NULL
  if (map->buckets[pos] == NULL)
    return NULL;
    
  else
  {
    map->current = pos;
    return map->buckets[pos];
  }
}

Pair * firstMap(HashMap * map) 
{
  // primera posicion del arreglo con un dato
  int pos = map->current; 

  while (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL) 
  {
    pos = (pos + 1) % map->capacity;
  }

  map->current = pos;
  
  return map->buckets[pos];
}

Pair * nextMap(HashMap * map) 
{
  int pos = map->current + 1;
  
  while (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL) 
  {
    pos = (pos + 1) % map->capacity;
  }
  
  map->current = pos;
  
  return map->buckets[pos];
}

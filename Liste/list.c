// creazione, distruzione, lista vuota? Numero elementi, inserimento, rimozione nodo
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo nodo_t;
struct nodo {
  int dato;
  nodo_t* precedente;
  nodo_t* successivo;
};

typedef struct lista lista_t;
struct lista {
  nodo_t* testa;
};

lista_t* creazione_lista() {
  lista_t* lista = (lista_t*) malloc(sizeof(lista_t));  //creazione
  if (lista == NULL) {
    printf("Allocazione della lista fallita\n");
    return NULL;
  }
  return lista;
}

bool lista_vuota(lista_t* lista) {
  if (lista->testa == NULL) 
    return true;
  else  
    return false;
}

void rimozione_lista(lista_t* lista) {
  if(!lista_vuota(lista))
  {
    nodo_t* p = lista->testa;
    nodo_t* q;
    while (p->successivo != NULL){
      q = p;
      p = q->successivo;
      free(q);
    }
    free(p);
  }
  free(lista);
  printf("Lista rimossa!\n");
}

int numero_elementi(lista_t* lista) {
  if (lista_vuota(lista))
    return 0;
  else {
    int contatore = 1;
    nodo_t* p = lista->testa;
    nodo_t* q;
    while (p->successivo != NULL) {
      contatore++;
      q = p;
      p = q->successivo; 
    }
    return contatore;
  }
}

nodo_t* creazione_nodo(int dato) {
  nodo_t* nodo = (nodo_t*) malloc(sizeof(nodo_t));  //creazione
  if (nodo == NULL) {
    printf("Allocazione del nuovo nodo non riuscita\n");
    return NULL;
  }
  nodo->dato = dato;
  return nodo;
}

int inserimento_nodo_coda(lista_t* lista, nodo_t* nodo) {
  if (lista->testa == NULL) {
    lista->testa = nodo;
  } else {
    nodo_t* p;
    nodo_t* q;
    p = lista->testa;
    do {
      q = p->successivo;
      if (q != NULL)         // devo andare ancora avanti
        p = q;
    } while (q != NULL);
    p->successivo = nodo;
    nodo->precedente = p;
  }
  printf("Nodo inserito\n");
  return 0;
}

int inserimento_nodo_testa(lista_t* lista, nodo_t* nodo) {
  if (lista->testa == NULL) {
    lista->testa = nodo;
  } else {
    nodo_t* p = lista->testa;
    lista->testa = nodo;
    nodo->successivo = p;
    p->precedente = nodo;
  }
  return 0;
}

int inserimento_nodo_ricerca(lista_t* lista, nodo_t* nodo, int valore) {
  if (lista->testa == NULL){
    printf("Attenzione! Non ho trovato %d nella lista perché quest'ultima é vuota.\nQuindi ho inserito il tuo nuovo dato come primo elemento.\n", valore);
    lista->testa = nodo;
  } else {
    bool trovato = false;
    nodo_t* p = lista->testa;
    nodo_t* q;
    while (!trovato){
      if (p->dato == valore)
        trovato = true;
      else {
        if (p->successivo == NULL)
          break;
        else {
          q = p;
          p = q->successivo;
        }
      }
    }
    if (trovato) 
      printf("Nuovo elemento inserito correttamente dopo il valore %d\n", valore);
    else
      printf("Attenzione! Valore %d non trovato.\nInserito nuovo elemento in fondo alla lista.\n", valore);
    if (p->successivo != NULL){
      q = p->successivo;
      nodo->successivo = q;
      q->precedente = nodo;
    }
    p->successivo = nodo;
    nodo->precedente = p;
  }
  return 0;
}

void rimozione_nodo_testa(lista_t* lista) {
  if (lista_vuota(lista))
    printf("Non ci sono nodi.\n");
  else {
    nodo_t* p = lista->testa;
    if (p->successivo == NULL)
     lista->testa = NULL;
    else {
      lista->testa = p->successivo;
      p->successivo->precedente = NULL;
    }
    free(p);
    printf("Nodo rimosso.\n");
  }
}

void rimozione_nodo_coda(lista_t* lista) {
  if(lista_vuota(lista))
    printf("La lista é vuota, non posso rimuovere nodi.\n");
  else {
    nodo_t* p = lista->testa;
    nodo_t* q;
    if (p->successivo == NULL){
      lista->testa = NULL;
    }
    else {
      while (p->successivo != NULL) {
        q = p;
        p = q->successivo;
      }
      q->successivo = NULL;
    }
    free(p);
    printf("Nodo rimosso\n");
  }
}

void rimozione_con_ricerca(lista_t* lista, int valore) {
  if (lista_vuota(lista)) {
    printf("La lista é vuota, il valore %d non esiste\n", valore);
  }
  else {
    nodo_t* p = lista->testa;
    nodo_t* q;
    bool trovato = false;
    if (p->successivo == NULL){
      if (p->dato == valore){
        lista->testa = NULL;
        free(p);
      }
      else {
        printf("Valore non trovato, nessun nodo é stato rimosso.\n");
      }
    } else {
      if (p->dato == valore){
        lista->testa = p->successivo;
        p->successivo->precedente = NULL;
        free(p);
        trovato = true;
      } else {
        while (p->successivo != NULL){
          q = p;
          p = q->successivo;
          if (p->dato == valore){
            if (p->successivo == NULL){
              q->successivo = NULL;
            } else {
              q->successivo = p->successivo;
              p->successivo->precedente = q;
            }
            free(p);
            trovato = true;
          }
        }
      }
    }
    if (trovato)
      printf("Nodo cancellato.\n");
    else 
      printf("Il valore %d non esiste\n", valore);
  }
}

void stampa(lista_t* lista) {
  if (lista_vuota(lista)){
    printf("La lista é vuota\n");
  } else {
    printf("Lista: ");
    nodo_t* p = lista->testa;
    while (p->successivo != NULL){
      printf("%d -> ", p->dato);
      p = p->successivo;
    }
    printf("%d -> vuoto\n", p->dato );
  }
}

int main(int argc, char** argv) {
  lista_t* lista = creazione_lista();
  stampa(lista);
  //creazione nodi:
  nodo_t* nodo1 = creazione_nodo(1);
  nodo_t* nodo2 = creazione_nodo(3);
  nodo_t* nodo3 = creazione_nodo(7);
  nodo_t* nodo4 = creazione_nodo(5);
  nodo_t* nodo5 = creazione_nodo(2);
  inserimento_nodo_ricerca(lista, nodo5, 8);
  inserimento_nodo_testa(lista, nodo1);
  inserimento_nodo_coda(lista, nodo2);
  inserimento_nodo_ricerca(lista, nodo3, 1);
  inserimento_nodo_ricerca(lista, nodo4, 4);
  stampa(lista);
  rimozione_nodo_coda(lista);
  stampa(lista);
  rimozione_nodo_testa(lista);
  stampa(lista);
  rimozione_con_ricerca(lista, 2);
  stampa(lista);
  rimozione_con_ricerca(lista, 4);
  stampa(lista);
  rimozione_lista(lista);
  return 0;
}
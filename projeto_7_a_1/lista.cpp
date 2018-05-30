#include <iostream>
using namespace std;

struct Registro {
  int valor;
  Registro *prox;
}

struct Lista {
  Registro *inicio;
  Registro *fim;
  int qtd;
};

Lista * inicializar(){
  Lista *l = new Lista;
  l->inicio = NULL;
  l->fim    = NULL;
  l->qtd    = 0;
  return l;
}

void inserir(Lista *l, int valor){

  Registro *reg = new Registro;

  if(reg == NULL){
    exit(-1);
  }

  reg->valor = valor;

  if (l->inicio == NULL) {
    l->inicio = reg;
  } else {
    Registro *aux = l->inicio;
    while (reg->valor > aux->valor) {
      aux = aux->prox;
    }
  }

}

int main() {



  return 0;
}

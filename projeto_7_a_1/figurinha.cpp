/*

****************************************
*         Projeto 7 a 1                *
****************************************
* Pacote Novo          *     Ok        *
****************************************
* Pilha de Repetidos   *               *
****************************************
* Album                *               *
****************************************
* Relatórios           *               *
****************************************
* Troca de figurinhas  *               *
****************************************
* Colar no album       *               *
****************************************

*/
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

struct Figurinha {
  int figurinha;
  Figurinha *prox;
};

//Pacote de figurinhas
struct Pacote {
  Figurinha *topo;
  int qtd;
};

Pacote * inicializarPacote(){
  Pacote *p = new Pacote;
  p->topo = NULL;
  p->qtd  = 0;
}

void verificaAlbum(Pacote *p){
  
}

//ESSA FUNÇÃO GERA UM PACOTE NOVO DE FIGURINHAS
void comprarFigurinha(Pacote *p){

  for(int i = 0; i < 5; i++){

    Figurinha *fig = new Figurinha;

    if(fig == NULL)
      exit(-1);

    fig->figurinha = rand() % 682;

    cout << fig->figurinha << endl;

    if(fig->figurinha == 0)
      fig->figurinha++;

    fig->prox = p->topo;
    p->topo = fig;
    p->qtd++;
  }

}

void imprimeFigurinhas(Pacote *p){

  if(p->topo == NULL){

    cout << "Não há figurinhas para serem mostradas.\n";

  } else {

    Figurinha *aux = new Figurinha;

    aux = p->topo;
    cout << "Figurinhas: ";
    while(aux != NULL){
      cout << aux->figurinha << " ";
      aux = aux->prox;
    }
    cout << endl << endl;
    delete aux;

  }
}

void destruirPacotes(P)

int main(){

  srand(time(NULL));

  Pacote *p = inicializarPacote();

  comprarFigurinha(p);

  imprimeFigurinhas(p);

  return 0;
}

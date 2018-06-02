#include <iostream>
#include <cstdlib>
#include <locale.h>
using namespace std;

struct Dados{
  int valor;
  Dados *prox;
};

struct Lista{
  Dados *head;
  int qtd;
};

static Dados *aux      = NULL; //Nó auxiliar para valor atual tanto para inserção como para exclusão
static Dados *anterior = NULL; //Nó auxiliar para valor anterior tanto para inserção como para exclusão

Lista * inicializar(){

  Lista *l  = new Lista;
  l->head   = NULL;
  l->qtd    = 0;

  return l;
}

void inserir(Lista *lista){

  Dados *novo = new Dados; //O novo elemento sendo alocado na memoria

  bool resposta = false; //Controla para saber se a ordenação foi feita

  aux = lista->head; //Nó auxiliar recebendo o valor da cabeça da lista

  if(novo == NULL){ //Caso nao tenha memoria o suficiente sai do programa

    exit(-1);

  } else {

    //pegando o valor
    cout << "Digite o valor que deseja inserir: ";
    cin >> novo->valor;

    //Se o elemento for o primeiro da lista ou menor do que o primeiro elemento da lista
    if(lista->head == NULL || novo->valor < lista->head->valor){

      novo->prox  = lista->head;
      lista->head = novo;
      lista->qtd++;

    } else {

      /********** INSERTION SORT *************/

      while (resposta == false) {

        anterior = aux; 
        aux      = aux->prox;

        if (aux == NULL) {

          anterior->prox = novo;
          novo->prox     = NULL;
          resposta = true;
          lista->qtd++;

        } else {

          if (aux->valor > novo->valor){
            anterior->prox = novo;
            novo->prox     = aux;
            resposta       = true;
            lista->qtd++;
          }

        }
      }
    }
  }
}

void remover(Lista *lista, int valor){

  aux = lista->head; //Nó auxiliar recebendo a cabeça da lista

  if(aux == NULL){

    cout << "Não há elementos para serem removidos.\n\n";

  } else {

    //Enquanto o proximo for diferente de NULL e o valor de aux for diferente do valor digitado
    while (aux->prox != NULL && aux->valor != valor) {
      anterior = aux;
      aux      = aux->prox;
    }

    if (aux->valor == valor) {

      //Caso o elemento à ser removido for do meio ou final da lista
      if(anterior != NULL)
        anterior->prox = aux->prox;

      //Se o elemento a ser removido for a cabeça da lista
      if(anterior == NULL && aux->prox != NULL)
        lista->head = aux->prox;

      delete aux; //Liberando a memoria
      cout << "Valor removido com sucesso.\n\n";

      //Quando a quantidade de elementos chegar a zero, a cabeça da lista será zerada (NULL)
      lista->qtd--;
      if(lista->qtd == 0){
        lista->head = NULL;
      }

    } else if (aux->prox == NULL) {
      cout << "Valor não encontrado para a remoção.\n\n";
    }
  }
}

void mostrar(Lista *lista){

  if(lista->head == NULL){

    cout << "Não há elementos na lista.\n\n";

  } else {

    aux = lista->head;

    cout << "Lista: ";
    while(aux != NULL){
      cout << aux->valor << " ";
      aux = aux->prox;
    }
    cout << endl << endl;

  }
}

void buscar(Lista *lista, int valor){

  int i = 1; //contador de posição

  Dados *aux = lista->head;

  while (aux->prox != NULL && aux->valor != valor) {
    aux = aux->prox;
    i++;
  }

  if (aux->valor == valor) {
    cout << "Valor encontrado na posição: " << i << endl << endl;
  } else if(aux->prox == NULL){
    cout << "Valor não encontrado.\n\n";
  }

}

int main(){

  setlocale(LC_ALL, "Portuguese");

  Lista *lista = inicializar();

  int opcao = 0, valor = 0;

  do {

    cout << "*** Lista ***\n\n";
    cout << "1 - Inserir\n";
    cout << "2 - Remover\n";
    cout << "3 - Mostrar\n";
    cout << "4 - Buscar\n";
    cout << "5 - Sair\n\n";
    cout << "Digite o opção desejada: ";

    cin >> opcao;

    switch (opcao) {

      case 1:
        inserir(lista);
      break;

      case 2:

        cout << "Digite o valor que deseja remover: ";
        cin >> valor;

        remover(lista, valor);

      break;

      case 3:
        mostrar(lista);
      break;

      case 4:

        cout << "Digite o valor que deseja buscar: ";
        cin >> valor;

        buscar(lista, valor);

      break;

      case 5:
      break;

      default:
        cout << "Valor inválido!\n";
      break;
    }
  } while(opcao != 5);

  return 0;
}

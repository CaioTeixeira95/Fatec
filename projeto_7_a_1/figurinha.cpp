/*
****************************************
*         Projeto 7 a 1                *
****************************************
* Pacote Novo          *     Ok        *
****************************************
* Pilha de Repetidos   *     Ok        *
****************************************
* Album                *     Ok        *
****************************************
* Relatórios           *     Ok        *
****************************************
* Troca de figurinhas  *     Ok        *
****************************************
* Gravar em arquivos   *     Ok        *
****************************************
* Ler de arquivos      *     Ok        *
****************************************
*/
#include <iostream>
#include <cstdlib>
#include <locale.h>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

struct Figurinha {
  int figurinha;
  Figurinha *prox;
};

//Pacote de figurinhas
struct Pacote {
  Figurinha *head;
  int qtd;
};

/* AUXILIAR NA BUSCA DE FIGURINHA NO ALBUM */
static Figurinha *aux = NULL;

/* FIGURINHAS ATUAIS AUXILIARES */
static Figurinha *aux_album           = NULL;
static Figurinha *aux_pacoteRepetidas = NULL;

/* FIGURINHAS ANTERIORES AUXILIARES */
static Figurinha *anterior_album           = NULL;
static Figurinha *anterior_pacoteRepetidas = NULL;

/* VARIAVEL QUE GRAVA E LE ARQUIVOS */
fstream arquivo;

Pacote * inicializarPacote();
void figurinhaAvulsa(Pacote *album, Pacote *pacoteRepetidas);
void trocarFigurinha(Pacote *album, Pacote *pacoteRepetidas);
void comprarFigurinha(Pacote *album, Pacote *pacoteRepetidas);
int verificaAlbum(Figurinha *novaFigurinha, Pacote *album, Pacote *pacoteRepetidas);
bool buscarAlbum(Pacote *album, int figurinha);
void imprimeFigurinhas(Pacote *p, int x);
void imprimeFigurinhasFaltantes(Pacote *album);
void destruir(Pacote *repetidas, Pacote *album);

void salvarArquivo(Pacote *album, Pacote *pacoteRepetidas);
void carregarArquivo(Pacote *album, Pacote *pacoteRepetidas);

int main(){

  setlocale(LC_ALL, "Portuguese");
  srand(time(NULL));

  Pacote *album           = inicializarPacote();
  Pacote *pacoteRepetidas = inicializarPacote();

  int opcao = 0;
  int valor = 0;

  do {

    cout << "*** Album da Copa do Mundo da Russia de 2018 ***\n\n";
    cout << "1 - Novo pacote de figurinha\n";
    cout << "2 - Colar figurinha avulsa\n";
    cout << "3 - Trocar figurinha\n";
    cout << "4 - Mostrar Album\n";
    cout << "5 - Figurinhas repetidas\n";
    cout << "6 - Figurinhas que faltam\n";
    cout << "7 - Buscar figurinha\n";
    cout << "8 - Sair\n\n";

    cout << "9  - Salvar progresso em um arquivo\n";
    cout << "10 - Carregar progresso\n\n";

    cout << "Digite o opção desejada: ";

    cin >> opcao;

    cout << "\n\n";

    switch (opcao) {

      case 1:
        comprarFigurinha(album, pacoteRepetidas);
      break;

      case 2:
        figurinhaAvulsa(album, pacoteRepetidas);
      break;

      case 3:
        trocarFigurinha(album, pacoteRepetidas);
      break;

      case 4:
        imprimeFigurinhas(album, 0);
      break;

      case 5:
        imprimeFigurinhas(pacoteRepetidas, 1);
      break;

      case 6:
        imprimeFigurinhasFaltantes(album);
      break;

      case 7:

        cout << "Digite a figurinha que deseja buscar: ";
        cin >> valor;

        if(buscarAlbum(album, valor) == false){
          cout << "Essa figurinha não está colada no album.\n\n";
        } else {
          cout << "Essa figurinha está colada no album.\n\n";
        }

      break;

      case 8: //Sair do sistema
      break;

      case 9:
        salvarArquivo(album, pacoteRepetidas);
      break;

      case 10:
        carregarArquivo(album, pacoteRepetidas);
      break;

      default:
        cout << "Valor inválido!\n\n";
      break;
    }
  } while(opcao != 8);

  destruir(pacoteRepetidas, album);

  return 0;
}

Pacote * inicializarPacote(){

  Pacote *p = new Pacote;
  p->head   = NULL;
  p->qtd    = 0;

  return p;

}

/* ESSA FUNÇÃO COLA UMA FIGURINHA DIGITADA PELO USUARIO NO ALBUM */
void figurinhaAvulsa(Pacote *album, Pacote *pacoteRepetidas){
  system("clear");
  int figurinha;
  cout << "Digite a figurinha que deseja colar: ";
  cin >> figurinha;

  Figurinha *figN = new Figurinha;
  figN->figurinha = figurinha;
  if(verificaAlbum(figN, album, pacoteRepetidas) == 0){
    cout << "Figurinha colada no album.\n\n";
  } else {
    cout << "Figurinha repetida. Ela foi adicionada a sua pilha de repetidas.\n\n";
  }
}

/* ESSA FUNÇÃO GERA UM PACOTE NOVO DE FIGURINHAS */
void comprarFigurinha(Pacote *album, Pacote *pacoteRepetidas){
  system("clear");
  if(album->qtd == 681){
    cout << "Você completou o seu album da Copa do Mundo da Russia. Parabéns!\n\n";
    return;
  }

  int cont_album = 0; //Contador para saber quantas figurinhas foram coladas no album
  int cont_repetidas = 0; //Contador para saber quantas figurinhas são repetidas
  Figurinha *fig = NULL;

  for(int i = 0; i < 5; i++){

    Figurinha *fig = new Figurinha;

    if(fig == NULL)
      exit(-1);

    fig->figurinha = rand() % 682;

    if(fig->figurinha == 0)
      fig->figurinha++;

    if(verificaAlbum(fig, album, pacoteRepetidas) == 0)
      cont_album++;
    else
      cont_repetidas++;

  }

  if (cont_album > 0)
    cout << "Foram coladas " << cont_album << " figurinhas no seu album. Parabéns!\n";

  if (cont_repetidas > 0)
    cout << cont_repetidas << " figurinhas são repetidas. Tente trocá-las!\n";

  cout << "\n";

}

/* ESSA FUNÇÃO TROCA FIGURINHAS */
void trocarFigurinha(Pacote *album, Pacote *pacoteRepetidas){
  system("clear");
  int figurinha = 0, figurinhaRepetida = 0;
  cout << "Digite a figurinha que você está recebendo na troca: ";
  cin >> figurinha;
  //Se a figurinha que a pessoa deseja trocar já estiver no album
  if(buscarAlbum(album, figurinha) == true){
    cout << "Você já possui essa figurinha no album.\n\n";
  } else { //Se a figurinha não estiver no album
    cout << "Digite sua figurinha repetida que deseja trocar com a figurinha " << figurinha << ": ";
    cin >> figurinhaRepetida;
    //Se a figurinha que você irá dar em troca não tem na pilha de repetidas
    if (buscarAlbum(pacoteRepetidas, figurinhaRepetida) == false) {
      cout << "Figurinha não encontrada na pilha de repetidas.\n\n";
    } else { //Se a figurinha estiver na pilha de repetidas
      aux_pacoteRepetidas = pacoteRepetidas->head;

      //Se a figurinha for a cabeça da minha pilha de repetidas
      if(pacoteRepetidas->head->figurinha == figurinhaRepetida){
        pacoteRepetidas->head = aux_pacoteRepetidas->prox;
        delete aux_pacoteRepetidas;
        pacoteRepetidas->qtd--;
      } else { //Se a figurinha estiver no meio ou final da pilha

        while(aux_pacoteRepetidas->figurinha != figurinhaRepetida){
          anterior_pacoteRepetidas = aux_pacoteRepetidas;
          aux_pacoteRepetidas      = aux_pacoteRepetidas->prox;
        }

        if(aux_pacoteRepetidas->figurinha == figurinhaRepetida){
          anterior_pacoteRepetidas->prox = aux_pacoteRepetidas->prox;
          delete aux_pacoteRepetidas;
          pacoteRepetidas->qtd--;
        }

      }

      Figurinha *figTroca = new Figurinha;
      figTroca->figurinha = figurinha;
      verificaAlbum(figTroca, album, pacoteRepetidas);
      cout << "Figurinha trocada com sucesso!\n\n";

    }
  }

}

/* ESSA FUNÇÃO COLA FIGURINHAS NO ALBUM E COLOCA FIGURINHAS REPETIDAS NA LISTA DE REPETIDAS */
int verificaAlbum(Figurinha *novaFigurinha, Pacote *album, Pacote *pacoteRepetidas){
  system("clear");
  bool resposta = false; //Controla para saber se a ordenação foi feita
  aux_album = album->head; //Nó auxiliar recebendo o valor da cabeça da album

  if(buscarAlbum(album, novaFigurinha->figurinha) == false){ // True = figurinha repetida

    //Se a figurinha for a primeira do album ou menor do que a primeira figurinha do album
    if(album->head == NULL || novaFigurinha->figurinha < album->head->figurinha){

      novaFigurinha->prox = album->head;
      album->head = novaFigurinha;
      album->qtd++;

    } else {

      /********** INSERTION SORT NO ALBUM *************/
      while (resposta == false) {

        anterior_album = aux_album;
        aux_album      = aux_album->prox;

        if (aux_album == NULL) {

          anterior_album->prox = novaFigurinha;
          novaFigurinha->prox = NULL;
          resposta = true;
          album->qtd++;

        } else {

          if (aux_album->figurinha > novaFigurinha->figurinha){

            anterior_album->prox  = novaFigurinha;
            novaFigurinha->prox   = aux_album;
            resposta = true;
            album->qtd++;

          }
        }

      }
        /* FIM INSERTION SORT NO ALBUM */
    }

    return 0;

  } else { //Se a figurinha for repetida será inserida na lista de figurinhas repetidas

    resposta = false; //Controla para saber se a ordenação foi feita
    aux_pacoteRepetidas = pacoteRepetidas->head; //Nó auxiliar recebendo o valor da cabeça do pacoteRepetidas

    //Se a figurinha for a primeira do album ou menor do que a primeira figurinha do album
    if(pacoteRepetidas->head == NULL || novaFigurinha->figurinha < pacoteRepetidas->head->figurinha){

      novaFigurinha->prox = pacoteRepetidas->head;
      pacoteRepetidas->head = novaFigurinha;
      pacoteRepetidas->qtd++;

    } else {

      /********** INSERTION SORT NA LISTA DE REPETIDAS *************/
      while (resposta == false) {

        anterior_pacoteRepetidas = aux_pacoteRepetidas;
        aux_pacoteRepetidas      = aux_pacoteRepetidas->prox;

        if (aux_pacoteRepetidas == NULL) {

          anterior_pacoteRepetidas->prox = novaFigurinha;
          novaFigurinha->prox = NULL;
          resposta = true;
          pacoteRepetidas->qtd++;

        } else {

          if (aux_pacoteRepetidas->figurinha > novaFigurinha->figurinha){

            anterior_pacoteRepetidas->prox = novaFigurinha;
            novaFigurinha->prox = aux_pacoteRepetidas;
            resposta = true;
            pacoteRepetidas->qtd++;

          }
        }
      }
      /* FIM INSERTION SORT NA LISTA DE REPETIDAS */
    }

    return 1;
  }
}

/* ESSA FUNÇÃO SERVE PARA VERIFICAR SE A FIGURINHA ESTÁ NO ALBUM */
bool buscarAlbum(Pacote *album, int figurinha){

  if (album->head == NULL) {
    return false;
  }

  aux = album->head;

  while (aux->prox != NULL && aux->figurinha != figurinha) {
    aux = aux->prox;
  }

  if (aux->figurinha == figurinha) {
    return true;
  } else if(aux->prox == NULL){
    return false;
  }

}

/* IMPRIME O ALBUM E TAMBÉM A PILHA DE FIGURINHAS REPETIDAS*/
void imprimeFigurinhas(Pacote *p, int x){
  system("clear");
  if(p->head == NULL){
    cout << "Não há figurinhas para serem mostradas.\n\n\n";
  } else {

    Figurinha *aux = new Figurinha;
    int i = 0;

    aux = p->head;

    if(x == 0)
      cout << "Você tem " << p->qtd << " figurinha(s) no seu album. Sendo ela(s):\n";
    else
      cout << "Você tem " << p->qtd << " figurinha(s) repetida(s). Sendo ela(s):\n";

    while(aux != NULL){
      cout << aux->figurinha << " ";
      i++;
      if(i == 10){
        cout << endl;
        i = 0;
      }
      aux = aux->prox;
    }
    cout << endl << endl;
    delete aux;

  }
}

/* ESSA FUNÇÃO CALCULA QUANTAS FIGURINHAS ESTÃO FALTANDO, E DESCREVE QUAIS SÃO */
void imprimeFigurinhasFaltantes(Pacote *album){
  system("clear");
  if(album->qtd == 681)
    cout << "Você completou o seu album. Parabéns!\n\n";
  else{

    cout << "Faltam " << 681 - album->qtd << " figurinhas para você completar o seu album. Sendo elas:\n\n";
    int x = 0;

    for(int i = 1; i < 682; i++) {
      if(buscarAlbum(album, i) == false){
        cout << i << " ";
        x++;
        if(x == 10) {
          cout << endl;
          x = 0;
        }
      }
    }
    cout << "\n\n";
  }

}

/* ESSA FUNÇÃO SALVA O PROGRESSO EM UM ARQUIVO TXT */
void salvarArquivo(Pacote *album, Pacote *pacoteRepetidas){
  system("clear");
  if(album->head == NULL && pacoteRepetidas->head == NULL){
    cout << "Não progresso para ser salvo.\n\n";
  } else {

    aux_album = album->head;
    aux_pacoteRepetidas = pacoteRepetidas->head;

    if(album->head != NULL){
      arquivo.open("album.txt", ios::out);
      while(aux_album != NULL){
        arquivo << aux_album->figurinha << endl;
        aux_album = aux_album->prox;
      }
      arquivo.close();
    }

    if(pacoteRepetidas->head != NULL){
      arquivo.open("pacoteRepetidas.txt", ios::out);
      while(aux_pacoteRepetidas != NULL){
        arquivo << aux_pacoteRepetidas->figurinha << endl;
        aux_pacoteRepetidas = aux_pacoteRepetidas->prox;
      }
      arquivo.close();
    } else {
      cout << "Não figurinhas repetidas para serem salvas.\n\n";
    }

    cout << "Progresso salvo com sucesso.\n\n";
  }
}

/* ESSA FUNÇÃO CARREGA O PROGRESSO DE UM ARQUIVO TXT */
void carregarArquivo(Pacote *album, Pacote *pacoteRepetidas){

  system("clear");
  string figurinha;

  arquivo.open("album.txt", ios::in | ios::app);
  if(arquivo.is_open()){
    while(getline(arquivo, figurinha)){
          Figurinha *figArqN = new Figurinha;
          istringstream ss(figurinha);
          ss >> figArqN->figurinha;
          verificaAlbum(figArqN, album, pacoteRepetidas);
      }
      arquivo.close();
  } else {
      cout << "Não foi possivel abrir o arquivo.\n";
  }

  arquivo.open("pacoteRepetidas.txt", ios::in | ios::app);
  if(arquivo.is_open()){
      while(getline(arquivo, figurinha)){
          Figurinha *figArqR = new Figurinha;
          istringstream ss(figurinha);
          ss >> figArqR->figurinha;
          verificaAlbum(figArqR, album, pacoteRepetidas);
      }
      arquivo.close();
  } else {
      cout << "Não foi possivel abrir o arquivo.\n";
  }
  cout << "Progresso carregado com sucesso.\n\n";

}

void destruir(Pacote *repetidas, Pacote *album){

  Figurinha *figurinha = new Figurinha;

  while(repetidas->head != NULL){
    figurinha       = repetidas->head;
    repetidas->head = figurinha->prox;
    delete figurinha;
  }

  delete repetidas;

  while(album->head != NULL){
    figurinha   = album->head;
    album->head = figurinha->prox;
    delete figurinha;
  }

  delete album;

}

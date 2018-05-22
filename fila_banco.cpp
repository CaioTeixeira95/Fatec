#include <iostream>
#include <string.h>
using namespace std;

struct Cliente{
    string nome;
    int idade;
    Cliente *prox;
};

struct Fila{
    Cliente *inicio;
    Cliente *fim;
    int tamanho;
};

Fila * inicializar(){

    Fila *fi;

    fi = new Fila;

    fi->inicio  = NULL;
    fi->fim     = NULL;
    fi->tamanho = 0;

}

void insereCliente(Fila *fb){

    Cliente *novo_cliente;

    novo_cliente = new Cliente;

    if(novo_cliente == NULL){

        cout << "Fila está cheia!\n\n";

    } else {

        cout << "Digite o nome do cliente: ";
        cin >> novo_cliente->nome;

        cout << "Digite a idade do cliente: ";
        cin >> novo_cliente->idade;

        //Ele sempre apontará para NULL porque ele é o ultimo da fila!
        novo_cliente->prox = NULL;

        //Se o cliente for o primeiro a ser inserido
        //O inicio apontará para ele

        /* Senão a variavel "prox" do elemento que atualmente está no fim da fila
         * receberá o novo elemento, ou seja, ele passará a apontar para o
         * novo elemento que será o fim da fila */

        if(fb->fim == NULL){
            fb->inicio = novo_cliente;
        } else {
            fb->fim->prox = novo_cliente;
        }

        fb->fim = novo_cliente;
        fb->tamanho++;
    }

    cout << endl << endl;
}

void removeCliente(Fila *fb){

    if(fb->inicio == NULL){

        cout << "Não há clientes para serem atendidos!\n\n";

    } else {

        Cliente *aux;
        aux = new Cliente;

        aux        = fb->inicio;
        fb->inicio = aux->prox;

        //Se o inicio da fila for nulo, temos que atualizar o fim da fila para nulo também,
        //pois, todos os elementos foram excluidos
        if(fb->inicio == NULL){
            fb->fim = NULL;
        }

        cout << "*** Cliente atendido ***\n\n";
        cout << "Nome:\t" << aux->nome << endl;
        cout << "Idade:\t" << aux->idade << endl << endl;

        delete aux;
        fb->tamanho--;

    }

    cout << endl << endl;
}

void imprime(Fila *fb){

    if(fb->inicio == NULL){

        cout << "Não há clientes na fila!\n\n";

    } else {

        int i = 0;
        Cliente *cli;
        cli = new Cliente;

        cli = fb->inicio;

        while(cli != NULL){

            cout << "*** Cliente " << i + 1 << " ***\n";
            cout << "Nome:\t" << cli->nome << endl;
            cout << "Idade:\t" << cli->idade << endl << endl;

            cli = cli->prox;

            i++;

        }

    }

    cout << endl << endl;

}

void buscaCliente(Fila *fb){

    if(fb->inicio == NULL){

        cout << "Não há clientes para serem buscados!\n\n";

    } else {

        string nome;
        int i = 0, cont = 0;

        cout << "Digite o nome do cliente que deseja buscar: ";
        cin >> nome;

        Cliente *cli;
        cli = new Cliente;

        cli = fb->inicio;

        while(cli != NULL){

            if(cli->nome.compare(nome) == 0){

                cout << "\n*** Cliente Encontrado ***\n\n";
                cout << "Nome:\t" << cli->nome << endl;
                cout << "Idade:\t" << cli->idade << endl;
                cout << "Posição na fila:\t" << i + 1 << endl;
                cont++;
                break;

            } else {

                cli = cli->prox;

            }

            i++;

        }

        if(cont == 0){

            cout << "\nNenhum cliente encontrado\n\n";

        }

    }

}

void destruirFila(Fila *fb){

    Cliente *aux;
    aux = new Cliente;

    while(fb->inicio != NULL){

        aux = fb->inicio;
        fb->inicio = aux->prox;

        delete aux;

    }

    delete fb;

}

void menu(Fila *fb){

    int opcao = 0;

    do{

        cout << "*** Banco Fatec ***\n\n";
        cout << "1 - Incluir cliente\n";
        cout << "2 - Atender cliente\n";
        cout << "3 - Mostrar clientes\n";
        cout << "4 - Buscar clientes\n";
        cout << "5 - Sair\n\n";
        cin >> opcao;

        cout << endl << endl;

        switch(opcao){

            case 1:
                insereCliente(fb);
            break;

            case 2:
                removeCliente(fb);
            break;

            case 3:
                imprime(fb);
            break;

            case 4:
                buscaCliente(fb);
            break;

            case 5:
            break;

            default:
                cout << "Valor inválido!\n";
            break;

        }

    }while(opcao != 5);

    destruirFila(fb);

}

int main(){

    Fila *fb = inicializar();

    menu(fb);

    return 0;
}

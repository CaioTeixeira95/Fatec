#include <iostream>
#include <string.h>
#include <locale.h>
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

void insereCliente(Fila *fb, Fila *fp){

    char op;

    Cliente *novo_cliente;

    novo_cliente = new Cliente;

    if(novo_cliente == NULL){

        cout << "Fila está cheia!\n\n";

    } else {

        cout << "Digite o nome do cliente: ";
        cin >> novo_cliente->nome;

        cout << "Digite a idade do cliente: ";
        cin >> novo_cliente->idade;

        cout << "Cliente preferencial? [S\\N]\n";
        cin >> op;
        op = toupper(op);

        while(op != 'S' && op != 'N'){
            cout << "Valor inválido! Digite S para Sim e N para Não. [S\\N]\n";
            cin >> op;
            op = toupper(op);
        }

        //Ele sempre apontará para NULL porque ele é o ultimo da fila!
        novo_cliente->prox = NULL;

        if(op == 'N'){ //Caso não seja preferencial

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

        } else { //Caso seja preferencial

            if(fp->fim == NULL){
                fp->inicio = novo_cliente;
            } else {
                fp->fim->prox = novo_cliente;
            }

            fp->fim = novo_cliente;
            fp->tamanho++;

        }
    }

    cout << endl << endl;
}

void removeCliente(Fila *fb, Fila *fp){

    if(fb->inicio == NULL && fp->inicio == NULL){ //Caso ambas as filas estarem vazias

        cout << "Não há clientes para serem atendidos!\n\n";

    } else { //Caso pelo menos uma das filas não estiver vazia

        Cliente *aux;
        aux = new Cliente;

        if(fp->inicio != NULL){

            aux        = fp->inicio;
            fp->inicio = aux->prox;

            //Se o inicio da fila for nulo, temos que atualizar o fim da fila para nulo também,
            //pois, todos os elementos foram excluidos
            if(fp->inicio == NULL){
                fp->fim = NULL;
            }

            cout << "*** Cliente preferencial ***\n\n";
            cout << "Nome:\t" << aux->nome << endl;
            cout << "Idade:\t" << aux->idade << endl << endl;

            delete aux;
            fp->tamanho--;

        } else {

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

    }

    cout << endl << endl;
}

void imprime(Fila *fb, Fila *fp){

    if(fb->inicio == NULL && fp->inicio == NULL){

        cout << "Não há clientes na fila!\n\n";

    } else {

        int i = 0;
        Cliente *cli;
        cli = new Cliente;

        cout << "***** PREFERENCIAL *****\n\n";

        if(fp->inicio == NULL){

            cout << "Não há clientes na fila preferencial!\n\n";

        } else {

            cli = fp->inicio;

            while(cli != NULL){

                cout << "*** Cliente preferencial " << i + 1 << "º ***\n";
                cout << "Nome:\t" << cli->nome << endl;
                cout << "Idade:\t" << cli->idade << endl << endl;

                cli = cli->prox;

                i++;

            }

        }

        //FIM FILA PREFERENCIAL

        cout << "***** COMUM *****\n\n";

        if(fb->inicio == NULL){

            cout << "Não há clientes na fila comum!\n\n";

        } else {

            i = 0;

            cli = fb->inicio;

            while(cli != NULL){

                cout << "*** Cliente " << i + 1 << "º ***\n";
                cout << "Nome:\t" << cli->nome << endl;
                cout << "Idade:\t" << cli->idade << endl << endl;

                cli = cli->prox;

                i++;

            }

        }
    }

    cout << endl << endl;

}

void buscaCliente(Fila *fb, Fila *fp){

    if(fb->inicio == NULL && fp->inicio == NULL){

        cout << "Não há clientes para serem buscados!\n\n";

    } else {

        string nome;
        int i = 0, cont = 0;

        cout << "Digite o nome do cliente que deseja buscar: ";
        cin >> nome;

        Cliente *cli;
        cli = new Cliente;

        //Busca na fila preferencial
        if(fp->inicio != NULL){


            cli = fp->inicio;

            while(cli != NULL){

                if(cli->nome.compare(nome) == 0){

                    cout << "\n*** Cliente Preferencial Encontrado ***\n\n";
                    cout << "Nome:\t" << cli->nome << endl;
                    cout << "Idade:\t" << cli->idade << endl;
                    cout << "Posição na fila: " << i + 1 << endl;
                    cont++;
                    break;

                } else {

                    cli = cli->prox;

                }

                i++;

            }

        }

        //Busca na fila normal
        if(fb->inicio != NULL){

            cli = fb->inicio;

            while(cli != NULL){

                if(cli->nome.compare(nome) == 0){

                    cout << "\n*** Cliente Comum Encontrado ***\n\n";
                    cout << "Nome:\t" << cli->nome << endl;
                    cout << "Idade:\t" << cli->idade << endl;
                    cout << "Posição na fila: " << i + 1 << endl;
                    cont++;
                    break;

                } else {

                    cli = cli->prox;

                }

                i++;

            }

        }

        if(cont == 0){

            cout << "\nNenhum cliente encontrado\n\n";

        }

    }

}

void destruirFila(Fila *fb, Fila *fp){

    Cliente *aux;
    aux = new Cliente;

    //Deletando fila normal
    while(fb->inicio != NULL){

        aux = fb->inicio;
        fb->inicio = aux->prox;

        delete aux;

    }

    delete fb;

    //Deletando fila preferencial
    while(fp->inicio != NULL){

        aux = fp->inicio;
        fp->inicio = aux->prox;

        delete aux;

    }

    delete fp;

}

void menu(Fila *fb, Fila *fp){

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
                insereCliente(fb, fp);
            break;

            case 2:
                removeCliente(fb, fp);
            break;

            case 3:
                imprime(fb, fp);
            break;

            case 4:
                buscaCliente(fb, fp);
            break;

            case 5:
            break;

            default:
                cout << "Valor inválido!\n";
            break;

        }

    }while(opcao != 5);

    destruirFila(fb, fp);

}

int main(){

    setlocale(LC_ALL, "Portuguese");

    Fila *fb = inicializar();
    Fila *fp = inicializar();

    menu(fb, fp);

    return 0;
}

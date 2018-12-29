#include <iostream>
#include <locale.h>
using namespace std;

class Elevador{

  private:

      int andar_atual; // 0 = terreo
      int qtd_andares;
      int capacidade;
      int qtd_pessoas;

  public:

      Elevador(int qtd_andares, int capacidade){
        this->qtd_andares = qtd_andares;
        this->capacidade  = capacidade;
        this->qtd_pessoas = 0;
        this->andar_atual = 0;
      }

      void entra(){
        if(this->qtd_pessoas < this->capacidade){
          cout << "Passageiro entrou no elevador.\n";
          this->qtd_pessoas++;
        } else {
          cout << "Elevador lotado.\n";
        }
      }

      void sai(){
        if(this->qtd_pessoas > 0){
          cout << "Passageiro saiu no elevador.\n";
          this->qtd_pessoas--;
        } else {
          cout << "Elevador vazio.\n";
        }
      }

      void sobe(){
        if(this->andar_atual < this->qtd_andares){
          cout << "Elevador subindo.\n";
          this->andar_atual++;
        } else {
          cout << "Elevador no último andar.\n";
        }
      }

      void desce(){
        if(this->andar_atual > 0){
          cout << "Elevador descendo.\n";
          this->andar_atual--;
        } else {
          cout << "Elevador no térreo.\n";
        }
      }

      void get(){
        cout << "Elevador\n\n";
        cout << "Andar atual:\t" << this->andar_atual << endl;
        cout << "Qtd. de passageiros:\t" << this->qtd_pessoas << endl;
        cout << "Capacidade:\t" << this->capacidade << endl;
        cout << "Qtd. de andares:\t" << this->qtd_andares << endl << endl;
      }

};

int main() {

  setlocale(LC_ALL, "Portuguese");

  Elevador *e = new Elevador(5, 5);

  e->get();

  e->entra();
  e->entra();
  e->entra();
  e->entra();

  e->sai();
  e->sai();

  e->sobe();
  e->sobe();
  e->sobe();
  e->sobe();

  e->desce();
  e->desce();
  e->desce();

  e->get();

  return 0;
}

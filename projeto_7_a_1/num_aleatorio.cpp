#include <iostream>
#include <cstdlib>
using namespace std;

int main(){

  int num = 0, cont = 0;

  srand(time(NULL));

  while (num != 681) {

    num = rand() % 682;
    if(num == 0){
      cout << "**** Deu zero ****\n";
      cout << "Numero: " << num + 1 << endl;
    } else {
      cout << "Numero: " << num << endl;
    }
    cont++;
  }

  cout << "*** Contador ****\n Valor: " << cont << endl;

  return 0;
}

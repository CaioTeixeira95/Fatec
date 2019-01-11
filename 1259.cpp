#include <bits/stdc++.h>
using namespace std;

int main() {

  int n = 0, x = 0, valor = 0;
  vector<int> impares;
  vector<int> pares;
  vector<int> todos;

  cin >> n;

  while (x < n) {

    cin >> valor;

    if(valor % 2 == 0){
      pares.push_back(valor);
    } else {
      impares.push_back(valor);
    }

    x++;
  }

  auto ordReversed = [](int &a, int &b)->bool{
    return a > b;
  };

  sort(pares.begin(), pares.end());
  sort(impares.begin(), impares.end(), ordReversed);

  for(auto i:pares){
    todos.push_back(i);
  }

  for(auto i:impares){
    todos.push_back(i);
  }

  for(auto i:todos){
    cout << i << endl;
  }

  return 0;
}

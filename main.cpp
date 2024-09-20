
#include <cmath>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_bits(int x, int nvar) {
  vector<int> resultado;
  for (int i = nvar - 1; i >= 0; i--) {
    resultado.push_back((x & (1 << i)) != 0);
  }
  return resultado;
}

void array_expose(string name, const vector<string> &array) {
  cout << name << endl;
  for (const auto &item : array) {
    cout << item << endl;
  }
}

int formula(unsigned int target, vector<string> *array, vector<int> y,
            vector<string> var_names) {
  if (target != 0 && target != 1) {
    cerr << "target precisa ser binário: " << target << endl;
    return 1;
  }
  int nvar = var_names.size();

  for (int i = 0; i < pow(2, nvar); i++) {
    if (y[i] == target) {
      vector<int> vars = get_bits(i, nvar);
      string buf;
      for (int j = 0; j < vars.size(); j++) {
        if (vars[j] == 1) {
          buf += var_names[j];
        } else {
          buf += "~" + var_names[j];
        }
        if (j < vars.size() - 1)
          buf += (target == 1) ? " * " : " + ";
      }
      array->push_back(buf);
    }
  }
  return 0;
}

int main() {
  vector<int> y;
  vector<string> mintermo;
  vector<string> maxtermo;
  vector<string> var_names;

  int nvar;
  cout << "Número de variáveis: ";
  cin >> nvar;

  cout << "Nomes das variáveis: ";
  for (int i = 0; i < nvar; i++) {
    string temp;
    cin >> temp;
    var_names.push_back(temp);
  }

  // Receber os valores de y
  cout << "# |";
  for (int i = 0; i < nvar; i++) {
    cout << var_names[i] << " |";
  }
  cout << " Y\n";

  for (int i = 0; i < pow(2, nvar); i++) {
    while (true) {
      cout << i << " |";
      for (int j = 0; j < nvar; j++) {
        cout << get_bits(i, nvar)[j] << " |";
      }
      cout << " ";

      int buf;
      cin >> buf;

      if (buf == 1 || buf == 0) {
        y.push_back(buf);
        break;
      } else {
        cerr << "Insira um número válido (0 ou 1)" << endl;
      }
    }
  }

  // Gerar mintermos e maxtermos
  formula(1, &mintermo, y, var_names); // Mintermos (produto de somas)
  formula(0, &maxtermo, y, var_names); // Maxtermos (soma de produtos)

  // Expor os resultados
  array_expose("Mintermo:", mintermo);
  array_expose("Maxtermo:", maxtermo);

  return 0;
}

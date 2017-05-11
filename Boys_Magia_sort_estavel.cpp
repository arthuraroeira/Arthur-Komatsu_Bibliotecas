/*
  Para problemas que necessitam de manter a ordem de entrada.
  Se caso o problema for ordenado utilizando o quick_sort que é o sort, a ordem
pode se perder, pois se trata de um método de ordenação instável. Isto é, ele
pode trocar de posições itens com o mesmo valor.
  O método stable_sort não faz isso, pois se trata de um método de ordenação
estável, logo se tiver dois valores iguais eles serão mantidos em suas respecti-
vas posições iniciais.
*/

/*Exemplo: ordene a string de acordo com o seu tamanho e caso haja um empate no
tamanho ordene por ordem de entrada.*/

#include <bits/stdc++.h>
using namespace std;

bool cmp(string a, string b){
  if(a.size() > b.size())
    return true;
  else
    return false;
}

void printa(vector <string> st){
  for(int i=0; i<st.size(); i++){
    if(i!=0)
      cout << ' ' << st[i];

    else
      cout << st[i];
  }

  cout << endl;
}

int main(int argc, char const *argv[]) {
  string s = "sj a sa df r e w f d s a v c x z sd fd av sd er te";
  cout << "String inicial:\n" << s << endl;
  istringstream is(s);
  string a;
  vector <string> st, ins;

  while(is >> a)
    st.push_back(a);

  ins = st;

  sort(ins.begin(), ins.end(), cmp);
  cout << "\nString com metodo instavel:\n";
  printa(ins);

  stable_sort(st.begin(), st.end(), cmp);
  cout << "\nString com metodo estavel:\n";
  printa(st);
  return 0;
}

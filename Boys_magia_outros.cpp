#include <bits/stdc++.h>
using namespace std;

/*
    Biblioteca Boys_magia_outros contendo funcoes uteis em questoes de matematica
    Sumario:
    >PesquisaBinaria
*/

//Busca binaria
int PesquisaBinaria (int x, int v[], int e, int d)
{
	int i = (e + d)/2;
	if (v[i] == x)
		return i;
	if (e >= d)
		return i; // Não foi encontrado
	else
		if (v[i] < x)
			return PesquisaBinaria(x, v, i+1, d);
		else
			return PesquisaBinaria(x, v, e, i-1);
}
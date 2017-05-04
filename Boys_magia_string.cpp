#include <bits/stdc++.h>
using namespace std;

/*
    Biblioteca Boys_magia_strings contendo funcoes uteis em questoes de matematica
    Sumario:
    >Border
    >KMPSearch
*/

void Border(string pat, long long int M, long long int *lps)
{
    long long int len = 0, i = 1;
    lps[0] = 0;

    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
                len = lps[len-1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

//Busca pat em txt, retorna vector<int> com as posições encontradas
void KMPSearch(string pat, string txt, vector<int> &v)
{
    long long int M = pat.size(), N = txt.size(), lps[M], i = 0, j = 0;
    Border(pat, M, lps);
 
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
 
        if (j == M)
        {
            v.push_back(i-j);
            j = lps[j-1];
        }
 
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
}

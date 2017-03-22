#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Quantidade de substrings dentro de string com intersecao
int Quantidade_substring_com_intersecao(char *String, char *Substring)
{
	int i, j=1, q=0;
	for(i = 0 ; i <= strlen(String)-strlen(Substring) ; i++)
		if(String[i] == Substring[0])
		{
			while(String[i+j] == Substring[j])
			{
				j++;
				if(j == strlen(Substring) )
				{
					q++;
					break;
				}
			}
			j = 1;
		}
	return q;
}

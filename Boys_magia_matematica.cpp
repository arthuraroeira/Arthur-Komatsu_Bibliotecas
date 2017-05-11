#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define C 1000000009
using ii = pair<ll, ll>;

/*
	Biblioteca Boys_magia_matematica contendo funcoes uteis em questoes de matematica
	Sumario:
	>Exp_rapida
	>MDC
	>MMC
	>Dec_to_Hex
	>Hex_to_Dec
	>Dec_Bin
	>Bin_Dec
	>Primos_Ate_N
	>FatorarN_ContemPrimosNecessarios
	>FatorarN_ContemTodosPrimos
	>Fatorar_NFatorial
	>Divisores
	>Binomial
	>Josephus
	>Fatorial_Resto_por_X
	>Ultimo_dig_Nfat_nao_0
	>Mult_Matrizes_Quadradas
*/

//Calcula base^pot em O[log(pot)]
ll Exp_rapida(ll base, ll pot) 
{
	ll resultado = 1;
	while(pot > 0)
	{
		if(pot % 2)
			resultado *= base;
		base *= base;
		pot /= 2;
	}
	return resultado;
}

//Retorna MDC de "x" e "y"
ll MDC(ll x, ll y)
{
	if (y==0)
		return x;
	return MDC(y, x % y);
}

//Retorna MMC de "x" e "y"
ll MMC(ll a,ll b)
{
	return a*b/MDC(a, b);
}

//Retorna string Hexadecimal de x Decimal
string Dec_to_Hex(ll x)
{
	stringstream ss;
	ss << hex << x;
	return ss.str();
}

//Retorna inteiro Decimal da string x Hexadecimal
ll Hex_to_Dec(string x)
{
	stringstream ss;
	ss << x ;
	ll decimal_value;
	ss >> hex >> decimal_value ;
	return decimal_value ;
}

//Retorna string Binaria de x Decimal
string Dec_Bin(ll n)
{
	string r;
	while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
	return r;
}

//Retorna inteiro Decimal da string x Binaria
ll Bin_Dec(string s)
{
	ll x = 0;
	for(ll i = 0 ; i < s.size() ; i++ )
		x += (s[i] - '0')*pow(2, s.size() - 1 - i);
	return x;
}

//Retorna todos os primos ate N, guardando no vetor Primos
//Tecnica: Crivo de Erastotenes - O[n*loglog(n)]
void Primos_Ate_N(ll N, vector<ll>& Primos)
{
	vector<bool> prime(N, 1);

	for (ll i = 2; i <= N; i++)
		if (prime[i])
		{
			Primos.push_back(i);
			for (ll j = 2*i; j <= N; j += i)
				prime[j] = 0;
		}
}

//Retorna todos os primos ate N, guardando no vetor Primos
//Tecnica: Crivo de Atkins - Mais rapido que Erastotenes
void Primos_Ate_N(ll N, vector<ll>& Primos)
{
	if (N > 2)  Primos.push_back(2);
	if (N > 3)  Primos.push_back(3);

	bool *sieve;
	sieve = (bool *)malloc(N*sizeof(bool));
	for (ll i=0; i<N; i++)
		sieve[i] = false;

	for (ll x = 1; x*x < N; x++)
		for (ll y = 1; y*y < N; y++)
		{
			ll n = (4*x*x)+(y*y);
			if (n <= N && (n % 12 == 1 || n % 12 == 5))
				sieve[n] ^= true;

			n = (3*x*x)+(y*y);
			if (n <= N && n % 12 == 7)
				sieve[n] ^= true;

			n = (3*x*x)-(y*y);
			if (x > y && n <= N && n % 12 == 11)
				sieve[n] ^= true;
		}

	for (ll r = 5; r*r < N; r++)
		if (sieve[r])
			for (ll i = r*r; i < N; i += r*r)
				sieve[i] = false;

	for (ll a = 5; a < N; a++)
		if (sieve[a])
			Primos.push_back(a);

}

//Fatora N, retornando um vetor de pares <fator, expoente> "Fatores" contendo SOMENTE os primos divisores de N
//Necessario por um vetor Primos contendo todos os primos ate pelo menos sqrt(N) (Primos_Ate_N( (ll) ceil( (double) sqrt(N) ), Primos))
void FatorarN_ContemPrimosNecessarios(ll N, vector<ll> Primos, vector<ii>& Fatores)
{
	ll count;
	for(auto i : Primos)
		if(N == 1 || N == 0)
			break;
		else if(N % i == 0)
		{
			for(count = 0 ; N % i == 0 ; count++)
				N /= i;
			Fatores.push_back(ii(i, count));
		}

	if(N != 1 && N != 0)
		Fatores.push_back(ii(N, 1));
}

//Fatora N, retornando um vetor de pares <fator, expoente> "Fatores" contendo TODOS os primos ate N
//Necessario por um vetor Primos contendo todos os primos ate pelo menos N (Primos_Ate_N(N, Primes))
void FatorarN_ContemTodosPrimos(ll N, vector<ll> Primos, vector<ii>& Fatores)
{
	ll count;

	for(auto i : Primos)
	{
		if(i > N)
			break;

		if(N % i == 0)
		{
			for(count = 0 ; N % i == 0 ; count++)
				N /= i;
			Fatores.push_back(ii(i, count));
		}
		else
			Fatores.push_back(ii(i, 0));
	}
}

//Fatora N!, retornando um vetor de pares <fator, expoente> "Fatores_Fat" contendo TODOS os primos ate N
//Necessario por um vetor Primos contendo todos os primos ate pelo menos N (Primos_Ate_N(N, Primes))
void Fatorar_NFatorial(ll N, vector<ll> Primos, vector<ii>& Fatores_Fat)
{
	for(auto i : Primos)
	{
		if(i > N)
			break;

		ll count = 0, aux = i;

		while(N / aux != 0)
		{	
			count += N / aux;
			aux *= i;
		}
		Fatores_Fat.push_back(ii(i, count));
	}
}

//Retorna um conjunto "divisores" de todos os divisores de Fatores. 
//Necessario por um vetor de pares do numero fatorado (FatorarN_ContemPrimosNecessarios(N, Primos, Fatores))
//Chamar Divisores(1, 0, Fatores, divisores)
void Divisores(ll N, ll i, vector<ii> Fatores, set<ll>& divisores)
{
	ll j, x, k;

	divisores.insert(1);
	for (j = i ; j < Fatores.size() ; j++)
	{
		x = Fatores[j].first * N;
		for (k = 0 ; k < Fatores[j].second ; k++)
		{
			divisores.insert(x);
			Divisores(x, j + 1, Fatores, divisores);
			x *= Fatores[j].first;
		}
	}
}

//Calcula Binomial[X, Y]
//Necessario por um vetor Primos contendo todos os primos ate pelo menos N (Primos_Ate_N(N, Primes))
ll Binomial(ll X, ll Y, vector<ll> Primos)
{
	vector<ii> Factor1, Factor2, Factor3;
	Fatorar_NFatorial(  X, Primos, Factor1);
	Fatorar_NFatorial(  Y, Primos, Factor2);
	Fatorar_NFatorial(X-Y, Primos, Factor3);

	ll comb = 1;
	for(int i = 0 ; i < Factor1.size() ; i++)
	{
		if(Primos[i] > X)
			break;
		if(i >= Factor2.size())
			Factor2.push_back(ii(0, 0));
		if(i >= Factor3.size())
			Factor3.push_back(ii(0, 0));
		comb *= Exp_rapida(Primos[i], Factor1[i].second-Factor2[i].second-Factor3[i].second);
	}
	return comb;
}

//Retorna a posicao que sobrou do problema de Josephus com n posicoes matando a cada k pessoas
//O[n]
ll Josephus(ll n, ll k) { return n == 1 ? 0 : (Josephus(n-1, k) + k) % n; }

//Retorna vetor "fat" contendo os valores de N! % X
void Fatorial_Resto_por_X(ll N, ll X, vector<ll>& fat)
{
	fat.assign(1, 1);
	for(ll i = 1 ; i <= N ; i++)
		fat.push_back( (fat[i-1] * i) % X );
}

//Retorna o ultimo digito nao-nulo de N!
ll Ultimo_dig_Nfat_nao_0(ll n)
{
	int dig[] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8};
	if (n < 10)
		return dig[n];
	if (((n/10)%10)%2 == 0)
		return (6*Ultimo_dig_Nfat_nao_0(n/5)*dig[n%10]) % 10;
	else
		return (4*Ultimo_dig_Nfat_nao_0(n/5)*dig[n%10]) % 10;
}

//Multiplica duas matrizes quadradas a[tam][tam], guardando em mult[tam][tam]
void Mult_Matrizes_Quadradas(ll **a, ll tam, ll **mult)
{
	for(ll i = 0; i < tam; ++i)
		for(ll j = 0; j < tam; ++j)
			for(ll k = 0; k < tam; ++k)
				mult[i][j] += a[i][k] * a[k][j];
}

int main()
{
	return 0;
}

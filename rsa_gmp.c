/*
Nomes: Eduardo Romao da Rocha - RA: 408468
	   Helio Ossamu Nakayama - RA : 408
Universidade Federal de Sao Carlos - campus Sorocaba
Introducao a Criptografia - 2016
Profa Dra Yeda Regina Venturini
Implementacao do Algoritmo RSA com GMP
*/

#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>

typedef struct{
	long long int p;
	long long int q;
} PQ;

long long int totiente(PQ pq);
long long int inverso(long long int a, long long int b);
long long int pot(long long int a, long long int b);
//int eh_primo(long long int x);
PQ getPQ(long long int x);
long long int gera_bin(long long int a, long long int tam, int *v);
long long int quadrado_mult(long long int tam, long long int c, long long int d, long long int n, int *v);

int main(){
	long long int n, e, c;
	long long int phi = 0, inv = 0;
	long long int m = 0;
	long long int tam = 0;
	int binario[10000];
	PQ pq;

	scanf("%lld %lld %lld", &n, &e, &c);

	pq = getPQ(n);
	phi = totiente(pq);
	inv = inverso(e, phi);
	tam = gera_bin(inv, tam, binario);

	//decriptando
	m = quadrado_mult(tam, c, inv, n, binario);
	printf("%lld\n", m);

	return 0;
}

long long int totiente(PQ pq){
	return ((pq.p - 1) * (pq.q - 1));
}

long long int inverso(long long int a, long long int b){
	long long int resto, aux_resto1 = b, aux_resto2 = a;
	long long int quoc;
	long long int s, aux_s1 = 0, aux_s2 = 1;
	long long int t, aux_t1 = 1, aux_t2 = 0;
	long long int ret;

	do{
		/*calculo*/
		resto = aux_resto2 % aux_resto1;
		quoc = (aux_resto2 - resto) / aux_resto1;
		
		s = aux_s2 - (quoc * aux_s1);
		t = aux_t2 - (quoc * aux_t1);

		/*swaps*/
		aux_t2 = aux_t1;
		aux_t1 = t;
		
		aux_s2 = aux_s1;
		aux_s1 = s;
		
		aux_resto2 = aux_resto1;
		aux_resto1 = resto;
	}while(resto != 0);

	ret = aux_s2;

	if(ret < 0) ret += b;

	return ret;
}

long long int pot(long long int a, long long int b){
	long long int i, ret = 1;

	for(i = 0; i < b; i++) ret *= a;

	return ret;
}

/*int eh_primo(long long int x){
	long long int i;

	if(x < 0) x *= -1;
	if(x == 2) return 1;
	if(x == 1) return 0;

	for(i = 2; i < x; i++){
		if(x % i == 0) return 0;
	}

	return 1;
}*/

PQ getPQ(long long int x){
	long long int i;
	PQ ret;

	for(i = 3; i < x / 2; i += 2){
		if(/*eh_primo(i) &&*/ (x % i) == 0){
			ret.p = i;
			ret.q = x / i;
			break;
		}
	}

	return ret;
}

long long int gera_bin(long long int a, long long int tam, int *v){
	int aux[10000];
	long long int i, k = 0;

	tam = 0;
	
	if(a == 1) v[tam] = 1;
	else if(a == 0) v[tam] = 0;
	else{
		while(a != 1 && a != 0){
			v[tam] = a % 2;
			a = a / 2;
			tam++;
		}
		
		tam++;
		v[tam - 1] = a;

		for(i = 0; i < tam; i++){
			aux[i] = v[i];
		}
		for(i = tam - 1; i >= 0; i--){
			v[k] = aux[i];
			k++;
		}
	}
	
	return tam;
}

long long int quadrado_mult(long long int tam, long long int c, long long int d, long long int n, int *v){
	long long int i, ret = c;

	for(i = 1; i < tam; i++){
		ret = pot(ret, 2) % n;
		if(v[i] == 1) ret = (ret * c) % n;
	}

	return ret;
}

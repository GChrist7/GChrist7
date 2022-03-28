#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Pessoa{
    int i; 
    int icrush;
}pessoa[100000];

int getGrau(int i, int n){ //Retorna o número de pessoas que têm interesse em pessoa[i].
    int j, grau;
    grau = 0;
    for(j=1 ; j<=n ; j++){
        if(pessoa[i].i == pessoa[j].icrush){
            grau++;
        }
    }
    grau++; //Aumenta o grau em 1, pois toda pessoa tem interesse em alguém.
    return grau;
}

int CheckInList(int i, int n){ //Checa se a pessoa[i] está na lista de seu icrush.
    int x, y, aux, aux2, cont;
    cont = 0;
    x = pessoa[i].i;
    aux = pessoa[i].i;
    y = pessoa[i].icrush;
    aux = pessoa[i].icrush;
    while(pessoa[aux].icrush != x){
        if(pessoa[aux].icrush == y)
            return 0;
        if(cont > n)
            return 0;
        aux2 = pessoa[aux].icrush;
        aux = aux2;
        cont++;
    }
    return 1;
}

int VaiParaSegunda(int V[], int i, int j, int n){ //Retorna 1 se a pessoa[i] vai para segunda fase e 0 se não vai.
    int grau;
    grau = getGrau(i, n);
    if(pessoa[pessoa[i].icrush].icrush == i)
        return 1;
    if(grau < 2){
        return 0;
    }
    if(grau >= 2)
        return CheckInList(i, n);
}

void FormaCasais(int n){
    int vdd, i, j;
    int V[100000];
    j = 0;
    for(i=1 ; i<=n ; i++){       
        vdd = VaiParaSegunda(V, i, j, n);            
        if(vdd == 1){
            V[j] = i; //Todos os índices dos participantes são inseridos no vetor V.
            j++;
        }
    }
    for(i=0 ; i<j ; i++){
        printf("%d ", V[i]); //Imprime o vetor V com todos os participantes da segunda fase.
    }
}

int main(){
    int n, i, indice;
    scanf("%d", &n);
    for(i=1 ; i<=n ; i++){
        scanf("%d", &indice);
        pessoa[indice].i = indice; //Insere o indice inserido pelo usuário na posição "indice" do vetor de struct.
        scanf("%d", &pessoa[indice].icrush);
    }
    FormaCasais(n);
    return 0;
}
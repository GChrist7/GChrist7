#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getPotencia(int n){ //Retorna maior a potência de 2 e a mais próxima de n
    int aux, potencia;
    potencia = 1;
    aux = n;
    if(aux == 1) //Caso n seja 1, retorna 0
        return 0;
    else{
        while(aux >= 2){
            aux = aux/2;
            potencia++;
        }
        return potencia;
    }
}

int getMenor(x, y){ //Retorna o menor valor entre x e y
    if(x < y)
        return x;
    else
        return y;
}


int Power2Coin(int n){
    int i, potencia, potmenor, potmaior, diferenca;
    int coins;
    potencia = getPotencia(n);
    potmaior = pow(2, potencia); 
    potmenor = pow(2, (potencia -1));
    if(potencia == 0 || potmenor == n)
        return 1;
    else{
        diferenca = getMenor((potmaior - n), (n - potmenor)); //Compara se é mais vantajoso devolver um troco ou adicionar mais moedas
        coins = 1 + Power2Coin(diferenca);
        return coins;
    }
}


int main(){
    int n, coins;
    scanf("%d", &n);
    coins = Power2Coin(n);
    printf("%d", coins);
    return 0;
}
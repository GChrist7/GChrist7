#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Eh_Primo(int n){
    int r, n2;
    int EhPrimo = 1; 
    r = (int) sqrt(n);
    for(n2=2; n2 <= r; n2++){

        if(n%n2 == 0){

            EhPrimo = 0;
            break;
        }
    }
    if(EhPrimo){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    int N;
    int nup, ndown, c, pup, pdown;
    c = 0;
    scanf("%d", &N);
    if(N == 4){
        printf("1");
    }
    else{
        nup = ndown = N/2;
        if(nup % 2 == 0){
            nup++;
            ndown--;
        }
        while(ndown > 1){
            if((Eh_Primo(nup) == 1) && (Eh_Primo(ndown) == 1)){
                c++;
            }
            nup = nup + 2;
            ndown = ndown - 2;
        }
        printf("%d", c);
    }
    return 0;
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){

    srand(time(NULL));
    int tam = 1000000;

    FILE *Arq = fopen("entrada_1000000_int.txt","w");

        if(Arq == NULL){
            return 0;
        }

    for(int i = 0; i < tam;i++){
        int num = rand() % 1000000;
        fprintf(Arq, "%d\n", num);
    }

    fclose(Arq);
    return 0;
}
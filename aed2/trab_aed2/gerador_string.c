#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char* gera_string(int tam) {
    char *s = malloc((tam + 1) * sizeof(char));
    for (int i = 0; i < tam; i++) {
        s[i] = 'A' + (rand() % 26); // Gera letras de A a Z
    }
    s[tam] = '\0';
    return s;
}

int main(){

    srand(time(NULL));
    int tam = 1000000;
    int tam_str = 4;

    FILE *Arq = fopen("entrada_1000000_str.txt","w");

        if(Arq == NULL){
            return 0;
        }

    for(int i = 0; i < tam;i++){
        char *s = gera_string(tam_str);
        fprintf(Arq, "%s\n", s);

        free(s);
    }

    fclose(Arq);
    return 0;
}
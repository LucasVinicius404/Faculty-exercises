#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contar_caracteres(char *vetor){
/** 
 * essa função tem como objetivo receber as string e contar os caracteres especias letras e digitos.
 * 
 * após isso retornar o calculo de (letras - digitos )* caracteres_especiais
 * 
*/

    int letra = 0,digito = 0,carac_especial = 0;


    for(int i = 0; i < strlen(vetor); i++){
        if(vetor[i] >= '0' && vetor[i] <= '9'){
            digito++;
        }else if(vetor[i] >= 'A' && vetor[i] <= 'Z' || vetor[i] >= 'a' && vetor[i] <= 'z'){
            letra++;
        }else{
            carac_especial++;
        }
    }
    return ((letra - digito) * carac_especial);
}

int compara_string(char *string1, char *string2){
    /**
     * essa função tem como objetivo comparar se duas string são iguais e retornar valor tratado na main
     */
   return strcmp(string1,string2);
}

int main(){
    /**
     * O codigo tem como objetivo receber duas strings do usuario e realizar as duas funções chamadas
     * 
     * -inputs: duas strings separadas por espaço do usuario
     * -output: saida seca com o resultado dos dois calculos e do comparativo
     * 
     * 
     */
    char string1[500],string2[500];
    
    fgets(string1, sizeof(string1),stdin);
    fgets(string2,sizeof(string2),stdin);

    string1[strcspn(string1, "\n")] = '\0';
    string2[strcspn(string2, "\n")] = '\0';

    int comparativo = -1;

    if(compara_string(string1,string2) == 0){
        comparativo = 1;
    }else{
        comparativo = 0;
    }

    int calc1 = contar_caracteres(string1);
    int calc2 = contar_caracteres(string2);

    printf("%d %d %d", calc1,calc2,comparativo);
}
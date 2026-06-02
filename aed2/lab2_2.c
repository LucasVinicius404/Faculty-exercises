#include <stdio.h>
#include <stdlib.h>
     
     
void primos(int *primo,int tam){
 /*
    a função ira pegar todos os numero primos que podem estar presente no intervalo delimitado pelo exercicio
     
    para os numeros primos o indice estará como 1, os numeros não primos ficam como 0
*/ 
    primo[0] = 0;
    primo[1] = 0;
     
    for(int i = 2; i < tam; i++){
        primo[i] = 1;
    }

    for(int i = 2; i * i < tam; i++) {
        if(primo[i] == 1) {
            
            for(int j = i * i; j < tam; j += i) {
                primo[j] = 0;
            }
        }
    }
}

int verificar_pares(int *vet, int *c, int *primo,int tam,int n){

    /*
    função que verifica as condições para os pares
    */
    int quant_par = 0;
    for(int i = 0; i < tam; i++){
        int a = vet[i];
     
        int b = n - a; //b recebe o que deveria ser par de a
            
        if(b >= -30000 && b <= 30000){ //verifica se está no valor delimitado pelo problema evitando tbm segment fault

            if(c[b + 30000] == 1 && a < b){//verifica  no vetor de frequencia se existe o numero b e se ele for maior que a quer dizer que o par já foi computado

                int total = b - a; // recebe a diferença de a para b
                if(primo[total] == 1){ // verifica se cumpre a segunda condição de ser primo verificando se ele é um no vetor de primo
                    quant_par++;
                }
            } 
        }
    }
    return quant_par;
}
     
int main(){
     /*
     a main recebe os parametros de funcionamento aloca vetores do tamanho maximo permitido do exercico
     vetor c = frequencia dos elementos digitados
     vetor primo = tabela para verificação de primos
     vetor padrão digitado pelo usuario   
     */
    int tam,n;
     
    scanf("%d %d", &tam,&n);
     
    int *vet = malloc(tam * sizeof(int));
     
    int *primo = malloc(60001 * sizeof(int));
     
    primos(primo,60001);
        
    int *c = malloc(60001 * sizeof(int));
     
    for(int i = 0;  i < tam; i++){
        int valor;
        scanf("%d", &valor);
        vet[i] = valor;
        c[valor + 30000] = 1; //inserção em O(1) no vetor de frequencia somado a 30.000 pois podem assumir valores negativos
    }
     
    int quant_pares = verificar_pares(vet,c,primo,tam,n);
     
    printf("%d", quant_pares);
     
    free(c);
    free(vet);
    free(primo);
     
    return 0;
}
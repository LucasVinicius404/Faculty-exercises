    #include <stdio.h>
    #include <stdlib.h>
     
    void procura_valor(int *vetor,int ini,int fim,int x){
        if(fim - ini== 1){ //caso base de quanto sobrou apenas dois indices do array 
            if(vetor[ini] < x && x < vetor[fim]){ //caso onde d
                printf("%d %d", vetor[ini], vetor[fim]);
            }else{
                printf("nao ha intervalo valido");
            }
            return;
        }
     
        int meio = (ini + fim)/2;
     
        if(x < vetor[meio]){ //se o meio for maior que x 
            procura_valor(vetor,ini,meio,x); //se maior o fim vira o meio pegando a porção da esquerda
        }else{
            procura_valor(vetor,meio,fim,x);// se menor meu ini vira meio pegando a porção da direita
        }
    }
     
    int main(){
     
        int valor, n;
     
        scanf("%d %d", &valor, &n); // captura do valor e tamanho array
        getchar();
     
        int *vetor = malloc(n * sizeof(int)); //alocação dinamica do array
     
        for(int i = 0; i < n; i++){ //preenchimento do array
            scanf("%d", &vetor[i]);
        }
     
        if(vetor[0] > valor || vetor[n-1] < valor){ //verificação inicial de casos da ponta
            printf("nao ha intervalo valido");
        }else{
        procura_valor(vetor,0,n-1,valor);
        } 
        
        free(vetor); //desalocação do vetor
    }
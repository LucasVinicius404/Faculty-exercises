#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int transforma_caracter(char c);
void minuscula(char *vet);
void radix_sort(char **vetor, int tam, int maior);
void counting_sort(char *vetor[], char *vetor_final[], int tam, int maior);

int main(){
int n,maior = 0;

    scanf("%d", &n);

    char **vetor = malloc(n * sizeof(char*));
        
        if(vetor == NULL){
            return 1;
        }
        for(int i = 0; i < n ; i++){
            char buffer[21];
            //recebimento da palavra completa até 20 caracteres
            scanf("%s", buffer);
            minuscula(buffer);
            int len = strlen(buffer);
                if(len > maior){
                    maior = len;
                }
            //aloca no vetor o tamanho exato da palavra mais o '\0'
            vetor[i] = malloc(strlen(buffer) + 1);
                if(vetor[i] == NULL){
                    for (int j = 0; j < i; j++) {
                    free(vetor[j]);
                }
                    free(vetor);
                    return 0;
                }
            //copia a palavra para o vetor
            strcpy(vetor[i],buffer);
        }
    for(int i = 0; i < n; i++){
        printf("%s.\n",vetor[i]);
    }
    printf("%d\n", maior);

    char **vetor_ordenado = malloc(n * sizeof(char*));
        if(vetor_ordenado == NULL){
            for (int j = 0; j < n; j++) {
                free(vetor[j]);
            }
                free(vetor);
                return 0;
            }                
    
    for(int i = 0; i < n; i++){
        //aloca espaço para palavra para cada indice do vetor ordenado
        vetor_ordenado[i] = malloc(maior + 1);
            strcpy(vetor_ordenado[i],vetor[i]);
            //verifica se a palavra nova é maior que a as anteriores
        if(strlen(vetor_ordenado[i]) < maior){
                //adiciona espaços em brancos para todos os indicides terem a mesma quantidade que é a do maior
            for(int j = strlen(vetor_ordenado[i]);j < maior; j++){
                vetor_ordenado[i][j] = ' ';
            }
        }
        vetor_ordenado[i][maior] = '\0';
    }

    radix_sort(vetor_ordenado, n, maior);

    int m, p;
    
    scanf("%d %d", &p, &m);
    
    int k = p - 1;
    while(m != 0){
        printf("%s\n", vetor_ordenado[k]);
        m--;
        k++;
    }
    
    for (int j = 0; j < n; j++) {
        free(vetor[j]); 
        free(vetor_ordenado[j]); 
    }
    free(vetor); 
    free(vetor_ordenado); 

    return 0;
}

void minuscula(char *vet){
    int i = 0;
    //percorre o vetor até achar o ultimo termo
    while(vet[i] != '\0'){
        //entra na condição se ele for maiusculo
        if(vet[i] >= 'A' && vet[i] <= 'Z'){
            //soma com 32 para achar seu representante minusculo
            vet[i] = vet[i] + 32;
        }
        i++;
    }
}

int transforma_caracter(char c){
    if(c == ' '){
        return 0;
    }
    //retorna um int baseado no ascii onde a = 1, b=2 e assim por diante
    return c - 'a' + 1;
}

void radix_sort(char **vetor, int tam, int maior){

    char **vetor_final = malloc(tam * sizeof(char *));
        if(vetor_final == NULL){
        return;
    }

    for(int i = maior - 1; i >= 0; i--){
        //começa passando o digito menos significativo e 
        counting_sort(vetor, vetor_final, tam, i);
    }

    free(vetor_final); 
}


void counting_sort(char *vetor[], char *vetor_final[], int tam, int k){
    //aloca espaço para um novo vetor com todos os termos em 0
    int *c = calloc(27,sizeof(int));
    //contagem da frequencia no vetor e adição no vetor auxiliar
    for(int i = 0; i < tam;i++){
        c[transforma_caracter(vetor[i][k])]++;
    }
    //soma a contagem das frequencias acumuladas
    for(int i = 1; i <= 26;i++){
        c[i] += c[i-1];
    }
    
    for (int i = 0; i <= 26; i++) {
    printf("%d", c[i]); 
        if (i < 26) {
        printf(" "); 
        }
    }
    printf("\n");

    for(int j = tam - 1; j >= 0; j--){
        //coloca a palavra na posição correta no vetor final
        vetor_final[c[transforma_caracter(vetor[j][k])]-1] = vetor[j];
        //decrementa do vetor de frequencia a frequencia achada
        c[transforma_caracter(vetor[j][k])]--;
    }
    //copia para o vetor original o vetor ordenado
    for(int i = 0; i < tam; i++){
        vetor[i] = vetor_final[i];
    }
    free(c);
} 

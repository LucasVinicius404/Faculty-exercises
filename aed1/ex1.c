#include <stdio.h>
#include <stdlib.h>

typedef struct cliente{ 

    float dinheiro;
    int livros;
    float *preco;
}cliente;

void registra_cliente(cliente *c);
void calculo_da_compra(cliente *c);

int main(){
    
    int n = 0;
    int i = 0;

    do{
        scanf("%d", &n);
    }while(n < 0 || n > 100 );
    
    

    cliente *c = malloc(n * sizeof(cliente));
        if(c == NULL){
            return 0;
        }
    
    do{
        registra_cliente(&c[i]);
        i++;
    }while(i < n);

    for(i = 0; i < n;i++){
        calculo_da_compra(&c[i]);
        free(c[i].preco);
    }
    free(c);

    return 0;
}

void registra_cliente(cliente *c){
    
    do{
       scanf("%f", &c->dinheiro); 
    }while(c->dinheiro < 0);

    do{
        scanf("%d", &c->livros);
    }while(c->livros < 0 || c->livros > 100);

    c->preco = malloc(c->livros * sizeof(float));
    if(c->preco == NULL){
        return;
    }

    for(int i = 0; i < c->livros; i++) {
        do {
            scanf("%f", &c->preco[i]);
        } while(c->preco[i] < 0);
    }
}

void calculo_da_compra(cliente *c){
    int compras = 0;
    float saldo = c->dinheiro;

    for(int i = 0; i < c->livros; i++){
        if(saldo >= c->preco[i]){
            saldo -= c->preco[i]; 
            compras++;           
        }
       
    }

    printf("%d %.2f\n", compras, saldo);
}
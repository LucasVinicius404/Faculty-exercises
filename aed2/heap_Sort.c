    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    typedef struct heap{
        int *valor;
        int tam;
    }heap;
     
    void heapSort(heap *vetor, int n);
    void BuildMaxHeap(heap *vetor, int tam);
    void maxHeapfy(heap *vetor, int i);
    void swap(int *a,int *b);
     
     
     
    int main(){
        int tam;
     
        scanf("%d", &tam);
     
        heap *vetor = malloc(sizeof(heap));
            if(vetor == NULL){
                return 1;
            }
        vetor->tam = tam;
        vetor->valor = malloc(tam * sizeof(int));
     
        for(int i = 0; i < tam; i++){
            scanf("%d",&vetor->valor[i]);
        }
     
        heapSort(vetor,tam - 1);
        
        for(int i = 0; i < tam; i++){
            printf("%d ",vetor->valor[i]);
        }
        
        free(vetor->valor);
        free(vetor);
        return 0;
        
    }
    void swap(int *a,int *b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }
     
    void heapSort(heap *vetor, int n){
        BuildMaxHeap(vetor,vetor->tam);
        for(int i = n; i > 0; i--){
            swap(&vetor->valor[0],&vetor->valor[i]);
            vetor->tam--;
            maxHeapfy(vetor,0);
        }
    }
     
    void BuildMaxHeap(heap *vetor, int tam){
        for(int i = (tam/2 - 1); i >= 0; i--){
            maxHeapfy(vetor,i);
        }
    }
     
    void maxHeapfy(heap *vetor, int i){
        int l = 2*i+1;
        int r = 2*i+2;
        int maior = i;
        if(l < vetor->tam && vetor->valor[l]>vetor->valor[i]){
            maior = l;
        }
        if(r<vetor->tam && vetor->valor[r]>vetor->valor[maior]){
            maior = r;
        }
        if(maior != i){
            swap(&vetor->valor[i],&vetor->valor[maior]);
            maxHeapfy(vetor,maior); 
        }
        
    }
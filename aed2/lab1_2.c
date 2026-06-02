    #include <stdio.h>
    #include <stdlib.h>
     
    typedef struct Candidatos{
        int quant_votos;
        int id;
    }cand;
     
    typedef struct Eleitor{
        int votos[3];
    }eleitor;
     
    eleitor *inicializa_eleitores(int eleitores){
        eleitor *e = malloc(eleitores * sizeof(eleitor));
            if(e == NULL){
                return NULL;
            }
        for(int i = 0; i < eleitores; i++){
            for(int j = 0; j < 3; j++){
                e[i].votos[j] = 0;
            }
        }
        return e;
    }
     
    cand *inicializa_candidatos(int candidatos){    
        cand *c = malloc(candidatos * sizeof(cand));
            if(c == NULL){
                return  NULL;
            }
        for(int i = 0; i < candidatos; i++){
            c[i].id = i + 1;
            c[i].quant_votos = 0;
        }
     
        return c;
    }
     
    void insertion_sort(cand *c, int tam){
        for(int i = 1; i < tam; i++){
            cand chave  = c[i];
            int j = i - 1;
                while(j >= 0 && c[j].quant_votos < chave.quant_votos || (c[j].quant_votos == chave.quant_votos && c[j].id > chave.id) ){
                    c[j + 1] = c[j];
                    j--; 
                }
            c[j + 1] = chave;
        }
    }
     
    void libera_struct(cand *c, eleitor *e){
        free(c);
        free(e);
    }
     
    int main(){
     
        int eleitores, candidatos;
        int votos_validos =0;
     
        scanf("%d %d", &eleitores, &candidatos);
     
        eleitor *e = inicializa_eleitores(eleitores);
     
        cand *c = inicializa_candidatos(candidatos);
     
        for(int i = 0; i < eleitores; i++){
            for(int j = 0; j < 3;j++){
                scanf("%d", &e[i].votos[j]);
     
            }
            int id = e[i].votos[0];
                if(id <= candidatos && id > 0){
                    c[id - 1].quant_votos++;
                    votos_validos++;
                }
        }
     
        if(votos_validos != 0){
            insertion_sort(c,candidatos);
     
            float porcentagem = (c[0].quant_votos * 100.0) / votos_validos;
     
            printf("%d %.2f\n", c[0].id, porcentagem);
     
            if(porcentagem < 50){
                int idxA = c[0].id, idxB = c[1].id, vA =0, vB =0;
                votos_validos = 0;
     
                for(int i = 0; i < eleitores; i++){
                    int j =0, achou =0;
     
                    while(j < 3 && achou == 0){
                        int voto = e[i].votos[j];
     
                        if(voto == idxA){
                            vA++;
                            votos_validos++;
                            achou = 1;
                        }else if(voto == idxB){
                            vB++;
                            votos_validos++;
                            achou = 1;
                        }
                        j++;
                    }
                }
            
                if(vA > vB || (vA == vB && idxA < idxB )){
                    float p = (vA * 100.0) / votos_validos;
                    printf("%d %.2f", idxA, p);
                }else{
                    float p = (vB * 100.0) / votos_validos;
                    printf("%d %.2f", idxB, p);
                }
            }
     
        }else{
            printf("0\n");
        }
     
        libera_struct(c,e);
        return 0;
    }
#include <stdio.h>

int verificar_navios(int L, int C, int i, int j, char tabuleiro[][105]) {
    /*
    função recursiva com as condições de paradas sendo as extremidades da matriz ou agua

    flag para ver se o navio foi destruido ou não

    marca a posição visitada como agua para evitar chamada repetitivas

    verifica se os navios são maiores que uma posição por isso a verificção dos lados dele

    se todas as extremidades dele foram destruidas
    ele retorna 1 marcando o navio como destruindo

    pela marcação de toda extensão dele como agua evita chamadas repetitivas no for da main tbm


    */
    if (i < 0 || i >= L || j < 0 || j >= C || tabuleiro[i][j] == '.') {
        return 1;
    }

    int fui_destruido = 1;

    if (tabuleiro[i][j] == '#') {
        fui_destruido = 0; 
    }

    tabuleiro[i][j] = '.';


    int resultado_baixo    = verificar_navios(L, C, i + 1, j, tabuleiro);
    int resultado_cima     = verificar_navios(L, C, i - 1, j, tabuleiro);
    int resultado_direita  = verificar_navios(L, C, i, j + 1, tabuleiro);
    int resultado_esquerda = verificar_navios(L, C, i, j - 1, tabuleiro);


    if (fui_destruido == 0 || resultado_baixo == 0 || resultado_cima == 0 || resultado_direita == 0 || resultado_esquerda == 0) {
        return 0; 
    }

    return 1; 
}

int main(){
    /*
    uma simulação de batalha naval

    o usuario digita as dimensões da matriz que é o tabuleiro

    as entradas só podem ser . ou # 
    - '.' = água
    -'#'  = pedaço do navio

    apos as entradas o usuario digita quantos tiros serão executados

    e depois digita as coordenadas dos tiros se encontrado o navio marca ele como x

    por fim chama a função para verificar os navios encontrados

    */
    int L, C;
    char tabuleiro[105][105];
    scanf("%d %d", &L, &C);


    for(int i =0; i < L; i++){
        for(int j = 0; j < C; j++){
            scanf(" %c", &tabuleiro[i][j]);
        }
    }

    int tiros,navios = 0;
    scanf("%d", &tiros);

    for(int i = 0; i < tiros; i++){
        int m , n;
        scanf("%d %d", &m,&n);
        //indices diminuidas para interação maquina e usuario
        m--; 
        n--;

        if(tabuleiro[m][n] == '#'){
            tabuleiro[m][n] = 'X';
        }
    }

    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            if(tabuleiro[i][j] == 'X'){
                if(verificar_navios(L,C,i,j,tabuleiro)){
                    navios++;
                }
            }
        }
    }

    printf("%d", navios);
    return 0;
}
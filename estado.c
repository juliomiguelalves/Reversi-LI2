#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "estado.h"
#include <stdlib.h>




void save(ESTADO e, char nome[]) {
    int i, j;
    FILE *f;
    f = fopen(nome, "w");
    char b;
    if (e.modo == 0) b = 'M';
    else b = 'A';
    fprintf(f, "%c %c\n", b, valtochar(e.peca));
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            VALOR a = valtochar(e.grelha[i][j]);
            fprintf(f, "%c ", a);
        }
        fprintf(f, "\n");
    }
    fclose(f);


}

void load(ESTADO *m, char nome[]) {
    int i, j;
    FILE *f;
    f = fopen(nome, "r");
    char b, c;
    fscanf(f, "%c %c ", &b, &c);
    m->peca = chartoval(c);
    if (b == 'M') m->modo = 0;
    else if (b == 'A') m->modo = 1;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            char a;
            fscanf(f, "%c ", &a);
            m->grelha[i][j] = chartoval(a);
        }
    }
    fclose(f);
}



ESTADO estadoinicial(char c2) {
    ESTADO m = {0};
    if (c2 == 'X') m.peca = VALOR_X;
    else if (c2 == 'O') m.peca = VALOR_O;

    m.grelha[3][4] = VALOR_X;
    m.grelha[4][3] = VALOR_X;
    m.grelha[3][3] = VALOR_O;
    m.grelha[4][4] = VALOR_O;
    return m;
}

void printa(ESTADO e) {
    char c = ' ';
    int a = 1;
    printf("\t");
    for (int i = 0; i < 8; i++) {
        printf("%d  ", a++);
    }
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '_';
                    break;
                }
                case VALOR_SUGESTAO: {
                    c = '.';
                    break;
                }
            }
            printf(" %c ", c);
        }
        printf("\n");
    }
    int r = contagemX(e);
    printf("#X = %d\n", r);
    int f = contagemO(e);
    printf("#O = %d\n", f);

}



VALOR chartoval(char a) {
    VALOR c = VAZIA;
    switch (a) {
        case 'X': {
            c = VALOR_X;
            break;
        }
        case 'O': {
            c = VALOR_O;
            break;
        }
        case ' ': {
            c = VAZIA;
            break;
        }
        case '.': {
            c = VALOR_SUGESTAO;
            break;
        }
        default:
            break;
    }
    return c;
}

char valtochar(VALOR a) {
    char c = ' ';
    {
        switch (a) {
            case VALOR_O: {
                c = 'O';
                break;
            }
            case VALOR_X: {
                c = 'X';
                break;
            }
            case VAZIA: {
                c = '_';
                break;
            }
            case VALOR_SUGESTAO: {
                c = '.';
                break;
            }
            default:
                break;
        }

    }
    return c;
}


int validoh(ESTADO *e, int i, int j) {
    VALOR aocontrario;
    if (e->peca == VALOR_X) aocontrario = VALOR_O;
    else aocontrario = VALOR_X;
    int valido = 0;
    if (e->grelha[i][j] == VAZIA) {
        int c = j + 1;
        while (c < 8 && e->grelha[i][c] == aocontrario) {
            c++;
            if (e->grelha[i][c] == e->peca) valido = 1;
        }
    }
    if (e->grelha[i][j] == VAZIA) {
        int c = j - 1;
        while (c >= 0 && e->grelha[i][c] == aocontrario) {
            c--;
            if (e->grelha[i][c] == e->peca) valido = 1;
        }
    }
    return valido;
}

int validov(ESTADO *e, int i, int j) {
    VALOR aocontrario;
    if (e->peca == VALOR_X) aocontrario = VALOR_O;
    else aocontrario = VALOR_X;
    int valido = 0;
    if (e->grelha[i][j] == VAZIA) {
        int l = i + 1;
        while (l < 8 && e->grelha[l][j] == aocontrario) {
            l++;
            if (e->grelha[l][j] == e->peca) valido = 1;
        }
    }
    if (e->grelha[i][j] == VAZIA) {
        int l = i - 1;
        while (l >= 0 && e->grelha[l][j] == aocontrario) {
            l--;
            if (e->grelha[l][j] == e->peca) valido = 1;
        }
    }
    return valido;
}

int validod(ESTADO *e, int i, int j) {
    VALOR aocontrario;
    if (e->peca == VALOR_X) aocontrario = VALOR_O;
    else aocontrario = VALOR_X;
    int valido = 0;
    if (e->grelha[i][j] == VAZIA) {
        int l = i + 1, c = j + 1;
        while (l < 8 && c < 8 && e->grelha[l][c] == aocontrario) {
            l++;
            c++;
            if (e->grelha[l][c] == e->peca) valido = 1;
        }
    }
    if (e->grelha[i][j] == VAZIA) {
        int l = i - 1, c = j - 1;
        while (l >= 0 && c >= 0 && e->grelha[l][c] == aocontrario) {
            l--;
            c--;
            if (e->grelha[l][c] == e->peca) valido = 1;
        }
    }
    if (e->grelha[i][j] == VAZIA) {
        int l = i - 1, c = j + 1;
        while (l >= 0 && c < 8 && e->grelha[l][c] == aocontrario) {
            l--;
            c++;
            if (e->grelha[l][c] == e->peca) valido = 1;
        }
    }
    if (e->grelha[i][j] == VAZIA) {
        int l = i + 1, c = j - 1;
        while (l < 8 && c >= 0 && e->grelha[l][c] == aocontrario) {
            l++;
            c--;
            if (e->grelha[l][c] == e->peca) valido = 1;
        }
    }
    return valido;
}


int procuravalidas(ESTADO *e) {
    int i, j, conta = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (validoh(e, i, j) == 1) conta++;
            else if (validov(e, i, j) == 1) conta++;
            else if (validoh(e, i, j) == 1) conta++;
        }
    }
    return conta;
}


void virar(ESTADO *e, int i, int j) {
    virah(e, i, j);
    virav(e, i, j);
    viradia(e, i, j);
}


void endgame(ESTADO m) {
    if (contagemX(m) > contagemO(m)) printf("\nO jogador X é o vencedor!\n");
    else if (contagemX(m) < contagemO(m)) printf("\nO jogador O é o vencedor!\n");
    else printf("\nEmpataram!\n");

}

ESTADO jogada(ESTADO m, int i, int j) {
    VALOR aocontrario;
    if (m.peca == VALOR_X) aocontrario = VALOR_O;
    else aocontrario = VALOR_X;
        m.grelha[i - 1][j - 1] = m.peca;
        virar(&m, i - 1, j - 1);
        m.peca = aocontrario;

    return m;
}


int contagemX(ESTADO m) {
    int i, j;
    int conta = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (m.grelha[i][j] == VALOR_X) conta++;
        }
    }
    return conta;
}

int contagemO(ESTADO e) {
    int i, j;
    int conta = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (e.grelha[i][j] == VALOR_O) conta++;
        }
    }
    return conta;
}


void virah(ESTADO *m, int i, int j) {
    VALOR aocontrario;
    if (m->peca == VALOR_O) aocontrario = VALOR_X;
    else aocontrario = VALOR_O;
    int k = j - 1;
    while (k > 0 && m->grelha[i][k] == aocontrario) {
        k--;
    }
    if (m->grelha[i][k] == m->peca) {
        for (int l = k + 1; l <= j - 1; l++) m->grelha[i][l] = m->peca;
    }

    k = j + 1;
    while (k < 8 && m->grelha[i][k] == aocontrario) {
        k++;
    }
    if (m->grelha[i][k] == m->peca) {
        for (int l = k - 1; l >= j + 1; l--) m->grelha[i][l] = m->peca;
    }

}

void virav(ESTADO *m, int i, int j) {
    VALOR aocontrario;
    if (m->peca == VALOR_O) aocontrario = VALOR_X;
    else aocontrario = VALOR_O;
    int k = i - 1;
    while (k > 0 && m->grelha[k][j] == aocontrario) {
        k--;
    }
    if (m->grelha[k][j] == m->peca) {
        for (int l = k + 1; l <= i - 1; l++) m->grelha[l][j] = m->peca;
    }
    k = i + 1;
    while (k < 8 && m->grelha[k][j] == aocontrario) {
        k++;
    }
    if (m->grelha[k][j] == m->peca) {
        for (int l = k - 1; l >= i + 1; l--) m->grelha[l][j] = m->peca;
    }

}


void viradia(ESTADO *m, int i, int j) {
    int r, t;
    VALOR aocontrario;
    if (m->peca == VALOR_O) aocontrario = VALOR_X;
    else aocontrario = VALOR_O;
    r = i - 1;
    t = j + 1;
    while (r > 0 && t < 8 && m->grelha[r][t] == aocontrario) {
        r--;
        t++;
    }
    if (m->grelha[r][t] == m->peca) {
        int l = r + 1;
        int k = t - 1;
        for (; l <= i - 1 && k >= j + 1; l++, k--) m->grelha[l][k] = m->peca;
    }


    r = i - 1;
    t = j - 1;
    while (r > 0 && t > 0 && m->grelha[r][t] == aocontrario) {
        r--;
        t--;
    }
    if (m->grelha[r][t] == m->peca) {
        int l = r + 1;
        int k = t + 1;
        for (; l <= i - 1 && k <= j - 1; l++, k++) m->grelha[l][k] = m->peca;
    }

    r = i + 1;
    t = j + 1;
    while (r < 8 && t < 8 && m->grelha[r][t] == aocontrario) {
        r++;
        t++;
    }
    if (m->grelha[r][t] == m->peca) {
        int l = r - 1;
        int k = t - 1;
        for (; l >= i + 1 && k >= j + 1; l--, k--) m->grelha[l][k] = m->peca;
    }


    r = i + 1;
    t = j - 1;
    while (r < 8 && t > 0 && m->grelha[r][t] == aocontrario) {
        r++;
        t--;
    }
    if (m->grelha[r][t] == m->peca) {
        int l = r - 1;
        int k = t + 1;
        for (; l >= i + 1 && k <= j - 1; l--, k++) m->grelha[l][k] = m->peca;
    }

}


void legalh(ESTADO *m, int r, int t) {
    VALOR aocontrario;
    int k = t + 1;
    if (m->peca == VALOR_O) aocontrario = VALOR_X;
    else aocontrario = VALOR_O;
    if (t <=6) {
       while (k < 7 && m->grelha[r][k] == aocontrario) {
            k++;
        }
        if (m->grelha[r][k - 1] == aocontrario && m->grelha[r][k] == VAZIA) {
            m->grelha[r][k] = VALOR_SUGESTAO;
        }
    }
   k = t - 1;
    if ( t >= 1) {
        while (k > 0 && m->grelha[r][k] == aocontrario) {
            k--;
        }
        if (m->grelha[r][k + 1] ==aocontrario && m->grelha[r][k] == VAZIA) {
            m->grelha[r][k] = VALOR_SUGESTAO;

        }
    }
}

void legalv(ESTADO *m, int r, int t) {
    VALOR aocontrario;
    int k = r + 1;
    if (m->peca == VALOR_O) aocontrario = VALOR_X;
    else aocontrario = VALOR_O;
    if (r <=6) {
        while (k < 7 && m->grelha[k][t] == aocontrario) {
            k++;
        }
        if (m->grelha[k - 1][t] != m->peca && m->grelha[k][t] == VAZIA) {
            m->grelha[k][t] = VALOR_SUGESTAO;

        }
    }
    k = r - 1;
    if (r >= 1) {
        while (k > 0 && m->grelha[k][t] == aocontrario) {
            k--;
        }
        if (m->grelha[k + 1][t] != m->peca && m->grelha[k][t] == VAZIA) {
            m->grelha[k][t] = VALOR_SUGESTAO;
        }
    }
}

void legald(ESTADO *m, int r, int t) {
    VALOR aocontrario;
    if (m->peca == VALOR_O) aocontrario = VALOR_X;
    else aocontrario = VALOR_O;
    int k = r - 1, z = t + 1;
    if (k >= 1 && t <= 6) {
        while (k > 0 && z < 7 && m->grelha[k][z] == aocontrario) {
            k--;
            z++;
        }
        if (m->grelha[k + 1][z - 1] == aocontrario && m->grelha[k][z] == VAZIA) {
            m->grelha[k][z] = VALOR_SUGESTAO;
        }
    }
    k = r - 1;
    z = t - 1;
    if (k >= 1 && z >= 1) {
        while (k > 0 && z > 0 && m->grelha[k][z] == aocontrario) {
            k--;
            z--;
        }
        if (m->grelha[k + 1][z + 1] == aocontrario && m->grelha[k][z] == VAZIA) {
            m->grelha[k][z] = VALOR_SUGESTAO;
        }
    }
    k = r + 1;
    z = t + 1;
    if (k <= 6 && z <= 6) {
        while (k < 7 && z < 7 && m->grelha[k][z] == aocontrario) {
            k++;
            z++;
        }
        if (m->grelha[k - 1][z - 1] == aocontrario && m->grelha[k][z] == VAZIA) {
            m->grelha[k][z] = VALOR_SUGESTAO;

        }
    }
    k = r + 1;
    z = t - 1;
    if (k <= 6 && z >= 1) {
        while (k < 7 && z > 0 && m->grelha[k][z] == aocontrario) {
            k++;
            z--;
        }
        if (m->grelha[k - 1][z + 1] == aocontrario && m->grelha[k][z] == VAZIA) {
            m->grelha[k][z] = VALOR_SUGESTAO;
        }
    }
}


void legal(ESTADO e) {

    ESTADO m = e;
    int r, t;
    for (r = 0; r < 8; r++) {
        for (t = 0; t < 8; t++) {
            if (e.grelha[r][t] == e.peca) {
                legalh(&m, r, t);
                legalv(&m, r, t);
                legald(&m, r, t);
            }
        }
    }
    printa(m);


}

void comandos(ESTADO e) {

    char linha[50];
    char c1, c2;
    int i, j;
    UNDO a=NULL;
    UNDO anterior;
    anterior=a;
    a = malloc(sizeof(struct UNDO));
    a->anterior=anterior;
    a->atual = e;
    do {
        if (e.grelha[4][4] != VAZIA) {
            VALOR aocontrario;
            if (e.peca == VALOR_X) aocontrario = VALOR_O;
            else aocontrario = VALOR_X;
            if (procuravalidas(&e) == 0) {
                e.peca = aocontrario;
                if (procuravalidas(&e) == 0) {
                    endgame(e);
                }
            }
        }

        char b = valtochar(e.peca);
        if(contagemO(e)+contagemX(e)==0){
            printf("MENU\n");
            printf("N X/O - Comando para iniciar um tabuleiro novo. A peça que colocar após o N é a peça que joga primeiro\n");
            printf("J x y - Comando para jogar\n");
            printf("S - Comando para mostrar todas as jogadas possíveis\n");
            printf("E (nome) - Comando para guardar um tabuleiro\n");
            printf("L (nome) - Comando para carregar um tabuleiro\n");
            printf("U - Comando para voltar à jogada anterior\n");
            printf("Q - Comando para encerrar o jogo\n");
        }
        if (contagemO(e) + contagemX(e) != 64 && contagemX(e) + contagemO(e) != 0)
            printf("É a vez do jogador (%c)\n", b);
        fgets(linha, 50, stdin);
        switch (toupper(linha[0])) {
            case 'N': {
                anterior=a;
                sscanf(linha, "%c %c", &c1, &c2);
                e = estadoinicial(toupper(c2));
                e.modo = 0;
                printa(e);
                a = malloc(sizeof(struct UNDO));
                a->anterior=anterior;
                a->atual = e;
                break;
            }
            case 'J': {
                anterior = a;
                sscanf(linha, "%c %d %d", &c1, &i, &j);
                if ((validoh(&e, i - 1, j - 1) || validov(&e, i - 1, j - 1)|| validod(&e, i - 1, j - 1) ) &&
                    e.grelha[i - 1][j - 1] == VAZIA) {
                    e = jogada(e, i, j);
                    a = malloc(sizeof(struct UNDO));
                    a->anterior = anterior;
                    a->atual = e;
                }
                else printf("\nJogada inválida, tente novamente!\n");
                printa(e);
                break;
            }
            case 'S': {
                sscanf(linha, "%c", &c1);
                legal(e);
                break;
            }
            case 'E': {
                char nome[60];
                sscanf(linha, "%c %s", &c1, nome);
                save(e, nome);
                break;
            }
            case 'L': {
                char nome[60];
                sscanf(linha, "%c %s\n", &c1, nome);
                load(&e, nome);
                anterior = a;
                a = malloc(sizeof(struct UNDO));
                a->anterior = anterior;
                a->atual = e;
                printa(e);
                break;
            }
            case 'U': {
                anterior=a;
                if (a->anterior != NULL) {
                    e = a->anterior->atual;
                    a = a->anterior;
                    free(anterior);
                }
                printa(e);
                break;
            }
            default:
                printf("Comando não existente! Tente novamente!");
                printa(e);
                break;
        }
    } while (toupper(linha[0]) != 'Q');
}

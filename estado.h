//
// Created by pja on 27/02/2019.
//



#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H




/**
 @file main.c
 @authors Júlio Alves, Lucie Dantas e Catarina Vieira


 Biblioteca de todas as funções utilizadas para a realização do trabalho
 */



// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O,VALOR_SUGESTAO} VALOR;


/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;

typedef struct UNDO {
    ESTADO atual;
    struct UNDO *anterior;
} *UNDO ;

void printa(ESTADO); /// Imprime o tabuleiro no ecrã
ESTADO estadoinicial(char); /// Coloca o tabuleiro pronto para começar a jogar
void endgame(ESTADO); /// Vê qual é o resultado final
int procuravalidas(ESTADO*); /// Procura se há jogadas válidas
ESTADO jogada(ESTADO,int,int); /// Coloca uma peça no tabuleiro
void virar(ESTADO*,int,int); /// Função que engloba as funções "viraX" para virar peças de acordo com uma orientação (diagonal,vertical ou horizontal)
void virah(ESTADO* ,int,int);
void virav(ESTADO *,int,int);
void viradia(ESTADO*,int,int);
int contagemX(ESTADO); /// conta o número de peças X no tabuleiro
int contagemO(ESTADO); /// conta o número de peças O no tabuleiro
void comandos(ESTADO); /// função com todos os comandos disponíveis
void legal(ESTADO); ///  função que engloba todas as funções "legalX" para indicar quais são as jogadas possíveis de acordo com uma orientação (diagonal,vertical ou horizontal)
void legalh(ESTADO *,int, int);
void legalv(ESTADO*,int, int);
void legald(ESTADO*,int,int);
void save(ESTADO,char[]); ///Função que guarda um tabuleiro
void load(ESTADO*,char[]); /// Função que carrega um tabuleiro
char valtochar(VALOR); /// Função que converte do tipo VALOR para o tipo CHAR
VALOR chartoval(char); /// Função que converte do tipo CHAR para o tipo VALOR
int validov(ESTADO*,int,int); /// Função que vê se é possível jogar segundo as peças colocadas na vertical
int validoh(ESTADO*,int,int);/// Função que vê se é possível jogar segundo as peças colocadas na horizontal
int validod(ESTADO*,int,int);/// Função que vê se é possível jogar segundo as peças colocadas na diagonal

#endif //PROJ_ESTADO_H
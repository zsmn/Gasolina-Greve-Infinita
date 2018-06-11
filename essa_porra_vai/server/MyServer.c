#include <stdlib.h>
#include "server.h"
#include <stdio.h>
#include <string.h>
// defines
#define DIREITA 1
#define ESQUERDA 2
#define CIMA 3
#define BAIXO 4
#define ATIRE 5
#define DANO 6
#define SPRITE_1 7
#define SPRITE_2 8
#define SPRITE_3 9
#define SPRITE_4 10
#define SPRITE_5 11
#define SPRITE_6 12
#define DEAD 13
#define jogadores 4
#define mensagem struct msg_ret_t
char pos[jogadores][5]; // matriz para armazenar posicoes iniciais do jogadores
char pers[jogadores];
char matrizOcupada[40][61];
char aux[5];
char aux2;
int i, cont = 0; // contador   
void pegaPers();
void posicaoInicial(char pos[][5]);
int bloqueiaPosicao(int posicaoX,int posicaoY,char tecla,char matrizOcupada[][61]);
void aceitaConexao();
void pegaPers();
void fazMov();
void preencheMatriz(char matrizOcupada[][61]);
int main() {
    preencheMatriz(matrizOcupada);
    posicaoInicial(pos); // coloca os jogadores nas posicoes iniciais
    serverInit(jogadores); // inicia o server
    system("clear");
    puts("o servidor esta funcionando!!");
    aceitaConexao(); // a conexao fica aberta para os usuarios entrarem
    pegaPers();
    broadcast(pers, jogadores*sizeof(char));
    fprintf(stderr,"sai e mandei");
    fprintf(stderr,"%c\n%c",pers[0],pers[1]);
    fazMov();
}
void posicaoInicial(char pos[][5]){
   int i;
    for(i=0;i<jogadores;i++){
        pos[i][0]=8;
        pos[i][1]=17;
        pos[i][2] = '0';
        pos[i][3] = '0';
    }
}
 
void aceitaConexao(){
    int id;
    int status=0;
    int ID_Disponivel=0;   
    broadcast(&status,sizeof(int));
    while(ID_Disponivel<jogadores){
        id = acceptConnection();
        if(id != NO_CONNECTION){
            fprintf(stderr,"O usuario[%d] foi conectado\n",id);
            ID_Disponivel++;
        }
        sendMsgToClient(&id,sizeof(int),id);
    }
    status = 1;
    broadcast(&status,sizeof(int));
}
void pegaPers(){
    while(cont < jogadores){
        mensagem msgjog2 = recvMsg(&aux2);
        if(msgjog2.status == MESSAGE_OK){
            pers[msgjog2.client_id] = aux2;
            cont++;
        }
    }
}
void fazMov(){
    while (1){
        mensagem msgjog = recvMsg(aux);
        if (msgjog.status == MESSAGE_OK){
            pos[msgjog.client_id][0]=aux[0];
            pos[msgjog.client_id][1]=aux[1];
            pos[msgjog.client_id][2]=aux[2];
            pos[msgjog.client_id][3]=aux[3];
            pos[msgjog.client_id][4]=aux[4];
            //fprintf(stderr,"x: %d y: %d\n",aux[0],aux[1]);
            if(pos[msgjog.client_id][4]=='w'){
                //fprintf(stderr,"cliquei w, jogador %d",msgjog.client_id);
                pos[msgjog.client_id][1]=bloqueiaPosicao(pos[msgjog.client_id][0],pos[msgjog.client_id][1],pos[msgjog.client_id][4],matrizOcupada);
                //fprintf(stderr," depois :x: %d y: %d\n",pos[msgjog.client_id][0],pos[msgjog.client_id][1]);
            }
            else if(pos[msgjog.client_id][4]=='s'){
                pos[msgjog.client_id][1]=bloqueiaPosicao(pos[msgjog.client_id][0],pos[msgjog.client_id][1],pos[msgjog.client_id][4],matrizOcupada);
                //fprintf(stderr,"cliquei s, jogador %d",msgjog.client_id);
                //fprintf(stderr," depois :x: %d y: %d\n",pos[msgjog.client_id][0],pos[msgjog.client_id][1]);
            }
            else if(pos[msgjog.client_id][4]=='a'){
                pos[msgjog.client_id][0]=bloqueiaPosicao(pos[msgjog.client_id][0],pos[msgjog.client_id][1],pos[msgjog.client_id][4],matrizOcupada);
                //fprintf(stderr,"cliquei a jogador %d",msgjog.client_id);
                //fprintf(stderr," depois :x: %d y: %d\n",pos[msgjog.client_id][0],pos[msgjog.client_id][1]);
            }
            else if(pos[msgjog.client_id][4]=='d'){
                pos[msgjog.client_id][0]=bloqueiaPosicao(pos[msgjog.client_id][0],pos[msgjog.client_id][1],pos[msgjog.client_id][4],matrizOcupada);
                //fprintf(stderr,"cliquei d, jogador %d",msgjog.client_id);
                //fprintf(stderr," depois :x: %d y: %d\n",pos[msgjog.client_id][0],pos[msgjog.client_id][1]);
            }
            broadcast(pos,jogadores*5);
        }
    }
}
int bloqueiaPosicao(int posicaoX,int posicaoY,char tecla,char matrizOcupada[][61]){
    if(tecla == 'w'){
        if(matrizOcupada[posicaoY-1][posicaoX]=='0'){
            posicaoY--;
            return posicaoY;
        }
        else{
            return posicaoY;
        }
    }
    else{
        if(tecla == 'a'){
            if(matrizOcupada[posicaoY][posicaoX-1]=='0'){
                posicaoX--;
                return posicaoX;
            }
            else{
                return posicaoX;
            }
        }
        else{
            if(tecla == 's'){
                if(matrizOcupada[posicaoY+1][posicaoX]=='0'){
                    posicaoY++;
                    return posicaoY;
                }
                else{
                    return posicaoY;
                }  
            }
            else if(tecla == 'd'){
                //printf("ENTREI SDJOIASJ\n");
                if(matrizOcupada[posicaoY][posicaoX+1]=='0'){
                    //printf("AQUI TBM\n");
                    posicaoX++;
                    return posicaoX;
                }
                else{
                    return posicaoX;
                }
            }
        }
    }
}
void preencheMatriz(char matrizOcupada[][61]){//foi alterada
    strcpy(matrizOcupada[0],"111111111111111111111111111111111111111111111111111111111111");
    strcpy(matrizOcupada[1],"111111111111111111111111111111111111111111111111111111111111");
    strcpy(matrizOcupada[2],"111111111111111111111111111111111111111111111111111111111111");
    strcpy(matrizOcupada[3],"111111111111111111111111111111111111111111111111111111111111");
    strcpy(matrizOcupada[4],"111100000000000000000000000000000000000000000000000000001111");
    strcpy(matrizOcupada[5],"111100000000000000000000000000000000000000000000000000001111");
    strcpy(matrizOcupada[6],"111100000000000000000000011110001111110011111111111111001111");
    strcpy(matrizOcupada[7],"111111111111111111111111111111111111110011111111111111001111");
    strcpy(matrizOcupada[8],"111111111111111111111111100111111100000000000000000011001111");
    strcpy(matrizOcupada[9],"111111111111111111111111100111111100000000000000000011001111");
    strcpy(matrizOcupada[10],"111111111111111111111111100111111111111111111111111011001111");
    strcpy(matrizOcupada[11],"111111111111111111111111100111111111111111111111111011001111");
    strcpy(matrizOcupada[12],"111111111111111111111111100111111111111111111111111011111111");
    strcpy(matrizOcupada[13],"111111111111111111111111101111111111111111111111111011111111");
    strcpy(matrizOcupada[14],"111100000111111111000000000000000000000000000000000000000000");
    strcpy(matrizOcupada[15],"111100000111111111000000000000000000000000000000000000000000");
    strcpy(matrizOcupada[16],"111100000111111111100000000000000000000000000000000000000000");
    strcpy(matrizOcupada[17],"111100000000000000000000000000000000000000000000000000000000");
    strcpy(matrizOcupada[18],"111100000000000000000000000000000100000000000000000011111111");
    strcpy(matrizOcupada[19],"111100000000000000000001111111111111111110000000000011111111");
    strcpy(matrizOcupada[20],"111100000000000000000011111111111111111110001111111111111111");
    strcpy(matrizOcupada[21],"111100000000111000000001000000111111111110001111111111111111");
    strcpy(matrizOcupada[22],"111100000000111000000001000000111111111110001111111111001111");
    strcpy(matrizOcupada[23],"111100000000000000000001111111111111111010001111111111001111");
    strcpy(matrizOcupada[24],"100000000000000000000001111111100000000000000000000000001111");
    strcpy(matrizOcupada[25],"100000000000000000000001111111111111111110001111111111001111");
    strcpy(matrizOcupada[26],"100000000000000000000000000000000000000000000000000011001111");
    strcpy(matrizOcupada[27],"111111110000000000000000000000000000000000000000000011001111");
    strcpy(matrizOcupada[28],"111111110000000011110000000000001111111111111111111111001111");
    strcpy(matrizOcupada[29],"111111111111111111111111000000001111111111111111111111001111");
    strcpy(matrizOcupada[30],"111111111111111111111111000000001111111111111111111111001111");
    strcpy(matrizOcupada[31],"111111111111111111111111000000001111111111111111111111001111");
    strcpy(matrizOcupada[32],"111100000011100000001111000000000000000000000000000000001111");
    strcpy(matrizOcupada[33],"111100000000000010001111000000000000000000000000000000001111");
    strcpy(matrizOcupada[34],"111100000000000000001111000000000000000000000000000000001111");
    strcpy(matrizOcupada[35],"111111111100111111111111000000000000000000000000000000001111");
    strcpy(matrizOcupada[36],"111100000000000000001111111111111111111101111111111000001111");
    strcpy(matrizOcupada[37],"111100000000000000000000111111111111111101111111111000001111");
    strcpy(matrizOcupada[38],"111100000000000000000000000000000000000000110000000000111111");
    strcpy(matrizOcupada[39],"111100000000000000000000000000000000000000111111111111111111");
}

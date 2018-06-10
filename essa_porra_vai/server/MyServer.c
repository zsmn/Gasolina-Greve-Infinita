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
#define jogadores 2
#define mensagem struct msg_ret_t
char pos[jogadores][4]; // matriz para armazenar posicoes iniciais do jogadores
char pers[jogadores];
char aux[4];
char aux2;
int i, cont = 0; // contador	
void pegaPers();
void posicaoInicial(char pos[][3]);
void aceitaConexao();
void pegaPers();
void fazMov();
int main() {
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
void posicaoInicial(char pos[][3]){
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
    		broadcast(pos,jogadores*4*sizeof(char)); 
  		}
	}
}

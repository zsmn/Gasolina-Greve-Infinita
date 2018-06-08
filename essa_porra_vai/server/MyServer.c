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
#define jogadores 3
#define mensagem struct msg_ret_t

void posicaoInicial(char pos[][2]);

void aceitaConexao();
int main() {
  char  pos[jogadores][2]; // matriz para armazenar posicoes iniciais do jogadores
  char aux[2];
  int i; // contador
	
	
  posicaoInicial(pos); // coloca os jogadores nas posicoes iniciais
  serverInit(jogadores); // inicia o server
  system("clear");
  puts("o servidor esta funcionando!!");
	aceitaConexao(); // a conexao fica aberta para os usuarios entrarem
  while (1){
    mensagem msgjog = recvMsg(aux);
    if (msgjog.status == MESSAGE_OK) {
      pos[msgjog.client_id][0]=aux[0];
      pos[msgjog.client_id][1]=aux[1];
      //broadcast(pos,2*sizeof(int));
      broadcast(pos,jogadores*2*sizeof(char)); 
    } 
  }
}
void posicaoInicial(char pos[][2]){
   int i;
	for(i=0;i<jogadores;i++){
		 pos[i][0]=8;
		 pos[i][1]=17;
	}
}

void aceitaConexao(){
	int id;
	int status=1;
	int ID_Disponivel=0;	
	while(ID_Disponivel<jogadores){
		id = acceptConnection();
		if(id != NO_CONNECTION){
			fprintf(stderr,"O usuario[%d] foi conectado\n",id);
			ID_Disponivel++;
		}
		sendMsgToClient(&id,sizeof(int),id);

	}
	broadcast(&status,sizeof(int));

}

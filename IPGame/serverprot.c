#include <stdlib.h>
#include "server.h"
#include <stdio.h>
#include <string.h>
#define jogadores 2
#define mensagem struct msg_ret_t
void checavalidespos(unsigned short posx,unsigned short posy,unsigned short passo,unsigned short* or);
int main() {
  int  pos[jogadores][2];
  int aux[2];
  pos[0][0]=8;
  pos[0][1]=17;
  pos[1][0]=8;
  pos[1][1]=17;
  serverInit(2);
  char tecla;
  int old;
  char dif;
  puts("o servidor esta funcionando!!");
  int count=0,i;
  int id;
  while(count<jogadores){
    id = acceptConnection();
    if (id != NO_CONNECTION) {
      puts("hey, alguem se conectou\n");
      fprintf(stderr,"id do cara: %d",id);
      count++;
    }
  }
  while (1){
    mensagem msgjog = recvMsg(aux);
    if (msgjog.status == MESSAGE_OK) {
      pos[msgjog.client_id][0]=aux[0];
      pos[msgjog.client_id][1]=aux[1];
      //broadcast(pos,2*sizeof(int));
      for(i=0;i<jogadores;i++){
         fprintf(stderr," jogadorID: %d posicao x:%d posicao y:%d\n",i,pos[i][0],pos[i][1]);
      }    
    } 
  }
}

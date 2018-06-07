#include <stdlib.h>
#include "server.h"
#include <stdio.h>
#include <string.h>
#define jogadores 4
#define mensagem struct msg_ret_t
void checavalidespos(unsigned short posx,unsigned short posy,unsigned short passo,unsigned short* or);
int main() {
  char  pos[jogadores][2];
  char aux[2];
  int i;
  for(i=0;i<jogadores;i++){
   pos[i][0]=8;
   pos[i][1]=17;
  }
  serverInit(jogadores);
  char tecla;
  int old;
  char dif;
  puts("o servidor esta funcionando!!");
  int count=0;
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
    if (msgjog.status == MESSAGE_OK){
      pos[msgjog.client_id][0]=aux[0];
      pos[msgjog.client_id][1]=aux[1];
      //broadcast(pos,2*sizeof(int));
      broadcast(pos,jogadores*2*sizeof(char)); 
    } 
  }
}

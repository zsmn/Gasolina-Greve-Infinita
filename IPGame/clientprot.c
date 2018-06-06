#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#define jogadores 2
void checavalidespos(unsigned short posx,unsigned short posy,unsigned short passo,unsigned short* or);
int main() {
  unsigned short  pos[2][2];
  serverInit(2);
  char tecla;
  puts("o servidor esta funcionando!!");
  while (1) 
  {
    int id = acceptConnection();
    if (id != NO_CONNECTION) {
      recvMsgFromClient(pos[id], id, WAIT_FOR_IT);
      printf("primeiro jogador conectou, coordenadas x: %d y: %d",pos[id][0],pos[id][1]);
    }
    struct msg_ret_t msgjog = recvMsg(&tecla);
    if (msgjog.status == MESSAGE_OK) {
      if (tecla == 'w'){ //ægora ele checa se tem colisao, para cima
	      pos[msgjog.client_id][1]-=5;
	      checavalidespos(pos[msgjog.client_id][0],pos[msgjog.client_id][1],-5,&pos[msgjog.client_id][1]);
	      sendMsgToClient(&pos[msgjog.client_id][1],2,msgjog.client_id);
      }
      else if (tecla == 'a'){//para a esquerda
         pos[msgjog.client_id][0]-=5;
         checavalidespos(pos[msgjog.client_id][0],pos[msgjog.client_id][1],-5,&pos[msgjog.client_id][0]);
          sendMsgToClient(&pos[msgjog.client_id][0],2,msgjog.client_id);
      }
      else if ('s' == tecla){//para baixo
         pos[msgjog.client_id][1]+=5;   
         checavalidespos(pos[msgjog.client_id][0],pos[msgjog.client_id][1],5,&pos[msgjog.client_id][1]); 
         sendMsgToClient(&pos[msgjog.client_id][1],2,msgjog.client_id);   
      }
      else if ('d' == tecla){//para a direita
         pos[msgjog.client_id][0]+=5;
         checavalidespos(pos[msgjog.client_id][0],pos[msgjog.client_id][1],5,&pos[msgjog.client_id][0]);
         sendMsgToClient(&pos[msgjog.client_id][0],2,msgjog.client_id);
      }              
    } 
  }
}
void checavalidespos(unsigned short posx,unsigned short posy,unsigned short passo,unsigned short* or){
    if(posx>=0&&posx<=960&&posy>=0&&posy<=70){
        *or-=passo;
    }
    else if(posx>=0&&posx<=63&&posy>=70&&posy<=392){
        *or-=passo;
    }
    else if(posx>=63&&posx<=145&&posy>=113&&posy<=233){
	    *or-=passo;
	}
	else if(posx>=145&&posx<=287&&posy>=121&&posy<=287){
	    *or-=passo;
	}
	else if(posx>=287&&posx<=401&&posy>=113&&posy<=233){
	    *or-=passo;
	}
    else if(posx>=401&&posx<=463&&posy>=96&&posy<=135){
	    *or-=passo;
	}
	else if(posx>=432&&posx<=546&&posy>=98&&posy<=234){
	    *or-=passo;
	}
	else if(posx>=544&&posx<=606&&posy>=102&&posy<=132){
	    *or-=passo;
	}
	else if(posx>=644&&posx<=860&&posy>=98&&posy<=130){
	    *or-=passo;
	}
	else if(posx>=900&&posx<=960&&posy>=68&&posy<=232){
	    *or-=passo;
	}
	else if(posx>=836&&posx<=862&&posy>=132&&posy<=232){
		*or-=passo;
	}
	else if(posx>=866&&posx<=898&&posy>=194&&posy<=232){
		*or-=passo;
    }
	else if(posx>=544&&posx<=814&&posy>=162&&posy<=232){
	    *or-=passo;
	}
	else if(posx>=198&&posx<=236&&posy>=344&&posy<=386){
	    *or-=passo;
	}
	else if(posx>=370&&posx<=492&&posy>=300&&posy<=426){
	    *or-=passo;
	}
	else if(posx>=492&&posx<=660&&posy>=316&&posy<=424){
	    *or-=passo;
	}
	else if(posx>=704&&posx<=866&&posy>=322&&posy<=388){
	    *or-=passo;
	}
	else if(posx>=836&&posx<=864&&posy>=290&&posy<=324){
	    *or-=passo;
	}
	else if(posx>=864&&posx<=960&&posy>=290&&posy<=354){
	    *or-=passo;
	}
	else if(posx>=704&&posx<=862&&posy>=412&&posy<=422){
	    *or-=passo;
	}
	else if(posx>=0&&posx<=960&&posy>=0&&posy<=70){
	    *or-=passo;
	}
	else if(posx>=832&&posx<=864&&posy>=420&&posy<=448){
	    *or-=passo;
	}
	else if(posx>=514&&posx<=862&&posy>=448&&posy<=520){
	    *or-=passo;
	}
	else if(posx>=900&&posx<=960&&posy>=354&&posy<=703){
	    *or-=passo;
	}
	else if(posx>=0&&posx<=66&&posy>=448&&posy<=703){
	    *or-=passo;
	}
	else if(posx>=64&&posx<=324&&posy>=450&&posy<=528){
	    *or-=passo;
	}
	else if(posx>=320&&posx<=386&&posy>=466&&posy<=602){
	    *or-=passo;
	}
	else if(posx>=66&&posx<=960&&posy>=646&&posy<=703){
	    *or-=passo;
	}
	else if(posx>=66&&posx<=158&&posy>=578&&posy<=584){
	    *or-=passo;
	}
	else if(posx>=196&&posx<=324&&posy>=578&&posy<=584){
		*or-=passo;
	}
	else if(posx>=388&&posx<=640&&posy>=578&&posy<=612){
		*or-=passo;
	}
	else if(posx>=662&&posx<=812&&posy>=578&&posy<=612){
		*or-=passo;
	}
	else if(posx<0||posx>=960||posy<0||posy>=703){
		*or-=passo;
	}
    else if(posx>=868&&posx<=898&&posy>=606&&posy<=644){
	    *or-=passo;
	}
	else if(posx<0||posx>=960||posy<0||posy>=703){
	    *or-=passo;
	}
}

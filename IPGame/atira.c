#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void tiros(int xo, int yo, int pox, int poy, int id, int posibala[6][75][2]){
	// xo e yo ponto clicado, po lugar dos chars
	int i;
	int x, y;
	double m;
	if(xo==pox && yo>poy){
		i=0;
		y=poy;
		while(y<=yo){
			y++;
			posibala[id][i][0]=xo;
			posibala[id][i][1]=y;
			i++;
		}
		posibala[id][i-1][0]=-1;
		posibala[id][i-1][1]=-1;
		for(i=0;i<100;i++){
			printf("posibala=(%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
			if(posibala[id][i][0]==-1)break;
		}
	}else{
		if(xo==pox && yo<poy){
			y=poy;
			i=0;
			while(y>=yo){
				y--;
				posibala[id][i][0]=xo;
				posibala[id][i][1]=y;
				i++;
			}
			posibala[id][i-1][0]=-1;
			posibala[id][i-1][1]=-1;
			for(i=0;i<100;i++){
				printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
				if(posibala[id][i][0]==-1)break;
			}
		}else{
			if(xo>pox){
				i=0;
				m=(double)(yo-poy)/(xo-pox);
				for(x=pox;x<=xo;x++,i++){
					y=(int)(m*(x-pox)+poy);
					posibala[id][i][0]=x;
					posibala[id][i][1]=y;
				}
				posibala[id][i][0]=-1;
				posibala[id][i][1]=-1;
				for(i=0;i<100;i++){
					printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
					if(posibala[id][i][0]==-1)break;
				}
			}else{
				i=0;
				m=(double)(yo-poy)/(xo-pox);
				for(x=pox;x>=xo;x--,i++){
					y=(int)(m*(x-pox)+poy);
					posibala[id][i][0]=x;
					posibala[id][i][1]=y;
				}
				posibala[id][i][0]=-1;
				posibala[id][i][1]=-1;
				for(i=0;i<100;i++){
					printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
					if(posibala[id][i][0]==-1)break;
				}
			}
		}
	}

}
int main(){
	int bala[6][75][2],xop,yop,ox,oy,di;
	printf("ID:\n");
	scanf("%d",&di);
	printf("Posi:\n");
	scanf("%d %d",&xop,&yop);
	printf("click:\n");
	scanf("%d %d",&ox,&oy);
	tiros(ox,oy,xop,yop,di,bala);
}
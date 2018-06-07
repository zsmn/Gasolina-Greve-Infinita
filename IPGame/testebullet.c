#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>

int main(){
	// x0 e y0 ponto clicado, po inico do charac
	int x,y,xo,yo,pox,poy;
	double m;
	printf("digite a posição(x,y) do jogador: ");
	scanf("%d %d",&pox,&poy);
	printf("digite a posição(x,y) do click: ");
	scanf("%d %d",&xo,&yo);
	if(xo==pox && yo>poy){
		y=poy;
		while(y<=yo)
		y++;
		printf("posi bala: (%d , %d)\n", x,y);
	}else{
		if(xo==pox && yo<poy){
			y=poy;
			while(y>=yo)
				y--;
			printf("pois bala: (%d , %d)\n", x,y);
		}else{
			if(xo>pox){
				m=(double)(yo-poy)/(xo-pox);
				for(x=pox;x<=xo;x++){
					y=(int)(m*(x-pox)+poy);
					printf("posi bala: (%d , %d)\n", x,y);
				}		
			}else{
				m=(double)(yo-poy)/(xo-pox);
				for(x=pox;x>=xo;x--){
					y=(int)(m*(x-pox)+poy);
					printf("posi bala: (%d , %d)\n", x,y);
				}		
			}
		
		}
	}


	return 0;
}
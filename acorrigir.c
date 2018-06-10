double tiros(int xo, int yo, int pox, int poy, int id, int posibala[6][960][2]){
    // xo e yo ponto clicado, po lugar dos chars
    int i;
    int x, y;
    double m=2.5;
    for(i=0;i<960;i++){
        posibala[id][i][0]=2;
        posibala[id][i][1]=2;
    }
    if(xo==pox){
        if(yo>poy){
            i=0;
            y=poy;
            while(y<=yo){
                y++;
                posibala[id][i][0]=xo;
                posibala[id][i][1]=y;
                i++;
            }
            posibala[id][i-1][0]=2;
            posibala[id][i-1][1]=2;
            /*for(i=0;i<100;i++){
                printf("posibala=(%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                if(posibala[id][i][0]==-1)break;
            }*/
            return m;
        }else{
            y=poy;
            i=0;
            while(y>=yo){
                y--;
                posibala[id][i][0]=xo;
                posibala[id][i][1]=y;
                i++;
            }
            posibala[id][i-1][0]=2;
            posibala[id][i-1][1]=2;
            /*for(i=0;i<100;i++){
                printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                if(posibala[id][i][0]==-1)break;
            }*/
            return m;
        }
    }
        else{
            m=(double)(yo-poy)/(xo-pox);
            if(m<5.6 && m>-5.6){
            if(xo>pox){
                i=0;
               // m=(double)(yo-poy)/(xo-pox);
                for(x=pox;x<=xo;x++,i++){
                    y=(int)(m*(x-pox)+poy);
                    posibala[id][i][0]=x;
                    posibala[id][i][1]=y;
                }
                posibala[id][i][0]=2;
                posibala[id][i][1]=2;
                /*for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==-1)break;
                }*/
                return m;
            }else{
                i=0;
               // m=(double)(yo-poy)/(xo-pox);
                for(x=pox;x>=xo;x--,i++){
                    y=(int)(m*(x-pox)+poy);
                    posibala[id][i][0]=x;
                    posibala[id][i][1]=y;
                }
                posibala[id][i][0]=2;
                posibala[id][i][1]=2;
                /*for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==-1)break;
                }*/
                return m;
            }
        }else{
            if(yo>poy){
            i=0;
            y=poy;
            while(y<=yo){
                y++;
                posibala[id][i][0]=xo;
                posibala[id][i][1]=y;
                i++;
            }
            posibala[id][i-1][0]=2;
            posibala[id][i-1][1]=2;
            /*for(i=0;i<100;i++){
                printf("posibala=(%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                if(posibala[id][i][0]==-1)break;
            }*/
            return m;
        }else{
            y=poy;
            i=0;
            while(y>=yo){
                y--;
                posibala[id][i][0]=xo;
                posibala[id][i][1]=y;
                i++;
            }
            posibala[id][i-1][0]=2;
            posibala[id][i-1][1]=2;
            /*for(i=0;i<100;i++){
                printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                if(posibala[id][i][0]==-1)break;
            }*/
            return m;
        }
        }

        }
    }
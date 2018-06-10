#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdbool.h>
const float tempofade = 1.5;
const int LARGURA_TELA = 960;
const int ALTURA_TELA = 703; //ðeclaro o tamanho das telas
const int passo = 1;  //declaro quantos passos ando
ALLEGRO_DISPLAY *janela = NULL; //ponteiro para a janela
ALLEGRO_SAMPLE *som_tiro=NULL; //ponteiro para o efeito sonoro de disparo
ALLEGRO_AUDIO_STREAM *musica = NULL; //ponteiro para a musica
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;  //ponteiro para a fila de eventos
ALLEGRO_BITMAP *imagem = NULL;  //ponteiro para a imagem
ALLEGRO_BITMAP *menu = NULL;  //ponteiro para o menu do jogo
ALLEGRO_BITMAP *grupo = NULL;   //lonteiro para o bitmap da imagem do grupo
ALLEGRO_BITMAP *fundo = NULL; //ponteiro do pano de fundo
ALLEGRO_BITMAP *quadrado = NULL;  //quadradinho q eh o jogador
//
ALLEGRO_BITMAP *tiro = NULL;// tiro pra desenhar
//

/* tela de seleção de personagens */
ALLEGRO_BITMAP *personagens = NULL; // tela da seleção de personagens

/* personagens */
ALLEGRO_BITMAP *perso1 = NULL;
ALLEGRO_BITMAP *perso2 = NULL;
ALLEGRO_BITMAP *perso3 = NULL;
ALLEGRO_BITMAP *perso4 = NULL;
ALLEGRO_BITMAP *perso5 = NULL;
ALLEGRO_BITMAP *perso6 = NULL;
/* personagens */

/* vida de personagens */
ALLEGRO_BITMAP *bvida = NULL;
ALLEGRO_TIMER *timer = NULL; // inicia o timer

int bloqueiaPosicao(int posicaoX,int posicaoY,char tecla,char matrizOcupada[][61]);//andar na matriz
void fadeout(int velocidade);  //função pra dar o fadeout
void checavalidespos(int posx,int posy,int passo,int* or);
void fadein(ALLEGRO_BITMAP *imagem, int velocidade);  //função q dao fadein
void setAudio(char k[]); //função de audio
void setarVida(int n);
bool inicializar();  //função q inicializa 
void preencheMatriz();// cria matriz
int bloqueiaPosicao(int posicaoX,int posicaoY,char tecla,char matrizOcupada[][61]);//anda na matriz
double tiros(int xo, int yo, int pox, int poy, int id, int posibala[6][960][2]);
int main(void){
    bool sair = false; //declaro a variavel sair
    if (!inicializar()){ //chamo inicializar, se der errado paro programa
        return -1;
    }
    int auxiliar = 0;
    int desenha = 1; //inicio desenha como 1
    int posx = 8, dir_x = passo; //seto a posição e a passada do personagem
    int posy = 17, dir_y = passo;
    int jogar = 1;
    int selecao;
    char matrizOcupada[40][61];
    preencheMatriz(matrizOcupada);
     
    /* variaveis da animacao do personagem */
    const int maxFrame = 2;
    int curFrame = 0;
    int frameCount = 0;
    int frameDelay = 1;
    int frameWidth = 42;
    int frameHeight = 38;
    int pp;
    int pers = 0;
    
    /* variaveis usavas pra a musica */
    int timer = 0;
    int ttest = 0;
    int musat = 0;
    
    /* tempo de cada musica */
    int tmpmusic[5] = {212, 152, 184, 280, 248};
    char endmusic[5][30] = {"sounds/whenyouwere.ogg", "sounds/waitandbleed.ogg",
    "sounds/timeofdying.ogg", "sounds/psychosocial.ogg", "sounds/freakonaleash.ogg"};

    // variavel pra obter a tecla pressionada
    char tecl;

    // variavel de vida do jogador
    int vida = 3;

    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer()); //começo a musica
    al_set_audio_stream_playing(musica, true); //comeca a musica

   // fadein(fundo, 1); //a imagem do pano de fundo entra
   // al_rest(tempofade); //dica durante 3 segundos
   // fadeout(1);//e sai
   // grupo = al_load_bitmap("resources/group.jpeg"); //seta a imagem do grupo
   // fadein(grupo, 1); //faz a aparecer a imagem do grupo
   // al_rest(tempofade); //€spera 3 segundos
   // fadeout(1); //e sai
    int bala[6][960][2];
    int i=0;
    int perm=0;
    int clickx;
    int clicky; 
    int testando=1;
    int m;
    //matriz e permissões da bala
    menu = al_load_bitmap("resources/menu.bmp");
    fadein(menu, 1);

    while(jogar != 0){
        al_draw_bitmap(menu, 0, 0, 0);
            while(!al_is_event_queue_empty(fila_eventos)){
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);
                
                if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    /* botao de inicio */
                    if(evento.mouse.x >= 112 && evento.mouse.x <= 362 &&
                    evento.mouse.y >= 482 && evento.mouse.y <= 580){
                        jogar = 0;
                        selecao = 1;
                    }
                    /* botao de opcoes */
                    if(evento.mouse.x >= 382 && evento.mouse.x <= 607 &&
                    evento.mouse.y >= 482 && evento.mouse.y <= 580){
                        jogar = 0;
                        selecao = 0;
                    }
                    /* botao de sair */
                    if(evento.mouse.x >= 626 && evento.mouse.x <= 862 &&
                    evento.mouse.y >= 482 && evento.mouse.y <= 580){
                        al_destroy_audio_stream(musica);
                        al_destroy_event_queue(fila_eventos);
                        al_destroy_display(janela); //tudo termina
                        return 0;
                    }
                }
            }
        al_rest(0.1);
    }

    //fadeout(1);
    personagens = al_load_bitmap("resources/perso.png");
    al_draw_bitmap(personagens, 0, 0, 0);
    //fadein(personagens, 1);
    
    perso1 = al_load_bitmap("resources/perso1.png");
    perso2 = al_load_bitmap("resources/perso2.png");
    perso3 = al_load_bitmap("resources/perso3.png");
    perso4 = al_load_bitmap("resources/perso4.png");
    perso5 = al_load_bitmap("resources/perso5.png");
    perso6 = al_load_bitmap("resources/perso6.png");
    
    while(selecao != 0){
        al_draw_bitmap(personagens, 0, 0, 0);
        
        al_convert_mask_to_alpha(perso1,al_map_rgb(255,0,255));
        al_convert_mask_to_alpha(perso2,al_map_rgb(255,0,255));
        al_convert_mask_to_alpha(perso3,al_map_rgb(255,0,255));
        al_convert_mask_to_alpha(perso4,al_map_rgb(255,0,255));
        al_convert_mask_to_alpha(perso5,al_map_rgb(255,0,255));
        al_convert_mask_to_alpha(perso6,al_map_rgb(255,0,255));
        al_draw_bitmap(perso1, 157, 339, 0);
        al_draw_bitmap(perso2, 422, 341, 0);
        al_draw_bitmap(perso3, 709, 342, 0);
        al_draw_bitmap(perso4, 151, 551, 0);
        al_draw_bitmap(perso5, 420, 552, 0);
        al_draw_bitmap(perso6, 705, 552, 0);
        al_flip_display();
        
            while(!al_is_event_queue_empty(fila_eventos)){
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);
                
                if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 157 && evento.mouse.x <= 339 &&
                    evento.mouse.y >= 339 && evento.mouse.y <= 432){
                        fprintf(stderr, "PERSO1\n");
                        pers = 1;
                        selecao = 0;
                    }
                    if(evento.mouse.x >= 422 && evento.mouse.x <= 519 &&
                    evento.mouse.y >= 341 && evento.mouse.y <= 434){
                        fprintf(stderr, "PERSO2\n");
                        selecao = 0;
                        pers = 2;
                    }
                    if(evento.mouse.x >= 709 && evento.mouse.x <= 807 &&
                    evento.mouse.y >= 342 && evento.mouse.y <= 435){
                        fprintf(stderr, "PERSO3\n");
                        selecao = 0;
                        pers = 3;
                    }
                    if(evento.mouse.x >= 151 && evento.mouse.x <= 246 &&
                    evento.mouse.y >= 551 && evento.mouse.y <= 644){
                        fprintf(stderr, "PERSO4\n");
                        selecao = 0;
                        pers = 4;
                    }
                    if(evento.mouse.x >= 420 && evento.mouse.x <= 515 &&
                    evento.mouse.y >= 552 && evento.mouse.y <= 645){
                        fprintf(stderr, "PERSO5\n");
                        selecao = 0;
                        pers = 5;
                    }
                    if(evento.mouse.x >= 705 && evento.mouse.x <= 801 &&
                    evento.mouse.y >= 552 && evento.mouse.y <= 645){
                        fprintf(stderr, "PERSO6\n");
                        selecao = 0;
                        pers = 6;
                    }
                }
            }
        al_rest(0.1);
    }                    
    
    imagem = al_load_bitmap("resources/aa.png");  //faz o download do mapa do jogo
    fadein(imagem, 1); //faz ela aparecer
    al_draw_bitmap(imagem, 0, 0, 0);  //coloca a imagem
    al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, (posx) * 16, (posy) * 16,21,19, 0);//desenha o personagem
    setarVida(vida);
    //bvida = al_load_bitmap("resources/bvida3.png");
    al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));
    al_draw_bitmap(bvida, 0, 0, 0);
    al_flip_display();// bota tudo isso para o jogador
    setAudio("sounds/whenyouwere.ogg");//começa a melhor musica possivel

    while (!sair){//entra no loop do jogo
        while (!al_is_event_queue_empty(fila_eventos)){//se  acontecer algo
            ALLEGRO_EVENT evento;   //declara variavel eveno
            al_wait_for_event(fila_eventos, &evento);//esse evento fica na fila
            
                if(evento.type == ALLEGRO_EVENT_TIMER){
                /* loop que controla o timer (que regula a musica) */
                    timer++;
                    if(timer == 60){
                        ttest++;
                        timer = 0;
                        if(ttest == tmpmusic[musat%5]){
                           ttest = 0;
                           musat++;
                           setAudio(endmusic[musat%5]);
                        }
                    }
                }
                if(perm==0){//Se essa variável valer 0, significa que nenhum disparo foi efetuado
                    if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && perm==0){//Se houver clique quando nao há disparo de determinado player
                        clickx = evento.mouse.x/16;//Pega a abscissa do clique em pixels e divide por 16 para poder ser colocada como índice da matriz do mapa posteriormente
                        clicky = evento.mouse.y/16;//Pega a ordenada do clique em pixels e divide por 16 para poder ser colocada como índice da matriz do mapa posteriormente
                        m = tiros(evento.mouse.x,evento.mouse.y,posx*16,posy*16,testando,bala);//a função tiro retorna o coeficiente angular da reta que define a trajetória do tiro
                        perm=1;//Se essa variável valer 1, significa que um disparo foi efetuado
			al_play_sample(som_tiro, 2.0, 0.0,3.0,ALLEGRO_PLAYMODE_ONCE,NULL); //Quando um disparo é efetuado, o som de disparo é reproduzido
                    }
                } 
                 if (evento.keyboard.keycode == ALLEGRO_KEY_W){ //agora ele checa se tem colisao, para cima
                    //posy -= dir_y;
                    //checavalidespos(posx,posy,-dir_y,&posy);
                    
                    desenha = 1;
                    tecl='w';
                    posy = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pp = 1;
                    }
                if (evento.keyboard.keycode == ALLEGRO_KEY_A){//para a esquerda
                   // posx -= dir_x;
                    //checavalidespos(posx,posy,-dir_x,&posx);
                    desenha=1;
                    tecl='a';
                    posx = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pp = 2;
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_S){//para baixo
                    //posy += dir_y;
                    //checavalidespos(posx,posy,dir_y,&posy);
                    desenha=1;
                    tecl='s';
                    posy = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pp = 0;
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_D){//para a direita
                    //posx += dir_x;
                    //checavalidespos(posx,posy,dir_x,&posx);
                    desenha=1;
                    tecl='d';
                    pp = 3;
                    posx = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                }
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){  //se n tiver evento, sai 
                sair = true;
                return 0;
            }
            if(desenha && al_is_event_queue_empty(fila_eventos)) {
                if(tecl == 's' || tecl == 'w' || tecl == 'a' || tecl == 'd'){
                    for(auxiliar = 0; auxiliar < 1; auxiliar++){//alterado de 5 pra 1
                    if(frameCount++ >= frameDelay){
                        if(curFrame++ >= maxFrame){
                            curFrame = 0;
                        }

                        frameCount = 0;
                    }
                    // como usar:
                    // al_draw_bitmap_region(*BITMAP, pontolarguraDaImagemOriginal, pontoAlturaDaImagemOriginal, LarguraDoFrameQueVcQuerPegar, AlturaDoFrameQueVcQuerPegar, xquevainascer, yquevainascer, 0);
                        al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//Desenha o mapa
                        al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                        setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                        al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                        al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                        al_flip_display();//atualizando a tela
                        al_clear_to_color(al_map_rgb(0, 0, 0)); // evita 'restos de pixeis'
			if(perm==1){//se houve disparo do personagem(essa condicional tá dentro da condicional que verifica se "WASD" foi pressionado)
                   
                    if(bala[testando][i][0]!=2){
                        if(matrizOcupada[(bala[testando][i+1][1])/16][(bala[testando][i+1][0])/16]=='1' && i>30){//Impede que a bala atravesse pŕedio e casas
                            perm=0;//torna "perm" 0 novamente pra indicar que o jogador poderá efetuar outro disparo, já que o disparo anterior foi "dissipado" -> (esse jogo só permite que uma bala por jogador fique ativa)
                            i=0;//a trajetória da bala fica armazenada na forma de duplas ordenadas na matriz bala, o "i" serve pra passar em ordem pelas coordenadas guardadas na matriz bala
                            al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//desenhando o mapa
                            al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                            setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                            al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                            al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                            al_flip_display();//atualizando a tela
                            al_clear_to_color(al_map_rgb(0, 0, 0));//evita restos de pixels
                        }else{//Se não há obstáculo, a bala poderá ser desenhadada
                    
                            tiro = al_load_bitmap("resources/sprite do tiro.bmp");//carregando a imagem que contém a bala
                            al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//desenhando o mapa
                            al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                            setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                            al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                            al_convert_mask_to_alpha(tiro,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os tiros transparente
                            al_draw_scaled_bitmap(tiro, 19 , 18, 19, 18, ((bala[testando][i][0])), ((bala[testando][i][1])),12,11.3, 0);//desenha a imagem com 12 x 11.3 pixels para a bala ficar menor que o personagem
                            al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                            al_flip_display();//atualizando a tela
                            al_clear_to_color(al_map_rgb(0, 0, 0));//evita restos de pixels  
                            i=i+10;//vai somando 10 para a a bala não ficar muito lenta(pega de 10 em 10 duplas ordenadas)     
                        }
                        }else{//se bala[testando][i][0]==2, significa que não há mais duplas ordenadas referentes a trajetória, então a bala deverá ser "dissipada", ou seja, não será mais desenhada
                            perm=0;//em consequência do dissipamento da bala, "perm" volta a valer 0 para o jogador poder voltar a disparar 
                            i=0;//volta para primeira dupla ordenada, pois ela que deverá ser usada primeiramente quando um novo disparo for efetuado
                             al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//desenhando o mapa
                            al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                            setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                            al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                            al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                            al_flip_display();//atualizando a tela
                            al_clear_to_color(al_map_rgb(0, 0, 0));//evita restos de pixels
                        }
                }
                    }
                    tecl = '0'; // evita que entre no loop dnv
                }
		//o "if(perm==1)" é repetido pois a bala se movimenta independentemente do jogador ter se movimentado
		if(perm==1){//se houve disparo do personagem(essa condicional tá fora da condicional que verifica se "WASD" foi pressionado)
                   
                    if(bala[testando][i][0]!=2){
                        if(matrizOcupada[(bala[testando][i+1][1])/16][(bala[testando][i+1][0])/16]=='1' && i>30){//Impede que a bala atravesse pŕedio e casas
                            perm=0;//torna "perm" 0 novamente pra indicar que o jogador poderá efetuar outro disparo, já que o disparo anterior foi "dissipado" -> (esse jogo só permite que uma bala por jogador fique ativa)
                            i=0;//a trajetória da bala fica armazenada na forma de duplas ordenadas na matriz bala, o "i" serve pra passar em ordem pelas coordenadas guardadas na matriz bala
                            al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//desenhando o mapa
                            al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                            setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                            al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                            al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                            al_flip_display();//atualizando a tela
                            al_clear_to_color(al_map_rgb(0, 0, 0));//evita restos de pixels
                        }else{//Se não há obstáculo, a bala poderá ser desenhadada
                    
                            tiro = al_load_bitmap("resources/sprite do tiro.bmp");//carregando a imagem que contém a bala
                            al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//desenhando o mapa
                            al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                            setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                            al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                            al_convert_mask_to_alpha(tiro,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os tiros transparente
                            al_draw_scaled_bitmap(tiro, 19 , 18, 19, 18, ((bala[testando][i][0])), ((bala[testando][i][1])),12,11.3, 0);//desenha a imagem com 12 x 11.3 pixels para a bala ficar menor que o personagem
                            al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                            al_flip_display();//atualizando a tela
                            al_clear_to_color(al_map_rgb(0, 0, 0));//evita restos de pixels  
                            i=i+10;//vai somando 10 para a a bala não ficar muito lenta(pega de 10 em 10 duplas ordenadas)     
                        }
                        }else{//se bala[testando][i][0]==2, significa que não há mais duplas ordenadas referentes a trajetória, então a bala deverá ser "dissipada", ou seja, não será mais desenhada
                            perm=0;//em consequência do dissipamento da bala, "perm" volta a valer 0 para o jogador poder voltar a disparar 
                            i=0;//volta para primeira dupla ordenada, pois ela que deverá ser usada primeiramente quando um novo disparo for efetuado
                             al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);//desenhando o mapa
                            al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(o boneco tava com um corpinho e um cabeção), há controle de pixels que é desenhado
                            setarVida(vida);//essa função recebe um inteiro que dirá o número de corações(vidas) o personagem tem
                            al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixando a cor rosa(que tá no fundo) na imagem que contém os corações transparente
                            al_draw_bitmap(bvida, 0, 0, 0);//desenhando os corações(vidas) na tela
                            al_flip_display();//atualizando a tela
                            al_clear_to_color(al_map_rgb(0, 0, 0));//evita restos de pixels
                        }
                }
            }
        }
    }
    al_destroy_audio_stream(musica);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela); //tudo termina
    return 0;
}
 
void fadeout(int velocidade){
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
    al_set_target_bitmap(buffer); 
    al_draw_bitmap(al_get_backbuffer(janela), 0, 0, 0); 
    al_set_target_bitmap(al_get_backbuffer(janela));
    if (velocidade <= 0){
        velocidade = 1;
    }
    else if (velocidade > 15){
        velocidade = 15;
    }
    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
        al_flip_display();
        al_rest(0.005); // Não é necessário caso haja controle de FPS
    }
 
    al_destroy_bitmap(buffer);
}

void fadein(ALLEGRO_BITMAP *imagem, int velocidade)
{
    if (velocidade < 0)
    {
        velocidade = 1;
    }
    else if (velocidade > 15)
    {
        velocidade = 15;
    }
 
    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(imagem, al_map_rgba(alfa, alfa, alfa, alfa), 0, 0, 0);
        al_flip_display();
        al_rest(0.005); // Não é necessário caso haja controle de FPS
    }
}
bool inicializar(){ //inicializa tudo e checa se tudo deu crto
    al_init_image_addon();
    
    if (!al_init()){
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
    timer = al_create_timer(1.0/480);//alterado
    if(!timer){
        fprintf(stderr, "Falha ao criar o timer.\n");
    }
    if (!al_install_audio()){
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        return false;
    }
    if (!al_init_acodec_addon()){
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        return false;
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        return false;
    }
    if (!al_install_keyboard()){
        fprintf(stderr, "Falha ao inicializar teclado.\n");
        return false;
    }
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela){
        fprintf(stderr, "Falha ao criar a janela.\n");
        return false;
    }
    
    // inicialização e configuração do mouse
    if(!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse");
        al_destroy_display(janela);
        return -1;
    }
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
    
    fila_eventos = al_create_event_queue();
    if (!fila_eventos){
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
    som_tiro = al_load_sample( "sounds/Tirosniper1.ogg" );
    if (!som_tiro){
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_sample(som_tiro);
        return 0;
    }
    musica = al_load_audio_stream("sounds/soundtest.ogg", 4, 1024);
    if (!musica){
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(janela);
        return false;
    }
    al_set_window_title(janela, "IP GAME");
    //quadrado = al_create_bitmap(20, 20);
    quadrado = al_load_bitmap("bon2.png"); // cria o 'personagem'
    if (!quadrado){
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return 0;
    }
    al_convert_mask_to_alpha(quadrado,al_map_rgb(255,0,255)); // usa a cor rosa como transparencia

    al_set_target_bitmap(quadrado);
    //al_clear_to_color(al_map_rgb(255, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(janela));
    fundo = al_load_bitmap("resources/cin.jpeg");
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_start_timer(timer);
    return true;
}

void setAudio(char k[]){ //comeca musiquinha
    al_set_audio_stream_playing(musica, false);
    musica = al_load_audio_stream(k, 4, 1024);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);
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
    strcpy(matrizOcupada[24],"000000000000000000000001111111100000000000000000000000001111");
    strcpy(matrizOcupada[25],"000000000000000000000001111111111111111110001111111111001111");
    strcpy(matrizOcupada[26],"000000000000000000000000000000000000000000000000000011001111");
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
int bloqueiaPosicao(int posicaoX,int posicaoY,char tecla,char matrizOcupada[][61]){
 
    if(tecla == 'w'){
        if(matrizOcupada[posicaoY-1][posicaoX]=='0'){
            matrizOcupada[posicaoY][posicaoX] = '0';
            matrizOcupada[posicaoY-1][posicaoX] = '1';
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
                matrizOcupada[posicaoY][posicaoX]='0';
                matrizOcupada[posicaoY][posicaoX-1]='1';
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
                    matrizOcupada[posicaoY][posicaoX]='0';
                    matrizOcupada[posicaoY+1][posicaoX]='1';
                    posicaoY++;
                    return posicaoY;
                }
                else{
                    return posicaoY;
                }  
            }
            else if(tecla == 'd'){
                printf("ENTREI SDJOIASJ\n");
                if(matrizOcupada[posicaoY][posicaoX+1]=='0'){
                    printf("AQUI TBM\n");
                    matrizOcupada[posicaoY][posicaoX]='0';
                    matrizOcupada[posicaoY][posicaoX+1]='1';
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

double tiros(int xo, int yo, int pox, int poy, int id, int posibala[6][960][2]){
    printf("ENTREIIIII\n");
    // xo e yo ponto clicado, po lugar dos chars
    int i;
    int x, y;
    double m=1;
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
            for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==2)break;
                }
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
            for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==2)break;
                }
            return m;
        }
    }
        else{
            m=(double)(yo-poy)/(xo-pox);
            if(m<1.73 && m>-1.73){
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
                for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==2)break;
                }
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
                for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==2)break;
                }
                return m;
            }
        }else{
            if(yo>poy){
                i=0;
                for(y=poy;y<=yo;y++,i++){
                    x =(int)pox + ((y-poy)/m);
                    posibala[id][i][0]=x;
                    posibala[id][i][1]=y;
                    
                }
                posibala[id][i-1][0]=2;
                posibala[id][i-1][1]=2;
                for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==2)break;
                }
                return m;
            }else{
                i=0;
                for(y=poy;y>=yo;y--,i++){
                    x =(int)pox + ((y-poy)/m);
                    posibala[id][i][0]=x;
                    posibala[id][i][1]=y;
                    
                }
                posibala[id][i-1][0]=2;
                posibala[id][i-1][1]=2;
                for(i=0;i<100;i++){
                    printf("posibala = (%d)(%d,%d)\n",i,posibala[id][i][0],posibala[id][i][1]);
                    if(posibala[id][i][0]==2)break;
                }
                return m;
            }
        }

    
    }
}

void setarVida(int n){
    if(n == 3){
        bvida = al_load_bitmap("resources/bvida3.png");
    }else if(n == 2){
        bvida = al_load_bitmap("resources/bvida2.png");
    }else if(n == 1){
        bvida = al_load_bitmap("resources/bvida1.png");
    }else{
        bvida = al_load_bitmap("resources/bvida0.png");
    }
}




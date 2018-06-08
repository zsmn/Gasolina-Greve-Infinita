#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>
#include "client.h"
#define jogadores 2
#define IP "172.20.4.20"
void conectar();
int id;
const float tempofade = 1.5;
const int LARGURA_TELA = 960;
const int ALTURA_TELA = 703; //ðeclaro o tamanho das telas
const int passo = 1;  //declaro quantos passos ando
 
int vida = 3;
char posx = 8; //seto a posição e a passada do personagem
char posy = 17;
int pp;
int frameWidth = 42;
int frameHeight = 38;
int curFrame = 0;
char pos[jogadores][2];
 
ALLEGRO_DISPLAY *janela = NULL; //ponteiro para a janela
ALLEGRO_AUDIO_STREAM *musica = NULL; //ponteiro para a musica
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;  //ponteiro para a fila de eventos
ALLEGRO_BITMAP *imagem = NULL;  //ponteiro para a imagem
ALLEGRO_BITMAP *menu = NULL;  //ponteiro para o menu do jogo
ALLEGRO_BITMAP *grupo = NULL;   //lonteiro para o bitmap da imagem do grupo
ALLEGRO_BITMAP *fundo = NULL; //ponteiro do pano de fundo
ALLEGRO_BITMAP *quadrado = NULL;  //quadradinho q eh o jogador
 
ALLEGRO_BITMAP *player1 = NULL;
ALLEGRO_BITMAP *player2 = NULL;
 
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
void fadein(ALLEGRO_BITMAP *imagem, int velocidade);  //função q dao fadein
void setAudio(char k[]); //função de audio
void setarVida(int n);
bool inicializar();  //função q inicializa
void preencheMatriz();// cria matriz
void desenhar();
int bloqueiaPosicao(int posicaoX,int posicaoY,char tecla,char matrizOcupada[][61]);//anda na matriz
int main(void){
    conectar();
    system("clear");
    fprintf(stderr,"essa porra sai");
    bool sair = false; //declaro a variavel sair
    if (!inicializar()){ //chamo inicializar, se der errado paro programa
        return -1;
    }
    int i;  
    int auxiliar = 0;
    int desenha = 1; //inicio desenha como 1
    int jogar = 1;
    int selecao;
    int dir_x = passo, dir_y = passo;
    char matrizOcupada[40][61];
    preencheMatriz(matrizOcupada);
   
    /* variaveis da animacao do personagem */
    const int maxFrame = 2;
    int frameCount = 0;
    int frameDelay = 1;
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
   fadein(fundo, 1); //a imagem do pano de fundo entra
   
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer()); //começo a musica
    al_set_audio_stream_playing(musica, true); //comeca a musica
	al_draw_bitmap(fundo, 0, 0, 0);   
al_rest(tempofade); //dica durante 3 segundos
    fadeout(1);//e sai
    grupo = al_load_bitmap("resources/group.jpeg"); //seta a imagem do grupo
    fadein(grupo, 1); //faz a aparecer a imagem do grupo
    al_rest(tempofade); //€spera 3 segundos
    fadeout(1); //e sai
    menu = al_load_bitmap("resources/menu.bmp");
    fadein(menu, 1);
		 /* seta os bitmaps */
     player1 = al_create_bitmap(20, 20);
     al_set_target_bitmap(player1);
     al_clear_to_color(al_map_rgb(255, 0, 0));
     player2 = al_create_bitmap(20, 20);
     al_set_target_bitmap(player2);
     al_clear_to_color(al_map_rgb(255, 255, 255));
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
 
    fadeout(1);
    personagens = al_load_bitmap("resources/perso.png");
    al_draw_bitmap(personagens, 0, 0, 0);
    fadein(personagens, 1);
   
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
         recvMsgFromServer(pos,DONT_WAIT);
         desenhar();
        while (!al_is_event_queue_empty(fila_eventos)){//se  acontecer algo
            ALLEGRO_EVENT evento;   //declara variavel eveno
            al_wait_for_event(fila_eventos, &evento);//esse evento fica na fila
           
                if(evento.type == ALLEGRO_EVENT_TIMER){
                    //desenhar();
                /* loop que controla o timer (que regula a musica) */
                    timer++;
                    if(timer == 600){
                        ttest++;
                        fprintf(stderr, "%i\n", ttest);
                        timer = 0;
                        if(ttest == tmpmusic[musat%5]){
                           ttest = 0;
                           musat++;
                           setAudio(endmusic[musat%5]);
                        }
                    }
                }
 
                 if (evento.keyboard.keycode == ALLEGRO_KEY_W){ //ægora ele checa se tem colisao, para cima
                   
                    desenha = 1;
                    tecl='w';
                    posy = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pp = 1;
                    pos[id][0]=posx;
                    pos[id][1]=posy;
                    sendMsgToServer(pos[id],2*sizeof(char));
                    desenhar();
                    }
                if (evento.keyboard.keycode == ALLEGRO_KEY_A){//para a esquerda
                   // posx -= dir_x;
                    //checavalidespos(posx,posy,-dir_x,&posx);
                    desenha=1;
                    tecl='a';
                    posx = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pp = 2;
                    pos[id][0]=posx;
                    pos[id][1]=posy;
                    sendMsgToServer(pos[id],2*sizeof(char));
                    desenhar();
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_S){//para baixo
                    //posy += dir_y;
                    //checavalidespos(posx,posy,dir_y,&posy);
                    desenha=1;
                    tecl='s';
                    posy = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pp = 0;
                    pos[id][0]=posx;
                    pos[id][1]=posy;
                    sendMsgToServer(pos[id],2*sizeof(char));
                    desenhar();
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_D){//para a direita
                    //posx += dir_x;
                    //checavalidespos(posx,posy,dir_x,&posx);
                    desenha=1;
                    tecl='d';
                    pp = 3;
                    posx = bloqueiaPosicao(posx,posy,tecl,matrizOcupada);
                    pos[id][0]=posx;
                    pos[id][1]=posy;
                    sendMsgToServer(pos[id],2*sizeof(char));
                    desenhar();
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
                    }
                    tecl = '0'; // evita que entre no loop dnv
                }
            }
        }
    }
    al_destroy_audio_stream(musica);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela); //tudo termina
    return 0;
}
 
void desenhar(){
    int i = 0;
    al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
     /* desenha os quadradinhos de cada jogador */
 
    al_draw_bitmap(player1, pos[0][0]*16, pos[0][1]*16, 0);
    al_draw_bitmap(player2, pos[1][0]*16, pos[1][1]*16, 0);
 
    /* printa as posicoes dos jogadores */
    for(i=0;i<jogadores;i++){
        fprintf(stderr," jogadorID: %d posicao x:%d posicao y:%d\n",i,pos[i][0],pos[i][1]);
    }
    fprintf(stderr,"obs: meu id eh: %d",id);
 
    al_draw_scaled_bitmap(quadrado, curFrame * frameWidth, pp * frameHeight, frameWidth, frameHeight, ((posx) * 16), ((posy) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa
    setarVida(vida);
    al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));
    al_draw_bitmap(bvida, 0, 0, 0);
    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0)); // evita 'restos de pixeis'
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
    if(fundo==NULL){
	fprintf(stderr,"essa porra deu bug");
    }
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
void conectar() {
  enum conn_ret_t ans;
  do{
    ans = connectToServer(IP);      
    if (ans == SERVER_DOWN) {
      puts("Servidor esta baixo :(!");
    } else if (ans == SERVER_FULL) {
      puts("servidor cheio!");
    } else if (ans == SERVER_CLOSED) {
      puts("servidor fechado para novas conexoes");
    } else if(ans==SERVER_TIMEOUT) {
      puts("servidor n respondeu");
    }
  }while(ans!=SERVER_UP);
  recvMsgFromServer(&id,WAIT_FOR_IT);
  fprintf(stderr,"ei, seu id eh: %d\n",id);
}

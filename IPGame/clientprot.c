#include <allegro5/allegro.h>
#include "client.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdbool.h>
const float tempofade = 1.5;
const int LARGURA_TELA = 960;
const int ALTURA_TELA = 703; //ðeclaro o tamanho das telas
const int passo = 3;  //declaro quantos passos ando
ALLEGRO_DISPLAY *janela = NULL; //ponteiro para a janela
ALLEGRO_AUDIO_STREAM *musica = NULL; //ponteiro para a musica
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;  //ponteiro para a fila de eventos
ALLEGRO_BITMAP *imagem = NULL;  //ponteiro para a imagem
ALLEGRO_BITMAP *menu = NULL;  //ponteiro para o menu do jogo
ALLEGRO_BITMAP *grupo = NULL;   //lonteiro para o bitmap da imagem do grupo
ALLEGRO_BITMAP *fundo = NULL; //ponteiro do pano de fundo
ALLEGRO_BITMAP *quadrado = NULL;  //quadradinho q eh o jogador

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

ALLEGRO_TIMER *timer = NULL; // inicia o timer
void fadeout(int velocidade);  //função pra dar o fadeout
void fadein(ALLEGRO_BITMAP *imagem, int velocidade);  //função q dao fadein
void setAudio(char k[]); //função de audio
bool inicializar();  //função q inicializa 
void conectar(unsigned short pos[2]);
int main(void){
    bool sair = false; //declaro a variavel sair
    if (!inicializar()){ //chamo inicializar, se der errado paro programa
        return -1;
    }
    int auxiliar = 0, testim = 0;
    int desenha = 1; //inicio desenha como 1
    unsigned short posx = 90, dir_x = passo; //seto a posição e a passada do personagem
    unsigned short posy = 270, dir_y = passo;
    int jogar = 1;
    int selecao;
    unsigned short pos[2];
    pos[0]=posx;
    pos[1]=posy;
    conectar(pos);   
    /* variaveis da animacao do personagem */
 	const int maxFrame = 2;
 	int curFrame = 0;
 	int frameCount = 0;
 	int frameDelay = 5;
 	int frameWidth = 48;
 	int frameHeight = 60;

    // variavel pra obter a tecla pressionada
    char tecl;

    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer()); //começo a musica
    al_set_audio_stream_playing(musica, true); //comeca a musica

    fadein(fundo, 1); //a imagem do pano de fundo entra
    al_rest(tempofade); //dica durante 3 segundos
    fadeout(1);//e sai
    grupo = al_load_bitmap("resources/group.jpeg"); //seta a imagem do grupo
    fadein(grupo, 1); //faz a aparecer a imagem do grupo
    al_rest(tempofade); //€spera 3 segundos
    fadeout(1); //e sai
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
                        selecao = 0;
                    }
                    if(evento.mouse.x >= 422 && evento.mouse.x <= 519 &&
                    evento.mouse.y >= 341 && evento.mouse.y <= 434){
                        fprintf(stderr, "PERSO2\n");
                        selecao = 0;
                    }
                    if(evento.mouse.x >= 709 && evento.mouse.x <= 807 &&
                    evento.mouse.y >= 342 && evento.mouse.y <= 435){
                        fprintf(stderr, "PERSO3\n");
                        selecao = 0;
                    }
                    if(evento.mouse.x >= 151 && evento.mouse.x <= 246 &&
                    evento.mouse.y >= 551 && evento.mouse.y <= 644){
                        fprintf(stderr, "PERSO4\n");
                        selecao = 0;
                    }
                    if(evento.mouse.x >= 420 && evento.mouse.x <= 515 &&
                    evento.mouse.y >= 552 && evento.mouse.y <= 645){
                        fprintf(stderr, "PERSO5\n");
                        selecao = 0;
                    }
                    if(evento.mouse.x >= 705 && evento.mouse.x <= 801 &&
                    evento.mouse.y >= 552 && evento.mouse.y <= 645){
                        fprintf(stderr, "PERSO6\n");
                        selecao = 0;
                    }
                }
            }
        al_rest(0.1);
    }                    
    
    imagem = al_load_bitmap("resources/aa.png");  //faz o download do mapa do jogo
    fadein(imagem, 1); //faz ela aparecer
	al_draw_bitmap(imagem, 0, 0, 0);  //coloca a imagem
	al_draw_bitmap_region(quadrado, 0, 0, frameWidth, frameHeight, posx, posy, 0); //desenha o quadradinho
	al_flip_display();// bota tudo isso para o jogador
 	setAudio("sounds/soundtest2.ogg");//começa a melhor musica possivel
    char tecla;
    while (!sair){//entra no loop do jogo
        while (!al_is_event_queue_empty(fila_eventos)){//se  acontecer algo
            ALLEGRO_EVENT evento;   //declara variavel eveno
            al_wait_for_event(fila_eventos, &evento);//esse evento fica na fila
            
		        if(evento.type == ALLEGRO_EVENT_TIMER){
		        	// aqui vai ser o timer (pretendo usar pra controlar o 'loop' da musica)
		        }

                 if (evento.keyboard.keycode == ALLEGRO_KEY_W){ //ægora ele checa se tem colisao, para cima
			        tecla='w';
			        sendMsgToServer((void*)&tecla,1);
			        desenha = 1;
			        tecl='W';
			        recvMsgFromServer(pos,WAIT_FOR_IT);
			        posx=pos[0];
			        posy=pos[1];
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_A){//para a esquerda
                    tecla='a';
                    sendMsgToServer((void*)&tecla,1);
			        desenha=1;
			        tecl='A';
			        recvMsgFromServer(pos,WAIT_FOR_IT);
			        posx=pos[0];
			        posy=pos[1];
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_S){//para baixo
                    tecla='s';
			        sendMsgToServer((void*)&tecla,1);
			        desenha=1;
			        tecl='S';
			        recvMsgFromServer(pos, WAIT_FOR_IT);
			        posx=pos[0];
			        posy=pos[1];
			        
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_D){//para a direita
                    tecla='d';
			        sendMsgToServer((void*)&tecla,1);
			        desenha=1;
			        tecl='D';
			        recvMsgFromServer(pos,WAIT_FOR_IT);
			        posx=pos[0];
			        posy=pos[1];
                }
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){  //se n tiver evento, sai 
                sair = true;
                return 0;
            }
            if(desenha && al_is_event_queue_empty(fila_eventos)) {
	            if(tecl == 'S' || tecl == 'W' || tecl == 'A' || tecl == 'D'){
	            	for(auxiliar = 0; auxiliar < 5; auxiliar++){
	            	if(frameCount++ >= frameDelay){
		           		if(curFrame++ >= maxFrame){
		           			curFrame = 0;
		           		}

		           		frameCount = 0;
		           	}
		           	// como usar:
		           	// al_draw_bitmap_region(*BITMAP, pontolarguraDaImagemOriginal, pontoAlturaDaImagemOriginal, LarguraDoFrameQueVcQuerPegar, AlturaDoFrameQueVcQuerPegar, xquevainascer, yquevainascer, 0);

				        al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
				        al_draw_bitmap_region(quadrado, curFrame * frameWidth, 0, frameWidth, frameHeight, posx, posy, 0);
			           	al_flip_display();
			           	al_clear_to_color(al_map_rgb(0, 0, 0)); // evita 'restos de pixeis'
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
    timer = al_create_timer(1.0/60);
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
 	quadrado = al_load_bitmap("bon2.bmp"); // cria o 'personagem'
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
void conectar(unsigned short pos[2]) {
  enum conn_ret_t ans;
  do{
    ans = connectToServer("172.22.73.11");      
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
  sendMsgToServer(pos, 2*sizeof(short));
  puts("estamos indo");
}

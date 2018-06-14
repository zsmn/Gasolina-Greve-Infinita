#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "client.h" //incluindo todas as blibliotecas
#define jogadores 2
/* variaveis globais */
const float tempofade = 0.3;  //tempo de fade
const int LARGURA_TELA = 960;
const int ALTURA_TELA = 703; 
bool sair = false;
int cond; 
int dessa;
char tecl;
char end[100];
int i;  
int auxiliar = 0;
int jogar = 1;
int selecao;
char matrizOcupada[40][61];
int opcoesat = 0;
/* variaveis da animacao do personagem */
const int maxFrame = 2;
int frameCount = 0;
int frameDelay = 1;
char pers;
/* variaveis usavas pra a musica */
int tempo = 0;
int ttest = 0;
int musat = 0;
/* tempo de cada musica */
int tmpmusic[5] = {212, 152, 184, 280, 248};
char endmusic[5][30] = {"sounds/whenyouwere.ogg", "sounds/waitandbleed.ogg","sounds/timeofdying.ogg", "sounds/psychosocial.ogg", "sounds/freakonaleash.ogg"};
int id;
char posx; //seto a posição e a passada do personagem
char posy;
int pp;
int frameWidth[6] = {45, 40, 40, 42, 40, 35};
int frameHeight[6] = {41, 48 , 50, 46, 42, 46};
int curFrame = 0;
char dados[jogadores][6];
char persEsc[jogadores];
/* armazenamento da resposta do server e uso da ampulheta */
int status = 0;
char amp[100];
char str[15];
/* criação do display e de alguns bitmaps */
ALLEGRO_DISPLAY *janela = NULL; //ponteiro para a janela
ALLEGRO_AUDIO_STREAM *musica = NULL; //ponteiro para a musica
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;  //ponteiro para a fila de eventos
ALLEGRO_BITMAP *imagem = NULL;  //ponteiro para a imagem
ALLEGRO_BITMAP *menu = NULL;  //ponteiro para o menu do jogo
ALLEGRO_BITMAP *options = NULL;  //ponteiro para o menu de opcoes(ip) do jogo
ALLEGRO_BITMAP *grupo = NULL;   //lonteiro para o bitmap da imagem do grupo
ALLEGRO_BITMAP *fundo = NULL; //ponteiro do pano de fundo
ALLEGRO_BITMAP *quadrado = NULL;  //quadradinho q eh o jogador
ALLEGRO_BITMAP *loading = NULL;
ALLEGRO_BITMAP *ampulheta = NULL;
ALLEGRO_BITMAP* player[jogadores];
ALLEGRO_BITMAP* telaVitoria = NULL;
ALLEGRO_BITMAP* telaDerrota = NULL;
/* tela de seleção de personagens */
ALLEGRO_BITMAP *personagens = NULL; // tela da seleção de personagens
/* character selection */
ALLEGRO_BITMAP *perso1 = NULL;
ALLEGRO_BITMAP *perso2 = NULL;
ALLEGRO_BITMAP *perso3 = NULL;
ALLEGRO_BITMAP *perso4 = NULL;
ALLEGRO_BITMAP *perso5 = NULL;
ALLEGRO_BITMAP *perso6 = NULL;
/* vida de personagens */
ALLEGRO_BITMAP *bvida = NULL;
ALLEGRO_TIMER *timer = NULL; // inicia o timer
/* inicia a fonte */
ALLEGRO_FONT *fonte = NULL;
/* declaração de funções */
void conectar();
int fadeout(int velocidade);  //função pra dar o fadeout
int fadein(ALLEGRO_BITMAP *imagem, int velocidade);  //função q dao fadein
void setAudio(char k[]); //função de audio
void setarVida(int n);
bool inicializar();  //função q inicializa
void desenhar();
void drawHourGlass();
void desenharSelecao();
void efeitoFade(ALLEGRO_BITMAP *bitmap);
void inicializaMenu();
void selectPersonagem();
void jogoInit();
void destroy();
void writeIP(ALLEGRO_EVENT event, char str[]);
int main(void){
    strcpy(str, "127.0.0.1");
    system("clear");
    /* declaracao de variaveis */
    if (!inicializar()){ //chamo inicializar, se der errado paro programa
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    fonte = al_load_font("resources/aa.ttf", 82, 0);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer()); //começo a musica
    al_set_audio_stream_playing(musica, true); //comeca a musica
    efeitoFade(fundo);
    grupo = al_load_bitmap("resources/group.jpeg"); //seta a imagem do grupo
    efeitoFade(grupo);
    menu = al_load_bitmap("resources/menu.bmp");
    fadein(menu, 1);
    /* seta os bitmaps */
    for(i=0;i<jogadores;i++){
        player[i]=al_create_bitmap(20, 20);
        al_set_target_bitmap(player[i]);
        al_clear_to_color(al_map_rgb(255, 0, 0));
    }
    inicializaMenu();
    selectPersonagem();
    conectar();        
    sendMsgToServer(&pers, 1);          
    loading = al_load_bitmap("resources/loading.png");
    while(status != 1){
        drawHourGlass();
    }
    recvMsgFromServer(persEsc, WAIT_FOR_IT);
    jogoInit();
    destroy();
    return 0;
}
void desenharSelecao(){
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
}
void efeitoFade(ALLEGRO_BITMAP *bitmap){
    fadein(bitmap, 1);
    al_draw_bitmap(bitmap, 0, 0, 0);  
    al_rest(tempofade);
    fadeout(1);
}
void drawHourGlass(){
    int i;
    recvMsgFromServer(&status,DONT_WAIT);
    loading = al_load_bitmap("resources/loading.png");
    al_draw_bitmap(loading, 0, 0, 0);
    for(i = 0; i < 240 && status != 1; i++){
        recvMsgFromServer(&status,DONT_WAIT);
        sprintf(amp, "resources/ampulheta/output-%d.png", i);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        ampulheta = al_load_bitmap(amp);
        al_draw_bitmap(loading, 0, 0, 0);
        al_draw_scaled_bitmap(ampulheta, 0, 0, 285, 215, 300, 395, 385, 315, 0);
        al_rest(0.04);
        al_flip_display();
    }
}
void desenhar(){
    int i = 0;
    al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
    /* desenha os quadradinhos de cada jogador */
    for(i=0;i<jogadores;i++){
        if(dados[i][0] > 0){
            sprintf(end, "resources/bon%c.png", persEsc[i]);
            quadrado = al_load_bitmap(end);
            al_convert_mask_to_alpha(quadrado,al_map_rgb(255,0,255));
            al_draw_scaled_bitmap(quadrado, (dados[i][3]-48) * frameWidth[persEsc[i]-49],  (dados[i][2]-48) * frameHeight[persEsc[i]-49], frameWidth[persEsc[i]-49], frameHeight[persEsc[i]-49], ((dados[i][0]) * 16), ((dados[i][1]) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa
        }
    }
    if(dados[id][0] < 0){
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 480, 0, ALLEGRO_ALIGN_CENTRE, "SPECTATING");
    }
 
    setarVida(dados[id][5]);//função que conta o número de vidas de cada jogador
    al_flip_display();//atualiza a tela
    al_clear_to_color(al_map_rgb(0, 0, 0)); // evita 'restos de pixeis'
}
int fadeout(int velocidade){
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(janela), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(janela));
    if (velocidade <= 0){
        if(velocidade<0.0001){
            return 0;
        }
        else{
            velocidade = 1;
        }
    }
    else if (velocidade > 15){
        velocidade = 15;
    }
    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade){
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
        al_flip_display();
        al_rest(0.005); // Não é necessário caso haja controle de FPS
    }
    al_destroy_bitmap(buffer);
}
int fadein(ALLEGRO_BITMAP *imagem, int velocidade){
    if (velocidade < 0){
        if(velocidade<0.0001){
            return 0;
        }
        else{
            velocidade = 1;
        }
    }
    else if (velocidade > 15){
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
bool inicializar(){ //inicializa tudo e checa se tudo foi inicializado com sucesso
    al_init_image_addon();
    if (!al_init()){
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
    timer = al_create_timer(1.0/60);//alterado
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
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
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
    quadrado = al_load_bitmap("resources/bon1.png"); // cria o 'personagem'
    if (!quadrado){
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return 0;
    }
    telaVitoria = al_load_bitmap("resources/win.png");
    telaDerrota = al_load_bitmap("resources/lose.png");
    al_convert_mask_to_alpha(quadrado,al_map_rgb(255,0,255)); // usa a cor rosa como transparencia
    al_set_target_bitmap(quadrado);
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
void setarVida(int n){
    if(n == 3){
        bvida = al_load_bitmap("resources/bvida3.png");
    }
    else if(n == 2){
        bvida = al_load_bitmap("resources/bvida2.png");
    }
    else if(n == 1){
        bvida = al_load_bitmap("resources/bvida1.png");
    }
    else{
        bvida = al_load_bitmap("resources/bvida0.png");
    }
    al_convert_mask_to_alpha(bvida,al_map_rgb(255,0,255));//deixan fundo da imagem, que tem os corações, transparente
    al_draw_bitmap(bvida, 0, 0, 0);//desenha a vida na tela
    al_flip_display();//atualiza a tela
}
void conectar(){
    enum conn_ret_t ans;
    do{
        ans = connectToServer(str);      
        if (ans == SERVER_DOWN) {
            puts("Servidor esta baixo :(!");
        }
        else if (ans == SERVER_FULL) {
            puts("servidor cheio!");
        }
        else if (ans == SERVER_CLOSED) {
            puts("servidor fechado para novas conexoes");
        }
        else if(ans==SERVER_TIMEOUT) {
            puts("servidor n respondeu");
        }
    } while(ans!=SERVER_UP);
    recvMsgFromServer(&id,WAIT_FOR_IT);
	if(id==0){
		posx=8;
		posy=17;
	}
    if(id == 1){
        posx = 4;
        posy = 4;
    }
    if(id == 2){
        posy = 15;
        posx = 20;
    }
    if(id == 3){
        posy = 39;
        posx = 7;
    }
}

 void inicializaMenu(){
    options = al_load_bitmap("resources/ip.png");
    al_draw_bitmap(menu, 0, 0, 0);
    while(jogar != 0 || opcoesat == 1){
        fadeout(0.00001);
        while(!al_is_event_queue_empty(fila_eventos)){
        if(jogar == 1) al_draw_bitmap(menu, 0, 0, 0);
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(jogar != 0){
                if(dessa == 1) al_draw_bitmap(menu, 0, 0, 0);
                if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    /* botao de inicio */
                    if(evento.mouse.x >= 112 && evento.mouse.x <= 362 &&evento.mouse.y >= 482 && evento.mouse.y <= 580){
                        menu = al_load_bitmap("resources/jogar_up.bmp");
                        al_draw_bitmap(menu,0,0,0);
                        al_flip_display();
                        al_rest(0.2);
                        menu = al_load_bitmap("resources/menu.bmp");
                        al_draw_bitmap(menu,0,0,0);
                        jogar = 0;
                        selecao = 1;
                    }
                    /* botao de opcoes */
                    if(evento.mouse.x >= 382 && evento.mouse.x <= 607 &&evento.mouse.y >= 482 && evento.mouse.y <= 580){
                        menu = al_load_bitmap("resources/opcoes_up.bmp");
                        al_draw_bitmap(menu,0,0,0);
                        al_flip_display();
                        al_rest(0.2);
                        menu = al_load_bitmap("resources/menu.bmp");
                        al_draw_bitmap(menu,0,0,0);
                        jogar = 0;
                        selecao = 0;
                        opcoesat = 1;
                        dessa = 0;
                        al_draw_bitmap(options, 0, 0, 0);
                        if (strlen(str) > 0){
                            al_draw_text(fonte, al_map_rgb(255, 255, 255), 470, 450, ALLEGRO_ALIGN_CENTRE, str);
                        }  
                    }
                    /* botao de sair */
                    if(evento.mouse.x >= 626 && evento.mouse.x <= 862 &&evento.mouse.y >= 482 && evento.mouse.y <= 580){
                        menu = al_load_bitmap("resources/sair_up.bmp");
                        al_draw_bitmap(menu,0,0,0);
                        al_flip_display();
                        al_rest(0.2);
                        menu = al_load_bitmap("resources/menu.bmp");
                        al_draw_bitmap(menu,0,0,0);
                        al_flip_display();
                        al_rest(0.5);
                        destroy();
                        exit(1);
                    }
                }
            }else{
                if(opcoesat == 1 && evento.type == ALLEGRO_EVENT_KEY_CHAR){
                    writeIP(evento, str);
                    al_draw_bitmap(options, 0, 0, 0);
                    if (strlen(str) > 0){
                        al_draw_text(fonte, al_map_rgb(255, 255, 255), 470, 450, ALLEGRO_ALIGN_CENTRE, str);
                    }
                }
            }
        }
        al_flip_display();
        al_rest(0.1);
    }
    fadeout(1);
}
void writeIP(ALLEGRO_EVENT event, char str[]){//função que permite a entrada de um IP pelo usuário, esse IP(tem que ser o mesmo para os quatro players) é necerrário para os jogadores poderem jogar em LAN
    if(strlen(str) < 15){
        char temp[] = {event.keyboard.unichar, '\0'};
        if(event.type == ALLEGRO_EVENT_KEY_CHAR){//recebe um caractere do teclado
            if ((event.keyboard.unichar >= '0' && event.keyboard.unichar <= '9') || event.keyboard.unichar == '.'){
                strcat(str, temp);
            }
        }
    }
    if(strlen(str)){
        if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
            str[strlen(str)-1] = '\0';
        }
    }
    if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
        opcoesat = 0;
        jogar = 1;
        dessa = 1;
    }
}
void selectPersonagem(){//carrega a imagem do personagem e depois desenha na tela para possibilitar a seleção de personagem feita pelo player
    personagens = al_load_bitmap("resources/perso.png");
    al_draw_bitmap(personagens, 0, 0, 0);
    fadein(personagens, 1);
    perso1 = al_load_bitmap("resources/perso2.png");
    perso2 = al_load_bitmap("resources/perso1.png");
    perso3 = al_load_bitmap("resources/perso3.png");
    perso4 = al_load_bitmap("resources/perso6.png");
    perso5 = al_load_bitmap("resources/perso5.png");
    perso6 = al_load_bitmap("resources/perso4.png");
    while(selecao != 0){
    	al_draw_bitmap(personagens, 0, 0, 0);
        desenharSelecao();
        while(!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);        
            if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){//posição do clique do mouse(em pixels) indica qual personagem foi escolhido
            	if(evento.mouse.x >= 157 && evento.mouse.x <= 339 &&evento.mouse.y >= 339 && evento.mouse.y <= 432){
                    pers = '1';
                    selecao = 0;
                }
                if(evento.mouse.x >= 422 && evento.mouse.x <= 519 &&evento.mouse.y >= 341 && evento.mouse.y <= 434){
                    selecao = 0;
                    pers = '2';
                }
                if(evento.mouse.x >= 709 && evento.mouse.x <= 807 &&evento.mouse.y >= 342 && evento.mouse.y <= 435){
                    selecao = 0;
                    pers = '3';
                }
                if(evento.mouse.x >= 151 && evento.mouse.x <= 246 &&evento.mouse.y >= 551 && evento.mouse.y <= 644){
                    selecao = 0;
                    pers = '4';
                }
                if(evento.mouse.x >= 420 && evento.mouse.x <= 515 &&evento.mouse.y >= 552 && evento.mouse.y <= 645){
                    selecao = 0;
                    pers = '5';
                }
                if(evento.mouse.x >= 705 && evento.mouse.x <= 801 &&evento.mouse.y >= 552 && evento.mouse.y <= 645){
                    selecao = 0;
                    pers = '6';
                }
            }
        }
        al_rest(0.1);
    }
}
void jogoInit(){//função que inicia o jogo
    int i;
    int contador = 0;
    dados[id][0] = posx;//posição na horizontal
    dados[id][1] = posy;//posição na vertical
    dados[id][2]='0';
    dados[id][3] = '0';
    dados[id][4]=0;//Posteriormente, armazenará a tecla pressionada
    dados[id][5]=3;//vida
    sendMsgToServer(dados[id], 6);
    imagem = al_load_bitmap("resources/aa.png");  //faz o carregamento do mapa do jogo
    fadein(imagem, 1); //faz ela aparecer
    al_draw_bitmap(imagem, 0, 0, 0);  //desenha o mapa
    for(i=0;i<jogadores;i++){
        if(dados[i][0] > 0){
            sprintf(end, "resources/bon%c.png", persEsc[i]);//acessando a folha de sprites dependendo da escolha de personagem do jogador
            quadrado = al_load_bitmap(end);
            al_convert_mask_to_alpha(quadrado,al_map_rgb(255,0,255));//Deixando o fundo da imagem, que contem a sprite, transparente 
            al_draw_scaled_bitmap(quadrado, (dados[i][3]-48) * frameWidth[pers-49],  (dados[i][2]-48) * frameHeight[pers-49], frameWidth[pers-49], frameHeight[pers-49], ((dados[i][0]) * 16), ((dados[i][1]) * 16),21,19, 0);//desenha o boneco sem ele parecer uma menina super poderosa(há controle de pixel desenhado na tela)
        }
    }
    setAudio("sounds/whenyouwere.ogg");//começa a melhor musica possivel
    while (!sair){//entra no loop do jogo
        if(recvMsgFromServer(dados,DONT_WAIT)!=NO_MESSAGE){
        	desenhar();//função que desenha na tela
		}
        for(i = 0; i < jogadores; i++){
            if(dados[i][0] < 0){
                contador++;
            }
        }
        if(dados[id][5]==0){//Se o personagem estiver sem vidas, a tela de derrota será desenhada na tela dele e permanecerá por 5 segundos
			fprintf(stderr, "%i\n", contador);
			if(contador >= jogadores - 1 && dados[id][0] <= 0){
			    fadein(telaDerrota, 1);
			    al_rest(5);
			    sair = 1;
			}
			contador = 0;
            continue;
        }
        if(contador >= jogadores - 1 && dados[id][0] > 0){//Se o personagem for o último em campo, a tela de vitória será desenhada para ele
            fadein(telaVitoria, 1);
            al_rest(5);
            sair = 1;
        }
        contador = 0;
        while (!al_is_event_queue_empty(fila_eventos)){//se  acontecer algo
            ALLEGRO_EVENT evento;   //declara variavel evento
            al_wait_for_event(fila_eventos, &evento);//esse evento fica na fila
            if(evento.type == ALLEGRO_EVENT_TIMER){
                tempo++;
                if(tempo == 60){
                    ttest++;
                    tempo = 0;
                    if(ttest == tmpmusic[musat%5]){
                        ttest = 0;
                        musat++;
                        setAudio(endmusic[musat%5]);
                    }
                }
            }
            else if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
            	if (evento.keyboard.keycode == ALLEGRO_KEY_W){ //agora ele checa se tem colisao, para cima
					al_flush_event_queue(fila_eventos);
                    tecl='w';
                    dados[id][2]='1';
                    dados[id][3]=curFrame + 48;
                    dados[id][4]=tecl;
                    sendMsgToServer(dados[id],6);//enviando mensagem para o servidor, para ele "espalhar" para os outros clientes
				}
                else if (evento.keyboard.keycode == ALLEGRO_KEY_A){//para a esquerda
					al_flush_event_queue(fila_eventos);
                    tecl='a';
                    dados[id][2]='2';
                    dados[id][3]=curFrame + 48;
                    dados[id][4]=tecl;
                    sendMsgToServer(dados[id],6);//enviando mensagem para o servidor, para ele "espalhar" para os outros clientes
				}
				else if (evento.keyboard.keycode == ALLEGRO_KEY_S){//para baixo
					al_flush_event_queue(fila_eventos);
                	tecl='s';
                    dados[id][2]='0';
                    dados[id][3]=curFrame + 48;
                    dados[id][4]=tecl;
                    sendMsgToServer(dados[id],6);//enviando mensagem para o servidor, para ele "espalhar" para os outros clientes
				}
                else if (evento.keyboard.keycode == ALLEGRO_KEY_D){//para a direita
					al_flush_event_queue(fila_eventos);
                    tecl='d';
                    dados[id][2]='3';
                    dados[id][3]=curFrame + 48;
                    dados[id][4]=tecl;
                    sendMsgToServer(dados[id],6);//enviando mensagem para o servidor, para ele "espalhar" para os outros clientes
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_P){//tecla que possibilita o soco, esse "if" checa a tecla pressionada anteriormente para saber a posição em que a sprite do soco será desenhada
					al_flush_event_queue(fila_eventos);
                    tecl='p';
					dados[id][3] = '3';
                    dados[id][4]=tecl;
		    		dados[id][3] = '0';
		    		sendMsgToServer(dados[id],6);
                }
            }
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){  //se não tiver evento, sai
                sair = true;
            }
            if(al_is_event_queue_empty(fila_eventos)) {
                if(tecl == 's' || tecl == 'w' || tecl == 'a' || tecl == 'd'){//se 'w', 'a', 's' ou 'd' foi teclado, vai haver animação
                    for(auxiliar = 0; auxiliar < 1; auxiliar++){
                        if(frameCount++ >= frameDelay){
                            if(curFrame++ >= maxFrame){
                                curFrame = 0;
                            }
                            frameCount = 0;                                                                             
                            dados[id][3]=curFrame + 48;
                        }
                    }
                    tecl = '0'; // evita que entre no loop dnv
                }
            }
        }
    }
}
void destroy(){//Função que encerra o programa, é chamada quando "sair" é clicado no menu inicial ou quando uma partida é encerrada
    al_destroy_audio_stream(musica);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela); 
}

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
 
const int LARGURA_TELA = 960;
const int ALTURA_TELA = 703;
 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *imagem = NULL;
ALLEGRO_BITMAP *fundo = NULL;

void fadeout(int velocidade);
void fadein(ALLEGRO_BITMAP *imagem, int velocidade);
void setAudio(char k[]);
bool inicializar();
 
int main(void)
{
    bool sair = false;
 
    if (!inicializar())
    {
        return -1;
    }
 
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);

    fadein(fundo, 1);
    al_rest(3.0);
    fadeout(1);

    imagem = al_load_bitmap("resources/aa.png");
    fadein(imagem, 1);

 		setAudio("sounds/soundtest2.ogg");
 		
    while (!sair)
    {
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            if (evento.type == ALLEGRO_EVENT_KEY_UP)
            {
                if (evento.keyboard.keycode == ALLEGRO_KEY_W)
                {
                    fprintf(stderr, "CIMA\n");
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_A)
                {
                    fprintf(stderr, "ESQUERDA\n");
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_S)
                {
                    fprintf(stderr, "BAIXO\n");
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_D)
                {
                    fprintf(stderr, "DIREITA\n");
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }
        }
    }
 
    al_destroy_audio_stream(musica);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
 
    return 0;
}
 
void fadeout(int velocidade)
{
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(janela), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(janela));
 
    if (velocidade <= 0)
    {
        velocidade = 1;
    }
    else if (velocidade > 15)
    {
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
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(imagem, al_map_rgba(alfa, alfa, alfa, alfa), 0, 0, 0);
        al_flip_display();
        al_rest(0.005); // Não é necessário caso haja controle de FPS
    }
}

bool inicializar()
{

	al_init_image_addon();

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
 
    if (!al_install_audio())
    {
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        return false;
    }
 
    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        return false;
    }
 
    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        return false;
    }
 
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar teclado.\n");
        return false;
    }
 
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar a janela.\n");
        return false;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }

    musica = al_load_audio_stream("sounds/soundtest.ogg", 4, 1024);
    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(janela);
        return false;
    }

 	al_set_window_title(janela, "IP GAME");

    fundo = al_load_bitmap("resources/cin.jpeg");
 
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
 
    return true;
}

void setAudio(char k[]){
	al_set_audio_stream_playing(musica, false);
	musica = al_load_audio_stream(k, 4, 1024);
 	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
 	al_set_audio_stream_playing(musica, true);
}
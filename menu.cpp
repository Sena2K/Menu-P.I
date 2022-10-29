#include <iostream>
#include <string>
#include <cstring>
#include <windows.h> 
#include <tchar.h>  
#include <stdio.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


int jogar();
int menu();
int largura = 960;
int altura = 540;

ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* hello_honey;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_TIMER* fps;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_SAMPLE* trilha = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_trilha = NULL;
ALLEGRO_DISPLAY* janela = NULL;

bool tocar_trilha = false;

int main() {

	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR ", "ERROR: 404", "Não foi possivel carregar a allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);

	trilha = al_load_sample("trilha.wav");

	inst_trilha = al_create_sample_instance(trilha);

	al_attach_sample_instance_to_mixer(inst_trilha, al_get_default_mixer());

	ventana = al_create_display(largura, altura);
	hello_honey = al_load_font("arial.ttf", 20, NULL);


	int largura_W = GetSystemMetrics(SM_CXSCREEN);
	int altura_W = GetSystemMetrics(SM_CYSCREEN);

	al_set_sample_instance_playmode(inst_trilha, ALLEGRO_PLAYMODE_LOOP);

	al_get_sample_instance_gain(inst_trilha);

	al_play_sample_instance(inst_trilha);

	al_set_window_title(ventana, "Jogo");
	al_set_window_position(ventana, largura_W / 2 - largura / 2, altura_W / 2 - altura / 2);


	//eventos timer
	segundoTimer = al_create_timer(1.0);
	fps = al_create_timer(1.0 / 30);

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(fps);
	al_start_timer(segundoTimer);

	menu();


	return 0;
}

int jogar()
{

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_filled_circle(200, 200, 100, al_map_rgb(255, 255, 255));
		al_flip_display();
	}
	return 1;
}
int menu() {
	int segundos = 0;
	int x = -1, y = -1;
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR azar = al_map_rgb(255, 50, 65);

	ALLEGRO_BITMAP* menu_null = al_load_bitmap("telestia1.jpg");
	ALLEGRO_BITMAP* menu_jugar = al_load_bitmap("telestiaj.jpg");
	ALLEGRO_BITMAP* menu_salir = al_load_bitmap("telestias.jpg");
	//menu

	int botoes[] = { 0 };

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);

		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			if (Evento.timer.source == segundoTimer) {
				segundos++;
			}

		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (botoes[0] == 0)
			al_draw_bitmap(menu_null, 0, 0, 0);
		else if (botoes[0] == 1)
			al_draw_bitmap(menu_jugar, 0, 0, 0);
		else
			al_draw_bitmap(menu_salir, 0, 0, 0);

		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			x = Evento.mouse.x;
			y = Evento.mouse.y;

			if (x >= 407 && x <= 550 && y >= 333 && y <= 362) {
				botoes[0] = 1;
				if (Evento.mouse.button & 1)
					jogar();
			}
			else {
				if (x >= 424 && x <= 528 && y >= 387 && y <= 409) {
					botoes[0] = 2;
					if (Evento.mouse.button & 1)
						return 1;
				}
				else {
					botoes[0] = 0;
				}

			}


		}

		al_flip_display();
	}
}
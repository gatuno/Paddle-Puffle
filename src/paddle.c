/*
 * paddle.c
 * This file is part of Paddle Puffle
 *
 * Copyright (C) 2011 - Félix Arreola Rodríguez
 *
 * Paddle Puffle is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Paddle Puffle is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paddle Puffle; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

/* ----------------
 * LEGAL NOTICE
 * ----------------
 *
 * This game is NOT related to Club Penguin in any way. Also,
 * this game is not intended to infringe copyrights, the graphics and
 * sounds used are Copyright of Disney.
 *
 * The new SDL code is written by Gatuno, and is released under
 * the term of the GNU General Public License.
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "draw-text.h"

#define FPS (1000/24)

/* Enumerar las imágenes */
enum {
	IMG_TITLE,
	
	IMG_TITLE_OPENING,
	
	IMG_BACKGROUND_NORMAL,
	IMG_BACKGROUND_NEW_0,
	IMG_BACKGROUND_NEW_1,
	IMG_BACKGROUND_FAIL_0,
	IMG_BACKGROUND_FAIL_1,
	
	IMG_CLOSE_BUTTON_UP,
	IMG_CLOSE_BUTTON_OVER,
	IMG_CLOSE_BUTTON_DOWN,
	
	IMG_BUTTON_UI_UP,
	IMG_BUTTON_UI_OVER,
	IMG_BUTTON_UI_DOWN,
	
	IMG_PADDLE_1,
	IMG_PADDLE_2,
	IMG_PADDLE_3,
	IMG_PADDLE_4,
	
	IMG_BLUE_NORMAL_1,
	IMG_BLUE_FALL_1,
	IMG_BLUE_FALL_2,
	IMG_BLUE_FALL_3,
	IMG_BLUE_BOUNCE_1,
	IMG_BLUE_BOUNCE_2,
	IMG_BLUE_BOUNCE_3,
	IMG_BLUE_BOUNCE_4,
	
	IMG_PINK_NORMAL_1,
	IMG_PINK_FALL_1,
	IMG_PINK_FALL_2,
	IMG_PINK_FALL_3,
	IMG_PINK_BOUNCE_1,
	IMG_PINK_BOUNCE_2,
	IMG_PINK_BOUNCE_3,
	IMG_PINK_BOUNCE_4,
	
	IMG_BLACK_NORMAL_1,
	IMG_BLACK_FALL_1,
	IMG_BLACK_FALL_2,
	IMG_BLACK_FALL_3,
	IMG_BLACK_BOUNCE_1,
	IMG_BLACK_BOUNCE_2,
	IMG_BLACK_BOUNCE_3,
	IMG_BLACK_BOUNCE_4,
	
	IMG_GREEN_NORMAL_1,
	IMG_GREEN_FALL_1,
	IMG_GREEN_FALL_2,
	IMG_GREEN_FALL_3,
	IMG_GREEN_BOUNCE_1,
	IMG_GREEN_BOUNCE_2,
	IMG_GREEN_BOUNCE_3,
	IMG_GREEN_BOUNCE_4,
	
	IMG_PURPLE_NORMAL_1,
	IMG_PURPLE_FALL_1,
	IMG_PURPLE_FALL_2,
	IMG_PURPLE_FALL_3,
	IMG_PURPLE_BOUNCE_1,
	IMG_PURPLE_BOUNCE_2,
	IMG_PURPLE_BOUNCE_3,
	IMG_PURPLE_BOUNCE_4,
	
	IMG_RED_NORMAL_1,
	IMG_RED_FALL_1,
	IMG_RED_FALL_2,
	IMG_RED_FALL_3,
	IMG_RED_BOUNCE_1,
	IMG_RED_BOUNCE_2,
	IMG_RED_BOUNCE_3,
	IMG_RED_BOUNCE_4,
	
	IMG_YELLOW_NORMAL_1,
	IMG_YELLOW_FALL_1,
	IMG_YELLOW_FALL_2,
	IMG_YELLOW_FALL_3,
	IMG_YELLOW_BOUNCE_1,
	IMG_YELLOW_BOUNCE_2,
	IMG_YELLOW_BOUNCE_3,
	IMG_YELLOW_BOUNCE_4,
	
	IMG_WHITE_NORMAL_1,
	IMG_WHITE_FALL_1,
	IMG_WHITE_FALL_2,
	IMG_WHITE_FALL_3,
	IMG_WHITE_BOUNCE_1,
	IMG_WHITE_BOUNCE_2,
	IMG_WHITE_BOUNCE_3,
	IMG_WHITE_BOUNCE_4,
	
	IMG_ORANGE_NORMAL_1,
	IMG_ORANGE_FALL_1,
	IMG_ORANGE_FALL_2,
	IMG_ORANGE_FALL_3,
	IMG_ORANGE_BOUNCE_1,
	IMG_ORANGE_BOUNCE_2,
	IMG_ORANGE_BOUNCE_3,
	IMG_ORANGE_BOUNCE_4,
	
	IMG_BROWN_NORMAL_1,
	IMG_BROWN_FALL_1,
	IMG_BROWN_FALL_2,
	IMG_BROWN_FALL_3,
	IMG_BROWN_BOUNCE_1,
	IMG_BROWN_BOUNCE_2,
	IMG_BROWN_BOUNCE_3,
	IMG_BROWN_BOUNCE_4,
	
	NUM_IMAGES
};

/* Los nombres de archivos */

const char *images_names[NUM_IMAGES] = {
	GAMEDATA_DIR "images/title.png",
	
	GAMEDATA_DIR "images/title-opening.png",
	
	GAMEDATA_DIR "images/normal.png",
	GAMEDATA_DIR "images/new-0.png",
	GAMEDATA_DIR "images/new-1.png",
	GAMEDATA_DIR "images/fail-0.png",
	GAMEDATA_DIR "images/fail-1.png",
	
	GAMEDATA_DIR "images/boton-close-up.png",
	GAMEDATA_DIR "images/boton-close-over.png",
	GAMEDATA_DIR "images/boton-close-down.png",
	
	GAMEDATA_DIR "images/boton-ui-up.png",
	GAMEDATA_DIR "images/boton-ui-over.png",
	GAMEDATA_DIR "images/boton-ui-down.png",
	
	GAMEDATA_DIR "images/paddle-1.png",
	GAMEDATA_DIR "images/paddle-2.png",
	GAMEDATA_DIR "images/paddle-3.png",
	GAMEDATA_DIR "images/paddle-4.png",
	
	GAMEDATA_DIR "images/puffle-blue-1.png",
	GAMEDATA_DIR "images/puffle-blue-2.png",
	GAMEDATA_DIR "images/puffle-blue-3.png",
	GAMEDATA_DIR "images/puffle-blue-4.png",
	GAMEDATA_DIR "images/puffle-blue-5.png",
	GAMEDATA_DIR "images/puffle-blue-6.png",
	GAMEDATA_DIR "images/puffle-blue-7.png",
	GAMEDATA_DIR "images/puffle-blue-8.png",
	
	GAMEDATA_DIR "images/puffle-pink-1.png",
	GAMEDATA_DIR "images/puffle-pink-2.png",
	GAMEDATA_DIR "images/puffle-pink-3.png",
	GAMEDATA_DIR "images/puffle-pink-4.png",
	GAMEDATA_DIR "images/puffle-pink-5.png",
	GAMEDATA_DIR "images/puffle-pink-6.png",
	GAMEDATA_DIR "images/puffle-pink-7.png",
	GAMEDATA_DIR "images/puffle-pink-8.png",
	
	GAMEDATA_DIR "images/puffle-black-1.png",
	GAMEDATA_DIR "images/puffle-black-2.png",
	GAMEDATA_DIR "images/puffle-black-3.png",
	GAMEDATA_DIR "images/puffle-black-4.png",
	GAMEDATA_DIR "images/puffle-black-5.png",
	GAMEDATA_DIR "images/puffle-black-6.png",
	GAMEDATA_DIR "images/puffle-black-7.png",
	GAMEDATA_DIR "images/puffle-black-8.png",
	
	GAMEDATA_DIR "images/puffle-green-1.png",
	GAMEDATA_DIR "images/puffle-green-2.png",
	GAMEDATA_DIR "images/puffle-green-3.png",
	GAMEDATA_DIR "images/puffle-green-4.png",
	GAMEDATA_DIR "images/puffle-green-5.png",
	GAMEDATA_DIR "images/puffle-green-6.png",
	GAMEDATA_DIR "images/puffle-green-7.png",
	GAMEDATA_DIR "images/puffle-green-8.png",
	
	GAMEDATA_DIR "images/puffle-purple-1.png",
	GAMEDATA_DIR "images/puffle-purple-2.png",
	GAMEDATA_DIR "images/puffle-purple-3.png",
	GAMEDATA_DIR "images/puffle-purple-4.png",
	GAMEDATA_DIR "images/puffle-purple-5.png",
	GAMEDATA_DIR "images/puffle-purple-6.png",
	GAMEDATA_DIR "images/puffle-purple-7.png",
	GAMEDATA_DIR "images/puffle-purple-8.png",
	
	GAMEDATA_DIR "images/puffle-red-1.png",
	GAMEDATA_DIR "images/puffle-red-2.png",
	GAMEDATA_DIR "images/puffle-red-3.png",
	GAMEDATA_DIR "images/puffle-red-4.png",
	GAMEDATA_DIR "images/puffle-red-5.png",
	GAMEDATA_DIR "images/puffle-red-6.png",
	GAMEDATA_DIR "images/puffle-red-7.png",
	GAMEDATA_DIR "images/puffle-red-8.png",
	
	GAMEDATA_DIR "images/puffle-yellow-1.png",
	GAMEDATA_DIR "images/puffle-yellow-2.png",
	GAMEDATA_DIR "images/puffle-yellow-3.png",
	GAMEDATA_DIR "images/puffle-yellow-4.png",
	GAMEDATA_DIR "images/puffle-yellow-5.png",
	GAMEDATA_DIR "images/puffle-yellow-6.png",
	GAMEDATA_DIR "images/puffle-yellow-7.png",
	GAMEDATA_DIR "images/puffle-yellow-8.png",
	
	GAMEDATA_DIR "images/puffle-white-1.png",
	GAMEDATA_DIR "images/puffle-white-2.png",
	GAMEDATA_DIR "images/puffle-white-3.png",
	GAMEDATA_DIR "images/puffle-white-4.png",
	GAMEDATA_DIR "images/puffle-white-5.png",
	GAMEDATA_DIR "images/puffle-white-6.png",
	GAMEDATA_DIR "images/puffle-white-7.png",
	GAMEDATA_DIR "images/puffle-white-8.png",
	
	GAMEDATA_DIR "images/puffle-orange-1.png",
	GAMEDATA_DIR "images/puffle-orange-2.png",
	GAMEDATA_DIR "images/puffle-orange-3.png",
	GAMEDATA_DIR "images/puffle-orange-4.png",
	GAMEDATA_DIR "images/puffle-orange-5.png",
	GAMEDATA_DIR "images/puffle-orange-6.png",
	GAMEDATA_DIR "images/puffle-orange-7.png",
	GAMEDATA_DIR "images/puffle-orange-8.png",
	
	GAMEDATA_DIR "images/puffle-brown-1.png",
	GAMEDATA_DIR "images/puffle-brown-2.png",
	GAMEDATA_DIR "images/puffle-brown-3.png",
	GAMEDATA_DIR "images/puffle-brown-4.png",
	GAMEDATA_DIR "images/puffle-brown-5.png",
	GAMEDATA_DIR "images/puffle-brown-6.png",
	GAMEDATA_DIR "images/puffle-brown-7.png",
	GAMEDATA_DIR "images/puffle-brown-8.png"
};

enum {
	SND_SQUEAK1,
	SND_SQUEAK2,
	SND_SQUEAK3,
	SND_OLDBOING,
	SND_OVER_TO_DOWN1,
	SND_OVER_TO_DOWN2,
	NUM_SOUNDS
};

const char *sound_names[NUM_SOUNDS] = {
	GAMEDATA_DIR "sounds/squeak1.wav",
	GAMEDATA_DIR "sounds/squeak2.wav",
	GAMEDATA_DIR "sounds/squeak3.wav",
	GAMEDATA_DIR "sounds/oldboing.wav",
	GAMEDATA_DIR "sounds/overtodown1.wav",
	GAMEDATA_DIR "sounds/overtodown2.wav",
};

#define MUS_CARNIE GAMEDATA_DIR "music/carnie.ogg"

/* Entrada 0 significa normal, 1 nuevo, 2 perdido */
enum {
	BACKGROUND_NORMAL = 0,
	BACKGROUND_NEW,
	BACKGROUND_FAIL
};

/* Autómata para el fondo */
static int background_frames[15][3] = {
	{0, 1, 8},
	{2, 1, 8},
	{3, 1, 8},
	{4, 1, 8},
	{5, 1, 8},
	{6, 1, 8},
	{7, 1, 8},
	{0, 1, 8},
	{9, 1, 8},
	{10, 1, 8},
	{11, 1, 8},
	{12, 1, 8},
	{13, 1, 8},
	{14, 1, 8}
};

static int background_outputs[15] = {
	IMG_BACKGROUND_NORMAL,
	IMG_BACKGROUND_NEW_0,
	IMG_BACKGROUND_NEW_0,
	IMG_BACKGROUND_NEW_0,
	IMG_BACKGROUND_NEW_0,
	IMG_BACKGROUND_NEW_1,
	IMG_BACKGROUND_NEW_1,
	IMG_BACKGROUND_NEW_1,
	IMG_BACKGROUND_FAIL_0,
	IMG_BACKGROUND_FAIL_0,
	IMG_BACKGROUND_FAIL_0,
	IMG_BACKGROUND_FAIL_0,
	IMG_BACKGROUND_FAIL_1,
	IMG_BACKGROUND_FAIL_1,
	IMG_BACKGROUND_FAIL_1
};

/* Autómata para un puffle */
enum {
	PUFFLE_NORMAL = 0,
	PUFFLE_FALL,
	PUFFLE_BOUNCE,
	NUM_PUFFLE_MODS
};

static int puffle_frames [17][NUM_PUFFLE_MODS] = {
	{0, 1, 8},
	{2, 1, 8},
	{3, 2, 8},
	{4, 3, 8},
	{5, 4, 8},
	{6, 5, 8},
	{7, 6, 8},
	{4, 7, 8},
	{9, 8, 8},
	{10, 9, 9},
	{11, 10, 10},
	{12, 11, 11},
	{13, 12, 12},
	{14, 13, 13},
	{15, 14, 14},
	{16, 15, 15},
	{0, 16, 16}
};

static int puffle_outputs [17] = {
	IMG_BLUE_NORMAL_1,
	IMG_BLUE_FALL_1,
	IMG_BLUE_FALL_1,
	IMG_BLUE_FALL_1,
	IMG_BLUE_FALL_2,
	IMG_BLUE_FALL_2,
	IMG_BLUE_FALL_3,
	IMG_BLUE_FALL_3,
	IMG_BLUE_BOUNCE_1,
	IMG_BLUE_BOUNCE_1,
	IMG_BLUE_BOUNCE_1,
	IMG_BLUE_BOUNCE_2,
	IMG_BLUE_BOUNCE_2,
	IMG_BLUE_BOUNCE_3,
	IMG_BLUE_BOUNCE_3,
	IMG_BLUE_BOUNCE_4,
	IMG_BLUE_BOUNCE_4
};

/* Autómata para el paddle */
enum {
	PADDLE_NORMAL = 0,
	PADDLE_BOUNCE,
	NUM_PADDLE_MODS
};

static int paddle_frames [5][NUM_PADDLE_MODS] = {
	{0, 1},
	{2, 1},
	{3, 2},
	{4, 3},
	{0, 4}
};

static int paddle_outputs [5] = {
	IMG_PADDLE_1,
	IMG_PADDLE_2,
	IMG_PADDLE_2,
	IMG_PADDLE_3,
	IMG_PADDLE_4
};

/* Para verificar los botones */
enum {
	BUTTON_NONE = 0,
	BUTTON_CLOSE,
	BUTTON_UI_PLAY
};

/* Codigos de salida */
enum {
	GAME_NONE = 0, /* No usado */
	GAME_CONTINUE,
	GAME_QUIT
};

enum {
	TEXT_HELP,
	TEXT_WARINING,
	TEXT_TICKETS,
	TEXT_SCORE_BOUNCE_POINTS,
	TEXT_SCORE_MOST_BOUNCED,
	TEXT_SCORE_PUFFLES_JUGGLED,
	TEXT_SCORE_TOTAL_TICKETS,
	TEXT_UI_PLAY,
	TEXT_UI_DONE,
	NUM_TEXTS
};

/* Estas cadenas son traducibles */
const char * text_strings[NUM_TEXTS] = {
	"- USE YOUR MOUSE TO BOUNCE THE \n  PUFFLES AND KEEP THEM IN THE AIR \n\n- EVERY TIME YOU BOUNCE A PUFFLE \n  YOU INCREASE YOUR SCORE \n\n- JUGGLE MORE AT ONCE TO WIN MORE \n\n- THE LONGER YOU CAN KEEP BOUNCING \n  THE SAME PUFFLE THE MORE YOU WIN",
	"WARNING! \n\nFIXME: CHANGE THIS \nTEXT.",
	"TICKETS",
	"BOUNCE POINTS:",
	"MOST BOUNCED PUFFLE:",
	"PUFFLES JUGGLED:",
	"TOTAL TICKETS:",
	"PLAY",
	"DONE"
};

static int text_info [NUM_TEXTS] = { /* Tamaño, por el momento */
	14,
	10,
	16,
	14,
	14,
	14,
	26,
	20,
	20
};

/* La estructura principal de un puffle */
typedef struct _Puffle {
	struct _Puffle *next;
	struct _Puffle *prev;
	int x;
	int y;
	float x_virtual;
	float y_virtual;
	int pop_num;
	int color;
	int frame;
} Puffle;

/* Prototipos de función */
int game_intro (void);
int game_loop (void);
void setup (void);
SDL_Surface * set_video_mode(unsigned flags);
void nuevo_puffle (void);
void eliminar_puffle (Puffle *p);
int map_button_in_game (int x, int y);
int map_button_in_opening (int x, int y);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * images[NUM_IMAGES];
SDL_Surface * texts[NUM_TEXTS];
Puffle *first_puffle = NULL;
Puffle *last_puffle = NULL;
int background_frame = 0;
int use_sound;
SDL_Surface *grey_screen;

Mix_Chunk * sounds[NUM_SOUNDS];
Mix_Music * mus_carnie;

TTF_Font *ttf20_outline, *ttf20_normal;
TTF_Font *ttf16_outline, *ttf16_normal;

int main (int argc, char *argv[]) {
	setup ();
	do {
		if (game_intro () == GAME_QUIT) break;
		if (game_loop () == GAME_QUIT) break;
		/* TODO: Pantalla de "gracias por jugar */
	} while (1 == 0);
	
	SDL_Quit ();
	return EXIT_SUCCESS;
}

int game_intro (void) {
	int done;
	SDL_Event event;
	SDLKey key;
	SDL_Rect dest_rect;
	Uint32 last_time, now_time;
	int last_button = 0, button_frame, button_pressed;
	int handposx, handposy;
	
	/* Iniciar la música */
	if (use_sound) {
		Mix_PlayMusic (mus_carnie, -1);
	}
	
	SDL_BlitSurface (images [IMG_BACKGROUND_NORMAL], NULL, screen, NULL);
	
	SDL_BlitSurface (grey_screen, NULL, screen, NULL);
	
	dest_rect.x = 107;
	dest_rect.y = 17;
	dest_rect.h = images [IMG_TITLE_OPENING]->h;
	dest_rect.w = images [IMG_TITLE_OPENING]->w;
	
	SDL_BlitSurface (images [IMG_TITLE_OPENING], NULL, screen, &dest_rect);
	
	dest_rect.x = 164;
	dest_rect.y = 161;
	dest_rect.h = texts [TEXT_HELP]->h;
	dest_rect.w = texts [TEXT_HELP]->w;
	
	SDL_BlitSurface (texts [TEXT_HELP], NULL, screen, &dest_rect);
	
	SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	
	do {
		last_time = SDL_GetTicks ();
		
		while (SDL_PollEvent(&event) > 0) {
			/* fprintf (stdout, "Evento: %i\n", event.type);*/
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Tengo un Mouse Down */
					if (event.button.button == SDL_BUTTON_RIGHT) done = GAME_CONTINUE;
					if (event.button.button != SDL_BUTTON_LEFT) break;
					if (last_button == BUTTON_NONE) last_button = map_button_in_opening (event.button.x, event.button.y);
					break;
				case SDL_MOUSEBUTTONUP:
					/* Tengo un mouse Up */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					if (last_button != BUTTON_NONE) {
						if (map_button_in_opening (event.button.x, event.button.y) == last_button) {
							/* Mouse down y mouse up sobre el mismo botón */
							/* Utilizar switch para muchos botones */
							if (last_button == BUTTON_CLOSE) {
								done = GAME_QUIT;
							} else {
								done = GAME_CONTINUE;
							}
							button_pressed = last_button;
						}
						last_button = BUTTON_NONE;
					}
					break;
			}
		}
		
		SDL_GetMouseState (&handposx, &handposy);
		/* Dibujar el botón de cierre */
		/* Posición original X:734, Y:22
		 * Centro +- 14.05 */
		dest_rect.x = 720; dest_rect.y = 8;
		if (button_pressed == BUTTON_CLOSE || (last_button == BUTTON_CLOSE && map_button_in_opening (handposx, handposy) == BUTTON_CLOSE)) {
			/* Está presionado el botón del mouse, y está sobre el botón */
			button_frame = IMG_CLOSE_BUTTON_DOWN;
			button_pressed = BUTTON_NONE;
		} else if (last_button == BUTTON_CLOSE) {
			button_frame = IMG_CLOSE_BUTTON_OVER;
		} else if (last_button == BUTTON_NONE && map_button_in_opening (handposx, handposy) == BUTTON_CLOSE) {
			button_frame = IMG_CLOSE_BUTTON_OVER;
		} else {
			button_frame = IMG_CLOSE_BUTTON_UP;
		}
		dest_rect.h = images [button_frame]->h; dest_rect.w = images [button_frame]->w;
		SDL_BlitSurface (images [IMG_BACKGROUND_NORMAL], &dest_rect, screen, &dest_rect);
		SDL_BlitSurface (grey_screen, &dest_rect, screen, &dest_rect);
		SDL_BlitSurface (images [button_frame], NULL, screen, &dest_rect);
		
		/* Dibujar el botón de "PLAY" */
		/* Posición original: X:299.45, Y:360.8 */
		dest_rect.x = 299; dest_rect.y = 359;
		if (button_pressed == BUTTON_UI_PLAY || (last_button == BUTTON_UI_PLAY && map_button_in_opening (handposx, handposy) == BUTTON_UI_PLAY)) {
			button_frame = IMG_BUTTON_UI_DOWN;
			button_pressed = BUTTON_NONE;
		} else if (last_button == BUTTON_UI_PLAY) {
			button_frame = IMG_BUTTON_UI_OVER;
		} else if (last_button == BUTTON_NONE && map_button_in_opening (handposx, handposy) == BUTTON_UI_PLAY) {
			button_frame = IMG_BUTTON_UI_OVER;
		} else {
			button_frame = IMG_BUTTON_UI_UP;
		}
		dest_rect.h = images [button_frame]->h; dest_rect.w = images [button_frame]->w;
		SDL_FillRect (screen, &dest_rect,
		              SDL_MapRGB (screen->format, 0xf0, 0xc4, 0x3f));
		SDL_BlitSurface (images [button_frame], NULL, screen, &dest_rect);
		dest_rect.x = 381 - (texts[TEXT_UI_PLAY]->w / 2); dest_rect.y = 373;
		dest_rect.h = texts [TEXT_UI_PLAY]->h; dest_rect.w = texts[TEXT_UI_PLAY]->w;
		SDL_BlitSurface (texts[TEXT_UI_PLAY], NULL, screen, &dest_rect);
		
		SDL_Flip (screen);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
	} while (!done);
	
	return done;
}

int game_loop (void) {
	int done = 0;
	SDL_Event event;
	SDLKey key;
	Uint32 last_time, now_time;
	SDL_Rect puf_pos;
	int sonido;
	int last_button = 0, button_frame, button_pressed;
	
	int handposx2, handposx1, handposx, handposy2, handposy1, handposy; /* Para calcular los desplazamientos del mouse */
	int fuerzax, fuerzay; /* Calculos de fuerza al golpear el puffle */
	float poder;
	float speed = 10, balance = 4;
	int wind = 1, wind_countdown = 240; /* Para evitar puffles estancados verticalmente */
	int n_puffles = 1, most_puffles = 1, dropped_puffles = 0; /* Llevar la cantidad de puffles */
	int count = 0, goal = 20, default_goal = 20; /* Para control de la generación de próximos puffles */
	int bounces = 0, role = 0; /* Bounces, golpes totales. Role, el mayor número de golpes */
	int paddle_x, paddle_y, paddle_frame = 0;
	int tickets = 0;
	Puffle *thispuffle;
	SDL_Surface *text_num;
	char text_buffer[6];
	
	nuevo_puffle ();
	background_frame = 0;
	SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_GetMouseState (&handposx, &handposy);
	
	paddle_x = handposx2 = handposx1 = handposx;
	paddle_y = handposy2 = handposy1 = handposy;
	
	do {
		last_time = SDL_GetTicks ();
		
		SDL_BlitSurface (images [background_outputs[background_frame]], NULL, screen, NULL);
		
		while (SDL_PollEvent(&event) > 0) {
			/* fprintf (stdout, "Evento: %i\n", event.type);*/
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Tengo un Mouse Down */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					if (last_button == BUTTON_NONE) last_button = map_button_in_game (event.button.x, event.button.y);
					break;
				case SDL_MOUSEBUTTONUP:
					/* Tengo un mouse Up */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					if (last_button != BUTTON_NONE) {
						if (map_button_in_game (event.button.x, event.button.y) == last_button) {
							/* Mouse down y mouse up sobre el mismo botón */
							/* Utilizar switch para muchos botones */
							if (last_button == BUTTON_CLOSE) {
								done = GAME_QUIT;
							}
							button_pressed = last_button;
						}
						last_button = BUTTON_NONE;
					}
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_z) {
						fprintf (stderr, "Sending new background\n");
						background_frame = background_frames [background_frame][BACKGROUND_NEW];
					} else if (key == SDLK_x) {
						fprintf (stderr, "Sending fail background\n");
						background_frame = background_frames [background_frame][BACKGROUND_FAIL];
					}
					
					if (key == SDLK_q) {
						fprintf (stderr, "Bounces = 60, activando wind\n");
						bounces = 60; /* Debug key */
					} else if (key == SDLK_w) {
						fprintf (stderr, "Bounces = 0, desactivando wind\n");
						bounces = 0;
					}
					/* TODO: Toggle Fullscreen */
					break;
				/*case SDL_VIDEOEXPOSE:
					refresh = 1;
					break;*/
			}
		}
		
		if (count >= goal) {
			count = 0;
			n_puffles++;
	
			if (n_puffles > 4) {
				goal = default_goal;
		
				if (default_goal > 5) {
					default_goal--;
				}
		
				if (dropped_puffles > 49) {
					default_goal += 20;
					dropped_puffles = 0;
				}
			} else if (n_puffles >= most_puffles) {
				goal = n_puffles * 20;
			} else {
				goal = n_puffles * 10;
			}
	
			if (most_puffles < n_puffles) {
				most_puffles = n_puffles;
			}
	
			nuevo_puffle ();
		}
		
		handposy2 = handposy1;
		handposy1 = handposy;
		
		handposx2 = handposx1;
		handposx1 = handposx;
		
		SDL_GetMouseState (&handposx, &handposy);
		
		fuerzay = handposy2 - handposy;
		
		if (fuerzay > 0) poder = fuerzay / 6;
		else poder = 0;
		
		fuerzax = handposx2 - handposx;
		
		thispuffle = first_puffle;
		do {
			if (thispuffle->y > 530) {
				/* Este puffle está perdido */
				n_puffles--;
				dropped_puffles++;
				
				if (n_puffles > 4) {
					goal = default_goal;
				} else if (n_puffles >= most_puffles) {
					goal = n_puffles * 20;
				} else {
					goal = n_puffles * 10;
				}
				
				if (thispuffle->prev != NULL) {
					thispuffle = thispuffle->prev;
					eliminar_puffle (thispuffle->next);
				} else {
					eliminar_puffle (thispuffle);
					thispuffle = first_puffle;
				}
			}
			if (thispuffle != NULL) thispuffle = thispuffle->next;
		} while (thispuffle != NULL);
		
		if (first_puffle == NULL) {
			done = GAME_CONTINUE;
			
			tickets = bounces + most_puffles * role;
			/* TODO: Fin del juego, todos los puffles perdidos */
			break;
		}
		
		thispuffle = first_puffle;
		do {
			thispuffle->x = thispuffle->x + thispuffle->x_virtual;
			thispuffle->y = thispuffle->y + thispuffle->y_virtual;
			
			if (thispuffle->x >= 720 && thispuffle->x_virtual >= 0) thispuffle->x_virtual *= -1;
			else if (thispuffle->x <= 40 && thispuffle->x_virtual < 0) thispuffle->x_virtual *= -1;
			
			if (thispuffle->y_virtual < -10) thispuffle->y_virtual *= 0.9;
			else thispuffle->y_virtual += 1; /* 1 de "Gravity" */
			
			if (thispuffle->x_virtual > 30 || thispuffle->x_virtual < -30) {
				thispuffle->x_virtual *= 0.95;
			}
			
			/* Si tiene un score (alias bounces) mayor a 50, aplicar un poco de viento */
			if (bounces > 50) { /* Bounces ajustado a 25, valor original 50 */
				if (wind) thispuffle->x_virtual += 0.1;
				else thispuffle->x_virtual -= 0.1;
				
				if (wind_countdown > 0) wind_countdown--;
			}
			
			if (wind_countdown == 0) {
				if (wind) wind = 0;
				else wind = 1;
				wind_countdown = 240;
			}		
			
			if (thispuffle->y > -99 && thispuffle->y_virtual >= 0) {
				if ((thispuffle->x > handposx - 70 && thispuffle->x < handposx + 70) && ((thispuffle->y + 30 > handposy && thispuffle->y + 30 < handposy + 100) || (thispuffle->y > handposy && thispuffle->y < handposy2))) {
					/* Bounce the puffle */
					sonido = SND_SQUEAK1 + (int) (2.0 * rand () / (RAND_MAX + 1.0));
					
					if (fuerzax > 300 || fuerzax < -300 || poder > 30) {
						sonido = SND_SQUEAK3;
					}
					
					thispuffle->x_virtual = (thispuffle->x - (handposx + fuerzax)) / balance;
					thispuffle->y_virtual = -1 * (speed + poder);
					
					bounces++; count++;
					
					if (speed < 40) speed += 0.2;
					else if (balance > 2) balance -= 0.2;
					
					/* TODO: Role and poptxt */
					thispuffle->pop_num++;
					
					if (thispuffle->pop_num > role) role = thispuffle->pop_num;
					
					thispuffle->frame = puffle_frames [thispuffle->frame][PUFFLE_BOUNCE];
					paddle_frame = paddle_frames [paddle_frame][PADDLE_BOUNCE];
					
					if (use_sound) Mix_PlayChannel (-1, sounds[sonido], 0);
					
					tickets = bounces + most_puffles * role;
				} else if ((thispuffle->y + 30 > handposy && thispuffle->y + 30 < handposy + 100) && ((thispuffle->x > handposx && thispuffle->x < handposx2) || (thispuffle->x < handposx && thispuffle->x > handposx2))) {
					/* Bounce the puffle */
					sonido = SND_SQUEAK1 + (int) (2.0 * rand () / (RAND_MAX + 1.0));
					
					if (fuerzax > 300 || fuerzax < -300 || poder > 30) {
						sonido = SND_SQUEAK3;
					}
					
					thispuffle->x_virtual = (thispuffle->x - (handposx + fuerzax)) / balance;
					thispuffle->y_virtual = -1 * (speed + poder);
					
					bounces++; count++;
					
					if (speed < 40) speed += 0.2;
					else if (balance > 2) balance -= 0.2;
					
					/* TODO: Role and poptxt */
					thispuffle->pop_num++;
					
					if (thispuffle->pop_num > role) role = thispuffle->pop_num;
					
					thispuffle->frame = puffle_frames [thispuffle->frame][PUFFLE_BOUNCE];
					paddle_frame = paddle_frames [paddle_frame][PADDLE_BOUNCE];
					
					if (use_sound) Mix_PlayChannel (-1, sounds[sonido], 0);
					
					tickets = bounces + most_puffles * role;
				}
			}
			
			if (thispuffle->y_virtual > 10) {
				thispuffle->frame = puffle_frames [thispuffle->frame][PUFFLE_FALL];
			}
			
			thispuffle->frame = puffle_frames [thispuffle->frame][PUFFLE_NORMAL];
			if (thispuffle != NULL) thispuffle = thispuffle->next;
		} while (thispuffle != NULL);
		
		/* Dibujar la cantidad de tickets */
		sprintf (text_buffer, "%d", tickets);
		text_num = draw_text_with_shadow (ttf16_normal, ttf16_outline, text_buffer);
		puf_pos.x = 607 + ((136 - text_num->w) / 2);
		puf_pos.y = 60 + ((26 - text_num->h) / 2);
		puf_pos.w = text_num->w; puf_pos.h = text_num->h;
		
		SDL_BlitSurface (text_num, NULL, screen, &puf_pos);
		SDL_FreeSurface (text_num);
		
		paddle_x = handposx;
		paddle_y = handposy;
		
		paddle_frame = paddle_frames[paddle_frame][PADDLE_NORMAL];
		
		/* Blit el paddle */
		puf_pos.x = paddle_x - 58; /* Constante temporal */
		puf_pos.y = paddle_y - 70; /* Constante temporal */
		puf_pos.h = images [paddle_outputs [paddle_frame]]->h;
		puf_pos.w = images [paddle_outputs [paddle_frame]]->w;
		
		SDL_BlitSurface (images [paddle_outputs [paddle_frame]], NULL, screen, &puf_pos);
		
		/* Dibujar el botón de cierre */
		/* Posición original X:734, Y:22
		 * Centro +- 14.05 */
		puf_pos.x = 720; puf_pos.y = 8;
		if (button_pressed == BUTTON_CLOSE || (last_button == BUTTON_CLOSE && map_button_in_game (handposx, handposy) == BUTTON_CLOSE)) {
			/* Está presionado el botón del mouse, y está sobre el botón */
			button_frame = IMG_CLOSE_BUTTON_DOWN;
			button_pressed = BUTTON_NONE;
		} else if (last_button == BUTTON_CLOSE) {
			button_frame = IMG_CLOSE_BUTTON_OVER;
		} else if (last_button == BUTTON_NONE && map_button_in_game (handposx, handposy) == BUTTON_CLOSE) {
			button_frame = IMG_CLOSE_BUTTON_OVER;
		} else {
			button_frame = IMG_CLOSE_BUTTON_UP;
		}
		SDL_BlitSurface (images[button_frame], NULL, screen, &puf_pos);
		
		thispuffle = first_puffle;
		do {
			if (thispuffle->y > -100) {
				/* Blit this puffle */
				puf_pos.x = thispuffle->x - 48; /* Constante temporal */
				puf_pos.y = thispuffle->y - 60; /* Constante temporal */
				puf_pos.w = images [puffle_outputs [thispuffle->frame]]->w;
				puf_pos.h = images [puffle_outputs [thispuffle->frame]]->h;
				SDL_BlitSurface (images [puffle_outputs [thispuffle->frame] + (thispuffle->color * 8)], NULL, screen, &puf_pos);
			}
			
			if (thispuffle != NULL) thispuffle = thispuffle->next;
		} while (thispuffle != NULL);
		
		/* Avanzar el escenario */
		background_frame = background_frames [background_frame][BACKGROUND_NORMAL];
		
		SDL_Flip (screen);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
	} while (!done);
	
	return done;
}
/* Set video mode: */
/* Mattias Engdegard <f91-men@nada.kth.se> */
SDL_Surface * set_video_mode (unsigned flags) {
	/* Prefer 16bpp, but also prefer native modes to emulated 16bpp. */

	int depth;

	depth = SDL_VideoModeOK (760, 480, 16, flags);
	return depth ? SDL_SetVideoMode (760, 480, depth, flags) : NULL;
}

void setup (void) {
	SDL_Surface * image;
	TTF_Font *ttf10, *ttf14, *ttf16, *ttf26, *temp_font;
	SDL_Color color;
	int g;
	
	/* Inicializar el Video SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"Error: No se pudo inicializar el sistema de video\n"
			"El error devuelto por SDL es:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	/* Crear la pantalla de dibujado */
	screen = set_video_mode (0);
	
	if (screen == NULL) {
		fprintf (stderr,
			"Error: I could not set up video for 760x480 mode.\n"
			"The Simple DirectMedia error that occured was:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	use_sound = 1;
	if (SDL_InitSubSystem (SDL_INIT_AUDIO) < 0) {
		fprintf (stdout,
			"Advertencia: No se pudo inicializar el sistema de audio\n"
			"Continuando...\n");
		use_sound = 0;
	}
	
	if (use_sound) {
		/* Inicializar el sonido */
		if (Mix_OpenAudio (22050, AUDIO_S16, 2, 4096) < 0) {
			fprintf (stdout,
				"Advertencia: <Poner un mensaje de error descriptivo>\n");
			use_sound = 0;
		}
	}
	
	for (g = 0; g < NUM_IMAGES; g++) {
		image = IMG_Load (images_names[g]);
		
		if (image == NULL) {
			fprintf (stderr,
				"Error al cargar el archivo:\n"
				"%s\n"
				"El error devuelto por SDL es:\n"
				"%s\n", images_names[g], SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		/*images[g] = SDL_DisplayFormat (image);
		
		if (images[g] == NULL) {
			fprintf (stderr,
				"\nError: Fallo al convertir imagen\n"
				"El error devuelto por SDL es:\n"
				"%s\n\n", SDL_GetError ());
			exit (EXIT_FAILURE);
		}
		
		SDL_FreeSurface (image); */
		images[g] = image;
		/* TODO: Mostrar la carga de porcentaje */
	}
	
	/* Pre-Dibujar la pantalla gris */
	grey_screen = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA, 760, 480, 32, 0, 0, 0, 0);
	SDL_FillRect (grey_screen, NULL,
	              SDL_MapRGB (grey_screen->format, 0, 0, 0)); /* Negro */
	SDL_SetAlpha (grey_screen, SDL_SRCALPHA, 128); /* Alpha al 50 % */
	
	if (use_sound) {
		for (g = 0; g < NUM_SOUNDS; g++) {
			sounds[g] = Mix_LoadWAV (sound_names [g]);
			
			if (sounds[g] == NULL) {
				fprintf (stderr,
					"Error: No se pudo cargar un archivo de sonido:\n"
					"%s\n"
					"El error devuelto por SDL es:\n"
					"%s\n", sound_names [g], SDL_GetError ());
				SDL_Quit ();
				exit (1);
			}
			Mix_VolumeChunk (sounds[g], MIX_MAX_VOLUME / 2);
		}
		
		/* Cargar la música */
		
		mus_carnie = Mix_LoadMUS (MUS_CARNIE);
		
		if (mus_carnie == NULL) {
			fprintf (stderr,
				"Error: No se pudo cargar un archivo de sonido:\n"
				"%s\n"
				"El error devuelto por SDL es:\n"
				"%s\n", MUS_CARNIE, SDL_GetError ());
			SDL_Quit ();
			exit (1);
		}
		
	}
	
	if (TTF_Init () < 0) {
		fprintf (stderr,
			"Error: No se pudo inicializar la librería SDL_ttf\n"
			"%s\n", TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	/* Tipografias 10, 14, 16, 20, 26 */
	ttf10 = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 10);
	ttf14 = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 14);
	ttf16 = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 16);
	ttf20 = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 20);
	ttf26 = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 26);
	
	TTF_SetFontStyle (ttf10, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf14, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf16, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf20, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf26, TTF_STYLE_ITALIC);
	
	if (!ttf10 || !ttf14 || !ttf16 || !ttf20 || !ttf26) {
		fprintf (stderr,
			"Error: No se pudo cargar la tipografía 'CCFaceFront'\n"
			"El error devuelto por SDL es:\n"
			"%s\n", TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	TTF_SetFontStyle (ttf10, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf14, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf16, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf26, TTF_STYLE_ITALIC);
	
	color.r = color.g = color.b = 0; /* Negro */
	
	for (g = 0; g < NUM_TEXTS; g++) {
		switch (text_info [g]) {
			case 10: temp_font = ttf10; break;
			case 14: temp_font = ttf14; break;
			case 16: temp_font = ttf16; break;
			case 20: temp_font = ttf20; break;
			case 26: temp_font = ttf26; break;
			default: temp_font = ttf16;
		}
		
		texts[g] = draw_text (temp_font, text_strings[g], &color);
	}
	
	TTF_CloseFont (ttf10);
	TTF_CloseFont (ttf14);
	TTF_CloseFont (ttf16);
	TTF_CloseFont (ttf20);
	TTF_CloseFont (ttf26);
	
	/* Copiar la palabra "Tickets" en el background */
	rect.x = 607 + ((135 - texts[TEXT_TICKETS]->w) / 2); rect.y = 38;
	rect.w = texts[TEXT_TICKETS]->w; rect.h = texts[TEXT_TICKETS]->h;
	for (g = IMG_BACKGROUND_NORMAL; g <= IMG_BACKGROUND_FAIL_1; g++) {
		SDL_BlitSurface (texts[TEXT_TICKETS], NULL, images[g], &rect);
	}
	
	/* Dejar abiertas las otras tipografias */
	ttf16_normal = ttf16;
	ttf20_normal = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 20);
	ttf20_outline = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 20);
	ttf16_outline = TTF_OpenFont (GAMEDATA_DIR "ccfacefront.ttf", 16);
	
	if (!ttf20_normal || !ttf20_outline || !ttf16_outline) {
		fprintf (stderr,
			"Error: No se pudo cargar la tipografía 'CCFaceFront'\n"
			"El error devuelto por SDL es:\n"
			"%s\n", TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	TTF_SetFontStyle (ttf16_outline, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf20_outline, TTF_STYLE_ITALIC);
	TTF_SetFontStyle (ttf20_normal, TTF_STYLE_ITALIC);
	
	TTF_SetFontOutline (ttf16_outline, OUTLINE_TEXT);
	TTF_SetFontOutline (ttf20_outline, OUTLINE_TEXT);
	
	/* Generador de números aleatorios */
	srand (SDL_GetTicks ());
}

void nuevo_puffle (void) {
	Puffle *new;
	static color = 0;
	new = (Puffle *) malloc (sizeof (Puffle));
	
	/* Inicializar el Puffle */
	new->color = color++;
	if (color >= 10) color = 0;
	new->frame = 0;
	new->x_virtual = new->y_virtual = new->pop_num = 0;
	
	new->y = -40;
	new->x = 20 + (int) (720.0 * rand () / (RAND_MAX + 1.0));
	
	/* Ahora sus campos para lista doble ligada */
	new->next = NULL;
	new->prev = last_puffle;
	
	if (last_puffle == NULL) {
		first_puffle = last_puffle = new;
	} else {
		last_puffle->next = new;
		last_puffle = new;
	}
	
	/* Background, dame un "more" */
	background_frame = background_frames [background_frame][BACKGROUND_NEW];
}

void eliminar_puffle (Puffle *p) {
	if (p == NULL) return;
	
	if (p->prev == NULL) { /* El primero de la lista */
		first_puffle = p->next;
	} else {
		p->prev->next = p->next;
	}
	
	if (p->next == NULL) {
		last_puffle = p->prev;
	} else {
		p->next->prev = p->prev;
	}
	
	free (p);
	
	/* Background, dame un "miss" */
	background_frame = background_frames [background_frame][BACKGROUND_FAIL];
}

inline int map_button_in_game (int x, int y) {
	/* Checar por el botón de cierre */
	if (x >= 720 && x < 748 && y >= 8 && y < 36) return BUTTON_CLOSE;
	return BUTTON_NONE;
}

inline int map_button_in_opening (int x, int y) {
	/* Checar por el botón de cierre */
	if (x >= 720 && x < 748 && y >= 8 && y < 36) return BUTTON_CLOSE;
	if (x >= 299 && x < 462 && y >= 360 && y < 407) return BUTTON_UI_PLAY;
	return BUTTON_NONE;
}

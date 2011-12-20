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

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#define FPS (1000/24)

/* Enumerar las imágenes */
enum {
	IMG_TITLE,
	
	IMG_BACKGROUND_NORMAL,
	
	IMG_BACKGROUND_NEW_0,
	IMG_BACKGROUND_NEW_1,
	
	IMG_BACKGROUND_FAIL_0,
	IMG_BACKGROUND_FAIL_1,
	
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
	
	NUM_IMAGES
};

/* Los nombres de archivos */

const char *images_names[NUM_IMAGES] = {
	DATA_PREFIX "images/title.png",
	
	DATA_PREFIX "images/normal.png",
	
	DATA_PREFIX "images/new-0.png",
	DATA_PREFIX "images/new-1.png",
	
	DATA_PREFIX "images/fail-0.png",
	DATA_PREFIX "images/fail-1.png",
	
	DATA_PREFIX "images/paddle-1.png",
	DATA_PREFIX "images/paddle-2.png",
	DATA_PREFIX "images/paddle-3.png",
	DATA_PREFIX "images/paddle-4.png",
	
	DATA_PREFIX "images/puffle-blue-1.png",
	DATA_PREFIX "images/puffle-blue-2.png",
	DATA_PREFIX "images/puffle-blue-3.png",
	DATA_PREFIX "images/puffle-blue-4.png",
	DATA_PREFIX "images/puffle-blue-5.png",
	DATA_PREFIX "images/puffle-blue-6.png",
	DATA_PREFIX "images/puffle-blue-7.png",
	DATA_PREFIX "images/puffle-blue-8.png"
};

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

/* La estructura principal de un puffle */
typedef struct _Puffle{
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
void setup (void);
SDL_Surface * set_video_mode(unsigned flags);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * images[NUM_IMAGES];
Puffle *first_puffle = NULL;
Puffle *last_puffle = NULL;
int num_rects;
int background_frame = 0;

/* Temp */
int puffle_frame = 0;
float puffle_y_virtual = 0;
int puffle_y_real = -40;

int main (int argc, char *argv[]) {
	int done;
	SDL_Event event;
	SDLKey key;
	Uint32 last_time, now_time;
	SDL_Rect puf;
	
	setup ();
	
	done = 0;
	
	do {
		last_time = SDL_GetTicks ();
		
		SDL_BlitSurface (images [background_outputs[background_frame]], NULL, screen, NULL);
		
		puf.x = 200 - (images [puffle_outputs [puffle_frame]]->w / 2);
		puf.y = puffle_y_real - images [puffle_outputs [puffle_frame]]->h;
		puf.w = images [puffle_outputs [puffle_frame]]->w; puf.h = images [puffle_outputs [puffle_frame]]->h;
		SDL_BlitSurface (images [puffle_outputs [puffle_frame]], NULL, screen, &puf);
		SDL_Flip (screen);
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Tengo un Mouse Down */
					
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_z) {
						background_frame = background_frames [background_frame][BACKGROUND_NEW];
					} else if (key == SDLK_x) {
						background_frame = background_frames [background_frame][BACKGROUND_FAIL];
					}
					
					if (key == SDLK_q) {
						/* Bounce the puffle */
						puffle_y_virtual = -20;
						puffle_frame = puffle_frames [puffle_frame][PUFFLE_BOUNCE];
					}
					break;
				/*case SDL_VIDEOEXPOSE:
					refresh = 1;
					break;*/
			}
		}
		
		background_frame = background_frames [background_frame][BACKGROUND_NORMAL];
		
		puffle_y_real = puffle_y_real + puffle_y_virtual;
		
		if (puffle_y_virtual < -10) puffle_y_virtual *= 0.9;
		else puffle_y_virtual += 1;
		
		if (puffle_y_virtual > 6) {
			puffle_frame = puffle_frames [puffle_frame][PUFFLE_FALL];
		} /*else if (puffle_y_virtual < -6) {
			puffle_frame = puffle_frames [puffle_frame];
		}*/
		
		puffle_frame = puffle_frames [puffle_frame][PUFFLE_NORMAL];
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
		SDL_Flip (screen);
	} while (!done);
	return 0;
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
	int g;
	
	/* Inicializar el Video SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"\nError: No se pudo inicializar el sistema de video\n"
			"El error devuelto por SDL es:\n"
			"%s\n\n", SDL_GetError());
		exit (1);
	}
	
	/* Crear la pantalla de dibujado */
	screen = set_video_mode (0);
	
	if (screen == NULL) {
		fprintf (stderr,
			"\nError: I could not set up video for 760x480 mode.\n"
			"The Simple DirectMedia error that occured was:\n"
			"%s\n\n", SDL_GetError());
		exit (1);
	}
	
	for (g = 0; g < NUM_IMAGES; g++) {
		image = IMG_Load (images_names[g]);
		
		if (image == NULL) {
			fprintf (stderr,
				"\nError al cargar el archivo:\n"
				"%s\n"
				"El error devuelto por SDL es:\n"
				"%s\n\n", images_names[g], SDL_GetError());
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
	
	/* TODO: Inicializar la TTF */
	
	/* Generador de números aleatorios */
	srand (SDL_GetTicks ());
}

void nuevo_puffle (void) {
	Puffle *new;
	new = (Puffle *) malloc (sizeof (Puffle));
	
	/* Inicializar el Puffle */
	new->color = 0; /* TODO: Cambiar el color */
	new->x_virtual = new->y_virtual = new->pop_num = 0;
	
	new->y = -40;
	new->x = 300; /* TODO: Debe ser random */
	
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
	if (p == NULL) return NULL;
	
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


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

#define MAX_RECTS 512

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
	
	IMG_BLUE_1,
	IMG_BLUE_2,
	IMG_BLUE_3,
	IMG_BLUE_4,
	
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
	DATA_PREFIX "images/puffle-blue-4.png"
};

/* Prototipos de función */
void setup (void);
SDL_Surface * set_video_mode(unsigned flags);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * images[NUM_IMAGES];
SDL_Rect rects[MAX_RECTS];
int num_rects;

int main (int argc, char *argv[]) {
	int done;
	SDL_Event event;
	Uint32 last_time, now_time;
	setup ();
	
	done = 0;
	SDL_BlitSurface (images [IMG_BACKGROUND_NORMAL], NULL, screen, NULL);
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Tengo un Mouse Down */
					
					break;
				/*case SDL_VIDEOEXPOSE:
					refresh = 1;
					break;*/
			}
		}
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
		/* Actualizar las zonas de la pantalla */
		/*fprintf (stdout, "Print: Num_Rects: %i\n", num_rects);
		fprintf (stdout, "Rect[0], x=%i, y=%i, w=%i, h=%i\n", rects[0].x, rects[0].y, rects[0].w, rects[0].h); */
		SDL_UpdateRects (screen, num_rects, rects);
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
			"\nError: I could not set up video for 640x480 mode.\n"
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
		
		images[g] = SDL_DisplayFormat (image);
		
		if (images[g] == NULL) {
			fprintf (stderr,
				"\nError: Fallo al convertir imagen\n"
				"El error devuelto por SDL es:\n"
				"%s\n\n", SDL_GetError ());
			exit (EXIT_FAILURE);
		}
		
		SDL_FreeSurface (image);
		/* TODO: Mostrar la carga de porcentaje */
	}
	
	/* TODO: Inicializar la TTF */
	
	/* Generador de números aleatorios */
	srand (SDL_GetTicks ());
}


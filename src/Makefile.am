# Automake file for Paddle Puffle

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = paddle-puffle
paddle_puffle_SOURCES = paddle.c

paddle_puffle_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" $(AM_CPPFLAGS)
paddle_puffle_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(AM_CFLAGS)
paddle_puffle_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS)

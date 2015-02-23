# Automake file for Paddle Puffle

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = paddle-puffle
paddle_puffle_SOURCES = paddle.c draw-text.c gettext.h

if MINGW32
paddle_puffle_SOURCES += strsep.c
endif

EXTRA_DIST = draw-text.h paddle.rc

if MINGW32
paddle_ico.o: paddle.rc ../data/paddle.ico
	$(WINDRES) $(srcdir)/paddle.rc -O coff -o paddle_ico.o

mingw_ldadd = paddle_ico.o

else # NOT MINGW
mingw_ldadd =
endif

paddle_puffle_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
paddle_puffle_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_CFLAGS) $(AM_CFLAGS)
paddle_puffle_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS) $(mingw_ldadd)
LDADD = $(LIBINTL)


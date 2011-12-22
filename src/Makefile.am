# Automake file for Paddle Puffle

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = paddle-puffle
paddle_puffle_SOURCES = paddle.c

paddle_puffle_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" $(AM_CPPFLAGS)
paddle_puffle_CFLAGS = $(PADDLE_CFLAGS) $(AM_CFLAGS)
paddle_puffle_LDADD = $(PADDLE_LIBS)

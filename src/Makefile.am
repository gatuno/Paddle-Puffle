# Automake file for Paddle Puffle

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = paddle-puffle
paddle_puffle_SOURCES = paddle.c draw-text.c draw-text.h gettext.h path.c path.h

if MINGW32
paddle_puffle_SOURCES += strsep.c
endif

EXTRA_DIST = paddle.rc

if MINGW32
paddle_ico.o: paddle.rc ../data/paddle.ico
	$(WINDRES) $(srcdir)/paddle.rc -O coff -o paddle_ico.o

mingw_ldadd = paddle_ico.o

else # NOT MINGW
mingw_ldadd =
endif

paddle_puffle_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
paddle_puffle_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_CFLAGS) $(AM_CFLAGS)
if MACOSX
# En MAC OS X, hay que ligar/compilar contra los frameworks
paddle_puffle_LDADD = $(SDL_LIBS)
else
paddle_puffle_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS) $(mingw_ldadd)
endif
LDADD = $(LIBINTL)

#------------------ Packaging rules for Mac OSX ------------------------

bundle_root = $(top_builddir)/etc/macfiles
bundle_name = $(bundle_root)/PaddlePuffle.app
# Special target to copy all needed game files to PaddlePuffle.app/Contents/Resources.
# For Mac OS X bundle.
.PHONY: bundle
bundle:
	-rm -rf $(bundle_root)
	mkdir -p $(bundle_name)/Contents/MacOS
	mkdir -p $(bundle_name)/Contents/Resources/data/
	echo "APPL????" > $(bundle_name)/Contents/PkgInfo
	cp $(top_builddir)/etc/Info.plist $(bundle_name)/Contents/
	cp $(top_builddir)/etc/paddle.icns $(bundle_name)/Contents/Resources/
	mkdir -p $(bundle_name)/Contents/Resources/data/images
	cp $(top_builddir)/data/images/* $(bundle_name)/Contents/Resources/data/images
	mkdir -p $(bundle_name)/Contents/Resources/data/music
	cp $(top_builddir)/data/music/* $(bundle_name)/Contents/Resources/data/music
	mkdir -p $(bundle_name)/Contents/Resources/data/sounds
	cp $(top_builddir)/data/sounds/* $(bundle_name)/Contents/Resources/data/sounds
	cp $(top_builddir)/data/*.ttf $(bundle_name)/Contents/Resources/data
	for cat in $(ALL_LINGUAS); do \
	  dir=$(bundle_name)/Contents/Resources/locale/$$cat/LC_MESSAGES; \
	  mkdir -p $$dir; \
	  echo "installing $$cat as $$dir/paddle-puffle.mo"; \
	  cp $(top_builddir)/po/$$cat.gmo $$dir/paddle-puffle.mo; \
	done

# Special target to copy the binary to PaddlePuffle.app/Contents/MacOS.
.PHONY: bundle-fw
bundle-fw: bundle
	cp paddle-puffle $(bundle_name)/Contents/MacOS/paddle-puffle
	mkdir  $(bundle_name)/Contents/Frameworks
	for i in SDL SDL_mixer SDL_image SDL_ttf ; do \
	  cp -a /Library/Frameworks/$${i}.framework $(bundle_name)/Contents/Frameworks/; \
	done
	strip $(bundle_name)/Contents/MacOS/paddle-puffle

# Special target to make a disk image of the bundled app
.PHONY: bundle-dmg
bundle-dmg: bundle-fw
	ln -s /Applications $(bundle_root)/Applications
	hdiutil create  -ov -srcfolder $(bundle_root) -volname PaddlePuffle -imagekey zlib-level=6 $(top_builddir)/etc/paddlepuffle.dmg


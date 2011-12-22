AC_INIT([Paddle Puffle], [0.1], [], [paddle-puffle])

AC_REVISION([Revision 1])

AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_SRCDIR([src/paddle.c])

# For debian systems, /usr as default
AC_PREFIX_DEFAULT([/usr])

# We need Gcc
AC_PROG_CC

# and automake
AM_INIT_AUTOMAKE([-Wall -Werror])

AM_PROG_CC_C_O

# Check for pkg-config
PKG_PROG_PKG_CONFIG

SDL_VERSION=1.2.14
SDL_IMAGE_VERSION=1.2.10

AC_MSG_CHECKING([if you have SDL installed on your system])
PKG_CHECK_EXISTS([sdl >= $SDL_VERSION], [AC_MSG_RESULT([yes])], [AC_MSG_FAILURE([SDL not found in your system])])

AC_MSG_CHECKING([if you have SDL_image installed on your system])
PKG_CHECK_EXISTS([SDL_image >= $SDL_IMAGE_VERSION], [AC_MSG_RESULT([yes])], [AC_MSG_FAILURE([SDL_image not found in your system])])

PKG_CHECK_MODULES([PADDLE],
	[sdl >= $SDL_VERSION
	SDL_image >= $SDL_IMAGE_VERSION])

AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_HOST

AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 data/Makefile
])

AC_OUTPUT

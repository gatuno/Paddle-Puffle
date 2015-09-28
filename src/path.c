/*
 * path.c
 * This file is part of Paddle Puffle
 *
 * Copyright (C) 2015 - Félix Arreola Rodríguez
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
 * along with Paddle Puffle. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef MACOSX
// for search paths
#include "NSSystemDirectories.h"
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#endif

char *systemdata_path;
char *l10n_path;
char *userdata_path;

//#ifdef __MINGW32__
//const char *PathSeparator = "\\";      // for path assembly
//#else
//const char *PathSeparator = "/";       // for path assembly
//#endif
//const char *PathSeparators = "/\\";    // for path splits

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

int split_path (const char *path, char * dir_part, char * filename_part) {
	int lslash, lnslash;
	int g, h;
	char *dup;
	
	lslash = -1;
	for (g = strlen (path) - 1; g >= 0; g--) {
		if (path[g] == '/' || path[g] == '\\') {
			lslash = g;
			break;
		}
	}
	
	if (
	#ifdef __MINGW32__
		lslash == 2 && path[1] == ':' && (path[0] >= 'A' && path[0] <= 'Z')
	#else
		lslash == 0 
	#endif
	) {
		return FALSE; // we cannot split the root directory apart
	}

	if (lslash == strlen (path) - 1) {
		// trailing slash
		dup = strdup (path);
		dup[lslash] = 0;
		g = split_path (dup, dir_part, filename_part);
		
		free (dup);
		return g;
	}
	
	if (lslash == -1) {
		return FALSE;
	}
	
	for (g = lslash; g >= 0; g--) {
		if (path[g] != '/' && path[g] != '\\') {
			lnslash = g;
			break;
		}
	}
	
	if (dir_part) {
		strncpy (dir_part, path, lnslash + 1);
		dir_part[lnslash + 1] = 0;
	}
	
	if (filename_part) {
		strcpy (filename_part, &path[lslash + 1]);
	}
	
	return TRUE;
}

void initSystemPaths (const char *argv_0) {
	char *progCallPath;
	int progdirexists;
	char *progdir;
	
#if MACOSX
	progCallPath = strdup (argv_0);
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef cfurlmain = CFBundleCopyExecutableURL(mainBundle);
	CFStringRef cffileStr = CFURLCopyFileSystemPath(cfurlmain, kCFURLPOSIXPathStyle);
	CFIndex cfmax = CFStringGetMaximumSizeOfFileSystemRepresentation(cffileStr);
	char *localbuffer;
	localbuffer = (char *) malloc (sizeof (char) * cfmax);
	if (CFStringGetFileSystemRepresentation(cffileStr, localbuffer, cfmax)) {
    	free (progCallPath);
		progCallPath = localbuffer; // error skips this and defaults to argv[0] which works for most purposes
	}
	CFRelease(cfurlmain);
	CFRelease(cffileStr);
	
	progdir = strdup (progCallPath);
	progdirexists = split_path (progCallPath, progdir, NULL);
	
    // Mac OS X applications are self-contained bundles,
    // i.e., directories like "Enigma.app".  Resources are
    // placed in those bundles under "Enigma.app/Contents/Resources",
    // the main executable would be "Enigma.app/Contents/MacOS/enigma".
    // Here, we get the executable name, clip off the last bit, chdir into it,
    // then chdir to ../Resources. The original SDL implementation chdirs to
    // "../../..", i.e. the directory the bundle is placed in. This breaks
    // the self-containedness.
	systemdata_path = (char *) malloc (sizeof (char) * (strlen (progdir) + 30));
	sprintf (systemdata_path, "%s/../Resources/data/", progdir);
	
	l10n_path = (char *) malloc (sizeof (char) * (strlen (progdir) + 30));
	sprintf (l10n_path, "%s/../Resources/locale", progdir);
	
	/* Liberar las cadenas temporales */
	free (progdir);
	free (progCallPath);
#else
	/* Para Windows, Linux */
	systemdata_path = GAMEDATA_DIR;
	
	l10n_path = LOCALEDIR;
#endif
}


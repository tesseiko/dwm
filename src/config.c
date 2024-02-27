/*
 ==============================================================================
 
 config.c
 Created: 14 Feb 2024 10:26:43pm
 Author: Manos Lefakis
 
 ==============================================================================
 */

#include <stdio.h>
#include <sys/types.h>
#include "Xlib.h"
#include <X11/Xft/Xft.h>
#include "util.h"
#include "drw.h"
#include "Monitor.h"
#include "Client.h"
// #include "dwm.h"
#include "x11manager.h"
#include <X11/Xatom.h>
#include <X11/Xproto.h>
#include "dwmAPI.h"
#include "vanitygaps.h"
#include <X11/XF86keysym.h>

#include "config.h"

/* tagging */
const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

// ResourcePref resources[19] = {
// 		{ "color0",		STRING,	&normbordercolor },
// 		{ "color8",		STRING,	&selbordercolor },
// 		{ "color0",		STRING,	&normbgcolor },
// 		{ "color4",		STRING,	&normfgcolor },
// 		{ "color0",		STRING,	&selfgcolor },
// 		{ "color4",		STRING,	&selbgcolor },
// 		{ "borderpx",		INTEGER, &borderpx },
// 		{ "snap",		INTEGER, &snap },
// 		{ "showbar",		INTEGER, &showbar },
// 		{ "topbar",		INTEGER, &topbar },
// 		{ "nmaster",		INTEGER, &nmaster },
// 		{ "resizehints",	INTEGER, &resizehints },
// 		{ "mfact",		FLOAT,	&mfact },
// 		{ "gappih",		INTEGER, &gappih },
// 		{ "gappiv",		INTEGER, &gappiv },
// 		{ "gappoh",		INTEGER, &gappoh },
// 		{ "gappov",		INTEGER, &gappov },
// 		{ "swallowfloating",	INTEGER, &swallowfloating },
// 		{ "smartgaps",		INTEGER, &smartgaps },
// };

const char *fonts[2]          = { "monospace:size=11", "icomoon:pixelsize=14:style=Regular"};

const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "140x33", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spsignal", "-g", "120x50",  "-e", "signal-desktop",NULL };
const char *spcmd3[] = {TERMINAL, "-n", "sptele", "-g", "80x30", "-e", "telegram-desktop", NULL };
const char *spcmd4[] = {TERMINAL, "-n", "spviber", "-g", "120x50", "-e", "viber", NULL };
const char *spcmd5[] = {TERMINAL, "-n", "spcalc", "-g", "40x10", "-e", "bc", "-lq", NULL };
const char *spcmd6[] = {TERMINAL, "-n", "spmess", "-g", "120x50", "-e", "messenger", NULL };
Sp scratchpads[6] = {
/* name          cmd  */
{"spterm",      spcmd1},
{"spsignal",    spcmd2},
{"sptele",      spcmd3},
{"spviber",     spcmd4},
{"spcalc",      spcmd5},
{"spdrop",      spcmd6},
};

const Rule rules[32] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class				instance					title			tags mask	isfloating   issticky   isterminal  noswallow  monitor */
	{ "Gimp",				NULL,						NULL,       	    1 << 8,		0,           0,         0,         0,        -1},
	{ TERMCLASS, 			NULL,						NULL,       	    0,          0,           0,         1,         0,        -1},
	{ NULL,      			NULL,       				"Event Tester",		0,          0,           0,         0,         1,        -1},
    { NULL,                 NULL,	  			        "panel", 	        SYSTRAYTAG,	1,           1,         0,         0,        -1},
    { NULL,		 			NULL,                       "cairo-dock", 		DOCKTAG,    1,           1,         0,         0,        -1},
    { NULL,		 			NULL,                       "Saving", 	        0,          1,           0,         0,         0,        -1},
    { NULL,		 			NULL,                       "Delete Project Items",0,       1,           0,         0,         0,        -1},
    { NULL,		 			NULL,                       "Mia", 	            0,          1,           0,         0,         0,        -1},
    { NULL,		 			NULL,                       "MIA", 	            0,          1,           0,         0,         0,        -1},
	{ NULL,		 			"ncmpcpp",	  				NULL,       	    0,          1,           0,         1,         0,        -1},
	{ NULL,		 			"megasync",	  				NULL,       	    0,          1,           0,         0,         0,        -1},
    { NULL,	     			"brave-browser",			NULL,				1,          0,           0,         1,         0,        -1},
    { "Zathura",			NULL,		  				NULL,				1 << 1,     0,           0,         0,         0,        -1},
    { "Inkscape",           NULL,						NULL,				1 << 3,     0,           0,         0,         0,        -1},
    { "GitAhead",			NULL,		  				NULL,				1 << 3,     0,           0,         0,         0,        -1},
    { "Steam",	 			NULL,						NULL,				1 << 4,     0,           0,         0,         0,        -1},
    { "VirtualBox Manager",	NULL,		  				NULL,				1 << 4,     0,           0,         0,         0,        -1},
    { "trello-nativefier-a9fb22",NULL,		  			NULL,				1 << 4,     0,           0,         0,         0,        -1},
    { NULL, 	 			NULL,						"EVALUATION",		1 << 5,     1,           0,         0,         0,        -1},
	{ NULL,		 			"qjackctl",  				NULL,       	    1 << 7,     0,           0,         0,         0,        -1},
	{ NULL,					"spotify", 		    		NULL,				1 << 7,     0,           0,         0,         0,        -1},
	{ "discord", 			NULL,						NULL,  				1 << 8,     0,           0,         0,         0,        -1},
    { "Slack",	 			NULL,		  				NULL,  				1 << 8,     0,           0,         0,         0,        -1},
	{ "zoom",	 			NULL,						NULL,  				1 << 8,     0,           0,         0,         0,        -1},
	{ NULL,		 			"jitsi meet",				NULL,				1 << 8,     1,           0,         1,         0,        -1},
	{ NULL,	     			NULL,						"pulsemixer",	    0,          1,           0,         1,         0,        -1},
	{ NULL,      			"spterm",    				NULL,       	    SPTAG(0),   1,           0,         1,         0,        -1},
	{ NULL,      			"spsignal",  				NULL,       	    SPTAG(1),	1,           0,         1,         0,        -1},
	{ NULL,      			"sptele",    				NULL,       	    SPTAG(2),   1,           0,         1,         0,        -1},
	{ NULL,      			"spviber",   				NULL,       	    SPTAG(3),   1,           0,         1,         0,        -1},
	{ NULL,      			"spmess",   				NULL,       	    SPTAG(5),   1,           0,         1,         0,        -1},
	{ NULL,      			"spcalc",    				NULL,       	    SPTAG(4),	1,           0,         1,         0,        -1},
};
//
// #include "shiftview.h"

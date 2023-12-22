/* See LICENSE file for copyright and license details. */
#ifndef CONFIG_H
#define CONFIG_H


#include "headers/dwm.h"
/* Constants */
#define TERMINAL "st"
#define DWMMODE "/home/lef/.local/bin/dwmmode/"
#define TERMCLASS "St"
#define BACKRES "xrandr  | grep '*' -B1 | grep -v '*' | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
#define FORWRES "xrandr  | grep '*' -A1 | grep -v '*' | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
#define SELRES "xrandr  | rofi -theme arthur fuzzy -dmenu | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"

/* appearance */
static unsigned int borderpx  = 0;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int cornerrad = 8;
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
//static char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
 char *fonts[]          = { "monospace:size=11", "icomoon:pixelsize=14:style=Regular"};
static char normbgcolor[]           = "#040200";
static char normbordercolor[]       = "#ffb55d";
static char normfgcolor[]           = "#deaf76";
static char selfgcolor[]            = "#ffb55d";
static char selbordercolor[]        = "#00bbff";
static char selbgcolor[]            = "#040200";
 char *colors[][3] = {
   /*               fg           bg           border   */
   [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
   [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
const char *name;
const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "140x33", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spsignal", "-g", "120x50",  "-e", "signal-desktop",NULL };
const char *spcmd3[] = {TERMINAL, "-n", "sptele", "-g", "80x30", "-e", "telegram-desktop", NULL };
const char *spcmd4[] = {TERMINAL, "-n", "spviber", "-g", "120x50", "-e", "viber", NULL };
const char *spcmd5[] = {TERMINAL, "-n", "spcalc", "-g", "40x10", "-e", "bc", "-lq", NULL };
const char *spcmd6[] = {TERMINAL, "-n", "spmess", "-g", "120x50", "-e", "messenger", NULL };

Sp scratchpads[] = {
/* name          cmd  */
{"spterm",      spcmd1},
{"spsignal",    spcmd2},
{"sptele",      spcmd3},
{"spviber",     spcmd4},
{"spcalc",      spcmd5},
{"spdrop",      spcmd6},
};

/* tagging */
const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
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

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
    { "|M|",	centeredmaster },		/* Master in middle, slaves on sides */

 	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

Key keys[] = {
	/* modifier             key				  function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	// { MODKEY|ShiftMask,		XK_Escape,			spawn,		SHCMD("") },
	{ MODKEY,				XK_grave,			togglescratch,	{.ui = 4} },
	{ MODKEY|ShiftMask,		XK_grave,			spawn,		SHCMD("dmenuunicode") },
	TAGKEYS(				XK_1,				0)
	TAGKEYS(				XK_2,				1)
	TAGKEYS(				XK_3,				2)
	TAGKEYS(				XK_4,				3)
	TAGKEYS(				XK_5,				4)
	TAGKEYS(				XK_6,				5)
	TAGKEYS(				XK_7,				6)
	TAGKEYS(				XK_8,				7)
	TAGKEYS(				XK_9,				8)
	{ MODKEY	,			XK_0,				view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,				tag,		{.ui = ~0 } },
	{ MODKEY,				XK_minus,			spawn,		SHCMD("pamixer -d 1; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_minus,			spawn,		SHCMD("pamixer -d 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ControlMask,	XK_minus,			spawn,		SHCMD(BACKRES) },
	{ MODKEY,				XK_equal,			spawn,		SHCMD("pamixer -i 1; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_equal,			spawn,		SHCMD("pamixer -i 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ControlMask,	XK_equal,			spawn,		SHCMD(FORWRES) },
	{ MODKEY,				XK_BackSpace,		spawn,		SHCMD("sysact") },
	{ MODKEY|ShiftMask,		XK_BackSpace,		spawn,		SHCMD("sysact") },

	{ MODKEY,				XK_Tab,				shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Tab,				spawn,		SHCMD("change_mode") },
	{ MODKEY,				XK_q,				spawn,		SHCMD(DWMMODE "q") },
	{ MODKEY|ShiftMask,		XK_q,				killclient,	{0} },
	{ MODKEY,				XK_w,				spawn,		SHCMD(DWMMODE "w") },
	{ MODKEY|ShiftMask,		XK_w,				spawn,		SHCMD("$BROWSER") },
	{ MODKEY|ControlMask,	XK_w,				spawn,		SHCMD(TERMINAL " -e sudo nmtui") },
	{ MODKEY,				XK_e,				spawn,		SHCMD(DWMMODE "e") },
	{ MODKEY|ShiftMask,		XK_e,				spawn,		SHCMD(TERMINAL " -e lf") },
	{ MODKEY|ControlMask,	XK_e,				spawn,		SHCMD(TERMINAL " -e htop") },
	{ MODKEY,				XK_r,				spawn,		SHCMD(DWMMODE "r") },
	{ MODKEY|ShiftMask,		XK_r,				spawn,		SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
	{ MODKEY,				XK_t,				setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,				setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,				XK_y,				setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,				setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,				XK_u,				setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,				setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,				XK_i,				setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,				setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,				XK_o,				incnmaster,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,				incnmaster,	{.i = -1 } },
	{ MODKEY,				XK_p,				spawn,		SHCMD("mpc toggle") },
	{ MODKEY|ShiftMask,		XK_p,				spawn,		SHCMD(TERMINAL " -e pulsemixer") },
	{ MODKEY,				XK_bracketleft,		spawn,		SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn,		SHCMD("mpc seek -60") },
	{ MODKEY,				XK_bracketright,	spawn,		SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,		XK_bracketright,	spawn,		SHCMD("mpc seek +60") },
	{ MODKEY,				XK_backslash,		togglescratch,	{.ui = 2}	 },
	{ MODKEY|ShiftMask,		XK_backslash,		togglescratch,	{.ui = 5}	 },

	{ MODKEY,				XK_a,				togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,				defaultgaps,	{0} },
	{ MODKEY,				XK_s,				togglesticky,	{0} },
	{ MODKEY|ShiftMask,		XK_s,				spawn,		SHCMD("dmenuvimsessions") },
	{ MODKEY,				XK_d,				spawn,          SHCMD("rofirun") },
	{ MODKEY|ShiftMask,		XK_d,				spawn,		SHCMD("dmenu_dragon") },
	{ MODKEY|ControlMask,	XK_d,				spawn,		SHCMD(SELRES) },
	{ MODKEY,				XK_f,				togglefullscr,	{0} },
	{ MODKEY|ShiftMask,		XK_f,				setlayout,	{.v = &layouts[8]} },
	// { MODKEY,				XK_g,				shiftview,	{ .i = -1 } },
	// { MODKEY|ShiftMask,		XK_g,				shifttag,	{ .i = -1 } },
	{ MODKEY,				XK_h,				shiftview,	{ .i = -1} },
	{ MODKEY|ShiftMask,		XK_h,				setmfact,	{.f = -0.05} },
	{ MODKEY|ControlMask,	XK_h,				shifttag,	{ .i = -1 } },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,				XK_l,				shiftview,   { .i = 1 } },
	{ MODKEY|ShiftMask,		XK_l,				setmfact,   {.f = +0.05} },
	{ MODKEY|ControlMask,	XK_l,				shifttag,	{ .i = 1 } },
	// { MODKEY,				XK_semicolon,		shiftview,	{ .i = 1 } },
	// { MODKEY|ShiftMask,		XK_semicolon,		shifttag,	{ .i = 1 } },
	{ MODKEY,				XK_apostrophe,		togglescratch,	{.ui = 1} },
	{ MODKEY|ShiftMask,		XK_apostrophe,		togglescratch,	{.ui = 3} },
	{ MODKEY,				XK_Return,			spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,			togglescratch,	{.ui = 0} },

	{ MODKEY,				XK_z,				incrgaps,	{.i = +3 } },
	// { MODKEY|ShiftMask,		XK_z,				spawn,		SHCMD("zoom") },
	{ MODKEY,				XK_x,				incrgaps,	{.i = -3 } },
	// { MODKEY|ShiftMask,		XK_x,				spawn,		SHCMD("") },
	{ MODKEY,				XK_c,				spawn,		SHCMD("toggle_cam") }, 
	// { MODKEY|ShiftMask,		XK_c,				spawn,		SHCMD(TERMINAL " -e abd -c") },
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,				XK_b,				togglebar,	{0} },
	// { MODKEY|ShiftMask,		XK_b,				spawn,		SHCMD("") },
	// { MODKEY,				XK_n,				spawn,		SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
	// { MODKEY|ShiftMask,		XK_n,				spawn,		SHCMD("dmenuvimsessions") },
	{ MODKEY,				XK_m,				spawn,		SHCMD(TERMINAL " -n ncmpcpp -e ncmpcpp") },
	{ MODKEY|ShiftMask,		XK_m,				spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,				XK_comma,			spawn,		SHCMD("mpc prev") },
	{ MODKEY|ShiftMask,		XK_comma,			spawn,		SHCMD("mpc seek 0%") },
	{ MODKEY,				XK_period,			spawn,		SHCMD("mpc next") },
	// { MODKEY|ShiftMask,		XK_period,			togglescratch,	{.ui = 4} },


	{ MODKEY,				XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,				XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,				XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,				XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,				XK_Insert,	spawn,		SHCMD("xdotool type $(cat ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },

	{ MODKEY,			XK_F1,		spawn,		SHCMD("mictoggle") },
	{ MODKEY,			XK_F2,		spawn,		SHCMD("tutorialvids") },
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
	{ MODKEY,			XK_F4,		spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	/* { MODKEY,			XK_F5,		xrdb,		{.v = NULL } }, */
	{ MODKEY,			XK_F6,		spawn,		SHCMD("torwrap") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("td-toggle") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("mw -Y") },
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam av://v4l2:$(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,		spawn,		SHCMD("remaps & notify-send \\\"⌨️ Keyboard remapping...\\\" \\\"Re-running keyboard defaults for any newly plugged-in keyboards.\\\"") },
	{ 0,				XK_F9,		spawn,		SHCMD("dunstctl close") },
	{ 0,				XK_F10,		spawn,		SHCMD("dunstctl action") },
	{ 0,				XK_F11,		spawn,		SHCMD("dunstctl history-pop") },
	{ 0,				XK_F12,		spawn,		SHCMD("dunstctl close-all") },
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,	XK_space,	togglefloating,	{0} },
	{ MODKEY|ControlMask,	XK_space,	togglealwaysontop,	{0} },

	{ 0,					XK_Print,	spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,	spawn,		SHCMD("maimpick") },
	{ MODKEY,				XK_Print,	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,				XK_Delete,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD(TERMINAL) },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD(TERMINAL " -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD(TERMINAL " -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e vim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         0,              9,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        zoom,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,		    0,	            Button2,	    focusstack,		    {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,		    0,	            Button4,	    focusstack,	    {.i = INC(+1) } },
	{ ClkTagBar,		    0,	            Button5,	    focusstack,	    {.i = INC(-1) } },
	{ ClkTagBar,            0,              8,              toggletag,      {0} },
	{ ClkTagBar,            0,              9,              tag,            {0} },
    { ClkTagBar,            MODKEY,         Button1,        toggletag,      {0} },
    { ClkTagBar,            MODKEY,         Button3,        tag,            {0} },
	{ ClkRootWin,		    0,	            Button2,	    pushstack,	    {0} },
	{ ClkRootWin,		    0,	            Button4,	    focusstack,	    {.i = INC(+1) } },
	{ ClkRootWin,		    0,	            Button5,	    focusstack,	    {.i = INC(-1) } },
	{ ClkRootWin,		    0,	            8,	            pushstack,	    {.i = INC(+1) } },
	{ ClkRootWin,		    0,	            9,	            pushstack,	    {.i = INC(-1) } },
};
#endif /* ifndef DEBUG */


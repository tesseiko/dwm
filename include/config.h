/* See LICENSE file for copyright and license details. */
#ifndef CONFIG_H
#define CONFIG_H

/* Constants */
#define TERMINAL "st"
#define DWMMODE "/home/lef/.local/bin/dwmmode/"
#define TERMCLASS "St"
#define BACKRES "xrandr  | grep '*' -B1 | grep -v '*' | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
#define FORWRES "xrandr  | grep '*' -A1 | grep -v '*' | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
#define SELRES "xrandr  | rofi -theme arthur fuzzy -dmenu | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"


typedef struct {
const char *name;
const void *cmd;
} Sp;
extern Sp scratchpads[6];

/* appearance */
static unsigned int borderpx  = 0;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int cornerrad = 8;
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
//static char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
extern const char *fonts[2];
static char normbgcolor[]           = "#040200";
static char normbordercolor[]       = "#ffb55d";
static char normfgcolor[]           = "#deaf76";
static char selfgcolor[]            = "#ffb55d";
static char selbordercolor[]        = "#00bbff";
static char selbgcolor[]            = "#040200";
extern const char *colors[2][3];

/* tagging */
extern const char *tags[9];

extern const Rule rules[32];

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
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
extern ResourcePref resources[19];


extern const Key keys[172];

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
extern const Button buttons[28];
#endif /* ifndef DEBUG */


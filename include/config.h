/* See LICENSE file for copyright and license details. */
#ifndef CONFIG_H
#define CONFIG_H

/* Constants */
#include "X.h"
#include "dwmAPI.h"
#include "vanitygaps.h"
#include <string>
#define TERMINAL "st"
#define DWMMODE "/home/lef/.local/bin/dwmmode/"
#define TERMCLASS "St"
#define BACKRES "xrandr  | grep '*' -B1 | grep -v '*' | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
#define FORWRES "xrandr  | grep '*' -A1 | grep -v '*' | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
#define SELRES "xrandr  | rofi -theme arthur fuzzy -dmenu | awk '{print $1}' | grep x | xargs xrandr -s &&xrandr | grep '*' | awk '{print $1}' | xargs notify-send || notify-send 'no change'"
/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      &dwmAPI::view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      &dwmAPI::toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      &dwmAPI::tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      &dwmAPI::toggletag,      {.ui = 1 << TAG} },
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


typedef struct {
const char *name;
const void *cmd;
} Sp;

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */

/* Xresources preferences */
enum resource_type {
    STRING = 0,
    INTEGER = 1,
    FLOAT = 2
};

union dst {
    const char *dst_s[8]; 
    const int *dst_i;
    const float *dst_f;
};

typedef struct {
	char *name;
	enum resource_type type;
    dst d;
} ResourcePref;

template<typename RT>
class ResourcePrefNew
{
public:
    ResourcePrefNew(std::string name, RT * holder): name(name), value(holder)
    {
    };
    std::string name;
    RT *value;
};

union Resource
{
    Resource(ResourcePrefNew<char[8]> p): r_c(p) {};
    Resource(ResourcePrefNew<int> p): r_i(p) {};
    Resource(ResourcePrefNew<unsigned int> p): r_u(p) {};
    Resource(ResourcePrefNew<float> p): r_f(p) {};
    ~Resource();
    ResourcePrefNew<char[8]> r_c;
    ResourcePrefNew<int> r_i;
    ResourcePrefNew<unsigned int> r_u;
    ResourcePrefNew<float> r_f;
};

class Configuration
{
public:
    Configuration(dwmAPI& api): api(api) {};

    Resource Resources[19] = {
            Resource(ResourcePrefNew<char[8]>( "color0",		&normbordercolor )),
            Resource(ResourcePrefNew<char[8]>( "color8",		&selbordercolor )),
            Resource(ResourcePrefNew<char[8]>( "color0",		&normbgcolor )),
            Resource(ResourcePrefNew<char[8]>( "color4",		&normfgcolor )),
            Resource(ResourcePrefNew<char[8]>( "color0",		&selfgcolor )),
            Resource(ResourcePrefNew<char[8]>( "color4",		&selbgcolor )),
            Resource(ResourcePrefNew<unsigned int>( "borderpx",		&borderpx )),
            Resource(ResourcePrefNew<unsigned int>( "snap",		&snap )),
            Resource(ResourcePrefNew<int>( "showbar",		&showbar )),
            Resource(ResourcePrefNew<int>( "topbar",		&topbar )),
            Resource(ResourcePrefNew<int>( "nmaster",		&nmaster )),
            Resource(ResourcePrefNew<int>( "resizehints",	&resizehints )),
            Resource(ResourcePrefNew<float>( "mfact",		&mfact )),
            Resource(ResourcePrefNew<unsigned int>( "gappih",		&gappih )),
            Resource(ResourcePrefNew<unsigned int>( "gappiv",		&gappiv )),
            Resource(ResourcePrefNew<unsigned int>( "gappoh",		&gappoh )),
            Resource(ResourcePrefNew<unsigned int>( "gappov",		&gappov )),
            Resource(ResourcePrefNew<int>( "swallowfloating",	&swallowfloating )),
            Resource(ResourcePrefNew<int>( "smartgaps",		&smartgaps )),
    };

    struct Key
    {
        unsigned int mod;
        KeySym keysym;
        void (dwmAPI::*func)(const Arg *);
        const Arg arg;
    } ;

    Key keys[172] = {
        /* modifier             key				  function        argument */
        STACKKEYS(MODKEY,                          &dwmAPI::focus)
        STACKKEYS(MODKEY|ShiftMask,                &dwmAPI::push)
        { MODKEY,				XK_grave,			&dwmAPI::togglescratch,	{.ui = 4} },
        { MODKEY|ShiftMask,		XK_grave,			&dwmAPI::spawn,		SHCMD("dmenuunicode") },
        TAGKEYS(				XK_1,				0)
        TAGKEYS(				XK_2,				1)
        TAGKEYS(				XK_3,				2)
        TAGKEYS(				XK_4,				3)
        TAGKEYS(				XK_5,				4)
        TAGKEYS(				XK_6,				5)
        TAGKEYS(				XK_7,				6)
        TAGKEYS(				XK_8,				7)
        TAGKEYS(				XK_9,				8)
        { MODKEY	,			XK_0,				&dwmAPI::view,		{.ui = ~0 } },
        { MODKEY|ShiftMask,		XK_0,				&dwmAPI::tag,		{.ui = ~0 } },
        { MODKEY,				XK_minus,			&dwmAPI::spawn,		SHCMD("pamixer -d 1; kill -44 $(pidof dwmblocks)") },
        { MODKEY|ShiftMask,		XK_minus,			&dwmAPI::spawn,		SHCMD("pamixer -d 5; kill -44 $(pidof dwmblocks)") },
        { MODKEY|ControlMask,	XK_minus,			&dwmAPI::spawn,		SHCMD(BACKRES) },
        { MODKEY,				XK_equal,			&dwmAPI::spawn,		SHCMD("pamixer -i 1; kill -44 $(pidof dwmblocks)") },
        { MODKEY|ShiftMask,		XK_equal,			&dwmAPI::spawn,		SHCMD("pamixer -i 5; kill -44 $(pidof dwmblocks)") },
        { MODKEY|ControlMask,	XK_equal,			&dwmAPI::spawn,		SHCMD(FORWRES) },
        { MODKEY,				XK_BackSpace,		&dwmAPI::spawn,		SHCMD("sysact") },
        { MODKEY|ShiftMask,		XK_BackSpace,		&dwmAPI::spawn,		SHCMD("sysact") },
        { MODKEY,				XK_Tab,				&dwmAPI::shiftview,	{ .i = -1 } },
        { MODKEY|ShiftMask,		XK_Tab,				&dwmAPI::spawn,		SHCMD("change_mode") },
        { MODKEY,				XK_q,				&dwmAPI::spawn,		SHCMD(DWMMODE "q") },
        { MODKEY|ShiftMask,		XK_q,				&dwmAPI::killclient,	{0} },
        { MODKEY,				XK_w,				&dwmAPI::spawn,		SHCMD(DWMMODE "w") },
        { MODKEY|ShiftMask,		XK_w,				&dwmAPI::spawn,		SHCMD("$BROWSER") },
        { MODKEY|ControlMask,	XK_w,				&dwmAPI::spawn,		SHCMD(TERMINAL " -e sudo nmtui") },
        { MODKEY,				XK_e,				&dwmAPI::spawn,		SHCMD(DWMMODE "e") },
        { MODKEY|ShiftMask,		XK_e,				&dwmAPI::spawn,		SHCMD(TERMINAL " -e lf") },
        { MODKEY|ControlMask,	XK_e,				&dwmAPI::spawn,		SHCMD(TERMINAL " -e htop") },
        { MODKEY,				XK_r,				&dwmAPI::spawn,		SHCMD(DWMMODE "r") },
        { MODKEY|ShiftMask,		XK_r,				&dwmAPI::spawn,		SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
        { MODKEY,				XK_t,				&dwmAPI::setlayout,	{.v = &layouts[0]} }, /* tile */
        { MODKEY|ShiftMask,		XK_t,				&dwmAPI::setlayout,	{.v = &layouts[1]} }, /* bstack */
        { MODKEY,				XK_y,				&dwmAPI::setlayout,	{.v = &layouts[2]} }, /* spiral */
        { MODKEY|ShiftMask,		XK_y,				&dwmAPI::setlayout,	{.v = &layouts[3]} }, /* dwindle */
        { MODKEY,				XK_u,				&dwmAPI::setlayout,	{.v = &layouts[4]} }, /* deck */
        { MODKEY|ShiftMask,		XK_u,				&dwmAPI::setlayout,	{.v = &layouts[5]} }, /* monocle */
        { MODKEY,				XK_i,				&dwmAPI::setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
        { MODKEY|ShiftMask,		XK_i,				&dwmAPI::setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
        { MODKEY,				XK_o,				&dwmAPI::incnmaster,	{.i = +1 } },
        { MODKEY|ShiftMask,		XK_o,				&dwmAPI::incnmaster,	{.i = -1 } },
        { MODKEY,				XK_p,				&dwmAPI::spawn,		SHCMD("mpc toggle") },
        { MODKEY|ShiftMask,		XK_p,				&dwmAPI::spawn,		SHCMD(TERMINAL " -e pulsemixer") },
        { MODKEY,				XK_bracketleft,		&dwmAPI::spawn,		SHCMD("mpc seek -10") },
        { MODKEY|ShiftMask,		XK_bracketleft,		&dwmAPI::spawn,		SHCMD("mpc seek -60") },
        { MODKEY,				XK_bracketright,	&dwmAPI::spawn,		SHCMD("mpc seek +10") },
        { MODKEY|ShiftMask,		XK_bracketright,	&dwmAPI::spawn,		SHCMD("mpc seek +60") },
        { MODKEY,				XK_backslash,		&dwmAPI::togglescratch,	{.ui = 2}	 },
        { MODKEY|ShiftMask,		XK_backslash,		&dwmAPI::togglescratch,	{.ui = 5}	 },
        { MODKEY,				XK_a,				&dwmAPI::togglegaps,	{0} },
        { MODKEY|ShiftMask,		XK_a,				&dwmAPI::defaultgaps,	{0} },
        { MODKEY,				XK_s,				&dwmAPI::togglesticky,	{0} },
        { MODKEY|ShiftMask,		XK_s,				&dwmAPI::spawn,		SHCMD("dmenuvimsessions") },
        { MODKEY,				XK_d,				&dwmAPI::spawn,          SHCMD("rofirun") },
        { MODKEY|ShiftMask,		XK_d,				&dwmAPI::spawn,		SHCMD("dmenu_dragon") },
        { MODKEY|ControlMask,	XK_d,				&dwmAPI::spawn,		SHCMD(SELRES) },
        { MODKEY,				XK_f,				&dwmAPI::togglefullscr,	{0} },
        { MODKEY|ShiftMask,		XK_f,				&dwmAPI::setlayout,	{.v = &layouts[8]} },
        { MODKEY,				XK_h,				&dwmAPI::shiftview,	{ .i = -1} },
        { MODKEY|ShiftMask,		XK_h,				&dwmAPI::setmfact,	{.f = -0.05} },
        { MODKEY|ControlMask,	XK_h,				&dwmAPI::shifttag,	{ .i = -1 } },
        { MODKEY,				XK_l,				&dwmAPI::shiftview,   { .i = 1 } },
        { MODKEY|ShiftMask,		XK_l,				&dwmAPI::setmfact,   {.f = +0.05} },
        { MODKEY|ControlMask,	XK_l,				&dwmAPI::shifttag,	{ .i = 1 } },
        { MODKEY,				XK_apostrophe,		&dwmAPI::togglescratch,	{.ui = 1} },
        { MODKEY|ShiftMask,		XK_apostrophe,		&dwmAPI::togglescratch,	{.ui = 3} },
        { MODKEY,				XK_Return,			&dwmAPI::spawn,		{.v = termcmd } },
        { MODKEY|ShiftMask,		XK_Return,			&dwmAPI::togglescratch,	{.ui = 0} },
        { MODKEY,				XK_z,				&dwmAPI::incrgaps,	{.i = +3 } },
        { MODKEY,				XK_x,				&dwmAPI::incrgaps,	{.i = -3 } },
        { MODKEY,				XK_c,				&dwmAPI::spawn,		SHCMD("toggle_cam") }, 
        { MODKEY,				XK_b,				&dwmAPI::togglebar,	{0} },
        { MODKEY,				XK_m,				&dwmAPI::spawn,		SHCMD(TERMINAL " -n ncmpcpp -e ncmpcpp") },
        { MODKEY|ShiftMask,		XK_m,				&dwmAPI::spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
        { MODKEY,				XK_comma,			&dwmAPI::spawn,		SHCMD("mpc prev") },
        { MODKEY|ShiftMask,		XK_comma,			&dwmAPI::spawn,		SHCMD("mpc seek 0%") },
        { MODKEY,				XK_period,			&dwmAPI::spawn,		SHCMD("mpc next") },
        { MODKEY,				XK_Left,	&dwmAPI::focusmon,	{.i = -1 } },
        { MODKEY|ShiftMask,		XK_Left,	&dwmAPI::tagmon,		{.i = -1 } },
        { MODKEY,				XK_Right,	&dwmAPI::focusmon,	{.i = +1 } },
        { MODKEY|ShiftMask,		XK_Right,	&dwmAPI::tagmon,		{.i = +1 } },
        { MODKEY,				XK_Page_Up,	&dwmAPI::shiftview,	{ .i = -1 } },
        { MODKEY|ShiftMask,		XK_Page_Up,	&dwmAPI::shifttag,	{ .i = -1 } },
        { MODKEY,				XK_Page_Down,	&dwmAPI::shiftview,	{ .i = +1 } },
        { MODKEY|ShiftMask,		XK_Page_Down,	&dwmAPI::shifttag,	{ .i = +1 } },
        { MODKEY,				XK_Insert,	&dwmAPI::spawn,		SHCMD("xdotool type $(cat ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
        { MODKEY,			XK_F1,		&dwmAPI::spawn,		SHCMD("mictoggle") },
        { MODKEY,			XK_F2,		&dwmAPI::spawn,		SHCMD("tutorialvids") },
        { MODKEY,			XK_F3,		&dwmAPI::spawn,		SHCMD("displayselect") },
        { MODKEY,			XK_F4,		&dwmAPI::spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
        { MODKEY,			XK_F6,		&dwmAPI::spawn,		SHCMD("torwrap") },
        { MODKEY,			XK_F7,		&dwmAPI::spawn,		SHCMD("td-toggle") },
        { MODKEY,			XK_F8,		&dwmAPI::spawn,		SHCMD("mw -Y") },
        { MODKEY,			XK_F9,		&dwmAPI::spawn,		SHCMD("dmenumount") },
        { MODKEY,			XK_F10,		&dwmAPI::spawn,		SHCMD("dmenuumount") },
        { MODKEY,			XK_F11,		&dwmAPI::spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam av://v4l2:$(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
        { MODKEY,			XK_F12,		&dwmAPI::spawn,		SHCMD("remaps & notify-send \\\"⌨️ Keyboard remapping...\\\" \\\"Re-running keyboard defaults for any newly plugged-in keyboards.\\\"") },
        { 0,				XK_F9,		&dwmAPI::spawn,		SHCMD("dunstctl close") },
        { 0,				XK_F10,		&dwmAPI::spawn,		SHCMD("dunstctl action") },
        { 0,				XK_F11,		&dwmAPI::spawn,		SHCMD("dunstctl history-pop") },
        { 0,				XK_F12,		&dwmAPI::spawn,		SHCMD("dunstctl close-all") },
        { MODKEY,			XK_space,	&dwmAPI::zoom,		{0} },
        { MODKEY|ShiftMask,	XK_space,	&dwmAPI::togglefloating,	{0} },
        { MODKEY|ControlMask,	XK_space,	&dwmAPI::togglealwaysonback,	{0} },
        { 0,					XK_Print,	&dwmAPI::spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
        { ShiftMask,			XK_Print,	&dwmAPI::spawn,		SHCMD("maimpick") },
        { MODKEY,				XK_Print,	&dwmAPI::spawn,		SHCMD("dmenurecord") },
        { MODKEY|ShiftMask,		XK_Print,	&dwmAPI::spawn,		SHCMD("dmenurecord kill") },
        { MODKEY,				XK_Delete,	&dwmAPI::spawn,		SHCMD("dmenurecord kill") },
        { MODKEY,			XK_Scroll_Lock,	&dwmAPI::spawn,		SHCMD("killall screenkey || screenkey &") },
        { 0, XF86XK_AudioMute,		&dwmAPI::spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
        { 0, XF86XK_AudioRaiseVolume,	&dwmAPI::spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
        { 0, XF86XK_AudioLowerVolume,	&dwmAPI::spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
        { 0, XF86XK_AudioPrev,		&dwmAPI::spawn,		SHCMD("mpc prev") },
        { 0, XF86XK_AudioNext,		&dwmAPI::spawn,		SHCMD("mpc next") },
        { 0, XF86XK_AudioPause,		&dwmAPI::spawn,		SHCMD("mpc pause") },
        { 0, XF86XK_AudioPlay,		&dwmAPI::spawn,		SHCMD("mpc play") },
        { 0, XF86XK_AudioStop,		&dwmAPI::spawn,		SHCMD("mpc stop") },
        { 0, XF86XK_AudioRewind,	&dwmAPI::spawn,		SHCMD("mpc seek -10") },
        { 0, XF86XK_AudioForward,	&dwmAPI::spawn,		SHCMD("mpc seek +10") },
        { 0, XF86XK_AudioMedia,		&dwmAPI::spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
        { 0, XF86XK_AudioMicMute,	&dwmAPI::spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
        { 0, XF86XK_PowerOff,		&dwmAPI::spawn,		SHCMD("sysact") },
        { 0, XF86XK_Calculator,		&dwmAPI::spawn,		SHCMD(TERMINAL " -e bc -l") },
        { 0, XF86XK_Sleep,		&dwmAPI::spawn,		SHCMD("sudo -A zzz") },
        { 0, XF86XK_WWW,		&dwmAPI::spawn,		SHCMD("$BROWSER") },
        { 0, XF86XK_DOS,		&dwmAPI::spawn,		SHCMD(TERMINAL) },
        { 0, XF86XK_ScreenSaver,	&dwmAPI::spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
        { 0, XF86XK_TaskPane,		&dwmAPI::spawn,		SHCMD(TERMINAL " -e htop") },
        { 0, XF86XK_Mail,		&dwmAPI::spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
        { 0, XF86XK_MyComputer,		&dwmAPI::spawn,		SHCMD(TERMINAL " -e lf /") },
        { 0, XF86XK_Launch1,		&dwmAPI::spawn,		SHCMD("xset dpms force off") },
        { 0, XF86XK_TouchpadToggle,	&dwmAPI::spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
        { 0, XF86XK_TouchpadOff,	&dwmAPI::spawn,		SHCMD("synclient TouchpadOff=1") },
        { 0, XF86XK_TouchpadOn,		&dwmAPI::spawn,		SHCMD("synclient TouchpadOff=0") },
        { 0, XF86XK_MonBrightnessUp,	&dwmAPI::spawn,		SHCMD("xbacklight -inc 15") },
        { 0, XF86XK_MonBrightnessDown,	&dwmAPI::spawn,		SHCMD("xbacklight -dec 15") },
    };

    struct Button{
        unsigned int click;
        unsigned int mask;
        unsigned int button;
        void (dwmAPI::*func)(const Arg *);
        const Arg arg;
    };

    /* button definitions */
    /* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
    const Button buttons[28] = {
        /* click                event mask      button          function        argument */
#ifndef __OpenBSD__
        { ClkWinTitle,          0,              Button2,        &dwmAPI::zoom,           {0} },
        { ClkStatusText,        0,              Button1,        &dwmAPI::sigdwmblocks,   {.i = 1} },
        { ClkStatusText,        0,              Button2,        &dwmAPI::sigdwmblocks,   {.i = 2} },
        { ClkStatusText,        0,              Button3,        &dwmAPI::sigdwmblocks,   {.i = 3} },
        { ClkStatusText,        0,              Button4,        &dwmAPI::sigdwmblocks,   {.i = 4} },
        { ClkStatusText,        0,              Button5,        &dwmAPI::sigdwmblocks,   {.i = 5} },
        { ClkStatusText,        ShiftMask,      Button1,        &dwmAPI::sigdwmblocks,   {.i = 6} },
#endif
        { ClkStatusText,        ShiftMask,      Button3,        &dwmAPI::spawn,          SHCMD(TERMINAL " -e vim ~/.local/src/dwmblocks/config.h") },
        { ClkClientWin,         MODKEY,         Button1,        &dwmAPI::movemouse,      {0} },
        { ClkClientWin,         0,              9,              &dwmAPI::movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        &dwmAPI::zoom,	{0} },
        { ClkClientWin,         MODKEY,         Button3,        &dwmAPI::resizemouse,    {0} },
        { ClkClientWin,		    MODKEY,		    Button4,	    &dwmAPI::incrgaps,	{.i = +1} },
        { ClkClientWin,		    MODKEY,		    Button5,	    &dwmAPI::incrgaps,	{.i = -1} },
        { ClkTagBar,            0,              Button1,        &dwmAPI::view,           {0} },
        { ClkTagBar,		    0,	            Button2,	    &dwmAPI::focusstack,		    {0} },
        { ClkTagBar,            0,              Button3,        &dwmAPI::toggleview,     {0} },
        { ClkTagBar,		    0,	            Button4,	    &dwmAPI::focusstack,	    {.i = INC(+1) } },
        { ClkTagBar,		    0,	            Button5,	    &dwmAPI::focusstack,	    {.i = INC(-1) } },
        { ClkTagBar,            0,              8,              &dwmAPI::toggletag,      {0} },
        { ClkTagBar,            0,              9,              &dwmAPI::tag,            {0} },
        { ClkTagBar,            MODKEY,         Button1,        &dwmAPI::toggletag,      {0} },
        { ClkTagBar,            MODKEY,         Button3,        &dwmAPI::tag,            {0} },
        { ClkRootWin,		    0,	            Button2,	    &dwmAPI::pushstack,	    {0} },
        { ClkRootWin,		    0,	            Button4,	    &dwmAPI::focusstack,	    {.i = INC(+1) } },
        { ClkRootWin,		    0,	            Button5,	    &dwmAPI::focusstack,	    {.i = INC(-1) } },
        { ClkRootWin,		    0,	            8,	            &dwmAPI::pushstack,	    {.i = INC(+1) } },
        { ClkRootWin,		    0,	            9,	            &dwmAPI::pushstack,	    {.i = INC(-1) } },
    };

    /* appearance */
    unsigned int borderpx  = 0;        /* border pixel of windows */
    unsigned int snap      = 32;       /* snap pixel */
    unsigned int cornerrad = 8;
    int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
    int showbar            = 1;        /* 0 means no bar */
    int topbar             = 1;        /* 0 means bottom bar */
    //*fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
    char *fonts[2];
    Sp scratchpads[6];
    char normbgcolor[8]           = "#040200";
    char normbordercolor[8]       = "#ffb55d";
    char normfgcolor[8]           = "#deaf76";
    char selfgcolor[8]            = "#ffb55d";
    char selbordercolor[8]        = "#00bbff";
    char selbgcolor[8]            = "#040200";
    char *colors[2][3] = {
        /*               fg           bg           border   */
        [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
        [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
    };

    int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
    unsigned int gappih    = 20;       /* horiz inner gap between windows */
    unsigned int gappiv    = 10;       /* vert inner gap between windows */
    unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
    unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */


    /* tagging */
    static const char *tags[9];

    static const Rule rules[32];

    /* layout(s) */
    float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
    int nmaster     = 1;    /* number of clients in master area */
    int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
    constexpr static const Layout layouts[] = {
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

private:
    dwmAPI api;
};



#endif /* ifndef DEBUG */


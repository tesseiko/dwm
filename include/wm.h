/*
 ==============================================================================
 
 wm.h
 Created: 26 Feb 2024 12:50:42pm
 Author: Manos Lefakis
 
 ==============================================================================
 */

#pragma once
#include <sys/types.h>
#include <X11/Xft/Xft.h>
#include "Xlib.h"
#include "drw.h"
#include "dwm.h"
class wm
{
public:
    wm();
    ~wm();


    Monitor *selmon;
    Drw *drw;
    Display *dpy;
    int lrpad;            /* sum of left and right padding for text */
    int bh, blw;      /* bar geometry */
    char stext[256];
    char rawstext[256];
    int dwmblockssig;
    unsigned int numlockmask;
    Atom wmatom[WMLast], netatom[NetLast];
    Window root, wmcheckwin;
    int sw, sh;           /* X display screen geometry width, height */
    Monitor *mons;
    int enablefullscreen;
    int enableoutergaps;
    Clr *scheme[2];
    Cur *cursor[CurLast];
    int screen;


    Monitor * dirtomon(int dir);
    void drawbar(Monitor *m);
    Monitor * recttomon(int x, int y, int w, int h);
    int updategeom(void);
    Monitor * wintomon(Window w);
    void manage(Window w, XWindowAttributes *wa);
};

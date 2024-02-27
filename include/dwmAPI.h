/*
 ==============================================================================
 
 dwmAPI.h
 Created: 15 Feb 2024 6:09:45pm
 Author: Manos Lefakis
 
 ==============================================================================
 */

#pragma once

#include "wm.h"

// for config
#define SYSTRAYTAG              1 << 18
#define DOCKTAG                 1 << 19
#define INC(X)                  ((X) + 2000)
#define SPTAG(i)		((1 << 9) << (i))

typedef union {
	int i;
	int ui;
	float f;
	const void *v;
} Arg;

class dwmAPI;

typedef struct {
	const char *wm_class;
	const char *instance;
	const char *title;
	unsigned int tags;
	int isfloating;
	int issticky;
	int isterminal;
	int noswallow;
	int monitor;
} Rule;

enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */

enum { SchemeNorm, SchemeSel }; /* color schemes */

class dwmAPI
{
public:
    dwmAPI(wm& winMan): winMan(winMan){};
    ~dwmAPI() {};

    void focusmon(const Arg *arg);
    void focusstack(const Arg *arg);
    void incnmaster(const Arg *arg);
    void movemouse(const Arg *arg);
    void pushstack(const Arg *arg);
    void quit(const Arg *arg);
    void resizemouse(const Arg *arg);
    int stackpos(const Arg *arg);
    void setlayout(const Arg *arg);
    void setmfact(const Arg *arg);
#ifndef __OpenBSD__
    void sigdwmblocks(const Arg *arg);
#endif
    void spawn(const Arg *arg);
    void shiftview(const Arg *arg);
    void shifttag(const Arg *arg);
    void tag(const Arg *arg);
    void tagmon(const Arg *arg);
    void togglebar(const Arg *arg);
    void togglefloating(const Arg *arg);
    void togglealwaysonback(const Arg *arg);
    void togglealwaysontop(const Arg *arg);
    void togglefullscr(const Arg *arg);
    void togglesticky(const Arg *arg);
    void togglescratch(const Arg *arg);
    void toggletag(const Arg *arg);
    void toggleview(const Arg *arg);
    void view(const Arg *arg);
    void zoom(const Arg *arg);
    void killclient(const Arg *arg);
    void togglegaps(const Arg *arg);
    void defaultgaps(const Arg *arg);
    void incrgaps(const Arg *arg);
private:
    wm winMan;
};

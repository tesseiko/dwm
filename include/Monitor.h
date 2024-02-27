/*
 ==============================================================================
 
 Monitor.h
 Created: 27 Feb 2024 11:05:28am
 Author: Manos Lefakis
 
 ==============================================================================
 */

#pragma once

class Monitor;
#include "Client.h"

typedef struct {
	const char *symbol;
	void (*arrange)(Monitor *);
} Layout;


class Monitor {
public:
	char ltsymbol[16];
	float mfact;
	int nmaster;
	int num;
	int by;               /* bar geometry */
	int mx, my, mw, mh;   /* screen size */
	int wx, wy, ww, wh;   /* window area  */
	int gappih;           /* horizontal gap between windows */
	int gappiv;           /* vertical gap between windows */
	int gappoh;           /* horizontal outer gaps */
	int gappov;           /* vertical outer gaps */
	unsigned int seltags;
	unsigned int sellt;
	unsigned int tagset[2];
	int showbar;
	int topbar;
	Client *clients;
	Client *sel;
	Client *stack;
	Monitor *next;
	Window barwin;
	const Layout *lt[2];
};


/*
 ==============================================================================
 
 x11manager.h
 Created: 14 Feb 2024 5:47:18am
 Author: Manos Lefakis
 
 ==============================================================================
 */

#ifndef X11MANAGER_H
#define X11MANAGER_H

extern Monitor *selmon;
extern Drw *drw;
extern Display *dpy;
extern int lrpad;            /* sum of left and right padding for text */
extern int bh, blw;      /* bar geometry */
extern char stext[256];
extern char rawstext[256];
extern int dwmblockssig;
extern unsigned int numlockmask;
extern Atom wmatom[WMLast], netatom[NetLast];
extern Window root, wmcheckwin;
extern int sw, sh;           /* X display screen geometry width, height */
extern Monitor *mons;

// extern static const char *spcmd2[];
// extern static const char *spcmd2[];
// extern static const char *spcmd3[];
// extern static const char *spcmd4[];
// extern static const char *spcmd5[];
// extern static const char *spcmd6[];
// extern static const char *tags[];
// extern Button buttons[];
// extern Key keys[];


int xerror(Display *dpy, XErrorEvent *ee);
void grabkeys(void);
#endif

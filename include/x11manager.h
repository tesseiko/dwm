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
extern int enablefullscreen;
extern int enableoutergaps;
extern Clr *scheme[2];
extern Cur *cursor[CurLast];
extern const char broken[];
extern int screen;

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
void load_xresources(void);
void cleanup(void);
void scan(void);
void setfullscreen(Client *c, int fullscreen);
void resizeclient(Client *c, int x, int y, int w, int h);
void restack(Monitor *m);
void cleanupmon(Monitor *mon);
void updateclientlist(void);
void unfocus(Client *c, int setfocus);
void focus(Client *c);
void showhide(Client *c);
Atom getatomprop(Client *c, Atom prop);
int gettextprop(Window w, Atom atom, char *text, unsigned int size);
void setup(void);
void configure(Client *c);
int sendevent(Client *c, Atom proto);
int xerrordummy(Display *dpy, XErrorEvent *ee);
void setclientstate(Client *c, long state);
void initHandlers();
void roundcorners(Client *c);
void applyrules(Client *c);
void grabbuttons(Client *c, int focused);
void swallow(Client *p, Client *c);
#endif

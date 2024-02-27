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

#include "wm.h"

int xerror(Display *dpy, XErrorEvent *ee);
void grabkeys(void);
void load_xresources(void);
void cleanup(void);
void scan(void);
void restack(Monitor *m);
void cleanupmon(Monitor *mon);
void updateclientlist(void);
int gettextprop(Window w, Atom atom, char *text, unsigned int size);
void setup(void);
int xerrordummy(Display *dpy, XErrorEvent *ee);


class event_handler
{
public:

    event_handler(wm& winMan);
    ~event_handler();

    void (event_handler::*handler[LASTEvent]) (XEvent *);
private:

    wm winMan;
    void buttonpress(XEvent *e);
    void clientmessage(XEvent *e);
    void configurerequest(XEvent *e);
    void configurenotify(XEvent *e);
    void destroynotify(XEvent *e);
    void enternotify(XEvent *e);
    void expose(XEvent *e);
    void focusin(XEvent *e);
    void keypress(XEvent *e);
    void mappingnotify(XEvent *e);
    void maprequest(XEvent *e);
    void motionnotify(XEvent *e);
    void propertynotify(XEvent *e);
    void unmapnotify(XEvent *e);
};
#endif

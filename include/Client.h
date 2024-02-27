/*
 ==============================================================================
 
 Client.h
 Created: 27 Feb 2024 10:03:42am
 Author: Manos Lefakis
 
 ==============================================================================
 */

#pragma once
#include "X.h"
#include "Xlib.h"
#include <X11/Xft/Xft.h>
#include <X11/Xresource.h>
#include "util.h"
#include "drw.h"
#include "Monitor.h"
#include <sys/types.h>
class Client {
public:
    Client();
    ~Client();

    void updatetitle();
    void updatewindowtype();
    void updatewmhints();
    int sendevent(Atom proto);
    void swallow(Client *p);
    void unswallow();
    void unmanage(int destroyed);
    void applyrules();
    void grabbuttons(int focused);
    void roundcorners();
    void resizeclient(int x, int y, int w, int h);
    void setfullscreen(int fullscreen);
    void setfocus();
    void focus(bool getNext=false);
    void unfocus(int setfocus);
    void showhide();
    Atom getatomprop(Atom prop);
    void configure();
    void setclientstate(long state);
    void detach();
    void detachstack();
    void attach();
    void attachstack();
    Client *nexttiled();
    void pop();
    void resize(int x, int y, int w, int h, int interact);
    int applysizehints(int *x, int *y, int *w, int *h, int interact);

    int isfixed, isfloating, isurgent, 
    neverfocus, oldstate, isfullscreen, 
    isterminal, noswallow, issticky, isalwaysontop, isalwaysonbackground;
    unsigned int tags;
    Client *next;
    Client *snext;
    Client *swallowing;
    int x, y, w, h;
    int bw, oldbw;
    Window win;
    Monitor *mon;
private:
	char name[256];
	float mina, maxa;
	int oldx, oldy, oldw, oldh;
	int basew, baseh, incw, inch, maxw, maxh, minw, minh;
	pid_t pid;
};


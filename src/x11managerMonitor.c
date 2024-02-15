/*
 ==============================================================================
 
 x11managerMonitor.c
 Created: 15 Feb 2024 5:46:50pm
 Author: Manos Lefakis
 
 ==============================================================================
 */
#include <stdio.h>
#include "Xlib.h"
#include <X11/Xft/Xft.h>
#include <X11/Xresource.h>
#include "util.h"
#include "drw.h"
#include "dwm.h"
#include "x11manager.h"
#include <X11/Xatom.h>
#include <X11/Xproto.h>
#include <X11/extensions/shape.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include "vanitygaps.h"
#include <XF86keysym.h>
#include "config.h"
#include <signal.h>

void
cleanupmon(Monitor *mon)
{
	Monitor *m;

	if (mon == mons)
		mons = mons->next;
	else {
		for (m = mons; m && m->next != mon; m = m->next);
		m->next = mon->next;
	}
	XUnmapWindow(dpy, mon->barwin);
	XDestroyWindow(dpy, mon->barwin);
	free(mon);
}

void
restack(Monitor *m)
{
	Client *c;
	XEvent ev;
	XWindowChanges wc;
    for (c = m->stack; c; c = c->snext) {
		roundcorners(c);
	}

	drawbar(m);
	if (!m->sel)
		return;
	if (m->sel->isfloating || !m->lt[m->sellt]->arrange)
		XRaiseWindow(dpy, m->sel->win);
	// TODO check efficiency here
 	/* raise the aot window */
    for(Monitor *m_search = mons; m_search; m_search = m_search->next){
 		for(c = m_search->clients; c; c = c->next){
 			if(c->isalwaysontop){
 				XRaiseWindow(dpy, c->win);
 				break;
 			} else if (c->isalwaysonbackground){
                XLowerWindow(dpy, c->win);
            }
 		}
 	}
	if (m->lt[m->sellt]->arrange) {
		wc.stack_mode = Below;
		wc.sibling = m->barwin;
		for (c = m->stack; c; c = c->snext)
			if (!c->isfloating && ISVISIBLE(c)) {
				XConfigureWindow(dpy, c->win, CWSibling|CWStackMode, &wc);
				wc.sibling = c->win;
			}
	}
	XSync(dpy, False);
	while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}


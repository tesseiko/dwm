/*
 ==============================================================================
 
 x11managerClient.c
 Created: 15 Feb 2024 5:32:02pm
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
#include "dwmAPI.h"
#include "config.h"
#include "Client.h"
#include <signal.h>

#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */
#define LENGTH(X)               (sizeof(X) / sizeof(X[0]))

const char broken[] = "broken";

void
Client::updatetitle()
{
	if (!gettextprop(win, netatom[NetWMName], name, sizeof name))
		gettextprop(win, XA_WM_NAME, name, sizeof name);
	if (name[0] == '\0') /* hack to mark broken clients */
		strcpy(name, broken);
};

void
Client::updatewindowtype()
{
	Atom state = getatomprop(c, netatom[NetWMState]);
	Atom wtype = getatomprop(c, netatom[NetWMWindowType]);

	if (state == netatom[NetWMFullscreen])
		setfullscreen(1);
	if (wtype == netatom[NetWMWindowTypeDialog])
		isfloating = 1;
}

void
Client::updatewmhints()
{
	XWMHints *wmh;

	if ((wmh = XGetWMHints(dpy, win))) {
		if (this == selmon->sel && wmh->flags & XUrgencyHint) {
			wmh->flags &= ~XUrgencyHint;
			XSetWMHints(dpy, win, wmh);
		} else
			isurgent = (wmh->flags & XUrgencyHint) ? 1 : 0;
		if (wmh->flags & InputHint)
			neverfocus = !wmh->input;
		else
			neverfocus = 0;
		XFree(wmh);
	}
}

int
Client::sendevent(Atom proto)
{
	int n;
	Atom *protocols;
	int exists = 0;
	XEvent ev;

	if (XGetWMProtocols(dpy, win, &protocols, &n)) {
			while (!exists && n--)
				exists = protocols[n] == proto;
			XFree(protocols);
		}

	if (exists) {
		ev.type = ClientMessage;
		ev.xclient.window = win;
		ev.xclient.message_type = wmatom[WMProtocols];
		ev.xclient.format = 32;
		ev.xclient.data.l[0] = proto;
		ev.xclient.data.l[1] = CurrentTime;
		XSendEvent(dpy, win, False, NoEventMask, &ev);
	}
	return exists;
}

// NOTE: svinw to deftero orisma!
void
Client::swallow(Client *p)
{
	if (noswallow || isterminal)
		return;
	if (!swallowfloating && isfloating)
		return;

	detach();
	detachstack();

	setclientstate(WithdrawnState);
	XUnmapWindow(dpy, p->win);

	p->swallowing = this;
	mon = p->mon;

	Window w = p->win;
	p->win = win;
	win = w;
	p->updatetitle();

	XWindowChanges wc;
	wc.border_width = p->bw;
	XConfigureWindow(dpy, p->win, CWBorderWidth, &wc);
	XMoveResizeWindow(dpy, p->win, p->x, p->y, p->w, p->h);
	XSetWindowBorder(dpy, p->win, scheme[SchemeNorm][ColBorder].pixel);

	arrange(p->mon);
	configure(p);
	updateclientlist();
}

void
Client::unswallow()
{
	win = swallowing->win;

	free(swallowing);
	swallowing = NULL;

	/* unfullscreen the client */
	setfullscreen(0);
	updatetitle();
	arrange(mon);
	XMapWindow(dpy, win);

	XWindowChanges wc;
	wc.border_width = bw;
	XConfigureWindow(dpy, win, CWBorderWidth, &wc);
	XMoveResizeWindow(dpy, win, x, y, w, h);
	XSetWindowBorder(dpy, win, scheme[SchemeNorm][ColBorder].pixel);

	setclientstate(NormalState);
	focus(NULL);
	arrange(mon);
}

void
Client::detach()
{
	Client **tc;

	for (tc = &mon->clients; *tc && *tc != this; tc = &(*tc)->next);

    *tc = next;
}

void
Client::detachstack()
{
	Client **tc, *t;

	for (tc = &mon->stack; *tc && *tc != this; tc = &(*tc)->snext);
	*tc = snext;

	if (this == mon->sel) {
		for (t = mon->stack; t && !ISVISIBLE(t); t = t->snext);
		mon->sel = t;
	}
}

void
Client::attach()
{
    next = mon->clients;
    mon->clients = this;
}


void
Client::pop()
{
    /*  
     * TODO: look her for stack refactoring
     *
     *
     * */
	detach();
	attach();
	focus();
	arrange(mon);
}

void
Client::attachstack()
{
    if (tags & (DOCKTAG | SYSTRAYTAG))
        return;

    fprintf(stderr, "Stacking %s tag:%d\n", name, tags);
    snext = mon->stack;
    mon->stack = this;
}

Client *
Client::nexttiled()
{
    Client *c = this;
	for (; c && (c->isfloating || !ISVISIBLE(c)); c = c->next);
	return c;
}

void
Client::unmanage(int destroyed)
{
	Monitor *m = mon;
	XWindowChanges wc;

	if (swallowing) {
		unswallow();
		return;
	}

	Client *s = swallowingclient(win);
	if (s) {
        // FIX: clean
		// free(s->swallowing);
		s->swallowing = NULL;
		arrange(m);
        focus(NULL);
		return;
	}

	detach();
	detachstack();
	if (!destroyed) {
		wc.border_width = oldbw;
		XGrabServer(dpy); /* avoid race conditions */
		XSetErrorHandler(xerrordummy);
		XConfigureWindow(dpy, win, CWBorderWidth, &wc); /* restore border */
		XUngrabButton(dpy, AnyButton, AnyModifier, win);
		setclientstate(WithdrawnState);
		XSync(dpy, False);
		XSetErrorHandler(xerror);
		XUngrabServer(dpy);
	}
// FIX: check about freeing
	// free(c);

	if (!s) {
		arrange(m);
		focus(NULL);
		updateclientlist();
	}
}

/* function implementations */
void
Client::applyrules()
{
	const char *wm_class, *instance;
	unsigned int i;
	const Rule *r;
	Monitor *m;
	XClassHint ch = { NULL, NULL };

	/* rule matching */
	isfloating = 0;
	tags = 0;
	XGetClassHint(dpy, win, &ch);
	wm_class    = ch.res_class ? ch.res_class : broken;
	instance = ch.res_name  ? ch.res_name  : broken;

	for (i = 0; i < LENGTH(rules); i++) {
		r = &rules[i];
		if ((!r->title || strstr(name, r->title))
		&& (!r->wm_class || strstr(wm_class, r->wm_class))
		&& (!r->instance || strstr(instance, r->instance)))
		{
			issticky = r->issticky;
			isterminal = r->isterminal;
			isfloating = r->isfloating;
			noswallow  = r->noswallow;
			tags |= r->tags;
            fprintf(stderr, "Applying rules for %s %s tag:%d\n", name, instance, tags);
			if ((r->tags & SPTAGMASK) && r->isfloating) {
				x = mon->wx + (mon->ww / 2 - WIDTH(this) / 2);
				y = mon->wy + (mon->wh / 2 - HEIGHT(this) / 2);
			}

			for (m = mons; m && m->num != r->monitor; m = m->next);
			if (m)
				mon = m;
		}
	}
	if (ch.res_class)
		XFree(ch.res_class);
	if (ch.res_name)
		XFree(ch.res_name);
    
    if (tags & (SYSTRAYTAG|DOCKTAG)) {
        tags &= (TAGMASK|SYSTRAYTAG|DOCKTAG);
    }
    else {
        tags = tags & TAGMASK ? tags & TAGMASK : (mon->tagset[mon->seltags] & ~SPTAGMASK);
    }

    fprintf(stderr, "Rules applied for %s tag:%d\n", name, tags);
    if (tags & SYSTRAYTAG) {
        snext = NULL;
        showhide();
    }
}

void
Client::grabbuttons(int focused)
{
	updatenumlockmask();
	{
		unsigned int i, j;
		unsigned int modifiers[] = { 0, LockMask, numlockmask, numlockmask|LockMask };
		XUngrabButton(dpy, AnyButton, AnyModifier, win);
		if (!focused)
			XGrabButton(dpy, AnyButton, AnyModifier, win, False,
				BUTTONMASK, GrabModeSync, GrabModeSync, None, None);
		for (i = 0; i < LENGTH(buttons); i++)
			if (buttons[i].click == ClkClientWin)
				for (j = 0; j < LENGTH(modifiers); j++)
					XGrabButton(dpy, buttons[i].button,
						buttons[i].mask | modifiers[j],
						win, False, BUTTONMASK,
						GrabModeAsync, GrabModeSync, None, None);
	}
}

void
Client::roundcorners()
{
    Window w = win;
    XWindowAttributes wa;
    XGetWindowAttributes(dpy, w, &wa);

    // If this returns null, the window is invalid.
    if(!XGetWindowAttributes(dpy, w, &wa))
        return;

    int width = borderpx * 2 + wa.width;
    int height = borderpx * 2 + wa.height;
    /* int width = win_attr.border_width * 2 + win_attr.width; */
    /* int height = win_attr.border_width * 2 + win_attr.height; */
    int rad = cornerrad * enablegaps * (1-enablefullscreen) * enableoutergaps; //config_theme_cornerradius;
    int dia = 2 * rad;

    // do not try to round if the window would be smaller than the corners
    if(width < dia || height < dia)
        return;

    Pixmap mask = XCreatePixmap(dpy, w, width, height, 1);
    // if this returns null, the mask is not drawable
    if(!mask)
        return;

    XGCValues xgcv;
    GC shape_gc = XCreateGC(dpy, mask, 0, &xgcv);
    if(!shape_gc) {
        XFreePixmap(dpy, mask);
        return;
    }

    XSetForeground(dpy, shape_gc, 0);
    XFillRectangle(dpy, mask, shape_gc, 0, 0, width, height);
    XSetForeground(dpy, shape_gc, 1);
    XFillArc(dpy, mask, shape_gc, 0, 0, dia, dia, 0, 23040);
    XFillArc(dpy, mask, shape_gc, width-dia-1, 0, dia, dia, 0, 23040);
    XFillArc(dpy, mask, shape_gc, 0, height-dia-1, dia, dia, 0, 23040);
    XFillArc(dpy, mask, shape_gc, width-dia-1, height-dia-1, dia, dia, 0, 23040);
    XFillRectangle(dpy, mask, shape_gc, rad, 0, width-dia, height);
    XFillRectangle(dpy, mask, shape_gc, 0, rad, width, height-dia);
    XShapeCombineMask(dpy, w, ShapeBounding, 0-wa.border_width, 0-wa.border_width, mask, ShapeSet);
    XFreePixmap(dpy, mask);
    XFreeGC(dpy, shape_gc);
}

void
Client::resizeclient(int x, int y, int w, int h)
{
	XWindowChanges wc;

	oldx = x; x = wc.x = x;
	oldy = y; y = wc.y = y;
	oldw = w; w = wc.width = w;
	oldh = h; h = wc.height = h;
	wc.border_width = bw;
	XConfigureWindow(dpy, win, CWX|CWY|CWWidth|CWHeight|CWBorderWidth, &wc);
	configure();
	roundcorners();
	XSync(dpy, False);
}

void
Client::setfullscreen(int fullscreen)
{
	if (fullscreen && !isfullscreen) {
		XChangeProperty(dpy, win, netatom[NetWMState], XA_ATOM, 32,
			PropModeReplace, (unsigned char*)&netatom[NetWMFullscreen], 1);
		isfullscreen = 1;
		oldstate = isfloating;
		oldbw = bw;
		bw = 0;
		isfloating = 1;
		resizeclient(mon->mx, mon->my, mon->mw, mon->mh);
        if (isalwaysonbackground)
            XLowerWindow(dpy, win);
        else
            XRaiseWindow(dpy, win);
	} else if (!fullscreen && isfullscreen){
		XChangeProperty(dpy, win, netatom[NetWMState], XA_ATOM, 32,
			PropModeReplace, (unsigned char*)0, 0);
		isfullscreen = 0;
		isfloating = oldstate;
		bw = oldbw;
		x = oldx;
		y = oldy;
		w = oldw;
		h = oldh;
		resizeclient(x, y, w, h);
		arrange(mon);
	}
}

void
Client::setfocus()
{
	if (!neverfocus) {
		XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
		XChangeProperty(dpy, root, netatom[NetActiveWindow],
			XA_WINDOW, 32, PropModeReplace,
			(unsigned char *) &(win), 1);
	}
	sendevent(wmatom[WMTakeFocus]);
}

void
Client::focus(bool focusNext)
{
    Client *c = this;
    if (focusNext || !ISVISIBLE(this))
		for (c = selmon->stack; c && !ISVISIBLE(c); c = snext);

	if (selmon->sel && selmon->sel != c)
		selmon->sel->unfocus(0);
	if (c) {
		if (mon != selmon)
			selmon = mon;
		if (isurgent)
			seturgent(0);
		detachstack();
		attachstack();
		grabbuttons(1);
		XSetWindowBorder(dpy, win, scheme[SchemeSel][ColBorder].pixel); // TODO: why this line is not in setfocus?
		setfocus();
	} else {
		XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
		XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
	}
	selmon->sel = this;
	drawbars();
}

void
Client::unfocus(int setfocus)
{
	// if (!c)
	// 	return;
	grabbuttons(0);
	XSetWindowBorder(dpy, win, scheme[SchemeNorm][ColBorder].pixel);
	if (setfocus) {
		XSetInputFocus(dpy, root, RevertToPointerRoot, CurrentTime);
		XDeleteProperty(dpy, root, netatom[NetActiveWindow]);
	}
}

int
Client::applysizehints(int *x, int *y, int *w, int *h, int interact)
{
	int baseismin;
	Monitor *m = mon;

	/* set minimum possible */
	*w = MAX(1, *w);
	*h = MAX(1, *h);
	if (interact) {
		if (*x > sw)
			*x = sw - WIDTH(this);
		if (*y > sh)
			*y = sh - HEIGHT(this);
		if (*x + *w + 2 * bw < 0)
			*x = 0;
		if (*y + *h + 2 * bw < 0)
			*y = 0;
	} else {
		if (*x >= m->wx + m->ww)
			*x = m->wx + m->ww - WIDTH(this);
		if (*y >= m->wy + m->wh)
			*y = m->wy + m->wh - HEIGHT(this);
		if (*x + *w + 2 * bw <= m->wx)
			*x = m->wx;
		if (*y + *h + 2 * bw <= m->wy)
			*y = m->wy;
	}
	if (*h < bh)
		*h = bh;
	if (*w < bh)
		*w = bh;
	if (resizehints || isfloating || !mon->lt[mon->sellt]->arrange) {
		/* see last two sentences in ICCCM 4.1.2.3 */
		baseismin = basew == minw && baseh == minh;
		if (!baseismin) { /* temporarily remove base dimensions */
			*w -= basew;
			*h -= baseh;
		}
		/* adjust for aspect limits */
		if (mina > 0 && maxa > 0) {
			if (maxa < (float)*w / *h)
				*w = *h * maxa + 0.5;
			else if (mina < (float)*h / *w)
				*h = *w * mina + 0.5;
		}
		if (baseismin) { /* increment calculation requires this */
			*w -= basew;
			*h -= baseh;
		}
		/* adjust for increment value */
		if (incw)
			*w -= *w % incw;
		if (inch)
			*h -= *h % inch;
		/* restore base dimensions */
		*w = MAX(*w + basew, minw);
		*h = MAX(*h + baseh, minh);
		if (maxw)
			*w = MIN(*w, maxw);
		if (maxh)
			*h = MIN(*h, maxh);
	}
	return *x != this->x || *y != this->y || *w != this->w || *h != this->h;
}

void
Client::resize(int x, int y, int w, int h, int interact)
{
	if (applysizehints(&x, &y, &w, &h, interact))
		resizeclient(x, y, w, h);
}

void
Client::showhide()
{
	// if (!c)
	// 	return;

    fprintf(stderr, "Trying to show %s tag:%d\n", name, tags);
	if (ISVISIBLE(this)) {
		if ((tags & SPTAGMASK) && isfloating) {
			x = mon->wx + (mon->ww / 2 - WIDTH(this) / 2);
			y = mon->wy + (mon->wh / 2 - HEIGHT(this) / 2);
		}
		if ((tags & SYSTRAYTAG)) {
			x = mon->wx + (mon->ww / 2 + mon->ww / 4);
			y =  1;
            fprintf(stderr, "Showing system tray: x %d y %d\n", x, y);
            XMoveWindow(dpy, win, x, y);
            fprintf(stderr, "Showing system tray: x %d y %d\n", x, y);
            resize(x, y, w, h, 0);
            snext->showhide();
		} else 
        {
            /* show clients top down */
            XMoveWindow(dpy, win, x, y);
            if ((!mon->lt[mon->sellt]->arrange || isfloating) 
                && !isfullscreen
                && !(tags & SYSTRAYTAG))
                resize(x, y, w, h, 0);
            snext->showhide();
        }
	} else {
		/* hide clients bottom up */
		snext->showhide();
		XMoveWindow(dpy, win, WIDTH(this) * -2, y);
	}
}

Atom
Client::getatomprop(Atom prop)
{
	int di;
	unsigned long dl;
	unsigned char *p = NULL;
	Atom da, atom = None;

	if (XGetWindowProperty(dpy, win, prop, 0L, sizeof atom, False, XA_ATOM,
		&da, &di, &dl, &dl, &p) == Success && p) {
		atom = *(Atom *)p;
		XFree(p);
	}
	return atom;
}

void
Client::configure()
{
	XConfigureEvent ce;

	ce.type = ConfigureNotify;
	ce.display = dpy;
	ce.event = win;
	ce.window = win;
	ce.x = x;
	ce.y = y;
	ce.width = w;
	ce.height = h;
	ce.border_width = bw;
	ce.above = None;
	ce.override_redirect = False;
	XSendEvent(dpy, win, False, StructureNotifyMask, (XEvent *)&ce);
}

void
Client::setclientstate(long state)
{
	long data[] = { state, None };

	XChangeProperty(dpy, win, wmatom[WMState], wmatom[WMState], 32,
		PropModeReplace, (unsigned char *)data, 2);
}


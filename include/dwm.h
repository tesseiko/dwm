#ifndef DWM_H
#define DWM_H



// other
//

#include "X.h"
#include "Xproto.h"
#include <sys/types.h>
#define BUTTONMASK              (ButtonPressMask|ButtonReleaseMask)
extern int enablegaps;
#define SPTAGMASK		(((1 << LENGTH(scratchpads))-1) << LENGTH(tags))
#define NUMTAGS			(LENGTH(tags) + LENGTH(scratchpads))
#define TAGMASK			((1 << NUMTAGS) - 1)

#include "Monitor.h"
#include "Client.h"
#define WIDTH(X)                ((X)->w + 2 * (X)->bw)
#define HEIGHT(X)               ((X)->h + 2 * (X)->bw)

#define TEXTW(X)                (drw_fontset_getwidth(drw, (X)) + lrpad)
#define CLEANMASK(mask)         (mask & ~(numlockmask|LockMask) & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))
#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]) || C->issticky)

typedef union {
	int i;
	int ui;
	float f;
	const void *v;
} Arg;

void arrange(Monitor *m);
void run(void);
void runAutostart(void);
Client *wintoclient(Window w);
void seturgent(Client *c, int urg);
int updategeom(void);
void updatebars(void);
void drawbars(void);
void drawbar(Monitor *m);
Client *swallowingclient(Window w);
void unmanage(Client *c, int destroyed);
void manage(Window w, XWindowAttributes *wa);
void setfocus(Client *c);
Monitor *recttomon(int x, int y, int w, int h);
void updatesizehints(Client *c);
void updatestatus(void);
void updatetitle(Client *c);
void updatewindowtype(Client *c);
void updatewmhints(Client *c);
void updatenumlockmask(void);
Client *termforwin(const Client *c);
pid_t winpid(Window w);
long getstate(Window w);
void sighup(int unused);
void sigterm(int unused);
void sigchld(int unused);
void copyvalidchars(char *text, char *rawtext);
Monitor *dirtomon(int dir);
int getrootptr(int *x, int *y);
void sendmon(Client *c, Monitor *m);
#ifndef __OpenBSD__
int getdwmblockspid(void);
#endif
void updatebarpos(Monitor *m);

Monitor *wintomon(Window w);
extern void (*handler[LASTEvent]) (XEvent *);


enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast }; /* default atoms */
/* enums */
enum { CurNormal, CurResize, CurMove, CurLast }; /* cursor */
enum { NetSupported, NetWMName, NetWMState, NetWMCheck,
       NetWMFullscreen, NetActiveWindow, NetWMWindowType,
       NetWMWindowTypeDialog, NetClientList, NetLast }; /* EWMH atoms */



void monocle(Monitor *m);

#endif // DWM_H


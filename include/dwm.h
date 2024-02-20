#ifndef DWM_H
#define DWM_H



// other
//

#include <sys/types.h>
#define BUTTONMASK              (ButtonPressMask|ButtonReleaseMask)
extern int enablegaps;
#define SPTAGMASK		(((1 << LENGTH(scratchpads))-1) << LENGTH(tags))
#define NUMTAGS			(LENGTH(tags) + LENGTH(scratchpads))
#define TAGMASK			((1 << NUMTAGS) - 1)

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

typedef struct Client Client;
typedef struct Monitor Monitor;

struct Client {
	char name[256];
	float mina, maxa;
	int x, y, w, h;
	int oldx, oldy, oldw, oldh;
	int basew, baseh, incw, inch, maxw, maxh, minw, minh;
	int bw, oldbw;
	unsigned int tags;
	int isfixed, isfloating, isurgent, 
		neverfocus, oldstate, isfullscreen, 
		isterminal, noswallow, issticky, isalwaysontop, isalwaysonbackground;
	pid_t pid;
	Client *next;
	Client *snext;
	Client *swallowing;
	Monitor *mon;
	Window win;
};

typedef struct {
	const char *symbol;
	void (*arrange)(Monitor *);
} Layout;

struct Monitor {
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


void arrange(Monitor *m);
Client *nexttiled(Client *c);
void resize(Client *c, int x, int y, int w, int h, int interact);
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
void detachstack(Client *c);
void detach(Client *c);
void attach(Client *c);
void attachstack(Client *c);
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
void pop(Client *);

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


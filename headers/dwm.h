#ifndef DWM_H
#define DWM_H

#include <X11/Xlib.h>
#include <stdlib.h>

// other
//

#include <X11/Xproto.h>
#define SPTAGMASK		(((1 << LENGTH(scratchpads))-1) << LENGTH(tags))

#define WIDTH(X)                ((X)->w + 2 * (X)->bw)
#define HEIGHT(X)               ((X)->h + 2 * (X)->bw)

typedef union {
	int i;
	unsigned int ui;
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

Monitor *selmon;

void arrange(Monitor *m);
Client *nexttiled(Client *c);
void resize(Client *c, int x, int y, int w, int h, int interact);

// config quick patches
int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
unsigned int gappih    = 20;       /* horiz inner gap between windows */
unsigned int gappiv    = 10;       /* vert inner gap between windows */
unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */

// for config
#include <X11/keysym.h>
#define SYSTRAYTAG              1 << 18
#define DOCKTAG                 1 << 19

#define LENGTH(X)               (sizeof X / sizeof X[0])

#define SPTAG(i)		((1 << LENGTH(tags)) << (i))
#define INC(X)                  ((X) + 2000)
#define GETINC(X)               ((X) - 2000)

enum { SchemeNorm, SchemeSel }; /* color schemes */

typedef struct {
	const char *class;
	const char *instance;
	const char *title;
	unsigned int tags;
	int isfloating;
	int issticky;
	int isterminal;
	int noswallow;
	int monitor;
} Rule;

void monocle(Monitor *m);
void spawn(const Arg *arg);
void togglescratch(const Arg *arg);
void view(const Arg *arg);
void toggleview(const Arg *arg);
void focusstack(const Arg *arg);
void pushstack(const Arg *arg);
void tag(const Arg *arg);
void toggletag(const Arg *arg);
void killclient(const Arg *arg);
void setlayout(const Arg *arg);
void incnmaster(const Arg *arg);
void togglesticky(const Arg *arg);
void togglefullscr(const Arg *arg);
void setmfact(const Arg *arg);
void togglebar(const Arg *arg);
void focusmon(const Arg *arg);
void tagmon(const Arg *arg);
void zoom(const Arg *arg);
void togglefloating(const Arg *arg);
void togglealwaysontop(const Arg *arg);
void togglealwaysonback(const Arg *arg);
void sigdwmblocks(const Arg *arg);
void movemouse(const Arg *arg);
void resizemouse(const Arg *arg);

/* Xresources preferences */
enum resource_type {
    STRING = 0,
    INTEGER = 1,
    FLOAT = 2
};


typedef struct {
	char *name;
	enum resource_type type;
	void *dst;
} ResourcePref;

enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */

typedef struct {
	unsigned int mod;
	KeySym keysym;
	void (*func)(const Arg *);
	const Arg arg;
} Key;

typedef struct {
	unsigned int click;
	unsigned int mask;
	unsigned int button;
	void (*func)(const Arg *arg);
	const Arg arg;
} Button;

#endif // DWM_H


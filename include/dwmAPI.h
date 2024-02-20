/*
 ==============================================================================
 
 dwmAPI.h
 Created: 15 Feb 2024 6:09:45pm
 Author: Manos Lefakis
 
 ==============================================================================
 */

// for config
#define SYSTRAYTAG              1 << 18
#define DOCKTAG                 1 << 19
#define INC(X)                  ((X) + 2000)
#define SPTAG(i)		((1 << 9) << (i))

void spawn(const Arg *arg);
void shiftview(const Arg *arg);
void shifttag(const Arg *arg);
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
int stackpos(const Arg *arg);
void quit(const Arg *arg);

typedef struct {
	unsigned int click;
	unsigned int mask;
	unsigned int button;
	void (*func)(const Arg *arg);
	const Arg arg;
} Button;


typedef struct {
	unsigned int mod;
	KeySym keysym;
	void (*func)(const Arg *);
	const Arg arg;
} Key;

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

typedef struct {
	const char *wm_class;
	const char *instance;
	const char *title;
	unsigned int tags;
	int isfloating;
	int issticky;
	int isterminal;
	int noswallow;
	int monitor;
} Rule;

enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */

enum { SchemeNorm, SchemeSel }; /* color schemes */


/*
 ==============================================================================
 
 vanitygaps.h
 Created: 14 Feb 2024 3:21:09am
 Author: Manos Lefakis
 
 ==============================================================================
 */

#ifndef VANITYGAPS_H
#define VANITYGAPS_H
/* Settings */
/* Key binding functions */
extern Monitor *selmon;
extern int smartgaps;        /* 1 means no outer gap when there is only one window */
extern unsigned int gappih;       /* horiz inner gap between windows */
extern unsigned int gappiv;       /* vert inner gap between windows */
extern unsigned int gappoh;       /* horiz outer gap between windows and screen edge */
extern unsigned int gappov;       /* vert outer gap between windows and screen edge */
void defaultgaps(const Arg *arg);
void incrgaps(const Arg *arg);
/* void incrigaps(const Arg *arg); */
/* void incrogaps(const Arg *arg); */
/* void incrohgaps(const Arg *arg); */
/* void incrovgaps(const Arg *arg); */
/* void incrihgaps(const Arg *arg); */
/* void incrivgaps(const Arg *arg); */
void togglegaps(const Arg *arg);

/* Layouts */
void bstack(Monitor *m);
void centeredmaster(Monitor *m);
void centeredfloatingmaster(Monitor *m);
void deck(Monitor *m);
void dwindle(Monitor *m);
void fibonacci(Monitor *m, int s);
void spiral(Monitor *m);
void tile(Monitor *);

/* Internals */
void getgaps(Monitor *m, int *oh, int *ov, int *ih, int *iv, unsigned int *nc);
void setgaps(int oh, int ov, int ih, int iv);

void setgaps(int oh, int ov, int ih, int iv);
void getgaps(Monitor *m, int *oh, int *ov, int *ih, int *iv, unsigned int *nc);
void getfacts(Monitor *m, int msize, int ssize, float *mf, float *sf, int *mr, int *sr);
void bstack(Monitor *m);
void centeredmaster(Monitor *m);
void centeredfloatingmaster(Monitor *m);
void deck(Monitor *m);
void fibonacci(Monitor *m, int s);
void dwindle(Monitor *m);
void spiral(Monitor *m);
void tile(Monitor *m);
#endif

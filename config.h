/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 30;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 30;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVuSansMNerdFontMono:size=9", "TwitterColorEmoji:pixelsize=14:antialias=true:autohint=true" };
static char termpgm[]               = "alacritty";
static char normbgcolor[]           = "#3c5182";
static char normbordercolor[]       = "#666666";
static char normfgcolor[]           = "#fafafa";
static char selfgcolor[]            = "#fafafa";
static char selbordercolor[]        = "#006996";
static char selbgcolor[]            = "#0f2045";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { termpgm, "-t", "spterm", NULL };
const char *spcmd2[] = { termpgm, "-t", "spcalc", "-e", "python", NULL };
const char *spcmd3[] = { termpgm, "-t", "sptrans", "-e", "trans", "-I", "ja:en", NULL };
const char *spcmd4[] = { termpgm, "-t", "spunits", "-e", "units", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",  spcmd1},
	{"spcalc",  spcmd2},
	{"sptrans", spcmd3},
	{"spunits", spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    instance   title          tags mask isfloat monitor float x,y,w,h */
	{ "Gimp",     NULL,    NULL,          1 << 8,   0,      -1,     -1,-1,-1,-1},
	{ termpgm,    NULL,    NULL,          0,        0,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "spterm",      SPTAG(0), 1,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "spcalc",      SPTAG(1), 1,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "sptrans",     SPTAG(2), 1,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "spunits",     SPTAG(3), 1,      -1,     -1,-1,-1,-1},
	{ "Firefox",  NULL,    NULL,          1 << 0,   0,       1,     -1,-1,-1,-1},
	{ "qutebrowser", NULL, NULL,          1 << 0,   0,       1,     -1,-1,-1,-1},
	{ "Chromium", NULL,    NULL,          1 << 0,   0,       1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "qute-editor", 0,        1,      -1,     -1,-1,-1,-1},
	{ "mgba",     NULL,    NULL,          0,        1,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "Graphics :)", 0,        1,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "fzf:",        0,        1,      -1,     -1,-1,-1,-1},
	{ NULL,       NULL,    "fzf: system", 0,        1,      -1,     1920-220,20,200,200},
};

/* layout(s) */
static const float mfact = 0.45;  /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;	  /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1			  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=", tile },	 /* Default: Master on left, slaves on right */
	{ "TTT", bstack }, /* Master on top, slaves on bottom */

	{ "H[]", deck },	  /* Master on left, slaves in monocle-like mode on right */
	{ "[M]", monocle }, /* All windows on top of eachother */

	{ "|M|", centeredmaster },		 /* Master in middle, slaves on sides */
	{ ">M>", centeredfloatingmaster }, /* Same but master floats */

	{ NULL, NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
	{ MODKEY,                           KEY, view,       { .ui = 1 << TAG } }, \
	{ MODKEY | ControlMask,             KEY, toggleview, { .ui = 1 << TAG } }, \
	{ MODKEY | ShiftMask,               KEY, tag,        { .ui = 1 << TAG } }, \
	{ MODKEY | ControlMask | ShiftMask, KEY, toggletag,  { .ui = 1 << TAG } },
#define STACKKEYS(MOD, ACTION) \
	{ MOD, XK_j, ACTION##stack, { .i = INC(+1) } }, \
	{ MOD, XK_k, ACTION##stack, { .i = INC(-1) } }, \
	{ MOD, XK_m, ACTION##stack, { .i = 0 } }, \

/* commands */
static const char *termcmd[] = { termpgm, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY, focus)
	STACKKEYS(MODKEY | ShiftMask, push)
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
	{ MODKEY,             XK_0, view, {.ui = ~0}},
	{ MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},

	{ MODKEY,             XK_Tab, view, {0}},
	{ MODKEY,             XK_x, killclient, {0}},
	{ MODKEY,             XK_o, incnmaster, {.i = +1}},
	{ MODKEY | ShiftMask, XK_o, incnmaster, {.i = -1}},
	{ MODKEY,             XK_a, togglegaps, {0}},
	{ MODKEY | ShiftMask, XK_a, defaultgaps, {0}},
	{ MODKEY,             XK_h, setmfact, {.f = -0.025}},
	{ MODKEY,             XK_l, setmfact, {.f = +0.025}},
	{ MODKEY | ShiftMask, XK_q, quit, {0}},
	{ MODKEY,             XK_Return, spawn, {.v = termcmd}},
	{ MODKEY,             XK_space, cyclelayout, {.ui = +1}},
	{ MODKEY | ShiftMask, XK_space, cyclelayout, {.ui = -1}},
	{ MODKEY | ShiftMask, XK_Return, togglescratch, {.ui = 0}},
	{ MODKEY,             XK_apostrophe, togglescratch, {.ui = 1}},
	{ MODKEY,             XK_t, togglescratch, {.ui = 2}},
	{ MODKEY | ShiftMask, XK_u, togglescratch, {.ui = 3}},

	{ MODKEY,             XK_equal, incrgaps, {.i = +3}},
	{ MODKEY,             XK_minus, incrgaps, {.i = -3}},
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,             XK_b, togglebar, {0}},
	{ MODKEY,             XK_Escape, focusmon, {.i = +1}},
	{ MODKEY,             XK_Left, tagmon, {.i = -1}},
	{ MODKEY,             XK_Right, tagmon, {.i = +1}},
	{ 0,                  XK_F13, xrdb, {.v = NULL}},
	{ MODKEY,             XK_F1, togglefloating, {0}},
	{ 0,                  XK_F11, togglefullscreen, {0}},
	{ MODKEY | ShiftMask | Mod1Mask | ControlMask, XK_F12, xrdb, {.v = NULL}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click      event mask   button   function      argument */
	{ ClkWinTitle,   0,         Button2, zoom,           { 0 } },
	{ ClkClientWin,  MODKEY,    Button1, movemouse,      { 0 } },
	{ ClkClientWin,  MODKEY,    Button2, togglefloating, { 0 } },
	{ ClkClientWin,  MODKEY,    Button3, resizemouse,    { 0 } },
	{ ClkClientWin,  MODKEY,    Button4, incrgaps,       { .i = +1 } },
	{ ClkClientWin,  MODKEY,    Button5, incrgaps,       { .i = -1 } },
	{ ClkTagBar,     0,         Button1, view,           { 0 } },
	{ ClkTagBar,     0,         Button3, toggleview,     { 0 } },
	{ ClkTagBar,     MODKEY,    Button1, tag,            { 0 } },
	{ ClkTagBar,     MODKEY,    Button3, toggletag,      { 0 } },
	{ ClkTagBar,     0,         Button4, shiftview,      { .i = -1 } },
	{ ClkTagBar,     0,         Button5, shiftview,      { .i = 1 } },
	{ ClkRootWin,    0,         Button2, togglebar,      { 0 } },
};

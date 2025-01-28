/* See LICENSE file for copyright and license details. */

/* Constants */
// #define TERMINAL "st"
// #define TERMCLASS "St"
#define TERMINAL "ghostty"
#define TERMCLASS "com.mitchellh.ghostty"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char normbgcolor[]     = "#232634";
static const char normbordercolor[] = "#303446";
static const char normfgcolor[]     = "#a5adce";
static const char selfgcolor[]      = "#303446";
static const char selbordercolor[]  = "#8caaee";
static const char selbgcolor[]      = "#8caaee";
static const char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

  // For ghostty terminal:
  // Follow GTK requirements (https://docs.gtk.org/gio/type_func.Application.id_is_valid.html) for --class name.
  const char *spcmd1[] = {TERMINAL, "--x11-instance-name=spterm", "--class=my.scratchpad", "--window-width=120", "--window-height=34", "--gtk-single-instance=false", NULL };
  const char *spcmd2[] = {TERMINAL, "--x11-instance-name=spcalc", "--class=my.scratchpad", "--window-width=50", "--window-height=20",  "--gtk-single-instance=false", "--font-size=17", "-e", "bc -lq", NULL };

  // For kitty terminal:
  // const char *spcmd1[] = {TERMINAL, "--name", "spterm", "-o", "remember_window_size=no", "-o", "initial_window_width=120c", "-o", "initial_window_height=34c", NULL };
  // const char *spcmd2[] = {TERMINAL, "--name", "spcalc", "-o", "initial_window_width=50c", "-o", "initial_window_height=20c" , "-e", "bc", "-lq", NULL };

  // For st terminal:
  // const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
  // const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
  // const char *spcmd3[] = {TERMINAL, "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
  // const char *spcmd4[] = {"keepassxc", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	//  {"spranger",    spcmd3},
	// {"keepassxc",   spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
  /* class     instance     title           tags mask  isfloating  isterminal  noswallow  monitor */
  { "Gimp",    NULL,        NULL,           0,         1,          0,           0,        -1 },
  { "Firefox", NULL,        NULL,           1 << 8,    0,          0,          -1,        -1 },
  { TERMCLASS, NULL,        NULL,           0,         0,          1,           0,        -1 },
  { NULL,      NULL,        "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
  { NULL,      "spterm",    NULL,           SPTAG(0),  1,          1,           0,        -1 },
  { NULL,      "spcalc",    NULL,           SPTAG(1),  1,          1,           0,        -1 },
  /* { TERMCLASS, "spfm",      NULL,           SPTAG(1),  1,          1,           0,        -1 }, */
  /* { TERMCLASS, "keepassxc", NULL,           SPTAG(2),  0,          1,           0,        -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
  { "[]=",      tile },                   /* First entry is default. Master on left, slaves on right */
  { "[M]",      monocle },                /* All windows on top of eachother */
  { "[@]",      spiral },                 /* Fibonacci spiral */
  { "[\\]",     dwindle },                /* Decreasing in size right and leftward */
  { "H[]",      deck },                   /* Master on left, slaves in monocle-like mode on right */
  { "TTT",      bstack },                 /* Master on top, slaves on bottom */
  { "===",      bstackhoriz },
  { "HHH",      grid },
  { "###",      nrowgrid },
  { "---",      horizgrid },
  { ":::",      gaplessgrid },
  { "|M|",      centeredmaster },         /* Master in middle, slaves on sides */
  { ">M>",      centeredfloatingmaster }, /* Same but master floats */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
  { MOD, XK_v,     ACTION##stack, {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
  STACKKEYS(MODKEY,                          focus)
  STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },   /* Spawn terminal */
  { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },               /* Close window */
  // { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } },
  { MODKEY,                       XK_b,      togglebar,      {0} },               /* Toggle status bar (may also middle click on desctop) */

  // WINDOW LAYOUTS
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },  /* tile */
  { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} },  /* bstack */
  { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },  /* spiral */
  { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },  /* dwindle */
  { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },  /* deck */
  { MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[1]} },  /* monocle */
  { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[11]} }, /* centeredmaster */
  { MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[12]} }, /* centeredfloatingmaster */
  { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[13]} }, /* floating (AKA normie) mode */
  { MODKEY,                       XK_f,      togglefullscr,  {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },           /* Make window float (move and resize with Mod+left/right click) */
  { MODKEY,                       XK_s,      togglesticky,   {0} },
  { MODKEY,                       XK_space,  zoom,           {0} },           /* Make selected window the master (or switch master with 2nd) */
  { MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },    /* Increase the number of master windows */
  { MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },    /* Decrease the number of master windows */
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },  /* Change width of master window */
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

  //
  // TAGS/WORKSPACES
  //
  /* Go to that number tag */
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  { MODKEY,                       XK_g,         shiftview,   { .i = -1 } }, /* Go to left tag (hold shift to send window there) */
  { MODKEY,                       XK_semicolon, shiftview,   { .i = 1 } },  /* Go to right tag (hold shift to send window there) */
  { MODKEY,                       XK_Tab,       view,        {0} }, /* Go to previous tag (may also use \ for Tab) */
  { MODKEY,                       XK_backslash, view,        {0} },

  /* Go to another display */
  { MODKEY,                       XK_Left,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_Right, focusmon,       {.i = +1 } },
  /* Move window to another display */
  { MODKEY|ShiftMask,             XK_Left,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_Right, tagmon,         {.i = +1 } },

  //
  // GAPS
  //
  { MODKEY|ShiftMask,             XK_apostrophe,  togglesmartgaps,  {0} }, /* Outer gaps disabled when only one client */
  { MODKEY,                       XK_a,           togglegaps,       {0} }, /* Toggle gaps */
  { MODKEY|ShiftMask,             XK_a,           defaultgaps,      {0} }, /* Gaps return to default values (may also hold MOD and middle click) */
  { MODKEY,                       XK_z,           incrgaps,         {.i = +3 } }, /* Increase/decrease gaps (may also hold Mod and scroll mouse) */
  { MODKEY,                       XK_x,           incrgaps,         {.i = -3 } },

  // { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
  // { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
  // { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
  // { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
  // { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
  // { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
  // { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
  // { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
  // { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
  // { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
  // { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
  // { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },


  //
  // AUDIO
  //
  { MODKEY,             XK_m,             spawn,    {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
  { MODKEY,             XK_comma,         spawn,    {.v = (const char*[]){ "mpc", "prev", NULL } } },               /* Previous track */
  { MODKEY|ShiftMask,   XK_comma,         spawn,    {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },         /* Restart track */
  { MODKEY,             XK_period,        spawn,    {.v = (const char*[]){ "mpc", "next", NULL } } },               /* Next track */
  { MODKEY|ShiftMask,   XK_period,        spawn,    {.v = (const char*[]){ "mpc", "repeat", NULL } } },             /* Toggle playlist looping */
  { MODKEY,             XK_p,             spawn,    {.v = (const char*[]){ "mpc", "toggle", NULL } } },             /* Toggle pause */
  { MODKEY|ShiftMask,   XK_p,             spawn,    SHCMD("mpc pause; pauseallmpv") },                              /* Force pause music player daemon and all mpv videos */
  { MODKEY,             XK_bracketleft,   spawn,    {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },        /* Back 10 seconds (holding shift moves by one minute) */
  { MODKEY|ShiftMask,   XK_bracketleft,   spawn,    {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
  { MODKEY,             XK_bracketright,  spawn,    {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },        /* Forward 10 seconds (holding shift moves by one minute) */
  { MODKEY|ShiftMask,   XK_bracketright,  spawn,    {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
  { MODKEY|ShiftMask,   XK_m,             spawn,    SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") }, /* Mute all audio */
  { MODKEY,             XK_minus,         spawn,    SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },  /* Decrease volume (holding shift increases amount) */
  { MODKEY|ShiftMask,   XK_minus,         spawn,    SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
  { MODKEY,             XK_equal,         spawn,    SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },  /* Increase volume (holding shift increases amount) */
  { MODKEY|ShiftMask,   XK_equal,         spawn,    SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },

  //
  // RECORDING
  //
  { 0,                  XK_Print,       spawn,    SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
  { ShiftMask,          XK_Print,       spawn,    {.v = (const char*[]){ "maimpick", NULL } } },
  { MODKEY,             XK_Print,       spawn,    {.v = (const char*[]){ "dmenurecord", NULL } } },
  { MODKEY|ShiftMask,   XK_Print,       spawn,    {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
  { MODKEY,             XK_Delete,      spawn,    {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
  { MODKEY,             XK_Scroll_Lock, spawn,    SHCMD("killall screenkey || screenkey &") },

  //
  // SYSTEM
  //
  { MODKEY,                      XK_grave,      spawn,  {.v = (const char*[]){ "dmenuunicode", NULL } } },
  { MODKEY,                      XK_BackSpace,  spawn,       {.v = (const char*[]){ "sysact", NULL } } },
  { MODKEY|ShiftMask,            XK_BackSpace,  spawn,       {.v = (const char*[]){ "sysact", NULL } } },
  // { MODKEY,                      XK_Insert,     spawn,    SHCMD("xdotool type $(grep -v '^#' ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
  { MODKEY,                      XK_Insert,     spawn,    SHCMD("clipmenu") },
  // { MODKEY,                     XK_F1,    spawn,    SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
  { MODKEY,                     XK_F1,    spawn,    SHCMD("zathura /usr/local/share/dwm/dwm.pdf") },
  // { MODKEY,                     XK_F2,    spawn,    {.v = (const char*[]){ "tutorialvids", NULL } } },
  { MODKEY,                     XK_F3,    spawn,    {.v = (const char*[]){ "displayselect", NULL } } },
  { MODKEY,                     XK_F4,    spawn,    SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
  // { MODKEY,                     XK_F5,    xrdb,     {.v = NULL } },
  // { MODKEY,                     XK_F6,    spawn,    {.v = (const char*[]){ "torwrap", NULL } } },
  // { MODKEY,                     XK_F7,    spawn,    {.v = (const char*[]){ "td-toggle", NULL } } },
  // { MODKEY,                     XK_F8,    spawn,    {.v = (const char*[]){ "mailsync", NULL } } },
  { MODKEY,                     XK_F9,    spawn,    {.v = (const char*[]){ "mounter", NULL } } },
  { MODKEY,                     XK_F10,   spawn,    {.v = (const char*[]){ "unmounter", NULL } } },
  { MODKEY,                     XK_F11,   spawn,    SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
  // { MODKEY,                     XK_F12,   spawn,    SHCMD("remaps") },


  //
  // BASIC PROGRAMS
  //
  { MODKEY,             XK_w,   spawn,    {.v = (const char*[]){ BROWSER, NULL } } },
  { MODKEY|ShiftMask,   XK_w,   spawn,    {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
  { MODKEY,             XK_e,   spawn,    SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
  { MODKEY|ShiftMask,   XK_e,   spawn,    SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
  { MODKEY,             XK_r,   spawn,    {.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
  { MODKEY|ShiftMask,   XK_r,   spawn,    {.v = (const char*[]){ TERMINAL, "-e", "btop", NULL } } },
  { MODKEY,             XK_n,   spawn,    {.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
  { MODKEY|ShiftMask,   XK_n,   spawn,    SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
  { MODKEY|ShiftMask,   XK_d,   spawn,    {.v = (const char*[]){ "passmenu", NULL } } },
  { MODKEY|ShiftMask,   XK_Return,        togglescratch,  {.ui = 0} },
  { MODKEY,             XK_apostrophe,    togglescratch,  {.ui = 1} },

  //
  //  XF86Keys
  //
  { 0, XF86XK_AudioMute,          spawn,    SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioRaiseVolume,   spawn,    SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioLowerVolume,   spawn,    SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioPrev,          spawn,    {.v = (const char*[]){ "mpc", "prev", NULL } } },
  { 0, XF86XK_AudioNext,          spawn,    {.v = (const char*[]){ "mpc", "next", NULL } } },
  { 0, XF86XK_AudioPause,         spawn,    {.v = (const char*[]){ "mpc", "pause", NULL } } },
  { 0, XF86XK_AudioPlay,          spawn,    {.v = (const char*[]){ "mpc", "play", NULL } } },
  { 0, XF86XK_AudioStop,          spawn,    {.v = (const char*[]){ "mpc", "stop", NULL } } },
  { 0, XF86XK_AudioRewind,        spawn,    {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
  { 0, XF86XK_AudioForward,       spawn,    {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
  { 0, XF86XK_AudioMedia,         spawn,    {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
  { 0, XF86XK_AudioMicMute,       spawn,    SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
  /* { 0, XF86XK_PowerOff,        spawn,    {.v = (const char*[]){ "sysact", NULL } } }, */
  { 0, XF86XK_Calculator,         spawn,    {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
  { 0, XF86XK_Sleep,              spawn,    {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
  { 0, XF86XK_WWW,                spawn,    {.v = (const char*[]){ BROWSER, NULL } } },
  { 0, XF86XK_DOS,                spawn,    {.v = termcmd } },
  { 0, XF86XK_ScreenSaver,        spawn,    SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
  { 0, XF86XK_TaskPane,           spawn,    {.v = (const char*[]){ TERMINAL, "-e", "btop", NULL } } },
  { 0, XF86XK_Mail,               spawn,    SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
  { 0, XF86XK_MyComputer,         spawn,    {.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
  /* { 0, XF86XK_Battery,         spawn,    SHCMD("") }, */
  { 0, XF86XK_Launch1,            spawn,    {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
  { 0, XF86XK_TouchpadToggle,     spawn,    SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
  { 0, XF86XK_TouchpadOff,        spawn,    {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
  { 0, XF86XK_TouchpadOn,         spawn,    {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
  { 0, XF86XK_MonBrightnessUp,    spawn,    {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
  { 0, XF86XK_MonBrightnessDown,  spawn,    {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
  { ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkClientWin,         MODKEY,         Button4,        incrgaps,       {.i = +1} },
  { ClkClientWin,         MODKEY,         Button5,        incrgaps,       {.i = -1} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
  { ClkTagBar,            0,              Button4,        shiftview,      {.i = -1} },
  { ClkTagBar,            0,              Button5,        shiftview,      {.i = 1} },
  { ClkRootWin,           0,              Button2,        togglebar,      {0} },
};


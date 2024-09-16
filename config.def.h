#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
	((hex >> 16) & 0xFF) / 255.0f, \
	((hex >> 8) & 0xFF) / 255.0f, \
	(hex & 0xFF) / 255.0f }
static const int sloppyfocus               = 1;
static const int bypass_surface_visibility = 0;
static const int smartgaps                 = 0;
static const int monoclegaps               = 0;
static const unsigned int borderpx         = 1;
static const unsigned int gappih           = 10;
static const unsigned int gappiv           = 10;
static const unsigned int gappoh           = 10;
static const unsigned int gappov           = 10;
static const float rootcolor[]             = COLOR(0x222222ff);
static const float bordercolor[]           = COLOR(0x444444ff);
static const float focuscolor[]            = COLOR(0x005577ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f};

#define TAGCOUNT (9)

static int log_level = WLR_ERROR;

static const char *const autostart[] = {
	"wbg", "$HOME/wall/anime_landscape.jpg", NULL,
	"foot", NULL,
	"wlr-randr", "--output", "Virtual-1", "--mode", "1920x1080", NULL,
	NULL
};

static const Rule rules[] = {
	/* app_id            title       tags mask  isfloating   isterm  noswallow  monitor */
	{ "Chromium",         NULL,       1 << 8,       0,          0,      0,         -1 }, /* Start on ONLY tag "9" */
	{ "foot",             NULL,       0,            0,          1,      1,         -1 }, /* make foot swallow clients that are not foot */
};

static const Layout layouts[] = {
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	   { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	   */
	/* defaults */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

static const struct xkb_rule_names xkb_rules = {
	.layout = "fr",
	.options = "caps:escape",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_ALT

#define TAGKEYS(KEY,SKEY,TAG) \
{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char *termcmd[] = { "foot", NULL };
static const char *menucmd[] = { "dmenu-wl_run", "-fn", "terminus", "-nb", "#080808", "-nf", "#f9f5d7", "-sb", "#202020", "-sf", "#f9f5d7", NULL };

static const Key keys[] = {
	/* modifier                  key                 function        argument */

	{ MODKEY|WLR_MODIFIER_SHIFT,						XKB_KEY_Q,          restartdwl,			{0} },
	{ MODKEY,                    						XKB_KEY_p,          spawn,          	{.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_Return,     spawn,          	{.v = termcmd} },
	{ MODKEY,                    						XKB_KEY_k,          focusstack,     	{.i = +1} },
	{ MODKEY,                    						XKB_KEY_l,          focusstack,     	{.i = -1} },
	{ MODKEY,                    						XKB_KEY_i,          incnmaster,     	{.i = +1} },
	{ MODKEY,                    						XKB_KEY_o,          incnmaster,     	{.i = -1} },
	{ MODKEY,                    						XKB_KEY_j,          setmfact,       	{.f = -0.05f} },
	{ MODKEY,                    						XKB_KEY_m,          setmfact,       	{.f = +0.05f} },
	{ MODKEY,                    						XKB_KEY_Return,     zoom,           	{0} },
	{ MODKEY,                    						XKB_KEY_Tab,        view,           	{0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_C,          killclient,     	{0} },
	{ MODKEY,                    						XKB_KEY_t,          setlayout,      	{.v = &layouts[0]} },
	{ MODKEY,                    						XKB_KEY_f,          setlayout,      	{.v = &layouts[1]} },
	{ MODKEY,                    						XKB_KEY_d,          setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,                    						XKB_KEY_space,      setlayout,      	{0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_space,      togglefloating, 	{0} },
	{ MODKEY,                    						XKB_KEY_e,          togglefullscreen,	{0} },
	{ MODKEY,                    						XKB_KEY_0,          view,				{.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_parenright, tag,            	{.ui = ~0} },
	{ MODKEY,                    						XKB_KEY_comma,      focusmon,       	{.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    						XKB_KEY_period,     focusmon,       	{.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_less,       tagmon,         	{.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_greater,    tagmon,         	{.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_LOGO,  						XKB_KEY_h,          incgaps,			{.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  						XKB_KEY_l,          incgaps,			{.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,		XKB_KEY_H,			incogaps,			{.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,		XKB_KEY_L,			incogaps,			{.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL,    	XKB_KEY_h,			incigaps,     	 	{.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL,    	XKB_KEY_l,			incigaps,     	 	{.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,							XKB_KEY_0,			togglegaps,			{0} },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,   	XKB_KEY_parenright, defaultgaps,		{0} },
	{ MODKEY,											XKB_KEY_y,          incihgaps,			{.i = +1 } },
	{ MODKEY,                    						XKB_KEY_o,          incihgaps,     		{.i = -1 } },
	{ MODKEY|WLR_MODIFIER_CTRL,  						XKB_KEY_y,          incivgaps,     		{.i = +1 } },
	{ MODKEY|WLR_MODIFIER_CTRL,  						XKB_KEY_o,          incivgaps,     		{.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  						XKB_KEY_y,          incohgaps,     		{.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  						XKB_KEY_o,          incohgaps,     		{.i = -1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_Y,          incovgaps,     		{.i = +1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, 						XKB_KEY_O,          incovgaps,     		{.i = -1 } },
	TAGKEYS(          XKB_KEY_1,						XKB_KEY_exclam,										0),
	TAGKEYS(          XKB_KEY_2, 						XKB_KEY_at,                        				 	1),
	TAGKEYS(          XKB_KEY_3, 						XKB_KEY_numbersign,                				 	2),
	TAGKEYS(          XKB_KEY_4, 						XKB_KEY_dollar,                    				 	3),
	TAGKEYS(          XKB_KEY_5, 						XKB_KEY_percent,                   				 	4),
	TAGKEYS(          XKB_KEY_6, 						XKB_KEY_asciicircum,               				 	5),
	TAGKEYS(          XKB_KEY_7, 						XKB_KEY_ampersand,                 				 	6),
	TAGKEYS(          XKB_KEY_8, 						XKB_KEY_asterisk,                  				 	7),
	TAGKEYS(          XKB_KEY_9, 						XKB_KEY_parenleft,                 				 	8),

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};

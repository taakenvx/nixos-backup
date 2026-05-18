#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }

/* appearance */
static const int sloppyfocus               = 1;
static const int bypass_surface_visibility = 0;
static const int gappih = 8;
static const int gappiv = 8;
static const int gappoh = 8;
static const int gappov = 8;
static const int smartgaps = 0;
static const int monoclegaps = 0;
static const unsigned int borderpx         = 1;
static const float rootcolor[]             = COLOR(0x141414ff);
static const float bordercolor[]           = COLOR(0x2a2a2aff);
static const float focuscolor[]            = COLOR(0xf6f6f6ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f};

/* tagging */
#define TAGCOUNT (5)

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id          title  tags mask  isfloating  monitor */
	{ "brave-browser", NULL,  1 << 1,   0,          -1 },
	{ "discord",       NULL,  1 << 2,   0,          -1 },
	{ "Spotify",       NULL,  1 << 4,   0,          -1 },
	{ "pavucontrol",   NULL,  0,        1,          -1 },
	{ "nautilus",      NULL,  0,        0,          -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	{ "[]=", tile    },
	{ "><>", NULL    },
	{ "[M]", monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	{ NULL, 0.55f, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.layout  = "us,br",
	.variant = ",abnt2",
	.options = "grp:alt_shift_toggle",
};

static const int repeat_rate  = 25;
static const int repeat_delay = 600;

/* trackpad */
static const int tap_to_click            = 1;
static const int tap_and_drag            = 1;
static const int drag_lock               = 1;
static const int natural_scrolling       = 0;
static const int disable_while_typing    = 1;
static const int left_handed             = 0;
static const int middle_button_emulation = 0;
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method   = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,  view,       {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,  toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, SKEY, toggletag, {.ui = 1 << TAG} }

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]      = { "foot", NULL };
static const char *wallcmd[]      = { "/home/obeskrov/.local/bin/wallpaper-select", NULL };
static const char *menucmd[]      = { "bemenu-run", "--tb", "#2a1018", "--tf", "#b08090", "--fb", "#2a1018", "--ff", "#f0e8ec", "--nb", "#2a1018", "--nf", "#b08090", "--hb", "#b08090", "--hf", "#2a1018", "--fn", "Noto Serif 12", NULL };
static const char *browsercmd[]   = { "brave", NULL };
static const char *filescmd[]     = { "thunar", NULL };
static const char *pavucmd[]      = { "pavucontrol", NULL };
static const char *discordcmd[]   = { "discord", NULL };
static const char *spotifycmd[]   = { "spotify", NULL };
static const char *sobercmd[]     = { "flatpak", "run", "org.vinegarhq.Sober", NULL };
static const char *volup[]        = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *voldown[]      = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *voltoggle[]    = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char *briup[]        = { "brightnessctl", "set", "5%+", NULL };
static const char *bridown[]      = { "brightnessctl", "set", "5%-", NULL };
static const char *mediaplay[]    = { "playerctl", "play-pause", NULL };
static const char *medianext[]    = { "playerctl", "next", NULL };
static const char *mediaprev[]    = { "playerctl", "previous", NULL };
static const char *printswappy[]  = { "/home/obeskrov/.local/bin/screenshot-swappy", NULL };

static const Key keys[] = {
	/* modifier                            key                               function          argument */
	{ MODKEY,                              XKB_KEY_Return,                   spawn,            {.v = termcmd} },
	{ MODKEY,                              XKB_KEY_d,                        spawn,            {.v = menucmd} },
	{ MODKEY,                              XKB_KEY_w,                        spawn,            {.v = wallcmd} },
	{ MODKEY,                              XKB_KEY_b,                        spawn,            {.v = browsercmd} },
	{ MODKEY,                              XKB_KEY_e,                        spawn,            {.v = filescmd} },
	{ MODKEY,                              XKB_KEY_v,                        spawn,            {.v = pavucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_D,                        spawn,            {.v = discordcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_S,                        spawn,            {.v = spotifycmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_X,                        spawn,            {.v = sobercmd} },
	/* print */
	{ MODKEY|WLR_MODIFIER_CTRL,            XKB_KEY_s,                        spawn,            {.v = printswappy} },
	/* volume */
	{ 0, XKB_KEY_XF86AudioRaiseVolume,                                        spawn,            {.v = volup} },
	{ 0, XKB_KEY_XF86AudioLowerVolume,                                        spawn,            {.v = voldown} },
	{ 0, XKB_KEY_XF86AudioMute,                                               spawn,            {.v = voltoggle} },
	/* brilho */
	{ 0, XKB_KEY_XF86MonBrightnessUp,                                         spawn,            {.v = briup} },
	{ 0, XKB_KEY_XF86MonBrightnessDown,                                       spawn,            {.v = bridown} },
	/* midia */
	{ 0, XKB_KEY_XF86AudioPlay,                                               spawn,            {.v = mediaplay} },
	{ 0, XKB_KEY_XF86AudioNext,                                               spawn,            {.v = medianext} },
	{ 0, XKB_KEY_XF86AudioPrev,                                               spawn,            {.v = mediaprev} },
	/* WM */
	{ MODKEY,                              XKB_KEY_q,                        killclient,       {0} },
	{ MODKEY,                              XKB_KEY_i,                        togglebar,        {0} },
	{ MODKEY,                              XKB_KEY_j,                        focusstack,       {.i = +1} },
	{ MODKEY,                              XKB_KEY_k,                        focusstack,       {.i = -1} },
	{ MODKEY,                              XKB_KEY_h,                        setmfact,         {.f = -0.05f} },
	{ MODKEY,                              XKB_KEY_l,                        setmfact,         {.f = +0.05f} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_space,                    togglefloating,   {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_F,                        togglefullscreen, {0} },
	{ MODKEY,                              XKB_KEY_t,                        setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                              XKB_KEY_f,                        setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                              XKB_KEY_m,                        setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                              XKB_KEY_Tab,                      view,             {0} },
	{ MODKEY,                              XKB_KEY_0,                        view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_parenright,               tag,              {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,           XKB_KEY_Q,                        quit,             {0} },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,  XKB_KEY_Terminate_Server,         quit,             {0} },
	TAGKEYS(XKB_KEY_1, XKB_KEY_exclam,     0),
	TAGKEYS(XKB_KEY_2, XKB_KEY_at,         1),
	TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign, 2),
	TAGKEYS(XKB_KEY_4, XKB_KEY_dollar,     3),
	TAGKEYS(XKB_KEY_5, XKB_KEY_percent,    4),
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};

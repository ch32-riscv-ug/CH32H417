
#include <stdint.h>
#include <stdio.h>

#include "wvui.h"
#include "lcd.h"
#include "GT9xx.h"

extern const wvui_font_t wvui_font_mont14;

#define PAGES_TOTAL 3u
#define C_TEXT    WVUI_RGB565(38, 46, 58)
#define C_DIM     WVUI_RGB565(112, 124, 140)
#define C_CARD    WVUI_RGB565(255, 255, 255)
#define C_BORDER  WVUI_RGB565(212, 220, 231)
#define C_DIV     WVUI_RGB565(204, 214, 227)
#define C_ACCENT  WVUI_RGB565(0, 150, 118)
#define C_WARM    WVUI_RGB565(226, 126, 28)
#define C_COOL    WVUI_RGB565(38, 104, 208)
#define C_TRACK   WVUI_RGB565(226, 232, 240)

enum
{
    P_ID_TITLE = 1,
    P_ID_CLOCK,
    P_ID_DIVIDER,
    P_ID_NAV_BOX,
    P_ID_NAV_DASH,
    P_ID_NAV_CTRL,
    P_ID_NAV_INFO,

    P_ID_CARD_L,
    P_ID_GAUGE,
    P_ID_GAUGE_VAL,
    P_ID_CARD_R,
    P_ID_SEG,
    P_ID_SIGNAL,
    P_ID_CHART,
    P_ID_CARD_B,
    P_ID_RING1,
    P_ID_RING2,
    P_ID_RING3,
    P_ID_PLANET,
    P_ID_STATE,
    P_ID_HEART,

    P_ID_CARD_1,
    P_ID_BRIGHT_L,
    P_ID_BRIGHT_V,
    P_ID_SLIDER,
    P_ID_CARD_2,
    P_ID_GAIN_L,
    P_ID_STEPPER,
    P_ID_GAIN_V,
    P_ID_CARD_3,
    P_ID_AUTO_L,
    P_ID_TOGGLE,
    P_ID_AUTO_V,
    P_ID_PROGRESS,
    P_ID_MSG,
    P_ID_APPLY,

    P_ID_LIST_CARD,
    P_ID_LIST,
    P_ID_INFO_1,
    P_ID_INFO_2,
    P_ID_INFO_4,
    P_ID_RESET
};

typedef struct
{
    uint8_t bright;
    int32_t gain;
    uint8_t auto_on;
    uint32_t boost_until;
    uint32_t msg_until;
    uint32_t ms;
    uint8_t page;
} pages_state_t;

static pages_state_t s_st;
static int32_t s_last_load = -1;

static char s_clock_text[16];
static char s_bright_text[8];
static char s_gain_text[8];
static char s_uptime_text[28];
static char s_load_text[28];
static char s_dash_text[28];
static char s_chip_text[32];

static uint8_t s_chart_samples[128];

static const int16_t s_sin[64] = {
       0,  100,  200,  297,  392,  483,  569,  650,
     724,  792,  851,  903,  946,  980, 1004, 1019,
    1024, 1019, 1004,  980,  946,  903,  851,  792,
     724,  650,  569,  483,  392,  297,  200,  100,
       0, -100, -200, -297, -392, -483, -569, -650,
    -724, -792, -851, -903, -946, -980,-1004,-1019,
   -1024,-1019,-1004, -980, -946, -903, -851, -792,
    -724, -650, -569, -483, -392, -297, -200, -100
};

static const char *const s_info_items[] = {
    "chip    ch32h417qeu6",
    "lcd     st7789 320x240",
    "bus     spi2 dma 16bit",
    "pfb     320x8 rgb565",
    "font    mont14 4bpp",
    "pages   3 dock tabs"
};

static void dash_enter(const wvui_page_t *self);
static void dash_tick(const wvui_page_t *self);
static void ctrl_enter(const wvui_page_t *self);
static void ctrl_tick(const wvui_page_t *self);
static void info_enter(const wvui_page_t *self);
static void info_tick(const wvui_page_t *self);

static const wvui_widget_desc_t s_dash_descs[] = {
    { WVUI_TYPE_BOX,      P_ID_CARD_L,         8,  30, 148, 112 },
    { WVUI_TYPE_BOX,      P_ID_CARD_R,       164,  30, 148, 112 },
    { WVUI_TYPE_BOX,      P_ID_CARD_B,         8, 148, 304,  50 },

    { WVUI_TYPE_GAUGE,    P_ID_GAUGE,         40,  34,  84,  84 },
    { WVUI_TYPE_LABEL,    P_ID_GAUGE_VAL,     46, 120,  72,  16 },

    { WVUI_TYPE_SEGDISP,  P_ID_SEG,          180,  38, 116,  26 },
    { WVUI_TYPE_LABEL,    P_ID_SIGNAL,       178,  70, 120,  14 },
    { WVUI_TYPE_CHART,    P_ID_CHART,        172,  84, 128,  50 },

    { WVUI_TYPE_ARC,      P_ID_RING1,         14, 150,  46,  46 },
    { WVUI_TYPE_ARC,      P_ID_RING2,         20, 156,  34,  34 },
    { WVUI_TYPE_ARC,      P_ID_RING3,         26, 162,  22,  22 },
    { WVUI_TYPE_BOX,      P_ID_PLANET,        33, 169,   8,   8 },
    { WVUI_TYPE_LABEL,    P_ID_STATE,         74, 154, 202,  18 },
    { WVUI_TYPE_INDICATOR,P_ID_HEART,        286, 168,  10,  10 },

    { WVUI_TYPE_LABEL,    P_ID_TITLE,         10,   4, 160,  18 },
    { WVUI_TYPE_LABEL,    P_ID_CLOCK,        170,   4, 140,  18 },
    { WVUI_TYPE_LINE,     P_ID_DIVIDER,        8,  24, 304,   1 },

    { WVUI_TYPE_BOX,      P_ID_NAV_BOX,        6, 204, 308,  32 },
    { WVUI_TYPE_BTN,      P_ID_NAV_DASH,      12, 208,  96,  24 },
    { WVUI_TYPE_BTN,      P_ID_NAV_CTRL,     112, 208,  96,  24 },
    { WVUI_TYPE_BTN,      P_ID_NAV_INFO,     212, 208,  96,  24 }
};

static const wvui_widget_desc_t s_ctrl_descs[] = {
    { WVUI_TYPE_BOX,      P_ID_CARD_1,         8,  30, 304,  58 },
    { WVUI_TYPE_LABEL,    P_ID_BRIGHT_L,      18,  36,  80,  16 },
    { WVUI_TYPE_LABEL,    P_ID_BRIGHT_V,     200,  36, 100,  16 },
    { WVUI_TYPE_SLIDER,   P_ID_SLIDER,        18,  58, 284,  18 },

    { WVUI_TYPE_BOX,      P_ID_CARD_2,         8,  94, 148,  54 },
    { WVUI_TYPE_LABEL,    P_ID_GAIN_L,        18,  98,  80,  16 },
    { WVUI_TYPE_STEPPER,  P_ID_STEPPER,       18, 118,  60,  24 },
    { WVUI_TYPE_LABEL,    P_ID_GAIN_V,        84, 122,  62,  16 },

    { WVUI_TYPE_BOX,      P_ID_CARD_3,       164,  94, 148,  54 },
    { WVUI_TYPE_LABEL,    P_ID_AUTO_L,       174,  98,  80,  16 },
    { WVUI_TYPE_TOGGLE,   P_ID_TOGGLE,       174, 118,  48,  22 },
    { WVUI_TYPE_LABEL,    P_ID_AUTO_V,       232, 120,  70,  16 },

    { WVUI_TYPE_PROGRESS, P_ID_PROGRESS,      18, 156, 284,  12 },
    { WVUI_TYPE_LABEL,    P_ID_MSG,            8, 178, 130,  16 },
    { WVUI_TYPE_BTN,      P_ID_APPLY,        170, 172, 132,  28 },

    { WVUI_TYPE_LABEL,    P_ID_TITLE,         10,   4, 160,  18 },
    { WVUI_TYPE_LABEL,    P_ID_CLOCK,        170,   4, 140,  18 },
    { WVUI_TYPE_LINE,     P_ID_DIVIDER,        8,  24, 304,   1 },

    { WVUI_TYPE_BOX,      P_ID_NAV_BOX,        6, 204, 308,  32 },
    { WVUI_TYPE_BTN,      P_ID_NAV_DASH,      12, 208,  96,  24 },
    { WVUI_TYPE_BTN,      P_ID_NAV_CTRL,     112, 208,  96,  24 },
    { WVUI_TYPE_BTN,      P_ID_NAV_INFO,     212, 208,  96,  24 }
};

static const wvui_widget_desc_t s_info_descs[] = {
    { WVUI_TYPE_BOX,      P_ID_LIST_CARD,      8,  30, 304,  78 },
    { WVUI_TYPE_LIST,     P_ID_LIST,          14,  34, 292,  70 },
    { WVUI_TYPE_LABEL,    P_ID_INFO_1,        12, 112, 300,  16 },
    { WVUI_TYPE_LABEL,    P_ID_INFO_2,        12, 130, 300,  16 },
    { WVUI_TYPE_LABEL,    P_ID_INFO_4,        12, 148, 190,  16 },
    { WVUI_TYPE_BTN,      P_ID_RESET,        210, 156, 100,  26 },

    { WVUI_TYPE_LABEL,    P_ID_TITLE,         10,   4, 160,  18 },
    { WVUI_TYPE_LABEL,    P_ID_CLOCK,        170,   4, 140,  18 },
    { WVUI_TYPE_LINE,     P_ID_DIVIDER,        8,  24, 304,   1 },

    { WVUI_TYPE_BOX,      P_ID_NAV_BOX,        6, 204, 308,  32 },
    { WVUI_TYPE_BTN,      P_ID_NAV_DASH,      12, 208,  96,  24 },
    { WVUI_TYPE_BTN,      P_ID_NAV_CTRL,     112, 208,  96,  24 },
    { WVUI_TYPE_BTN,      P_ID_NAV_INFO,     212, 208,  96,  24 }
};

static wvui_page_t s_page_dash = {
    .descs = s_dash_descs,
    .count = (uint16_t)(sizeof(s_dash_descs) / sizeof(s_dash_descs[0])),
    .pinned = 1u,
    .on_enter = dash_enter,
    .on_tick = dash_tick
};

static wvui_page_t s_page_ctrl = {
    .descs = s_ctrl_descs,
    .count = (uint16_t)(sizeof(s_ctrl_descs) / sizeof(s_ctrl_descs[0])),
    .pinned = 1u,
    .on_enter = ctrl_enter,
    .on_tick = ctrl_tick
};

static wvui_page_t s_page_info = {
    .descs = s_info_descs,
    .count = (uint16_t)(sizeof(s_info_descs) / sizeof(s_info_descs[0])),
    .pinned = 1u,
    .on_enter = info_enter,
    .on_tick = info_tick
};

static int16_t pages_sin(uint16_t a)
{
    return s_sin[a & 63u];
}

static int16_t pages_cos(uint16_t a)
{
    return s_sin[(uint16_t)(a + 16u) & 63u];
}

static void page_label(uint16_t id, const char *text, wvui_color_t color, uint8_t align)
{
    wvui_widget_t *w = wvui_widget_find_by_id(id);

    wvui_label_set_font(w, &wvui_font_mont14);
    wvui_label_set_color(w, color);
    wvui_label_set_align(w, align);
    wvui_label_set_text(w, text);
}

static void card_style(uint16_t id)
{
    wvui_widget_t *w = wvui_widget_find_by_id(id);

    wvui_box_set_colors(w, C_CARD, C_BORDER);
    wvui_box_set_border_width(w, 1u);
    wvui_box_set_radius(w, 10u);
}

static void go_page(uint8_t idx)
{
    wvui_page_t *p;

    if (idx >= PAGES_TOTAL)
    {
        return;
    }

    s_st.page = idx;
    p = (idx == 0u) ? &s_page_dash : ((idx == 1u) ? &s_page_ctrl : &s_page_info);
    wvui_page_go(p);
}

static void on_nav(wvui_widget_t *w, void *user)
{
    uint8_t idx = (uint8_t)(uintptr_t)user;

    (void)w;

    if (idx == s_st.page)
    {
        return;
    }
    go_page(idx);
}

static void dock_style(void)
{
    static const uint16_t ids[PAGES_TOTAL] = { P_ID_NAV_DASH, P_ID_NAV_CTRL, P_ID_NAV_INFO };
    static const char *const texts[PAGES_TOTAL] = { "DASH", "CTRL", "INFO" };
    wvui_widget_t *w;
    uint8_t i;

    w = wvui_widget_find_by_id(P_ID_NAV_BOX);
    wvui_box_set_colors(w, WVUI_RGB565(250, 252, 255), WVUI_RGB565(212, 220, 231));
    wvui_box_set_border_width(w, 1u);
    wvui_box_set_radius(w, 10u);

    for (i = 0u; i < PAGES_TOTAL; i++)
    {
        w = wvui_widget_find_by_id(ids[i]);
        wvui_btn_set_font(w, &wvui_font_mont14);
        wvui_btn_set_text(w, texts[i]);
        wvui_btn_set_radius(w, 8u);
        if (i == s_st.page)
        {
            wvui_btn_set_colors(w, WVUI_RGB565(0, 160, 126), WVUI_RGB565(0, 188, 148),
                               WVUI_RGB565(255, 255, 255));
            wvui_btn_set_border(w, WVUI_RGB565(0, 132, 102));
        }
        else
        {
            wvui_btn_set_colors(w, WVUI_RGB565(240, 244, 249), WVUI_RGB565(228, 234, 242), C_DIM);
            wvui_btn_set_border(w, WVUI_RGB565(212, 220, 231));
        }
        wvui_btn_set_click_cb(w, on_nav, (void *)(uintptr_t)i);
    }
}

static void header_style(const char *title)
{
    page_label(P_ID_TITLE, title, C_TEXT, WVUI_LABEL_ALIGN_LEFT);
    page_label(P_ID_CLOCK, s_clock_text, C_DIM, WVUI_LABEL_ALIGN_RIGHT);
    wvui_line_set_color(wvui_widget_find_by_id(P_ID_DIVIDER), C_DIV);
    dock_style();
}

static void on_bright(wvui_widget_t *w, uint8_t value, void *user)
{
    (void)w;
    (void)user;

    s_st.bright = value;
    snprintf(s_bright_text, sizeof(s_bright_text), "%u", (unsigned)value);
    wvui_label_set_text(wvui_widget_find_by_id(P_ID_BRIGHT_V), s_bright_text);
    wvui_progress_set_value(wvui_widget_find_by_id(P_ID_PROGRESS), value);
}

static void on_gain(wvui_widget_t *w, int32_t value, void *user)
{
    (void)w;
    (void)user;

    s_st.gain = value;
    snprintf(s_gain_text, sizeof(s_gain_text), "%ld", (long)value);
    wvui_label_set_text(wvui_widget_find_by_id(P_ID_GAIN_V), s_gain_text);
}

static void on_auto(wvui_widget_t *w, uint8_t on, void *user)
{
    (void)w;
    (void)user;

    s_st.auto_on = on;
    wvui_label_set_text(wvui_widget_find_by_id(P_ID_AUTO_V), (on != 0u) ? "ENGAGED" : "IDLE");
}

static void on_apply(wvui_widget_t *w, void *user)
{
    (void)w;
    (void)user;

    s_st.boost_until = s_st.ms + 1200u;
    s_st.msg_until = s_st.ms + 1200u;
    wvui_label_set_text(wvui_widget_find_by_id(P_ID_MSG), "BOOST QUEUED");
}

static void on_reset(wvui_widget_t *w, void *user)
{
    (void)w;
    (void)user;

    s_st.bright = 128u;
    s_st.gain = 42;
    s_st.auto_on = 0u;
    s_st.boost_until = 0u;
    s_st.msg_until = 0u;
}

static void dash_enter(const wvui_page_t *self)
{
    wvui_widget_t *w;

    (void)self;

    s_last_load = -1;

    card_style(P_ID_CARD_L);
    card_style(P_ID_CARD_R);
    card_style(P_ID_CARD_B);

    w = wvui_widget_find_by_id(P_ID_GAUGE);
    wvui_gauge_set_angles(w, 256u, 0u);
    wvui_gauge_set_colors(w, C_TRACK, C_ACCENT, C_WARM);
    wvui_gauge_set_width(w, 7u);
    wvui_gauge_set_needle(w, 2u);
    wvui_gauge_set_radius(w, 40u);
    wvui_gauge_set_value(w, s_st.bright);

    page_label(P_ID_GAUGE_VAL, s_dash_text, C_TEXT, WVUI_LABEL_ALIGN_CENTER);

    w = wvui_widget_find_by_id(P_ID_SEG);
    wvui_segdisp_set_digits(w, 4u);
    wvui_segdisp_set_seg_size(w, 22u, 26u, 3u);
    wvui_segdisp_set_gap(w, 6u);
    wvui_segdisp_set_colors(w, C_WARM, WVUI_RGB565(232, 228, 220));
    wvui_segdisp_set_value(w, 0u);

    page_label(P_ID_SIGNAL, "SIGNAL", C_DIM, WVUI_LABEL_ALIGN_LEFT);

    w = wvui_widget_find_by_id(P_ID_CHART);
    (void)wvui_chart_bind(w, s_chart_samples, sizeof(s_chart_samples));
    wvui_chart_set_colors(w, C_ACCENT, WVUI_RGB565(224, 238, 232));
    wvui_chart_set_ring(w, 1u);

    w = wvui_widget_find_by_id(P_ID_RING1);
    wvui_arc_set_angles(w, 0u, 0u);
    wvui_arc_set_radius(w, 22u);
    wvui_arc_set_width(w, 1u);
    wvui_arc_set_color(w, WVUI_RGB565(178, 198, 218));

    w = wvui_widget_find_by_id(P_ID_RING2);
    wvui_arc_set_angles(w, 0u, 0u);
    wvui_arc_set_radius(w, 15u);
    wvui_arc_set_width(w, 1u);
    wvui_arc_set_color(w, WVUI_RGB565(160, 184, 208));

    w = wvui_widget_find_by_id(P_ID_RING3);
    wvui_arc_set_angles(w, 0u, 0u);
    wvui_arc_set_radius(w, 9u);
    wvui_arc_set_width(w, 1u);
    wvui_arc_set_color(w, WVUI_RGB565(142, 168, 196));

    w = wvui_widget_find_by_id(P_ID_PLANET);
    wvui_box_set_colors(w, C_WARM, C_WARM);
    wvui_box_set_border_width(w, 0u);
    wvui_box_set_radius(w, 4u);

    page_label(P_ID_STATE, "STATUS NOMINAL", C_ACCENT, WVUI_LABEL_ALIGN_LEFT);

    w = wvui_widget_find_by_id(P_ID_HEART);
    wvui_indicator_set_colors(w, WVUI_RGB565(216, 224, 234), C_ACCENT);
    wvui_indicator_set_on(w, 1u);

    header_style("DASHBOARD");
}

static void dash_tick(const wvui_page_t *self)
{
    static uint32_t next_seg;
    static uint32_t next_chart;
    static uint32_t next_state;
    uint32_t ms = s_st.ms;
    uint16_t a;
    int32_t v;
    int32_t dx;
    int32_t dy;
    uint8_t boost;

    (void)self;

    boost = (ms < s_st.boost_until) ? 1u : 0u;
    a = (uint16_t)((ms >> ((s_st.auto_on != 0u) ? 4u : 5u)) + ((boost != 0u) ? (ms >> 7) : 0u));

    v = (int32_t)s_st.bright + (((int32_t)pages_sin(a) * 40) / 1024);
    if (boost != 0u)
    {
        v += 30;
    }
    if (v < 0)
    {
        v = 0;
    }
    if (v > 255)
    {
        v = 255;
    }
    wvui_gauge_set_value(wvui_widget_find_by_id(P_ID_GAUGE), (uint8_t)v);
    if (v != s_last_load)
    {
        s_last_load = v;
        snprintf(s_dash_text, sizeof(s_dash_text), "LOAD %ld", (long)v);
        wvui_label_set_text(wvui_widget_find_by_id(P_ID_GAUGE_VAL), s_dash_text);
    }

    dx = ((int32_t)pages_cos((uint16_t)(a * 2u)) * 22) / 1024;
    dy = ((int32_t)pages_sin((uint16_t)(a * 2u)) * 22) / 1024;
    wvui_widget_set_pos(wvui_widget_find_by_id(P_ID_PLANET), (int16_t)(37 + dx - 4),
                       (int16_t)(173 + dy - 4));

    if (ms >= next_seg)
    {
        next_seg = ms + 200u;
        wvui_segdisp_set_value(wvui_widget_find_by_id(P_ID_SEG), (uint32_t)((ms / 1000u) % 10000u));
    }

    if (ms >= next_chart)
    {
        next_chart = ms + 60u;
        v = 128 + (((int32_t)pages_sin((uint16_t)((a * 3u) + 24u)) * 70) / 1024);
        if (boost != 0u)
        {
            v += 35;
        }
        if (v < 0)
        {
            v = 0;
        }
        if (v > 255)
        {
            v = 255;
        }
        wvui_chart_push(wvui_widget_find_by_id(P_ID_CHART), (uint8_t)v);
    }

    if (ms >= next_state)
    {
        next_state = ms + 300u;
        wvui_label_set_text(wvui_widget_find_by_id(P_ID_STATE),
                           (boost != 0u) ? "BOOST ACTIVE" : "STATUS NOMINAL");
        wvui_label_set_color(wvui_widget_find_by_id(P_ID_STATE), (boost != 0u) ? C_WARM : C_ACCENT);
    }
}

static void ctrl_enter(const wvui_page_t *self)
{
    wvui_widget_t *w;

    (void)self;

    card_style(P_ID_CARD_1);
    card_style(P_ID_CARD_2);
    card_style(P_ID_CARD_3);

    page_label(P_ID_BRIGHT_L, "BRIGHT", C_DIM, WVUI_LABEL_ALIGN_LEFT);
    snprintf(s_bright_text, sizeof(s_bright_text), "%u", (unsigned)s_st.bright);
    page_label(P_ID_BRIGHT_V, s_bright_text, C_TEXT, WVUI_LABEL_ALIGN_RIGHT);

    w = wvui_widget_find_by_id(P_ID_SLIDER);
    wvui_slider_set_colors(w, C_TRACK, C_ACCENT, C_WARM);
    wvui_slider_set_radius(w, 0u);
    wvui_slider_set_value(w, s_st.bright);
    wvui_slider_set_change_cb(w, on_bright, 0);

    page_label(P_ID_GAIN_L, "GAIN", C_DIM, WVUI_LABEL_ALIGN_LEFT);
    w = wvui_widget_find_by_id(P_ID_STEPPER);
    wvui_stepper_set_range(w, 0, 100, 0);
    wvui_stepper_set_step(w, 1);
    wvui_stepper_set_colors(w, WVUI_RGB565(238, 242, 247), C_TEXT, WVUI_RGB565(196, 208, 222));
    wvui_stepper_set_value(w, s_st.gain);
    wvui_stepper_set_change_cb(w, on_gain, 0);
    snprintf(s_gain_text, sizeof(s_gain_text), "%ld", (long)s_st.gain);
    page_label(P_ID_GAIN_V, s_gain_text, C_TEXT, WVUI_LABEL_ALIGN_RIGHT);

    page_label(P_ID_AUTO_L, "AUTO", C_DIM, WVUI_LABEL_ALIGN_LEFT);
    w = wvui_widget_find_by_id(P_ID_TOGGLE);
    wvui_toggle_set_colors(w, WVUI_RGB565(212, 220, 232), C_ACCENT, WVUI_RGB565(255, 255, 255));
    wvui_toggle_set_radius(w, 11u);
    wvui_toggle_set_on(w, s_st.auto_on);
    wvui_toggle_set_change_cb(w, on_auto, 0);
    page_label(P_ID_AUTO_V, (s_st.auto_on != 0u) ? "ENGAGED" : "IDLE", C_TEXT,
               WVUI_LABEL_ALIGN_LEFT);

    w = wvui_widget_find_by_id(P_ID_PROGRESS);
    wvui_progress_set_colors(w, WVUI_RGB565(230, 236, 244), C_COOL);
    wvui_progress_set_radius(w, 6u);
    wvui_progress_set_value(w, s_st.bright);

    page_label(P_ID_MSG, "READY", C_DIM, WVUI_LABEL_ALIGN_LEFT);

    w = wvui_widget_find_by_id(P_ID_APPLY);
    wvui_btn_set_font(w, &wvui_font_mont14);
    wvui_btn_set_text(w, "APPLY");
    wvui_btn_set_colors(w, WVUI_RGB565(38, 104, 214), WVUI_RGB565(64, 132, 236),
                       WVUI_RGB565(255, 255, 255));
    wvui_btn_set_border(w, WVUI_RGB565(24, 84, 190));
    wvui_btn_set_radius(w, 10u);
    wvui_btn_set_click_cb(w, on_apply, 0);

    header_style("CONTROL");
}

static void ctrl_tick(const wvui_page_t *self)
{
    (void)self;

    if ((s_st.msg_until != 0u) && (s_st.ms >= s_st.msg_until))
    {
        s_st.msg_until = 0u;
        wvui_label_set_text(wvui_widget_find_by_id(P_ID_MSG), "READY");
    }
}

static void info_enter(const wvui_page_t *self)
{
    wvui_widget_t *w;

    (void)self;

    card_style(P_ID_LIST_CARD);

    w = wvui_widget_find_by_id(P_ID_LIST);
    wvui_list_set_font(w, &wvui_font_mont14);
    wvui_list_set_row_height(w, 18);
    wvui_list_set_colors(w, WVUI_RGB565(200, 224, 242), C_DIM, C_TEXT);
    wvui_list_bind(w, s_info_items, (uint16_t)(sizeof(s_info_items) / sizeof(s_info_items[0])));
    wvui_list_set_selected(w, 0u);

    if (touchChipInfo.ready != 0u)
    {
        snprintf(s_chip_text, sizeof(s_chip_text), "touch   GT%s %ux%u", touchChipInfo.id,
                 (unsigned)touchChipInfo.width, (unsigned)touchChipInfo.height);
    }
    else
    {
        snprintf(s_chip_text, sizeof(s_chip_text), "touch   not detected");
    }
    page_label(P_ID_INFO_1, s_chip_text, C_TEXT, WVUI_LABEL_ALIGN_LEFT);
    page_label(P_ID_INFO_2, s_uptime_text, C_TEXT, WVUI_LABEL_ALIGN_LEFT);
    page_label(P_ID_INFO_4, s_load_text, C_TEXT, WVUI_LABEL_ALIGN_LEFT);

    w = wvui_widget_find_by_id(P_ID_RESET);
    wvui_btn_set_font(w, &wvui_font_mont14);
    wvui_btn_set_text(w, "RESET");
    wvui_btn_set_colors(w, WVUI_RGB565(252, 230, 232), WVUI_RGB565(246, 208, 212),
                       WVUI_RGB565(158, 44, 56));
    wvui_btn_set_border(w, WVUI_RGB565(228, 176, 182));
    wvui_btn_set_radius(w, 10u);
    wvui_btn_set_click_cb(w, on_reset, 0);

    header_style("SYSTEM INFO");
}

static void info_tick(const wvui_page_t *self)
{
    static uint32_t next_info;

    (void)self;

    if (s_st.ms < next_info)
    {
        return;
    }
    next_info = s_st.ms + 200u;

    snprintf(s_uptime_text, sizeof(s_uptime_text), "uptime  %lu s", (unsigned long)(s_st.ms / 1000u));
    wvui_label_set_text(wvui_widget_find_by_id(P_ID_INFO_2), s_uptime_text);

    snprintf(s_load_text, sizeof(s_load_text), "bright %u  gain %ld", (unsigned)s_st.bright,
             (long)s_st.gain);
    wvui_label_set_text(wvui_widget_find_by_id(P_ID_INFO_4), s_load_text);
}

void wvui_demo_pages_init(void)
{
    s_st.bright = 128u;
    s_st.gain = 42;
    s_st.auto_on = 0u;
    s_st.boost_until = 0u;
    s_st.msg_until = 0u;
    s_st.ms = 0u;
    s_st.page = 0u;

    snprintf(s_clock_text, sizeof(s_clock_text), "T+0s");
    snprintf(s_bright_text, sizeof(s_bright_text), "128");
    snprintf(s_gain_text, sizeof(s_gain_text), "42");
    snprintf(s_uptime_text, sizeof(s_uptime_text), "uptime  0 s");
    snprintf(s_load_text, sizeof(s_load_text), "bright 128  gain 42");
    snprintf(s_dash_text, sizeof(s_dash_text), "LOAD 128");
    snprintf(s_chip_text, sizeof(s_chip_text), "touch   --");

    (void)wvui_page_reset(&s_page_dash);
}

void wvui_demo_pages_tick(uint32_t ms)
{
    static uint32_t next_clock;

    s_st.ms = ms;

    if (ms >= next_clock)
    {
        next_clock = ms + 500u;
        snprintf(s_clock_text, sizeof(s_clock_text), "T+%lus", (unsigned long)(ms / 1000u));
        wvui_label_set_text(wvui_widget_find_by_id(P_ID_CLOCK), s_clock_text);
    }
}



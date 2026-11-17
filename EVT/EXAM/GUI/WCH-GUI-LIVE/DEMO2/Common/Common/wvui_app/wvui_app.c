#include "debug.h"
#include "wvui_app.h"

#define APP_REFRESH_MS (20u)

static uint32_t s_ms;
static uint16_t s_prev_ms;
static uint16_t s_last_poll;
static uint8_t s_started;

int app_init(void)
{
    wvui_rect_t all;
    int16_t w = 0;
    int16_t h = 0;

    wvui_screen_size(&w, &h);

    all.x0 = 0;
    all.y0 = 0;
    all.x1 = (int16_t)(w - 1);
    all.y1 = (int16_t)(h - 1);

    wvui_demo_pages_init();

    wvui_invalidate(all);

    return 0;
}

void wvui_app_tick(void)
{
    uint16_t now = (uint16_t)(TIM_GetCounter(TIM4) >> 3);

    if (s_started == 0u)
    {
        s_started = 1u;
        s_prev_ms = now;
        s_last_poll = (uint16_t)(now - APP_REFRESH_MS);
    }

    s_ms += (uint16_t)(now - s_prev_ms);
    s_prev_ms = now;

    wvui_demo_pages_tick(s_ms);

    if ((uint16_t)(now - s_last_poll) >= APP_REFRESH_MS)
    {
        s_last_poll = now;

        wvui_frame_poll();
    }
}

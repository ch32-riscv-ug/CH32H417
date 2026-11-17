#ifndef WVUI_APP_H
#define WVUI_APP_H

#include "wvui.h"

int app_init(void);
void wvui_app_tick(void);

void wvui_demo_pages_init(void);
void wvui_demo_pages_tick(uint32_t ms);

#endif /* WVUI_APP_H */

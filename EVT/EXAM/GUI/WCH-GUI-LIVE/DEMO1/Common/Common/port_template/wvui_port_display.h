#ifndef WVUI_PORT_DISPLAY_H
#define WVUI_PORT_DISPLAY_H

/* ============================================================================
 * 显示端口 —— 把 wvui_port_t 接到面板驱动上
 * ----------------------------------------------------------------------------
 * 用法（三步）：
 *
 *   1. 替换 `wvui_port_display.c` 下半部分的五个 `lcd_*` 空实现
 *      （SPI/并口初始化、CASET/RASET、发像素、等 DMA、收尾）；
 *   2. 在同文件的 `s_port` 里填对齐粒度、页式标志与带宽；
 *   3. 上电先 configure，再把端口交给 wvui_init()（面板尺寸在 wvui_cfg_t 里）：
 *
 *          wvui_port_display_configure(0u);
 *          wvui_init(wvui_port_display(), &cfg);
 *
 * 五阶段包装不用动：移植时只改 .c 里的五个 `lcd_*` 函数体。
 * ==========================================================================*/

#include <stdint.h>
#include "wvui_port.h"

/* 面板侧的五个函数（空实现在 wvui_port_display.c，移植时替换那五个函数体）。 */
int lcd_init(void);
void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void lcd_write_pixels(const uint16_t *pixels, uint32_t count);
void lcd_wait_done(void);
void lcd_end_transaction(void);

/* 异步标志：0 = lcd_write_pixels 发完才返回（阻塞）；1 = 启动 DMA 后立刻返回。
 * 阻塞端口下 wvui_init() 用整块 PFB 分块推屏；双缓冲需要 async = 1，
 * 且 wvui_cfg_t.double_buffer = 1、PFB 容量能放下两行。 */
void wvui_port_display_configure(uint8_t async);

/* 取端口句柄，交给 wvui_init()。未 configure 时返回 NULL。 */
const wvui_port_t *wvui_port_display(void);

#endif /* WVUI_PORT_DISPLAY_H */

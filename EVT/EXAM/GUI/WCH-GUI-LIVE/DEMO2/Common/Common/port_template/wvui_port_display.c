/* ============================================================================
 * 显示端口 —— 五阶段包装 + 面板空实现
 * ----------------------------------------------------------------------------
 * 文件分两段：
 *
 *   第一段（要改）：五个 `lcd_*` 函数。现在是空面板，让自检在任何平台上都能跑
 *   通；移植时把函数体换成你的 SPI/并口读写与时序。
 *
 *   第二段（不用改）：五阶段包装与能力字段。一个事务（一个脏矩形）的顺序：
 *
 *       set_window(x0,y0,x1,y1)     1 次，之后控制器地址自增
 *       flush_begin()               1 次   "开始写显存"命令（RAMWR）与拉低片选放这里
 *       flush(pixels,count)         1..N 次   N = 矩形按 PFB 行容量分成的块数
 *       flush_wait()                1..M 次   复用缓冲之前必有一次（阻塞驱动为空）
 *       flush_end()                 1 次   收尾：拉高片选等
 *
 * 像素是 native uint16_t RGB565；字节序（高字节先行）由 lcd_write_pixels 负责。
 * ==========================================================================*/

#include "wvui_port_display.h"

#include "lcd.h"
#include "spi.h"

/* ---- 第一段：面板侧，移植时只改这里的五个函数体 ---------------------------- */

int lcd_init(void)
{
    /* ← 换成 SPI/并口、GPIO、复位时序、面板寄存器（如 0x11 退睡眠、0x29 开显示）、
     *   背光。返回 0 = 成功。 */
    LCD_Init();
    return 0;
}

void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_SetWindows(x0, y0, x1, y1);
    SPI2_SetDataSize(SPI_DataSize_16b);
}

static void lcd_dma_wait(void)
{
    uint32_t timeout;

    timeout = 0x100000u;
    while (SPI2_DMA_TX_CH->CNTR > 0u)
    {
        if (--timeout == 0u)
        {
            DMA_Cmd(SPI2_DMA_TX_CH, DISABLE);
            break;
        }
    }

    timeout = 0x100000u;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
    {
        if (--timeout == 0u)
        {
            break;
        }
    }
}

void lcd_write_pixels(const uint16_t *pixels, uint32_t count)
{
    uint16_t n;

    lcd_dma_wait();

    LCD_CS_CLR();
    LCD_DC_SET();

    while (count > 0u)
    {
        n = (count > 0xFFFFu) ? (uint16_t)0xFFFFu : (uint16_t)count;

        SPI2_Write_DMA16((uint16_t *)pixels, n);

        pixels += n;
        count -= n;

        if (count > 0u)
        {
            lcd_dma_wait();
        }
    }
}

void lcd_wait_done(void)
{
    lcd_dma_wait();
}

void lcd_end_transaction(void)
{
    lcd_dma_wait();

    LCD_CS_SET();
    SPI2_SetDataSize(SPI_DataSize_8b);
}

/* ---- 第二段：五阶段与能力字段，不用改 -------------------------------------- */

static uint8_t s_ready;

static void tmpl_set_window(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    lcd_set_window((uint16_t)x0, (uint16_t)y0, (uint16_t)x1, (uint16_t)y1);
}

static void tmpl_flush_begin(void)
{
}

static void tmpl_flush(const void *pixels, uint32_t count)
{
    lcd_write_pixels((const uint16_t *)pixels, count);
}

static void tmpl_flush_wait(void)
{
    lcd_wait_done();
}

static void tmpl_flush_end(void)
{
    lcd_end_transaction();
}

/* 能力字段是运行期值：换屏改这里即可，wvui_init() 校验后返回 WVUI_ERR_*。
 *   align_x/y  命令设窗的彩屏（ST7789/ILI9341 等）→ 1/1；
 *              页式 OLED（SSD1306 等）→ align_y = 8 且 paged = 1。
 *   bus_bytes_per_ms  不进像素：只进统计与合并成本估算。
 *              SPI @ 40 MHz、8 位/帧 → 40e6 / 8 / 1000 = 5000；不确定填 0。 */
static wvui_port_t s_port =
{
    .set_window = tmpl_set_window,
    .flush_begin = tmpl_flush_begin,
    .flush = tmpl_flush,
    .flush_wait = tmpl_flush_wait,
    .flush_end = tmpl_flush_end,
    .async = 0u,
    .align_x = 1u,
    .align_y = 1u,
    .paged = 0u,
    .bus_bytes_per_ms = 0u
};

void wvui_port_display_configure(uint8_t async)
{
    s_port.async = (uint8_t)(async != 0u);
    s_ready = 1u;
}

const wvui_port_t *wvui_port_display(void)
{
    return (s_ready != 0u) ? &s_port : 0;
}

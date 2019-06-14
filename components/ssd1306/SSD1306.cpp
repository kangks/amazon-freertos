#include "SSD1306.h"

#define INVERT_COLOR(x) (( x == White ) ? Black:White)
#define ABS(x)   ((x) > 0 ? (x) : -(x))

// Control byte
#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40

/* SSD1306 data buffer */
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

void SSD1306::write_command(uint8_t command)
{
    uint8_t datawrite[2];
    datawrite[0] = OLED_CONTROL_BYTE_CMD_STREAM; 
    datawrite[1] = command;

    m_i2c.write(m_address, &datawrite[0], 2, true);
}

void SSD1306::PowerOn()
{
    write_command(0x8D);
    write_command(0x14);
    write_command(0xAF);    
}

void SSD1306::PowerOff()
{
    write_command(0x8D);
    write_command(0x10);
    write_command(0xAE);    
}

void SSD1306::init()
{
    //if (GPIO_IS_VALID_GPIO(m_resetpin))
    if ((m_resetpin > 0) && (m_resetpin < GPIO_PIN_COUNT)) 
    {
        // reset the oled
        gpio_pad_select_gpio((gpio_num_t) m_resetpin);
        /* Set the GPIO as a push/pull output */
        gpio_set_direction((gpio_num_t) m_resetpin, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t) m_resetpin, 0);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) m_resetpin, 1);

    }
    /* Init LCD */
    write_command(0xAE); //display off
    write_command(0x20); //Set Memory Addressing Mode
    write_command(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    write_command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    write_command(0xC8); //Set COM Output Scan Directionwrite_command(command)
    write_command(0x00); //---set low column address
    write_command(0x10); //---set high column address
    write_command(0x40); //--set start line address
    write_command(0x81); //--set contrast control register
    write_command(0xFF);
    write_command(0xA1); //--set segment re-map 0 to 127
    write_command(0xA6); //--set normal display
    write_command(0xA8); //--set multiplex ratio(1 to 64)
    write_command(0x3F); //
    write_command(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    write_command(0xD3); //-set display offset
    write_command(0x00); //-not offset
    write_command(0xD5); //--set display clock divide ratio/oscillator frequency
    write_command(0xF0); //--set divide ratio
    write_command(0xD9); //--set pre-charge period
    write_command(0x22); //
    write_command(0xDA); //--set com pins hardware configuration
    write_command(0x12);
    write_command(0xDB); //--set vcomh
    write_command(0x20); //0x20,0.77xVcc
    write_command(0x8D); //--set DC-DC enable
    write_command(0x14); //
    write_command(0xAF); //--turn on SSD1306 panel

    /* Clear screen */
    Fill(Black);

    /* Update screen */
    UpdateScreen();

    /* Set default values */
    m_currentx = 0;
    m_currenty = 0;

    /* Initialized OK */
    m_initialized = true;
}

void SSD1306::UpdateScreen()
{
    uint8_t m;

    // Deactivate Scrolling when updating RAM
    write_command(0x2E);

    for (m = 0; m < 8; m++) {
        write_command(0xB0 + m);
        write_command(0x00);
        write_command(0x10);

        m_i2c.write_reg(m_address, OLED_CONTROL_BYTE_DATA_STREAM, &SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH, false);
    }
}

void SSD1306::ToggleInvert()
{
    uint16_t i;

    /* Toggle invert */
    m_inverted = !m_inverted;

    /* Do memory toggle */
    for (i = 0; i < sizeof(SSD1306_Buffer); i++) {
        SSD1306_Buffer[i] = ~SSD1306_Buffer[i];
    }    
}

void SSD1306::Fill(Color color)
{
    /* Set memory */
    memset(SSD1306_Buffer, (color == Black) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));    
}

void SSD1306::DrawPixel(uint16_t x, uint16_t y, Color color)
{
    if (
            x >= SSD1306_WIDTH ||
            y >= SSD1306_HEIGHT
       ) {
        /* Error */
        return;
    }

    /* Check if pixels are inverted */
    if (m_inverted) {
       color = INVERT_COLOR(color); 
    }

    /* Set color */
    if (color == White) {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }    
}

void SSD1306::GotoXY(uint16_t x, uint16_t y)
{
    /* Set write pointers */
    m_currentx = x;
    m_currenty = y;
}

char SSD1306::Putc(char ch, FontDef_t * Font, Color color)
{
    uint32_t i, b, j;

    /* Check available space in LCD */
    if (
            SSD1306_WIDTH <= (m_currentx + Font->FontWidth) ||
            SSD1306_HEIGHT <= (m_currenty + Font->FontHeight)
       ) 
    {
        /* Error */
        return 0;
    }

    /* Go through font */
    for (i = 0; i < Font->FontHeight; i++) {
        b = Font->data[(ch - 32) * Font->FontHeight + i];
        for (j = 0; j < Font->FontWidth; j++) {
            if ((b << j) & 0x8000) {
                DrawPixel(m_currentx + j, (m_currenty + i), color);
            } else {
                DrawPixel(m_currentx + j, (m_currenty + i), INVERT_COLOR(color));
            }
        }
    }

    /* Increase pointer */
    m_currentx += Font->FontWidth;

    /* Return character written */
    return ch;    
}

char SSD1306::Puts(const char * istr, FontDef_t * Font, Color color)
{
    char * str = (char *) istr;
    /* Write characters */
    while (*str) {
        /* Write character by character */
        if (Putc(*str, Font, color) != *str) {
            /* Return error */
            return *str;
        }

        /* Increase string pointer */
        str++;
    }

    /* Everything OK, zero should be returned */
    return *str;    
}

void SSD1306::DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color color)
{
    int16_t dx, dy, sx, sy, err, e2, i, tmp;

    /* Check for overflow */
    if (x0 >= SSD1306_WIDTH) {
        x0 = SSD1306_WIDTH - 1;
    }
    if (x1 >= SSD1306_WIDTH) {
        x1 = SSD1306_WIDTH - 1;
    }
    if (y0 >= SSD1306_HEIGHT) {
        y0 = SSD1306_HEIGHT - 1;
    }
    if (y1 >= SSD1306_HEIGHT) {
        y1 = SSD1306_HEIGHT - 1;
    }

    dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;
    err = ((dx > dy) ? dx : -dy) / 2;

    if (dx == 0) {
        if (y1 < y0) {
            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }

        if (x1 < x0) {
            tmp = x1;
            x1 = x0;
            x0 = tmp;
        }

        /* Vertical line */
        for (i = y0; i <= y1; i++) {
            DrawPixel(x0, i, color);
        }

        /* Return from function */
        return;
    }

    if (dy == 0) {
        if (y1 < y0) {
            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }

        if (x1 < x0) {
            tmp = x1;
            x1 = x0;
            x0 = tmp;
        }

        /* Horizontal line */
        for (i = x0; i <= x1; i++) {
            DrawPixel(i, y0, color);
        }

        /* Return from function */
        return;
    }

    while (1) {
        DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }    
}

void SSD1306::DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color)
{
    /* Check input parameters */
    if (
            x >= SSD1306_WIDTH ||
            y >= SSD1306_HEIGHT
       ) {
        /* Return error */
        return;
    }

    /* Check width and height */
    if ((x + w) >= SSD1306_WIDTH) {
        w = SSD1306_WIDTH - x;
    }
    if ((y + h) >= SSD1306_HEIGHT) {
        h = SSD1306_HEIGHT - y;
    }

    /* Draw 4 lines */
    DrawLine(x, y, x + w, y, color);         /* Top line */
    DrawLine(x, y + h, x + w, y + h, color); /* Bottom line */
    DrawLine(x, y, x, y + h, color);         /* Left line */
    DrawLine(x + w, y, x + w, y + h, color); /* Right line */    
}

void SSD1306::DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color)
{
   uint8_t i;

    /* Check input parameters */
    if (
            x >= SSD1306_WIDTH ||
            y >= SSD1306_HEIGHT
       ) {
        /* Return error */
        return;
    }

    /* Check width and height */
    if ((x + w) >= SSD1306_WIDTH) {
        w = SSD1306_WIDTH - x;
    }
    if ((y + h) >= SSD1306_HEIGHT) {
        h = SSD1306_HEIGHT - y;
    }

    /* Draw lines */
    for (i = 0; i <= h; i++) {
        /* Draw lines */
        DrawLine(x, y + i, x + w, y + i, color);
    }
}

void SSD1306::DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, Color color)
{
    /* Draw lines */
    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x3, y3, color);
    DrawLine(x3, y3, x1, y1, color);
}

void SSD1306::DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, Color color)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = ABS(x2 - x1);
    deltay = ABS(y2 - y1);
    x = x1;
    y = y1;

    if (x2 >= x1) {
        xinc1 = 1;
        xinc2 = 1;
    } else {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1) {
        yinc1 = 1;
        yinc2 = 1;
    } else {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay){
        xinc1 = 0;
        yinc2 = 0;
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;
    } else {
        xinc2 = 0;
        yinc1 = 0;
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++) {
        DrawLine(x, y, x3, y3, color);

        num += numadd;
        if (num >= den) {
            num -= den;
            x += xinc1;
            y += yinc1;
        }
        x += xinc2;
        y += yinc2;
    }
}

void SSD1306::DrawCircle(int16_t x0, int16_t y0, int16_t r, Color color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    DrawPixel(x0, y0 + r, color);
    DrawPixel(x0, y0 - r, color);
    DrawPixel(x0 + r, y0, color);
    DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        DrawPixel(x0 + x, y0 + y, color);
        DrawPixel(x0 - x, y0 + y, color);
        DrawPixel(x0 + x, y0 - y, color);
        DrawPixel(x0 - x, y0 - y, color);

        DrawPixel(x0 + y, y0 + x, color);
        DrawPixel(x0 - y, y0 + x, color);
        DrawPixel(x0 + y, y0 - x, color);
        DrawPixel(x0 - y, y0 - x, color);
    }
}

void SSD1306::DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, Color color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    DrawPixel(x0, y0 + r, color);
    DrawPixel(x0, y0 - r, color);
    DrawPixel(x0 + r, y0, color);
    DrawPixel(x0 - r, y0, color);
    DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }    
}

void SSD1306::DrawXbm(int16_t x0, int16_t y0, int16_t width, uint16_t height, const char * xbm, Color color)
{
    int16_t widthInXbm = (width + 7) / 8;
    uint8_t data = 0;
    int16_t x = 0, y = 0;

    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            if (x & 7) {
                data >>= 1; // Move a bit
            } else { // Read new data every 8 bit
                data = *(xbm + (x / 8) + y * widthInXbm);
            }
            // if there is a bit draw it
            if (data & 0x01)
            {
                DrawPixel( m_currentx + x, m_currenty + y, color);
            }

        }
    }    
}




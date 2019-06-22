#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "I2CMaster.h"
#include "fonts.h"

#define SSD1306_I2C_ADDR         0x3C   //0x78

/* SSD1306 settings */
/* SSD1306 width in pixels */
#define SSD1306_WIDTH            128

/* SSD1306 LCD height in pixels */
#define SSD1306_HEIGHT           64

class SSD1306
{
    public:
        SSD1306(I2CMaster & i2c,  int8_t reset_pin = -1, uint8_t address = SSD1306_I2C_ADDR )
            :m_i2c(i2c),
            m_address(address),
            m_currentx(0), 
            m_currenty(0),
            m_resetpin(reset_pin),
            m_inverted(false),
            m_initialized(false)
        {}

        ~SSD1306() {}

        enum Color { 
            Black = 0x0,
            White = 0x1
        };

        void init();
        void PowerOn();
        void PowerOff();
        void UpdateScreen();
        void ToggleInvert();
        void Fill(Color color);
        void DrawPixel(uint16_t x, uint16_t y, Color color);
        void GotoXY(uint16_t x, uint16_t y);
        char Putc(char ch, FontDef_t * Font, Color color);
        char Puts(const char * str, FontDef_t * Font, Color color);
        void DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color color);
        void DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);
        void DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);
        void DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, Color color);
        void DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, Color color);        
        void DrawCircle(int16_t x0, int16_t y0, int16_t r, Color color);
        void DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, Color color);
        void DrawXbm(int16_t x0, int16_t y0, int16_t width, uint16_t height, const char * xbm, Color color);

    private:
        void write_command(uint8_t command);

        I2CMaster & m_i2c;
        uint8_t m_address;
        uint16_t m_currentx;
        uint16_t m_currenty;
        int8_t  m_resetpin;
        bool m_inverted;
        bool m_initialized;

};

#endif

#include "FreeRTOS.h"
#include "freertos/portmacro.h"

#if defined (__cplusplus)
extern "C" {
#endif
    #include "task.h"
#if defined (__cplusplus)
}
#endif

#include "SSD1306.h"
#include "oledDisplay.hpp"

void OledDisplay::init(){
};

void OledDisplay::display(const char* buffer){
    memcpy(this->tmpbuff,buffer,MAX_LENGTH);
};

void OledDisplay::displayLoop(void *pvParameter)
{
    while(true) {
        m_ssd.Fill(SSD1306::Black);
        m_ssd.GotoXY(0, 15);
        m_ssd.Puts(&tmpbuff[0], &Font_7x10, SSD1306::White);
        m_ssd.UpdateScreen();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
};

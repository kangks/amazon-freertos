#include "ssd1306.h"
#define MAX_LENGTH 50

class OledDisplay{
    public:
        OledDisplay(SSD1306 & m_ssd)
            :m_ssd(m_ssd)
        {}

        void init();
        void display(const char*);
        void displayLoop(void *);
    private:
        char tmpbuff[MAX_LENGTH];
        SSD1306 & m_ssd;
};
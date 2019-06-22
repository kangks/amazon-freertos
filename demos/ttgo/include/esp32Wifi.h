#ifndef _ESP32WIFI_H_
#define _ESP32WIFI_H_

#include "aws_application_version.h"
#include "aws_appversion32.h"

class Esp32Wifi
{
    public:
        Esp32Wifi();
        int init( void );
    private:
        void prvWifiConnect( void );
        uint8_t ucIPAddress[ 4 ] =
        {
            configIP_ADDR0,
            configIP_ADDR1,
            configIP_ADDR2,
            configIP_ADDR3
        };
        uint8_t ucNetMask[ 4 ] =
        {
            configNET_MASK0,
            configNET_MASK1,
            configNET_MASK2,
            configNET_MASK3
        };
        uint8_t ucGatewayAddress[ 4 ] =
        {
            configGATEWAY_ADDR0,
            configGATEWAY_ADDR1,
            configGATEWAY_ADDR2,
            configGATEWAY_ADDR3
        };
        uint8_t ucDNSServerAddress[ 4 ] =
        {
            configDNS_SERVER_ADDR0,
            configDNS_SERVER_ADDR1,
            configDNS_SERVER_ADDR2,
            configDNS_SERVER_ADDR3
        };
        uint8_t ucMACAddress[ 6 ] =
        {
            configMAC_ADDR0,
            configMAC_ADDR1,
            configMAC_ADDR2,
            configMAC_ADDR3,
            configMAC_ADDR4,
            configMAC_ADDR5
        };        
};

#endif

#ifndef _AWS_IOT_MQTT_H_
#define _AWS_IOT_MQTT_H_

/* MQTT includes. */
#include "aws_mqtt_agent.h"

/**
 * @brief The length of the ACK string appended to messages that are echoed back
 * to the MQTT broker.
 */
#define echoACK_STRING_LENGTH    4

/**
 * @brief Dimension of the character array buffers used to hold data (strings in
 * this case) that is published to and received from the MQTT broker (in the cloud).
 */
#define echoMAX_DATA_LENGTH      20

/**
 * @brief A block time of 0 simply means "don't block".
 */
#define echoDONT_BLOCK           ( ( TickType_t ) 0 )

/* IoT simple subscribe/publish example task parameters. */
#define democonfigMQTT_SUB_PUB_TASK_STACK_SIZE            ( configMINIMAL_STACK_SIZE * 8 )
#define democonfigMQTT_SUB_PUB_TASK_PRIORITY              ( tskIDLE_PRIORITY + 5 )
#define democonfigMQTT_TIMEOUT						       pdMS_TO_TICKS( 3000 )
#define democonfigMQTT_AGENT_CONNECT_FLAGS                 ( mqttagentREQUIRE_TLS | mqttagentUSE_AWS_IOT_ALPN_443 )
#define democonfigMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT	       pdMS_TO_TICKS( 12000 )
#define democonfigMQTT_ECHO_TASK_STACK_SIZE                ( configMINIMAL_STACK_SIZE * 8 )
#define democonfigMQTT_ECHO_TASK_PRIORITY                  ( tskIDLE_PRIORITY + 5 )

class AwsIoTMqtt{
    public:
        AwsIoTMqtt();
        ~AwsIoTMqtt();
        void init(void);
        void prvPublishNextMessage( const uint8_t* echoTOPIC_NAME, char* message );
    private:
        BaseType_t prvCreateClientAndConnectToBroker( void );
        MQTTAgentHandle_t xMQTTHandle;
};

#endif
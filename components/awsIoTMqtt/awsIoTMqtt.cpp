/* Standard includes. */
#include "string.h"
#include "stdio.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#if defined (__cplusplus)
extern "C" {
#endif

    /* MQTT includes. */
    #include "aws_mqtt_agent.h"

#if defined (__cplusplus)
}
#endif

/* Credentials includes. */
#include "aws_clientcredential.h"

#include "awsIotMqtt.h"

AwsIoTMqtt::AwsIoTMqtt(){
    xMQTTHandle = NULL;
};

AwsIoTMqtt::~AwsIoTMqtt(){
    /* Disconnect the client. */
    ( void ) MQTT_AGENT_Disconnect( xMQTTHandle, democonfigMQTT_TIMEOUT );
};

void AwsIoTMqtt::init(void){
    prvCreateClientAndConnectToBroker();
};

BaseType_t AwsIoTMqtt::prvCreateClientAndConnectToBroker( void )
{
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn = pdFAIL;
    MQTTAgentConnectParams_t xConnectParameters =
    {
        clientcredentialMQTT_BROKER_ENDPOINT,               /* The URL of the MQTT broker to connect to. */
        democonfigMQTT_AGENT_CONNECT_FLAGS,                 /* Connection flags. */
        pdFALSE,                                            /* Deprecated. */
        clientcredentialMQTT_BROKER_PORT,                   /* Port number on which the MQTT broker is listening. Can be overridden by ALPN connection flag. */
        ( const uint8_t * ) clientcredentialIOT_THING_NAME, /* Client Identifier of the MQTT client. It must be unique per broker. */
        0,                                                  /* The length of the client Id, filled in later as not const. */
        pdFALSE,                                            /* Deprecated. */
        NULL,                                               /* User data supplied to the callback. Can be NULL. */
        NULL,                                               /* Callback used to report various events. Can be NULL. */
        NULL,                                               /* Certificate used for secure connection. Can be NULL. */
        0                                                   /* Size of certificate used for secure connection. */
    };

    /* Check this function has not already been executed. */
    configASSERT( xMQTTHandle == NULL );

    /* Check that basic configuration has been completed. These settings are
     * given special treatment here since the Hello World demo is what we
     * recommend developers to run first. */
    if( ( xConnectParameters.pucClientId == NULL ) ||
        ( strcmp( "", ( const char * ) xConnectParameters.pucClientId ) == 0 ) ||
        ( xConnectParameters.pcURL == NULL ) ||
        ( strcmp( "", xConnectParameters.pcURL ) == 0 ) )
    {
        configPRINTF( ( "ERROR: you must configure the MQTT client name and broker URL.\r\n" ) );
        configASSERT( pdFALSE );
    }
    else
    {
        /* The MQTT client object must be created before it can be used.  The
         * maximum number of MQTT client objects that can exist simultaneously
         * is set by mqttconfigMAX_BROKERS. */
        xReturned = MQTT_AGENT_Create( &xMQTTHandle );

        if( xReturned == eMQTTAgentSuccess )
        {
            /* Fill in the MQTTAgentConnectParams_t member that is not const,
             * and therefore could not be set in the initializer (where
             * xConnectParameters is declared in this function). */
            xConnectParameters.usClientIdLength = ( uint16_t ) strlen( ( const char * ) xConnectParameters.pucClientId );

            /* Connect to the broker. */
            configPRINTF( ( "MQTT echo attempting to connect to %s.\r\n", clientcredentialMQTT_BROKER_ENDPOINT ) );
            xReturned = MQTT_AGENT_Connect( xMQTTHandle,
                                            &xConnectParameters,
                                            democonfigMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT );

            if( xReturned != eMQTTAgentSuccess )
            {
                /* Could not connect, so delete the MQTT client. */
                ( void ) MQTT_AGENT_Delete( xMQTTHandle );
                configPRINTF( ( "ERROR:  MQTT echo failed to connect with error %d.\r\n", xReturned ) );
            }
            else
            {
                configPRINTF( ( "MQTT echo connected.\r\n" ) );
                xReturn = pdPASS;
            }
        }
    }

    return xReturn;
};

void AwsIoTMqtt::prvPublishNextMessage( const uint8_t* echoTOPIC_NAME, char* cDataBuffer )
{
    MQTTAgentPublishParams_t xPublishParameters;
    MQTTAgentReturnCode_t xReturned;
    // char cDataBuffer[ echoMAX_DATA_LENGTH ];

    /* Check this function is not being called before the MQTT client object has
     * been created. */
    configASSERT( xMQTTHandle != NULL );

    /* Create the message that will be published, which is of the form "Hello World n"
     * where n is a monotonically increasing number. Note that snprintf appends
     * terminating null character to the cDataBuffer. */
    // ( void ) snprintf( cDataBuffer, echoMAX_DATA_LENGTH, "Hello World %d", ( int ) xMessageNumber );

    /* Setup the publish parameters. */
    memset( &( xPublishParameters ), 0x00, sizeof( xPublishParameters ) );
    xPublishParameters.pucTopic = echoTOPIC_NAME;
    xPublishParameters.pvData = cDataBuffer;
    xPublishParameters.usTopicLength = ( uint16_t ) strlen( ( const char * ) echoTOPIC_NAME );
    xPublishParameters.ulDataLength = ( uint32_t ) strlen( cDataBuffer );
    xPublishParameters.xQoS = eMQTTQoS1;

    /* Publish the message. */
    xReturned = MQTT_AGENT_Publish( xMQTTHandle,
                                    &( xPublishParameters ),
                                    democonfigMQTT_TIMEOUT );

    if( xReturned == eMQTTAgentSuccess )
    {
        configPRINTF( ( "Echo successfully published '%s'\r\n", cDataBuffer ) );
    }
    else
    {
        configPRINTF( ( "ERROR:  Echo failed to publish '%s'\r\n", cDataBuffer ) );
    }

    /* Remove compiler warnings in case configPRINTF() is not defined. */
    ( void ) xReturned;
}
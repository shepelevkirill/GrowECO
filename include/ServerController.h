/**
    GrowECO Project

    ServerController.h
    Purpose: Library for controlling server (data exchange and etc)

    @author Kirill Shepelev
    @version 1.0 28/09/2017
*/

#ifndef SERVER_CONTROLLER_H_
#define SERVER_CONTROLLER_H_
#include "NetworkController.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "Arduino.h"
#include "ArduinoJson.h"
#include "ClimateData.h"
#include "ActionData.h"
#include "WiFiManager.h"
#include "groweco_debug.h"

typedef uint16_t HTTPStatusCode;

class ServerController {
    public:
        // Enumeration with statuses of connection
        enum ConnectionStatus {
            SERVER_CONNECTED,
            SERVER_ERROR
        };

        struct HTTPResponse {
            HTTPResponse(HTTPStatusCode statusCode, String data) : data(data), statusCode(statusCode) {}

            String data;
            HTTPStatusCode statusCode;
        };

        struct Settings {
            bool autowatering_enabled;
            uint8_t autowatering_threshold;
        };

        /**
         * Set other Token
         * @param  token Device Token
         * @return          Status of Connection (CONNECTION_SERVER_CONNECTED, CONNECTION_BAD_AUTH_KEY or CONNECTION_SERVER_ERROR)
         */
        static void setToken(String token) {
            Serial.print("Set token to ");
            Serial.println(token);
            _token = token;
        }

        static void setHost(const char* host) {
            _host = host;
        }

        /**
         * Update sensors data on the server
         * @param data Data of the sensors
         */
        static void updateSensors(ClimateData *data);

        static void getSettings(bool ifUpdated = true);


        static ActionData getAction(void);

    
        HTTPStatusCode lastStatusCode = 0; // contains last HTTP status code
        static Settings settings;

    private:
        static ConnectionStatus checkServer(void);
        static HTTPResponse doRequest(const char* path, const char* requestType, String json="");
        static JsonArray& parseArray(HTTPResponse& response);
        static JsonObject& parseObject(HTTPResponse& response);


        static String _token;
        static const char* _host;
        static DynamicJsonBuffer jsonBuffer;

        ServerController(void) {}
        ~ServerController(void) {}
};

#endif

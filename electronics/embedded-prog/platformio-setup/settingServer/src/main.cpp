#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "goswami81";
const char* password = "secret72";

//set webserver port number to 80(default port number for http)
WiFiServer server(80); //creates a server obj with default http port 80
//this server obj will be used to listen for incoming client(browser) requests
//will respond with html

//header var to store http request, will be used to check urls?
String header;

//auxiliary variables to store the current output state
String outputState = "off";

//assign output variables to GPIO pins
const int output = 18;
//current time
unsigned long currentTime = millis();
//previous time
unsigned long previousTime = 0;
//timeout time in milliseconds
const unsigned long timeoutTime = 2000;


void setup() {
    Serial.begin(115200);
    Serial.println("Hello, Arduino!");
    pinMode(output, OUTPUT);

    //set output to low
    digitalWrite(output, LOW);

    //cpnnect to wifi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(". ");
    }
    Serial.println("");//enter
    //print wifi connected message and IP address to access webserver
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());//Shows ESP32’s local IP address
    //start webserver, and begin listening for clients
    server.begin();

}
void loop() {
    WiFiClient client = server.available(); // listen for incoming clients
    //checks if a browser is trying to connect
    if (client) { //if a new client connects
        Serial.println("New Client Connected. ");
        currentTime = millis();
        previousTime = currentTime;
        String currentLine = ""; //make a String to hold incoming data from the client

        while (client.connected() && currentTime - previousTime <= timeoutTime) { //loop while the client's connected
            currentTime = millis();
            if (client.available()) { //if there's data to read from the client
                char c = client.read(); //read a byte from the client
                Serial.write(c); //print the byte
                header+=c; //builds the full http request in the header variable
                if (c == '\n') { //if the byte read is a newline character

                    //if the current line is blank, you got two newline characters in a row.
                    //that is the end of the HTTP req so response needs to be sent
                    if (currentLine.length() == 0) { 
                        Serial.println("Sending Response to Client. ");
                        //HTTP headers always start with a response code (eg HTTP/1.1 200 OK)
                        //and content type, connection is closed after the response
                        //followed by a blank line marking end of the header
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type: text/html");
                        client.println("Connection: close");
                        client.println();

                        //turn the output pin on or off based on the request
                        if (header.indexOf("GET /output/on") >= 0) {
                            Serial.println("Output On Request");
                            outputState = "on";
                            digitalWrite(output, HIGH); //turn the output pin on
                        }
                        else if (header.indexOf("GET /output/off") >= 0) {
                            Serial.println("Output Off Request");
                            outputState = "off";
                            digitalWrite(output, LOW); //turn output pin off
                        }
                        //HTML webpage tp send to client
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<title>ESP32 Web Server</title>");

                        client.println("<link rel=\"icon\" href=\"data:,\">"); 
                        /*  
                        Browsers automatically request /favicon.ico.

                        If you don’t include this line:
                        Browser sends another HTTP request
                        ESP32 logs a second client
                        Confuses beginners (“why is it loading twice?”)
                        This line tells the browser:
                        “The favicon exists, and it’s empty.”

                        So:
                        No extra request
                        Cleaner serial output*/

                        client.println("<style>body { font-family: Arial; text-align: center; margin: 0px auto; padding-top: 30px;}");
                        client.println(".button { display: inline-block; background-color: #e7bd3b; border: none; ");
                        client.println("border-radius: 4px; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

                        client.println("</style></head>");
                        //head over body starts
                        client.println("<body>");

                        // Web Page Heading
                        client.println("<h1>ESP32 Web Server</h1>");
                        // Display current state, and ON/OFF buttons for GPIO 18
                        client.println("<p>Output - State " + outputState + "</p>");


                        if (outputState=="off") {
                            client.println("<a href=\"/output/on\" class=\"button\">ON</a>");
                        }
                        if (outputState=="on") {
                            client.println("<a href=\"/output/off\" class=\"button\">OFF</a>");
                        }
                        client.println("</body></html>");

                        //http response ends with another blank line
                        client.println();
                        //break out of the while loop
                        break;

                    }
                    else { //if only one newline
                        currentLine = ""; //clear current line
                    }
                } 
                else if (c!='\r') { //if the byte is not a carriage return character
                    currentLine+=c; //add it to the end of the currentLine
                }   
            }

        }
        //clear the header variable
        header = "";
        //close the connection
        client.stop();
        Serial.println("Client Disconnected\n");

    }
}

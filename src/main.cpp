#include <Arduino.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire onewire(2);
DallasTemperature sensor(&onewire);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
const IPAddress ip(192, 168, 0, 177);

EthernetServer server(80);

void setup() {
      Ethernet.begin(mac, ip);

      if (EthernetNoHardware == Ethernet.hardwareStatus())
      {
            while (true)
            {
                  delay(1); 
            }
      }
      while (LinkOFF == Ethernet.linkStatus())
      {
            delay(1000);
      }

      // start the server
      server.begin();
}

void loop()
{
      // listen for incoming clients
      EthernetClient client = server.available();
      if (client)
      {
            // NEW CLIENT;
            // an HTTP request ends with a blank line
            bool currentLineIsBlank = true;
            while (client.connected())
            {
                  if (client.available())
                  {
                        char c = client.read();
                        if (c == '\n' && currentLineIsBlank) // Request end
                        {
                              // send a standard HTTP response header
                              client.println("HTTP/1.1 200 OK");
                              client.println("Content-Type: text/html");
                              client.println("Connection: close"); // the connection will be closed after completion of the response
                              client.println("Refresh: 5");        // refresh the page automatically every 5 sec
                              client.println();
                              client.println("<!DOCTYPE HTML>");
                              client.println("<html>");

                              sensor.requestTemperatures();

                              client.println(sensor.getTempCByIndex(0));

                              client.println("</html>");
                              break;
                        }
                        if (c == '\n')
                        {
                              // New line
                              currentLineIsBlank = true;
                        }
                        else if (c != '\r')
                        {
                              currentLineIsBlank = false;
                        }
                  }
            }
            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
      }
}
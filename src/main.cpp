#include <Arduino.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "HTML.hpp"

OneWire onewire(7);
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

      sensor.begin();
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
                              HTML::print_header(client);

                              client.println("<html>");
                              HTML::print_head(client);

                              sensor.requestTemperatures();

                              client.println("<body>");

                              client.println("<div>");
                              client.println("<h2  style='font-size: 4em;'>Temperatura actual</h2>");
                              client.println("<p style='font-size: 8em;'>" + String(sensor.getTempCByIndex(0)) + "C</p>");
                              client.println("</div>");

                              client.println("</body>");

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
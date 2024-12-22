#include <Ethernet.h>

namespace HTML
{
      static const char header[86] = "HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\nRefresh: 5\n<!DOCTYPE HTML>";

      void print_header(EthernetClient client)
      {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response
            client.println("Refresh: 5");        // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
      }

      void print_head(EthernetClient client)
      {
            client.println("<head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("<title> Termometro </title>");
            client.println("<style>");
            client.println("body {");
            client.println("display: flex;");
            client.println("justify-content: center;");
            client.println("align-items: center;");
            client.println("height: 100vh;");
            client.println("margin: 0;");
            client.println("background: linear-gradient(to top, #87CEEB, #FFFFFF);");
            client.println("font-family: Arial, sans-serif;");
            client.println("}");
            client.println("p {text-align:center;}");
            client.println("h2 {text-align:center;}");
            client.println("</style>");
            client.println("</head>");
      }
};
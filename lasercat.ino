#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {  0x90, 0xA2, 0xDA, 0x00, 0x77, 0xF2 };
IPAddress gateway(0,0,0,0);
IPAddress subnet(255,255,255,0);
IPAddress ip(192,168,1,148);
EthernetServer server(80);
int ledPin = 13;                 // LED connected to digital pin 13


void EtherStart() {
  delay(500);
  Ethernet.begin(mac, ip, gateway, subnet);
  delay(1000);
  server.begin();
  delay(500);
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void setup() {
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  Serial.begin(9600);

  Serial.println("Starting w5100");
  EtherStart();
  
  digitalWrite(ledPin, LOW);    // sets the LED off
}

void loop() {
    digitalWrite(ledPin, LOW);    // sets the LED off
EthernetClient client = server.available();
  if (client) {
    

    
    
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      String request;
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
                    // add a meta refresh tag, so the browser pulls again every 5 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          client.println("<body>hi</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
        else if (c == '?') {

          
            digitalWrite(ledPin, HIGH);   // sets the LED on
            delay(1000);                  // waits for a second
        }
        else if (c == '#') {
            digitalWrite(ledPin, LOW);    // sets the LED off
  delay(1000);                  // waits for a second
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    

  }
  
}

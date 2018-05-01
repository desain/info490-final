/*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Limitations:
 *    only RSA certificates
 *    no support of Perfect Forward Secrecy (PFS)
 *    TLSv1.2 is supported since version 2.4.0-rc1
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

char const PRE_FACT = '+';
char const POST_FACT = '+';

const char* ssid = "IllinoisNet_Guest";//"ND";
const char* password = "";//"ooooiiii";

const char* host = "tmaalny5b1.execute-api.us-east-1.amazonaws.com";
String url = "/prod/info490-proxy";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "35 85 74 EF 67 35 A7 CE 40 69 50 F3 C0 F6 80 CF 80 3B 2E 19";

void setup() {
  Serial.begin(4800);
  Serial.println();
  Serial.print("connecting to ");
  Serial.print(ssid);
  Serial.print(' ');
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(" connected w/ IP ");
  Serial.println(WiFi.localIP());
}

void sendFact(char *fact) {
  Serial.print(PRE_FACT);
  Serial.print(fact);
  Serial.print(POST_FACT);
}
void sendFact(String fact) {
  sendFact(fact.c_str());
}

void loop() {
  if (Serial.available() == 0) {
    return;
  }
  Serial.read(); //just read anything as the signal to find a fact

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(' ');
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n"
               "User-Agent: ESP8266\r\n"
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  bool readingHeaders = true;
  while (readingHeaders) {
    if (!client.connected()) {
      sendFact("Cats hate when their WiFi connection is dropped");
    }
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") readingHeaders = false;
  }
  Serial.println("Finished headers");
  Serial.print(PRE_FACT);
  while (client.connected()) {
    char c = client.read();
    if (isAscii(c)) {
      Serial.print(c);
    }
  }
  Serial.print(POST_FACT);
  Serial.println("done!");
}

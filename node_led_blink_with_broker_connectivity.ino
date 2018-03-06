#include <PubSubClient.h>
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic



const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
char message_buff[100];

void callback(char* topic, byte* payload, unsigned int length) 
{
  
    int i = 0;

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length,DEC));
  
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
  
  Serial.println("Payload: " + msgString);
  int state = digitalRead(13);  // get the current state of GPIO1 pin
  /*
   * IO PIN MAPPING OF NODEMCU
   * 
   * IO INDEX - GPIO PINS
   * 
   * o-16
   * 1-5
   * 2-4
   * 3-0
   * 4-2
   * 5-14
   * 6-12
   * 7-13
   * 8-15
   * 9-3
   * 10-1
   * 11-9
   * 12-10
   * 
   */

  if (msgString == "Light1"){    // if there is a "1" published to any topic (#) on the broker then:
    digitalWrite(13, LOW);     // set pin to the opposite state 
    Serial.println("Switching Light1 ON"); 
  }
  else if(msgString == "Light1OFF")
  {
    digitalWrite(13, HIGH);     // set pin to the opposite state 
    Serial.println("Switching Light1 OFF"); 
  }
//  if (msgString == "FON"){    // if there is a "1" published to any topic (#) on the broker then:
//    digitalWrite(5, LOW);     // set pin to the opposite state 
//    Serial.println("Switching F ON"); 
//  }
//  else if(msgString == "FOFF")
//  {
//  
//    digitalWrite(5, HIGH);     // set pin to the opposite state 
//    Serial.println("Switching F OFF"); 
//  }       //fsot6s9k7d
//  if (msgString == "L2ON"){    // if there is a "1" published to any topic (#) on the broker then:
//    digitalWrite(4, LOW);     // set pin to the opposite state 
//    Serial.println("Switching L2 ON"); 
//  }
//  else if(msgString == "L2OFF")
//  {
//  
//    digitalWrite(4, HIGH);     // set pin to the opposite state 
//    Serial.println("Switching L2 OFF"); 
//  }
//  if (msgString == "BLON"){    // if there is a "1" published to any topic (#) on the broker then:
//    digitalWrite(0, LOW);     // set pin to the opposite state 
//    Serial.println("Switching BL ON"); 
//  }
//  else if(msgString == "BLOFF")
//  {
//  
//    digitalWrite(0, HIGH);     // set pin to the opposite state 
//    Serial.println("Switching BL OFF"); 
//  }
//  if (msgString == "PPON"){    // if there is a "1" published to any topic (#) on the broker then:
//    digitalWrite(2, HIGH);     // set pin to the opposite state 
//    Serial.println("Switching PP ON"); 
//  }
//  else if(msgString == "PPOFF")
//  {
//  
//    digitalWrite(2, LOW);     // set pin to the opposite state 
//    Serial.println("Switching PP OFF"); 
//  }
//  if (msgString == "SLON"){    // if there is a "1" published to any topic (#) on the broker then:
//    digitalWrite(14, HIGH);     // set pin to the opposite state 
//    Serial.println("Switching SL ON"); 
//  }
//  else if(msgString == "SLOFF")
//  {  
//    digitalWrite(14, LOW);     // set pin to the opposite state 
//    Serial.println("Switching SL OFF"); 
//  }
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
    // client.publish("kazi/shubham/saif/rishabh");
      // ... and resubscribe
      client.subscribe("kazi/shubham/saif/rishabh");
    }
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(13, OUTPUT);
//  pinMode(5, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(0, OUTPUT);
//  pinMode(2, OUTPUT);
//  pinMode(14, OUTPUT);
  digitalWrite(13,HIGH);
//  digitalWrite(5,HIGH);
//  digitalWrite(4,HIGH);
//  digitalWrite(0,HIGH);
//  digitalWrite(2,HIGH);
//  digitalWrite(14,HIGH);
  Serial.begin(115200);
  delay(10);
  WiFiManager wifiManager;
  //1wifiManager.resetSettings(); 
  wifiManager.autoConnect("NodeMCU");
  Serial.println("Connected to network!!!");
  Serial.println();
  Serial.println();  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void loop() 
{
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2000) 
  {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Hey!! I'm alive #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    //client.publish("<OUT TOPIC>", msg);
  }
}

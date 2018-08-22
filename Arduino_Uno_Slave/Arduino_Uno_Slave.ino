#include <Wire.h>
#include <ArduinoJson.h>


void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Serial.begin(115200);           /* start serial for debug */

  pinMode(3, OUTPUT);
 
}

void loop() {
 delay(100);
}

void processCall(String command){
      DynamicJsonBuffer jsonBuffer;
      JsonObject& root= jsonBuffer.parseObject(command);
      
       if (root.success()) {
          int gpio = atoi(root["gpio"]);
          Serial.println(gpio);
          int state = atoi(root["state"]);
          Serial.println(state);

          //set GPIO state  
          digitalWrite(gpio, state);
       }
}


// function that executes when data is received from master
void receiveEvent(int howMany) {
  String data="";
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    data += c;
    
  }
    Serial.println(data);           /* print the request data */
    processCall(data);         /* to newline */
}


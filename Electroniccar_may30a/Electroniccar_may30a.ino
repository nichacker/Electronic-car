#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX

void stopMotors() {
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}

void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  Serial.println("Bluetooth Car Ready");
  Serial.println("Waiting for commands...");
  
  // Test motors on startup
  Serial.println("Testing motors...");
  digitalWrite(11, HIGH);
  delay(200);
  digitalWrite(11, LOW);
  delay(100);
  
  stopMotors();
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();
    
    // Debug: Show exactly what we received
    Serial.print("Received: ");
    Serial.print(command);
    Serial.print(" (ASCII: ");
    Serial.print((int)command);
    Serial.println(")");
    
    switch (command) {
      case 'F':
      case 'f':  // Try both uppercase and lowercase
        Serial.println("Command: FORWARD");
        stopMotors();
        digitalWrite(11, HIGH);
        digitalWrite(8, HIGH);
        break;
        
      case 'B':
      case 'b':
        Serial.println("Command: BACKWARD");
        stopMotors();
        digitalWrite(10, HIGH);
        digitalWrite(9, HIGH);
        break;
        
      case 'L':
      case 'l':
        Serial.println("Command: LEFT");
        stopMotors();
        digitalWrite(10, HIGH);
        digitalWrite(8, HIGH);
        break;
        
      case 'R':
      case 'r':
        Serial.println("Command: RIGHT");
        stopMotors();
        digitalWrite(11, HIGH);
        digitalWrite(9, HIGH);
        break;
        
      case 'S':
      case 's':
        Serial.println("Command: STOP");
        stopMotors();
        break;
        
      default:
        Serial.print("Unknown command: ");
        Serial.println(command);
        stopMotors();
        break;
    }
  }
}
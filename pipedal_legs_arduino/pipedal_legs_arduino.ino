#include <Servo.h>

int received_serial_message[11];
int old_serial_message[11];
bool receivingData = false;
int index = 0;

Servo sl_1;
Servo sl_2;
Servo sl_3;
Servo sl_4;
Servo sl_5;

Servo sr_1;
Servo sr_2;
Servo sr_3;
Servo sr_4;
Servo sr_5;

int start_position[10]={90,180,25,155,55,
                        90,15,140,25,105};
int set_position[10];

void process_data(){
  // Print the received array
  for (int i = 0; i < 11; i++) {
    Serial.print("Element ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(received_serial_message[i]);
  }
}

void set_servos(int message[10]){
  sl_1.write(message[0]);
  sl_2.write(message[1]);
  sl_3.write(message[2]);
  sl_4.write(message[3]);
  sl_5.write(message[4]);

  sr_1.write(message[5]);
  sr_2.write(message[6]);
  sr_3.write(message[7]);
  sr_4.write(message[8]);
  sr_5.write(message[9]);
}

// Modes to put robot servos in.
// Mode 0: start position
// Mode 1: move based on input
// Mode 2: freeze in place
// Mode 3: cut power
int mode = 0;

void setup() {
  // put your setup code here, to run once:
  sl_1.attach(6);
  sl_2.attach(5);
  sl_3.attach(7);
  sl_4.attach(8);
  sl_5.attach(9);

  sr_1.attach(A4);
  sr_2.attach(A3);
  sr_3.attach(A2);
  sr_4.attach(A1);
  sr_5.attach(A0);

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveMessage();
  if (received_serial_message[0] != old_serial_message[0]) {
    mode = received_serial_message[0];
    Serial.print("Mode changed to: ");
    Serial.println(mode);
    memcpy(old_serial_message,received_serial_message,sizeof(received_serial_message));
  }
  
  if (mode == 0){
    memcpy(set_position,start_position,sizeof(start_position));
    set_servos(set_position);
  }
  
  if (mode == 1){
    for (int i = 0; i <10; i++) {
      set_position[i] = received_serial_message[i+1];
    }
    set_servos(set_position);
  }
}

void receiveMessage() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();

    if (receivedChar == '<') {
      receivingData = true;
      index = 0;
    }

    else if (receivedChar == '>') {
      receivingData = false;
      process_data();
    }

    else if (receivingData) {
      // Expecting two bytes per integer
      if (index < 11 * 2) {
        int byteIndex = index % 2;
        if (byteIndex == 0) {
          // First byte (low byte)
          received_serial_message[index / 2] = receivedChar & 0xFF;
        } else {
          // Second byte (high byte)
          received_serial_message[index / 2] |= (receivedChar & 0xFF) << 8;
        }
        index++;
      }
    }
  }
 }
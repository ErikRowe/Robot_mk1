#include <Servo.h>

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
// Mode 1: move based on input from uart
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

  Serial.begin()9600;
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mode == 0){
    memcpy(set_position,start_position,sizeof(start_position));
    set_servos(set_position);
  }

}

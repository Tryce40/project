#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
 
#define ENA  0
#define ENB  1
#define IN1 23
#define IN2 24
#define IN3  4
#define IN4 17
 
  int seq[4][4] = {{0, 1, 0, 1},
                   {1, 0, 0, 1},
                   {1, 0, 1, 0},
                   {0, 1, 1, 0}};
 
 
void setup() {
    wiringPiSetup();
        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
 
        delay(30);
 
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
}
 
void reverse(int steps, int d) {    //i: steps, j: delay
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
 
   for(int i=0; i<steps; i++) {
    for(int j=4; j>0; j--) {
      digitalWrite(IN1, seq[j][0]);
      digitalWrite(IN1, seq[j][1]);
      digitalWrite(IN1, seq[j][2]);
      digitalWrite(IN1, seq[j][3]);
      delay(d);
    }
  }
 
 digitalWrite(ENA, LOW);
 digitalWrite(ENB, LOW);
}
 
void forward(int steps, int d) {    // i: steps, j: delay
  digitalWrite(ENA, HIGH);      // enable both motors (bi-polar)
  digitalWrite(ENB, HIGH);
 
 
  for(int i=0; i<steps; i++) {      // loop for # of steps
    for(int j=0; j<4; j++) {        // write sequence at each step
      digitalWrite(IN1, seq[j][0]);
      digitalWrite(IN1, seq[j][1]);
      digitalWrite(IN1, seq[j][2]);
      digitalWrite(IN1, seq[j][3]);
      delay(d);
    }
  }
 
  digitalWrite(ENA, LOW);       // disable both motors
  digitalWrite(ENB, LOW);
}
 
 
int main(void) {
    setup();
       
        forward(80, 20);
        reverse(80, 20);
 
    return 0;
}

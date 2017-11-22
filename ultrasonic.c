#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
 
#define TRIG 0
#define ECHO 1
 
void setup() {
    printf("Attempting to setup wiringPi.\n");     
    if(wiringPiSetup()) {                   // wiringPiSetup() return 1 on failure
        printf("Setup wiringPi failed!\n");             //            0 on success
    } else {
        printf("Setup wiringPi successfully.\n");
    }
 
    printf("Set TRIG pin to %d\n", TRIG);           // initialize ports as either inputs or outputs
        pinMode(TRIG, OUTPUT);
    printf("Set ECHO pin to %d\n", ECHO);
        pinMode(ECHO, INPUT);
 
        digitalWrite(TRIG, LOW);                //TRIG pin must start LOW
        delay(30);
}
 
int getCM() {
    long timeToTerminate, startTime, maxDelay;          // inialize variables
        maxDelay = 35736;                       // ensure waves will not interfere with eachother
 
        digitalWrite(TRIG, HIGH);                   // emit ultrasonic wave for 20 microseconds
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
    /*
     *  Wait for echo start
     */
        timeToTerminate = micros() + maxDelay;              // micros() gives the current time in microseconds                 
        while(digitalRead(ECHO) == LOW && micros() < timeToTerminate); 
    /*
     *  Wait for echo end
     */
        startTime = micros();
    timeToTerminate = micros() + maxDelay;
        while(digitalRead(ECHO) == HIGH && micros() < timeToTerminate); // loop will break when signal is lost
    long travelTime = micros() - startTime;
        int distance = travelTime/58;                   // covert distance to centimeters
 
        return distance;
}
 
int main(void) {
    setup();
    while(1) {
            printf("Distance: %dcm\n", getCM());
        delayMicroseconds(357360);
    }
    return 0;
}

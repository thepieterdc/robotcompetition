/* 
 * File:   main.c
 * Author: pieter
 *
 * Created on 7 april 2017, 17:20
 */
#include <dwengoConfig.h>
#include <dwengoADC.h>
#include <dwengoBoard.h>
#include <dwengoLCD.h>
#include <dwengoMotor.h>

#define MOTOR_LINKS setSpeedMotor2
#define MOTOR_RECHTS setSpeedMotor1

#define GROND_VOOR 2
#define GROND_ACHTER 1
#define VER_LINKS 0
#define VER_RECHTS 3

void vooruit(int spd);

void achteruit(int spd);

void links_terplekke(int spd);

void links_vooruit(int spd);

void rechts_terplekke(int spd);

void rechts_vooruit(int spd);

int sensor(int adc);

void stop();
    
int main(int argc, char** argv) {
    initBoard();
    backlightOn();
    initMotor();
    initADC();
    initLCD();
    
    while(1) {
        if(sensor(GROND_VOOR) > 250 && sensor(GROND_ACHTER) < 250) {
            vooruit(1023);
        } if(sensor(GROND_VOOR) < 250 && sensor(GROND_ACHTER) > 250) {
            achteruit(1023);
        }
    }
}

void vooruit(int spd) {
    MOTOR_LINKS(spd);
    MOTOR_RECHTS(spd);
}

void achteruit(int spd) {
    MOTOR_LINKS(-spd);
    MOTOR_RECHTS(-spd);
}

void links_terplekke(int spd) {
    MOTOR_LINKS(spd);
    MOTOR_RECHTS(-spd);
}

void links_vooruit(int spd) {
    MOTOR_LINKS(spd);
    MOTOR_RECHTS(spd*2/3);
}

void rechts_terplekke(int spd) {
    MOTOR_LINKS(-spd);
    MOTOR_RECHTS(spd);
}

void rechts_vooruit(int spd) {
    MOTOR_LINKS(spd*2/3);
    MOTOR_RECHTS(spd);
}

int sensor(int adc) {
    return readADC(adc);
}

void stop() {
    MOTOR_LINKS(0);
    MOTOR_RECHTS(0);
}
/* 
 * File:   main.c
 * Author: pieter
 *
 * Created on 7 april 2017, 17:20
 */
#include <dwengoConfig.h>
#include <dwengoADC.h>
#include <dwengoBoard.h>
#include <dwengoMotor.h>

typedef int bool;
#define true 1
#define false 0

#define MOTOR_LINKS setSpeedMotor2
#define MOTOR_RECHTS setSpeedMotor1

#define VER_THRESHOLD 150

#define MOTORSPEED 1000

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

bool lijncheck();
    
int starti;
int startk;
int i;
int threshold;
int klaar;
bool kant;

int main(int argc, char** argv) {
    initBoard();
    initMotor();
    initADC();
    kant = false;
    
    while(SW_C != PRESSED);
    starti = 5;
    while(starti > 0) {
        startk = 25;
        LEDS = (startk << 3) + starti;
        while(startk > 0) {
            LEDS = (startk << 3) + starti;
            startk--;
            delay_ms(40);
        }
        starti--;
    }
    vooruit(MOTORSPEED);
    delay_ms(900);
    stop();
    delay_ms(8500);
    while(1){
        if(lijncheck()) continue;
        if(sensor(VER_LINKS) >= VER_THRESHOLD && sensor(VER_RECHTS) >= VER_THRESHOLD) {
            vooruit(MOTORSPEED);
        } else if(sensor(VER_LINKS) >= VER_THRESHOLD) {
            links_vooruit(MOTORSPEED);
        } else if(sensor(VER_RECHTS) >= VER_THRESHOLD) {
            rechts_vooruit(MOTORSPEED);
        } else {
            kant = !kant;
            klaar = 0;
            i = 0;
            threshold = 32;
            
            if(!kant) {
                links_terplekke(600);
            } else {
                rechts_terplekke(600);
            }
            
            
            while(klaar < 5) {
                if(lijncheck()) break;
                i++;
                if(sensor(VER_LINKS) >= VER_THRESHOLD-10 || sensor(VER_RECHTS) >= VER_THRESHOLD-10) {
                    klaar++;
                }
                if(i > threshold) {
                    i = 0;
                    threshold *= 2;
                    kant = !kant;
                    if(!kant) {
                        links_terplekke(600);
                    } else {
                        rechts_terplekke(600);
                    }
                }
                delay_ms(20);
            }
        }
        delay_ms(50);
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

bool lijncheck() {
    if(sensor(GROND_VOOR) > 250 && sensor(GROND_ACHTER) < 250) {
        vooruit(MOTORSPEED);
        delay_ms(200);
        return true;
    } if(sensor(GROND_VOOR) < 250 && sensor(GROND_ACHTER) > 250) {
        achteruit(MOTORSPEED);
        delay_ms(200);
        return true;
    }
    return false;
}
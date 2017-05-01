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

int main(int argc, char** argv) {
    initBoard();
    backlightOn();
    initLCD();
    initADC();
    
    while(1) {
        clearLCD();
        printIntToLCD(readADC(0), 0, 0);
        printIntToLCD(readADC(1), 1, 1);
        delay_ms(500);
    }
}
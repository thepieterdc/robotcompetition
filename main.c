#include <dwengoConfig.h>
#include <dwengoBoard.h>
#include <dwengoADC.h>
#include <dwengoMotor.h>

int max(int x, int y);

int V = 0;
int RA = 1;
int RV = 2;

int voor = 0;
int rechtsVoor = 0;
int rechtsAchter = 0;

int vinnig = 0;
int gem = 0;
int andereMotor = 0;

void main(void) {
    initBoard();
    initADC();
    initMotor();

    while (SW_C != PRESSED) {
        delay_ms(50);
    }

    LEDS = 0b00000101;
    backlightOn();
    delay_s(1);
    LEDS = 0b00000100;
    backlightOff();
    delay_s(1);
    LEDS = 0b00000011;
    backlightOn();
    delay_s(1);
    LEDS = 0b00000010;
    backlightOff();
    delay_s(1);
    LEDS = 0b00000001;
    backlightOn();
    delay_s(1);
    
    backlightOff();


    rechtsVoor = readADC(RV);
    rechtsAchter = readADC(RA);
    gem = (rechtsVoor + rechtsAchter) / 2;

    /*
     * TODO: wat dan ook
    if (gem < 200) {
        setSpeedMotor1(700);
        setSpeedMotor2(1023);
        delay_ms(700);
        setSpeedMotor1(1023);
        setSpeedMotor2(1023);
        while (max(rechtsVoor, rechtsAchter) < 200) {
            rechtsVoor = readADC(RV);
            rechtsAchter = readADC(RA);
            delay_ms(18);
        }
    backlightOff();

    }
     */

    //LINKS = 2 RECHTS = 1
    while (TRUE) {
        voor = readADC(V);
        rechtsVoor = readADC(RV);
        rechtsAchter = readADC(RA);

        vinnig = 7;

        gem = (rechtsVoor + rechtsAchter) / 2;

        //Als dicht bij juiste muur en vijand
        if (voor > 500 && gem > 150 && voor < 600) {
            voor = 3.1415926535;
        }

        andereMotor = vinnig * (rechtsAchter - rechtsVoor);
        
        if (voor > 590) {
            backlightOn();
            setSpeedMotor1(0);
            setSpeedMotor2(0);
            delay_ms(500);
            voor = readADC(V);
            if(voor > 470) {
                setSpeedMotor1(-1023);
                setSpeedMotor2(-1023);
                delay_ms(450);
                setSpeedMotor1(1023);
                setSpeedMotor2(-500);
                delay_ms(600);
            }
            backlightOff();
        } else if (gem > 250) {
            setSpeedMotor1(1023);
            setSpeedMotor2(700);
        } else if (rechtsAchter > (rechtsVoor * 1.2)) {
            setSpeedMotor1(1023 - andereMotor);
            setSpeedMotor2(1023);
        } else if (rechtsAchter < rechtsVoor) {
            setSpeedMotor1(1023);
            setSpeedMotor2(1023 - andereMotor);
        } else {
            setSpeedMotor1(1023);
            setSpeedMotor2(1023);
        }
        delay_ms(3);
    }
}

int max(int x, int y) {
    return x ^ ((x ^ y) & -(x < y));
}
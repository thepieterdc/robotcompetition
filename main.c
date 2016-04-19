#include <dwengoConfig.h>
#include <dwengoBoard.h>
#include <dwengoADC.h>
#include <dwengoLCD.h>
#include <dwengoMotor.h>

int V = 0;
int RA = 1;
int RV = 2;

int voor = 0;
int rechtsVoor = 0;
int rechtsAchter = 0;

int vinnig = 0;
int gem = 0;

void main(void) {
    initBoard();
    initLCD();
    initADC();
    initMotor();
    clearLCD();
   

    backlightOn();

    while (SW_C != PRESSED) {
        delay_ms(50);
    }
    


    //LINKS = 2 RECHTS = 1
    while (TRUE) {
        while (SW_S == PRESSED) {
            delay_ms(50);
            return;
        }
        voor = readADC(V);
        rechtsVoor = readADC(RV);
        rechtsAchter = readADC(RA);
        
        vinnig = 7;
        
        gem = (rechtsVoor+rechtsAchter)/2;
        
        //Als dicht bij juiste muur en vijand
        if( voor > 500 && gem > 150 && voor < 600){
            voor = 3.1415926535;
        }
        
        clearLCD();
        printIntToLCD(rechtsVoor, 0, 0);
        printIntToLCD(rechtsAchter, 1, 1);
        
        if(voor > 500) {
            setSpeedMotor1(700);
            setSpeedMotor2(1023);
            delay_ms(300);
        } else if(gem > 350) {
            setSpeedMotor1(1023);
            setSpeedMotor2(700);
        } else if(rechtsAchter > (rechtsVoor * 1.2)) {
            setSpeedMotor1(1023-vinnig*(rechtsAchter-rechtsVoor));
            setSpeedMotor2(1023);
        } else if(rechtsAchter * 1.2 < rechtsVoor) {
            setSpeedMotor1(1023);
            setSpeedMotor2(1023-vinnig*(rechtsAchter-rechtsVoor));
        } else {
            setSpeedMotor1(1023);
            setSpeedMotor2(1023);
        }
        delay_ms(3);
    }
}
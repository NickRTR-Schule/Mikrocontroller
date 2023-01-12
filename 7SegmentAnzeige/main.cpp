#include "mbed.h"

//                                  0           1           2           3           4           5           6           7           8           9           
const char anzeigeTabelle[10]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b11111101, 0b00000111, 0b01111111, 0b11101111};

void anzeigen(int zaeler) {
    while(true) {
        int zehner = zaeler / 10;
        int einser = zaeler - zehner * 10;

        zehnerStelle = 1;
        anzeige = anzeigeTabelle[zehner];
        thread_sleep_for(10);
        zehnerStelle = 0;

        einerStelle = 1;
        anzeige = anzeigeTabelle[einser];
        thread_sleep_for(10);
        einerStelle = 0;
    }
}

int main()
{
    DigitalOut einerStelle(PC_11);
    DigitalOut zehnerStelle(PC_12);

    PortOut anzeige(PortC, 0xFF);

    // count up
    DigitalIn buttonUp(PB_4);
    buttonUp.mode(PullDown);

    // count down
    DigitalIn buttonDown(PB_3);
    buttonDown.mode(PullDown);

    // reset
    DigitalIn buttonReset(PB_0);
    buttonDown.mode(PullDown);

    int zaeler = 0;

    while (true) {
        if (buttonUp == true) {
            zaeler++;
        }

        if (buttonDown == true) {
            zaeler--;
        }

        if (buttonReset = true) {
            zaeler = 0;
        }

        while (buttonUp == true || buttonDown == true || buttonReset == true) {} // only count on flanks

        if (zaeler == 100 || zaeler < 0) {
            zaeler = 0;
        }

        anzeigen(zaeler);
    }
}

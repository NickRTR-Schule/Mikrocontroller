#include "mbed.h"
#include "MFS.h"

Ticker tick;
Ticker ticktick;
MFS display;

int displayNr = 0x1000;

int wert = 0;
int digit = 0;

int seg7[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int dig[4] = {0x1000, 0x2000, 0x4000, 0x8000};

void zaehlerErhoehen() {
    wert++;
    if (wert == 10000) wert = 0;
}

void anzeigeAktualisieren() {
    int ziffer = (int)(wert/(pow(10,digit))) % 10;
    display = dig[digit] + seg7[ziffer];

    digit++;
    if (digit==4) digit = 0;
}

int main() {
    tick.attach(&anzeigeAktualisieren, 5ms);
    ticktick.attach(&zaehlerErhoehen, 250ms);
}

#include "mbed.h"
#include "platform/mbed_thread.h"
#include <cstdio>
#include "LCD.h"

DigitalOut trigger(PA_10);
InterruptIn echoR(PC_8);
InterruptIn echoL(PC_9);

int laufzeitR;
int laufzeitL;

lcd mylcd;

// Motor
DigitalOut m1(PC_1);
DigitalOut m2(PC_7);

void fahreGeradeaus() {
    m1 = 1;
    m2 = 1;
}

void fahreRechts() {
    m1 = 0;
    m2 = 1;
}

void fahreLinks() {
    m1 = 1;
    m2 = 0;
}

void stopp() {
    m1 = 0;
    m2 = 0;
}

void fahren() {
    if (laufzeitL/58 < 20 && laufzeitR/58 < 20) {
        stopp();
    } else if (laufzeitL/58 < 20) {
        fahreRechts();
    } else if (laufzeitR/58 < 20) {
        fahreLinks();
    } else {
        fahreGeradeaus();
    }
}

void init() {
    RCC->APB1ENR |= 0b100000;
    TIM7->PSC=31; // Takt in µs
    TIM7->ARR=10;
    TIM7->CNT=0;
    TIM7->CR1=1;

    RCC->APB1ENR |= 0b10000;
    TIM6->PSC=31; // Takt in µs
    TIM6->ARR=0xFFFF;
    TIM6->CNT=0xFFFF;
    TIM6->CR1=1;

    RCC->APB1ENR |= 0b1000;
    TIM5->PSC=31; // Takt in µs
    TIM5->ARR=0xFFFF;
    TIM5->CNT=0xFFFF;
    TIM5->CR1=1;
}

void echoARise() {
    TIM6->CNT=0;
}

void echoAFall() {
    laufzeitR = TIM6->CNT;
}

void echoBRise() {
    TIM5->CNT=0;
}

void echoBFall() {
    laufzeitL = TIM5->CNT;
}

void anzeigen() {
    mylcd.printf("Abstand L: %dcm", laufzeitL/58);
    mylcd.cursorpos(40);
    mylcd.printf("Abstand R: %dcm", laufzeitR/58);
    //thread_sleep_for(250);
}

int main() {
    mylcd.cursorpos(0);

    __enable_irq();

    init();

    echoR.mode(PullDown);
    echoR.rise(&echoARise);
    echoR.fall(&echoAFall);

    echoL.mode(PullDown);
    echoL.rise(&echoBRise);
    echoL.fall(&echoBFall);

    while(true) {

        trigger = true;

        if (TIM7->SR==1) {
            trigger = false;
        }
        anzeigen();
        mylcd.clear();
        fahren();
    }
}
 


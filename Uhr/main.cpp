#include "mbed.h"
#include "platform/mbed_thread.h"
#include "LCD.h"
#include <string>

int zeit = 0;
lcd mylcd;

void init() {
    RCC->APB1ENR |= 0b10000;
    TIM6->PSC=31999; // Takt in ms
    TIM6->ARR=999; // -> 1s Timer
    TIM6->CNT=0;
    TIM6->SR=0;
    TIM6->CR1=1;
}

void stundenRise() {
    zeit += 3600;
}

void minutenRise() {
    zeit += 60;
}

void sekundenRise() {
    zeit += 1;
}

int main() {
    init();

    mylcd.cursorpos(0);

    InterruptIn stundenButton(PA_1);
    InterruptIn minutenButton(PA_6);
    InterruptIn sekundenButton(PA_10);

    stundenButton.mode(PullDown);
    minutenButton.mode(PullDown);
    sekundenButton.mode(PullDown);

    stundenButton.rise(&stundenRise);
    minutenButton.rise(&minutenRise);
    sekundenButton.rise(&sekundenRise);

    __enable_irq();

    while(true) {   
        if (TIM6->SR==1) {
            TIM6->SR=0;
            zeit++;

            mylcd.clear();
            int stunden = zeit / 3600;
            int minuten = (zeit - stunden * 3600) / 60;
            int sekunden = zeit - stunden * 3600 - minuten * 60;
            mylcd.printf("%d:%d:%d", stunden, minuten, sekunden);
        }
    }
}
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
    TIM6->CR1=0;
}

void startRise() {
    TIM6->CR1=1;
}

void stoppRise() {
    TIM6->CR1=0;
}

void resetRise() {
    zeit = 0;
    TIM6->CNT=0;
}

int main() {
    init();

    mylcd.clear();
    mylcd.cursorpos(0);
    mylcd.printf("Press PA1 to");
    mylcd.cursorpos(40);
    mylcd.printf("start -_-");

    InterruptIn startButton(PA_1);
    InterruptIn stoppButton(PA_6);
    InterruptIn resetButton(PA_10);

    startButton.mode(PullDown);
    stoppButton.mode(PullDown);
    resetButton.mode(PullDown);

    startButton.rise(&startRise);
    stoppButton.rise(&stoppRise);
    resetButton.rise(&resetRise);

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
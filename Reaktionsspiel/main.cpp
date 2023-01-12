#include "mbed.h"
#include "mbed_thread.h"
#include "LCD.h"
#include <cstdio>

InterruptIn button(PA_1);
DigitalOut led(PC_1);
PortOut leds(PortC);

lcd mylcd;
int score = 0;

void buttonRise() {
    if (leds == 0b00100000) {
        score += 1;
    } else if (leds != 0b00100000 && score > 0) {
        score -= 1;
    }
}

int main()
{
    button.mode(PullDown);
    button.rise(&buttonRise);
    button.enable_irq();

    mylcd.clear();

    leds = 0b10000000;

    while(true) {
        if (leds == 0b10000000) {
            leds = 0b00000001;
            thread_sleep_for(350);
        }
        leds = leds<<1;
        thread_sleep_for(200);

        mylcd.cursorpos(0);
        mylcd.printf("Punktzahl: %d", score);
        printf("Punktzahl: %d\n", score);
    }
}

#include "mbed.h"
#include "platform/mbed_thread.h"

#define SIRENE_DELAY 500

int main()
{
    DigitalOut sirene(PC_0);
    DigitalIn button(PB_0);
    button.mode(PullDown);

    bool scharf = false;

    while (true) {
        if (button == true) {
            scharf = !scharf;
            thread_sleep_for(20); // prellen verhindern
        }

        while(button == true) {}

        while (scharf == true) {
            sirene = true;
            thread_sleep_for(SIRENE_DELAY);
            sirene = false;
            thread_sleep_for(SIRENE_DELAY);
        }
    }
}


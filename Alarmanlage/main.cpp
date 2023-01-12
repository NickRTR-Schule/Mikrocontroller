#include "PinNamesTypes.h"
#include "mbed.h"
#include "platform/mbed_thread.h"

#define SIRENE_DELAY 500

int main()
{
    DigitalOut sirene(PC_0);

    DigitalOut gelb(PC_1);
    DigitalOut rot(PC_2);
    DigitalOut blau(PC_3);

    DigitalIn button(PB_0);
    button.mode(PullDown);

    DigitalIn magnet(PB_1);
    magnet.mode(OpenDrain);

    DigitalIn lichtschranke(PB_3);
    lichtschranke.mode(PullDown);

    DigitalIn mikrofon(PB_2);
    mikrofon.mode(OpenDrain);

    DigitalOut status(LED1);

    bool scharf = false; // Alarmanlage ist Anfangs ausgeschalten

    while (true) {
        // Button schält Alarmanlage scharf und nicht scharf
        if (button == 0) {
            scharf = !scharf;
            thread_sleep_for(20);
        }

        while (button == 0) {}

        if (scharf == true) {
            status = true;
            // wenn die Alarmanlage scharf ist und magnet, lichtschranke oder Mikrofon ausgelöst haben ertönt der Alarm
            if (magnet == 0 || lichtschranke == 1 || mikrofon == 0) {
                sirene = true;
            }
        } else {
            // Wird die Alarmanlage abgestellt verstummt der Alarm
            status = false;
            sirene = false;
        }
    }
}


#include "InterruptIn.h"
#include "PinNamesTypes.h"
#include "PortNames.h"
#include "PortOut.h"
#include "mbed.h"

InterruptIn button(PA_1);
InterruptIn button2(PA_6);

DigitalOut led(PC_1);
PortOut port(PortC);

void buttonRise() {
    led = true;
}

void button2Rise() {
    led = false;
}

int main()
{
    button.mode(PullDown);
    button2.mode(PullDown);
    button.rise(&buttonRise);
    button2.rise(&button2Rise);
    button.enable_irq();
}

#include "LCD.h"
#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE 20ms
BufferedSerial hc05(PB_10, PB_11, 9600);
DigitalOut lm_u(PC_7);
DigitalOut lm_o(PC_6);
DigitalOut rm_u(PC_0);
DigitalOut rm_o(PC_1);
lcd mylcd;
int main() {
  char daten[15];
  int anz;
  mylcd.clear();
  mylcd.cursorpos(0);
  while (true) {
    if (hc05.readable()) {
      ThisThread::sleep_for(BLINKING_RATE);
      anz = hc05.read(daten, 15);
      for (int i = 0; i < anz; i++) {
        if (daten[i] == 'F') {
          lm_u = 1;
          rm_u = 1;
          lm_o = 0;
          rm_o = 0;
        };

        if (daten[i] == 'B') {
          lm_u = 0;
          rm_u = 0;
          lm_o = 1;
          rm_o = 1;
        };

        if (daten[i] == 'X') {
          lm_o = 0;
          rm_o = 0;
          lm_u = 0;
          rm_u = 0;
        };

        if (daten[i] == 'R') {
          lm_o = 0;
          rm_o = 0;
          lm_u = 0;
          rm_u = 1;
        };

        if (daten[i] == 'L') {
          lm_o = 0;
          rm_o = 0;
          lm_u = 1;
          rm_u = 0;
        };

        mylcd.cursorpos(0);
        mylcd.printf("Empfangen: %c", daten[i]);
      }
    }
    ThisThread::sleep_for(BLINKING_RATE);
  }
}
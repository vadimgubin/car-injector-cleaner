#include <Arduino.h>

#include <string.h>
#include "PWM.h"

const int pin_1A = 8;
const int pin_1B = 7;
const int pin_1C = 9; //button

const int pin_2A = 4;
const int pin_2B = 5;
const int pin_2C = 6; //button

const int pwm = 10;

unsigned char enc_1A = 1;
unsigned char enc_1B = 1;
unsigned char enc_2A = 1;
unsigned char enc_2B = 1;

int fr = 3; //value from 1 to 2000
int wd = 128; //value from 1 to

char code1[] = "    ";
char code2[] = "    ";
int cnt1 = 0;
int cnt2 = 0;

void readEncoder1();

void readEncoder2();

void setup() {
    pinMode(pin_1A, INPUT);
    pinMode(pin_1B, INPUT);
    pinMode(pin_1C, INPUT);

    pinMode(pin_2A, INPUT);
    pinMode(pin_2B, INPUT);
    pinMode(pin_2C, INPUT);

    //  pinMode(LED_BUILTIN, OUTPUT);
    pinMode(pwm, OUTPUT);
    Serial.begin(9600);
    InitTimersSafe();

}

void loop() {
    readEncoder1();
    readEncoder2();
}

void setPwm() {
    Serial.println(fr);
    Serial.println(wd);
    SetPinFrequencySafe(pwm, fr);
    pwmWrite(pwm, wd);
}

void readEncoder1() {
    unsigned char encoder_A = digitalRead(pin_1A); // read encoder_A state
    unsigned char encoder_B = digitalRead(pin_1B); // read encored_B state
    if (encoder_A != enc_1A) {
        enc_1A = encoder_A;// save encoder_A state
        code1[cnt1] = 'A';
        cnt1++;
    }

    if (encoder_B != enc_1B) {
        enc_1B = encoder_B; //save encoder_B state
        code1[cnt1] = 'B';
        cnt1++;
    }

    if (cnt1 == 4) {
        cnt1 = 0;
        if (strcmp(code1, "ABAB") == 0) {
            // increment
            if (wd < 255) {
                wd++;
            }
            setPwm();
        }

        if (strcmp(code1, "BABA") == 0) {
            // decrement
            if (wd > 1) {
                wd--;
            }
            setPwm();
        }
    }


}

void readEncoder2() {
    unsigned char encoder_A = digitalRead(pin_2A);
    unsigned char encoder_B = digitalRead(pin_2B);
    if (encoder_A != enc_2A) {
        enc_2A = encoder_A;
        code2[cnt2] = 'A';
        cnt2++;
    }

    if (encoder_B != enc_2B) {
        enc_2B = encoder_B;
        code2[cnt2] = 'B';
        cnt2++;
    }

    if (cnt2 == 4) {
        cnt2 = 0;
        if (strcmp(code2, "ABAB") == 0) {
            // increment
            if (fr < 2000) {
                fr++;
            }
            setPwm();
        }

        if (strcmp(code2, "BABA") == 0) {
            // decrement
            if (fr > 1) { //todo + need to use double value from 0.01 to 0.99
                fr--;
            }
            setPwm();
        }
    }

}
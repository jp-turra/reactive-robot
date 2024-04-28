#include "Arduino.h"
#include "L298N.h"

MOTOR_L298N::MOTOR_L298N(int ina_pin, int inb_pin, int enable_pin)
{
    ina_pin_ = ina_pin;
    inb_pin_ = inb_pin;
    enable_pin_ = enable_pin;

    pinMode(ina_pin_, OUTPUT);
    pinMode(inb_pin_, OUTPUT);
    pinMode(enable_pin_, OUTPUT);
}

void MOTOR_L298N::set_speed(int speed)
{
    int ina_value = LOW;
    int inb_value = LOW;

    if (speed > 0)
    {
        ina_value = HIGH;
    }
    else if (speed < 0)
    {
        inb_value = HIGH;
    }

    digitalWrite(ina_pin_, ina_value);
    digitalWrite(inb_pin_, inb_value);
    analogWrite(enable_pin_, constrain(abs(speed), 0, 255));
}

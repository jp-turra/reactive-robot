/**
 * @file L298N.cpp
 * 
 * @author João Pedro Verona Turra
 * 
 * @brief  Behavior of the interface for the L298N H-Bridge motor driver
 *
 **************************************************************************
 * 
 *  GNU GPL v3.0
 * 
 *  Copyright (c) 2024 João Pedro Verona Turra
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 **************************************************************************
*/

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

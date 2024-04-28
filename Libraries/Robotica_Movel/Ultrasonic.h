/**
 * @file Ultrasonic.h
 * 
 * @author João Pedro Verona Turra
 * 
 * @brief  Interface for the Ultrasonic sensor HC-SR04
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

#ifndef ROBOTICA_MOVEL__ULTRASONIC_H
#define ROBOTICA_MOVEL__ULTRASONIC_H

#include "Arduino.h"

#define SOUND_SPEED_CM_US 0.0343
#define SOUND_SPEED_CM_US_2 (SOUND_SPEED_CM_US / 2)

class Ultrasonic
{
  public:
    Ultrasonic(int trigger_pin, int echo_pin, unsigned long timeout);
    Ultrasonic(int trigger_pin, int echo_pin);
    void read(float & distance_cm);
    void set_timeout(unsigned long timeout);
    void set_mean_avg(float new_value_weight, float old_value_weight);

    void Ultrasonic::set_timeout_from_distance_cm(float distance_cm);
    static unsigned long get_timeout_from_distance_cm(float distance_cm);

    bool is_valid_reading() { return valid_reading_; }

  private:
    int trigger_pin_;
    int echo_pin_;
    unsigned long timeout_;

    float new_value_weight_ = 1;
    float old_value_weight_ = 0;
    float last_distance_cm_ = 0;

    bool valid_reading_ = false;
};


#endif // !ROBOTICA_MOVEL__ULTRASONIC_H
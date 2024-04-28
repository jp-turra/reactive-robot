/**
 * @file L298N.h
 * 
 * @author João Pedro Verona Turra
 * 
 * @brief  Interface for the L298N H-Bridge motor driver
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

#ifndef ROBOTICA_MOVEL__L298N_H
#define ROBOTICA_MOVEL__L298N_H

class MOTOR_L298N
{
    public:
        MOTOR_L298N(int ina_pin, int inb_pin, int enable_pin);

        void set_speed(int speed);

    private:
        int ina_pin_;
        int inb_pin_;
        int enable_pin_;
};

#endif

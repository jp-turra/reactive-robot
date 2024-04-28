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

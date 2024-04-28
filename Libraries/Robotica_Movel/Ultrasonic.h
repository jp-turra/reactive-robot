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
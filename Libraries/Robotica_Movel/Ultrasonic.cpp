#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trigger_pin, int echo_pin, unsigned long timeout)
{
  trigger_pin_ = trigger_pin;
  echo_pin_ = echo_pin;
  timeout_ = timeout;

  pinMode(trigger_pin_, OUTPUT);
  pinMode(echo_pin_, INPUT);
}

Ultrasonic::Ultrasonic(int trigger_pin, int echo_pin)
{
  trigger_pin_ = trigger_pin;
  echo_pin_ = echo_pin;
  set_timeout_from_distance_cm(400);

  pinMode(trigger_pin_, OUTPUT);
  pinMode(echo_pin_, INPUT);
}

void Ultrasonic::read(float & distance_cm)
{
  digitalWrite(trigger_pin_, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin_, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin_, LOW);

  float duration = pulseIn(echo_pin_, HIGH, timeout_);
  distance_cm = (duration * SOUND_SPEED_CM_US_2) * new_value_weight_ + (last_distance_cm_ * old_value_weight_);
  last_distance_cm_ = distance_cm;

  valid_reading_ = distance_cm > 0;
}

void Ultrasonic::set_timeout(unsigned long timeout)
{
  timeout_ = timeout;
}

void Ultrasonic::set_timeout_from_distance_cm(float distance_cm)
{
  timeout_ = get_timeout_from_distance_cm(distance_cm);
}

void Ultrasonic::set_mean_avg(float new_value_weight, float old_value_weight)
{
  new_value_weight_ = new_value_weight;
  old_value_weight_ = old_value_weight;
}

static unsigned long Ultrasonic::get_timeout_from_distance_cm(float distance_cm)
{
  return (unsigned long)(distance_cm / SOUND_SPEED_CM_US_2);
}
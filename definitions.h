#ifndef ROBOTICA_MOVEL__DEFINITIONS_H
#define ROBOTICA_MOVEL__DEFINITIONS_H

// Define the mean average value for new values of the ultrasonic sensors.
#define US_MAVG_NEW_VAL_WEIGHT 0.15

// Max distance of the ultrasonic sensors can read in cm
#define US_MAX_DISTANCE 400.0

// Ultrasonic pins
#define US1_TRIGGER 8
#define US1_ECHO 9
#define US2_TRIGGER 24
#define US2_ECHO 22
#define US3_TRIGGER 10
#define US3_ECHO 11

// L298N pins
#define LM_ENA_PIN 5
#define LM_IN1_PIN 4
#define LM_IN2_PIN 3
#define LM_IN3_PIN 2
#define LM_IN4_PIN 6
#define LM_ENB_PIN 7

// Motor PWM min and max (experimental values)
#define LM_PWM_MIN 100
#define LM_PWM_MAX 255

// IR pin
#define IR_PIN 13

// Distance to trigger obstacle avoidance
#define TRIGGER_DIST_CM 20

// Distance to fix robot movement
#define KEEP_DIST_CM 10

// Enable/Disable printing
#define USE_PRINT false

// Map of IR keys
typedef enum
{
  IR_KEY_1 = 0x45,
  IR_KEY_2 = 0x46,
  IR_KEY_3 = 0x47,
  IR_KEY_4 = 0x44,
  IR_KEY_5 = 0x40,
  IR_KEY_6 = 0x43,
  IR_KEY_7 = 0x07,
  IR_KEY_8 = 0x15,
  IR_KEY_9 = 0x09,
  IR_KEY_STAR = 0x16,
  IR_KEY_HASH = 0x0D,
  IR_KEY_OK = 0x1C,
  IR_KEY_UP = 0x18,
  IR_KEY_DOWN = 0x52,
  IR_KEY_LEFT = 0x08,
  IR_KEY_RIGHT = 0x5A,
} ir_key_map_e;

// Map of ultrasonic distances index
typedef enum
{
  US_FRONT_INDEX = 0,
  US_RIGHT_INDEX,
  US_LEFT_INDEX
} us_distance_index_e;

// States of the reactive behavior
typedef enum
{
  STATE_STOP = 0,
  STATE_MANUAL,
  STATE_FORWARD,
  STATE_SEARCH,
  STATE_TURN
} robot_state_e;

#endif // !ROBOTICA_MOVEL__DEFINITIONS_H
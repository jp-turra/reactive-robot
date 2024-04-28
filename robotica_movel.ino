#include "Ultrasonic.h"
#include "L298N.h"
#include "IRremote.hpp"
#include "definitions.h"

// Distance (in cm) reading vector
float distance[3] = {0, 0, 0};

// Processing time of main loop
unsigned long time = 0;
// Desired time sample of main loop
unsigned long Ts = 20000; // 20ms

// Start reactive behavior counter
unsigned int counter_start = 0;

// Wait counter to choose a side to turn
unsigned int counter_wait = 0;

// One second target counter
const unsigned int target_counter = 50; // 1 s

// Store the turn around target distance
float target_distance = 0;
// Store a flag to keep turning left or right (false)
bool turn_left_flag = 0;

// Store speed values
float left_speed = 0.0;
float right_speed = 0.0;

// Last ir command received. Used to avoid repeated commands
uint16_t last_ir_command = 0;

// State of reactive behavior
robot_state_e state = STATE_FORWARD;

// Ultrasonic sensors
Ultrasonic us_front = Ultrasonic(US1_TRIGGER, US1_ECHO);
Ultrasonic us_right = Ultrasonic(US2_TRIGGER, US2_ECHO);
Ultrasonic us_left = Ultrasonic(US3_TRIGGER, US3_ECHO);

// Motors
MOTOR_L298N left_motor = MOTOR_L298N(LM_IN1_PIN, LM_IN2_PIN, LM_ENA_PIN);
MOTOR_L298N right_motor = MOTOR_L298N(LM_IN3_PIN, LM_IN4_PIN, LM_ENB_PIN);

void setup() {
  // Start serial communication at 460800 bps
  Serial.begin(460800);

  // Define the mean average value of the ultrasonic sensors to avoid noise
  us_front.set_mean_avg(US_MAVG_NEW_VAL_WEIGHT, 1 - US_MAVG_NEW_VAL_WEIGHT);
  us_right.set_mean_avg(US_MAVG_NEW_VAL_WEIGHT, 1 - US_MAVG_NEW_VAL_WEIGHT);
  us_left.set_mean_avg(US_MAVG_NEW_VAL_WEIGHT, 1 - US_MAVG_NEW_VAL_WEIGHT);

  // Set the timeout of the ultrasonic sensors
  us_front.set_timeout_from_distance_cm(US_MAX_DISTANCE);
  us_right.set_timeout_from_distance_cm(US_MAX_DISTANCE);
  us_left.set_timeout_from_distance_cm(US_MAX_DISTANCE);

  // Set speed to 0
  left_motor.set_speed(0);
  right_motor.set_speed(0);

  // Start IR receiver
  IrReceiver.begin(IR_PIN);
}

void loop() {
  time = micros();

  read_ir_controller();

  update_ultrasonic_sensors(USE_PRINT);

  // Wait for 1 second to start reactive behavior
  if (counter_start == target_counter)
  {
    do_reactive_behavior();
  }
  else
  {
    counter_start ++;
  }
  
  set_speed(USE_PRINT);

  if (USE_PRINT)
  {
    Serial.print(" ");
    Serial.print(target_distance, 2);
  }
  
  
  while ((time + Ts) > micros()) {};
  // Serial.println("");
}

/**
 * @brief Do the reactive behavior. 
 * It goes forward until it finds an obstacle, then it searches for the biggest direction to turn and turns.
*/
void do_reactive_behavior()
{
  if (state == STATE_FORWARD)
  {
    // Define the speed to 50% more than the minimum
    left_speed = LM_PWM_MIN * 1.5;
    right_speed = LM_PWM_MIN * 1.5;

    // Detect an obstacle
    if (distance[US_FRONT_INDEX] <= TRIGGER_DIST_CM)
    {
      state = STATE_TURN;
      counter_wait = 0;
    }
    // TODO: Make keep dist shorter when both side are closer to any object
    else if (distance[US_LEFT_INDEX] <= KEEP_DIST_CM)
    {
      keep_pid_safe_distance(false);
    }
    else if (distance[US_RIGHT_INDEX] <= KEEP_DIST_CM)
    {
      keep_pid_safe_distance(true);
    }    
    
  }
  else if (state == STATE_TURN)
  {
    left_speed = 0;
    right_speed = 0;
    search_biggest_direction_and_change();
  }
  else if (state != STATE_MANUAL)
  {
    left_speed = 0.0;
    right_speed = 0.0;
  }
}

/**
 * @brief Search for the biggest direction to turn and turns until front sensor achieves the target distance
*/
void search_biggest_direction_and_change()
{
  // Wait 1s to avoid noise on the reading and choose the biggest direction
  if (counter_wait >= target_counter)
  {
    
    if (counter_wait == target_counter)
    {
      turn_left_flag = distance[US_RIGHT_INDEX] < distance[US_LEFT_INDEX];
      target_distance = turn_left_flag ? distance[US_LEFT_INDEX] : distance[US_RIGHT_INDEX];
      counter_wait++;
    }

    turn(turn_left_flag, target_distance);
  }
  else
  {
    counter_wait ++;
  }

}

/**
 * @brief Turn left or right
*/
void turn(bool use_left, float target_distance)
{
  if (use_left)
  {
    left_speed = -LM_PWM_MIN;
    right_speed = LM_PWM_MIN;
  }
  else
  {
    left_speed = LM_PWM_MIN;
    right_speed = -LM_PWM_MIN;
  }

  if (distance[US_FRONT_INDEX] >= target_distance)
  {
    state = STATE_FORWARD;
  }
}

/**
 * @brief Keep pid safe distance from sides obstacles
*/
void keep_pid_safe_distance(bool use_left)
{
  // TODO: Add this correctly
  if (use_left)
  {
    left_speed = 100.0;
    right_speed = 70.0;
  }
  else
  {
    left_speed = 70.0;
    right_speed = 100.0;
  }
}

/**
 * @brief Update the ultrasonic sensors
 * @param print If true, print the distance of each sensor
*/
void update_ultrasonic_sensors(bool print)
{
  us_front.read(distance[0]);
  us_right.read(distance[1]);
  us_left.read(distance[2]);

  if (print)
  {
    for (uint8_t i = 0; i < 3; i++)
    {
      Serial.print(" ");
      Serial.print(distance[i], 2);
    }
  }
}

/**
 * @brief Read the IR controller and then handle the command. It ignores duplicated commands
*/
void read_ir_controller()
{
  if (IrReceiver.decode() )
  {
    uint16_t command = IrReceiver.decodedIRData.command;
    uint8_t flags = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_AUTO_REPEAT;
    if (last_ir_command != command || (last_ir_command == command && (flags & (IRDATA_FLAGS_IS_AUTO_REPEAT | IRDATA_FLAGS_IS_REPEAT))))
    {
      last_ir_command = command;
      handle_ir_command(command);
    }

    IrReceiver.resume();
  }
}

/**
 * @brief Handle the IR command
 * 
 * @param command The IR command
*/
void handle_ir_command(uint16_t command)
{
  switch(command)
  {
    // Stop's the robot
    case IR_KEY_OK:
      state = STATE_MANUAL;
      left_speed = 0;
      right_speed = 0;
      break;

    // Start the reactive behavior
    case IR_KEY_1:
      state = STATE_FORWARD;
      break;

    // Move the robot forward in manual mode
    case IR_KEY_UP:
      if (state == STATE_MANUAL)
      {
        left_speed = 100;
        right_speed = 100;
      }
      break;

    // Move the robot backward in manual mode
    case IR_KEY_DOWN:
      if (state == STATE_MANUAL)
      {
        left_speed = -100;
        right_speed = -100;
      }
      break;

    // Move the robot to the left in manual mode
    case IR_KEY_LEFT:
      if (state == STATE_MANUAL)
      {
        left_speed = -100;
        right_speed = 100;
      }
      break;

    // Move the robot to the right in manual mode
    case IR_KEY_RIGHT:
      if (state == STATE_MANUAL)
      {
        left_speed = 100;
        right_speed = -100;
      }
      break;
    default:
      break;
  }

}

/**
 * @brief Constrain and set the speed of the left and right motors
 * 
 * @param print If true, print the speed
*/
void set_speed(bool print)
{
  // If speed is too low, set it to 0 to avoid stalling the motors
  if (left_speed > -LM_PWM_MIN && left_speed < LM_PWM_MIN)
  {
    left_speed = 0.0;
  }

  // If speed is too low, set it to 0 to avoid stalling the motors
  if (right_speed > -LM_PWM_MIN && right_speed < LM_PWM_MIN)
  {
    right_speed = 0.0;
  }

  left_speed = constrain(left_speed, -LM_PWM_MAX, LM_PWM_MAX);
  right_speed = constrain(right_speed, -LM_PWM_MAX, LM_PWM_MAX);

  if (print)
  {
    Serial.print(" ");
    Serial.print(left_speed, 2);
    Serial.print(" ");
    Serial.print(right_speed, 2);
  }

  left_motor.set_speed(-left_speed); // The left motor is pysically inverted, so we need to invert the speed
  right_motor.set_speed(right_speed);
}

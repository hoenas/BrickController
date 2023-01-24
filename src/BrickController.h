#ifndef BrickController_h
#define BrickController_h

// #define _PWM_LOGLEVEL_       4
#include "ESP32_FastPWM.h"

#define MOTOR1_PIN1 25
#define MOTOR1_PIN2 26
#define MOTOR2_PIN1 13
#define MOTOR2_PIN2 5
#define MOTOR3_PIN1 12
#define MOTOR3_PIN2 27
#define MOTOR4_PIN1 4
#define MOTOR4_PIN2 33
#define MOTOR5_PIN1 19
#define MOTOR5_PIN2 21 // check again
#define MOTOR6_PIN1 8
#define MOTOR6_PIN2 7
#define MOTOR_PIN_COUNT 12

// 12-bit resolution
#define PWM_RESOLUTION 12
// 1kHz frequency
#define PWM_FREQUENCY 1000.0f

#define DUTY_CYCLE_OFF 0.0f
#define DUTY_CYCLE_MIN_ON 15.0f
#define DUTY_CYCLE_MAX_ON 100.0f
#define DUTY_CYCLE_MAX_ZERO_PERCENTAGE 0.1f
#define DUTY_CYCLE_GRADIENT (DUTY_CYCLE_MAX_ON - DUTY_CYCLE_MIN_ON) / 100.0

enum Direction
{
    Right = 0,
    Left = 1
};

class BrickController
{
public:
    BrickController();
    void setMotor(uint8_t motor, float motorSpeed, uint8_t motorDirection);
    void setMotor(uint8_t motor, float motorSpeed, uint8_t motorDirection, unsigned long duration);
    void setMotors(uint8_t *motors, float *motorSpeeds, uint8_t *motorDirections, uint8_t motorCount);
    void haltMotors();

private:
    ESP32_FAST_PWM *pwmInstances[MOTOR_PIN_COUNT];
    uint32_t motorPins[MOTOR_PIN_COUNT] = {MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2, MOTOR3_PIN1, MOTOR3_PIN2, MOTOR4_PIN1, MOTOR4_PIN2, MOTOR5_PIN1, MOTOR5_PIN2, MOTOR6_PIN1, MOTOR6_PIN2};
};

#endif // BrickController_h

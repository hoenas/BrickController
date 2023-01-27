#ifndef BrickController_h
#define BrickController_h

#include <cmath>
#include <Arduino.h>

#define MOTOR1_PIN1 25
#define MOTOR1_PIN2 26
#define MOTOR2_PIN1 13 // WHATS WRONG
#define MOTOR2_PIN2 5
#define MOTOR3_PIN1 12
#define MOTOR3_PIN2 27
#define MOTOR4_PIN1 4
#define MOTOR4_PIN2 33
#define MOTOR5_PIN1 19 // WHATS WRONG
#define MOTOR5_PIN2 21
#define MOTOR6_PIN1 8
#define MOTOR6_PIN2 7
#define MOTOR_PIN_COUNT 12

#define LEDC_FREQUENCY 1000
#define LEDC_RESOLUTION 12
#define LEDC_WRITE_MIN_VALUE 0
#define LEDC_WRITE_MAX_VALUE pow(2, LEDC_RESOLUTION)
#define MOTOR_MAX_VALUE 100

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
    void setMotors(uint8_t *motors, float motorSpeed, uint8_t motorDirection, uint8_t motorCount);
    void haltMotors();

private:
    uint32_t motorPins[MOTOR_PIN_COUNT] = {MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2, MOTOR3_PIN1, MOTOR3_PIN2, MOTOR4_PIN1, MOTOR4_PIN2, MOTOR5_PIN1, MOTOR5_PIN2, MOTOR6_PIN1, MOTOR6_PIN2};
};

#endif // BrickController_h

#include "BrickController.h"

BrickController::BrickController()
{

    // Setup PWM controllers
    for (int i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        analogWrite(this->motorPins[i], 0);
    }
}

void BrickController::setMotor(uint8_t motor, float motor_speed, uint8_t motor_direction)
{
    if (motor >= 0 && motor < MOTOR_PIN_COUNT / 2)
    {
        float normalized_speed = max(0.0f, motor_speed);
        normalized_speed = min(100.0f, normalized_speed);

        Serial.println(normalized_speed);
        if (motor_direction == Right)
        {
            analogWrite(motorPins[motor * 2], (uint8_t)round(normalized_speed), MOTOR_MAX_VALUE);
            analogWrite(motorPins[motor * 2 + 1], 0);
        }
        else
        {
            analogWrite(motorPins[motor * 2], 0);
            analogWrite(motorPins[motor * 2 + 1], (uint8_t)round(normalized_speed), MOTOR_MAX_VALUE);
        }
    }
}

void BrickController::setMotor(uint8_t motor, float motorSpeed, uint8_t motorDirection, unsigned long duration)
{
    this->setMotor(motor, motorSpeed, motorDirection);
    delay(duration);
    this->setMotor(motor, 0, motorDirection);
}

void BrickController::setMotors(uint8_t *motors, float motorSpeed, uint8_t motorDirection, uint8_t motorCount)
{
    for (uint8_t i; i < motorCount; i++)
    {
        this->setMotor(motors[i], motorSpeed, motorDirection);
    }
}

void BrickController::haltMotors()
{
    for (uint8_t i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        analogWrite(motorPins[i], 0);
    }
}
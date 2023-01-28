#include "BrickController.h"

BrickController::BrickController()
{

    // Setup PWM controllers
    for (int i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        Serial.print("Seting up motor pin: ");
        Serial.println(this->motorPins[i]);
        ledcSetup(i, LEDC_FREQUENCY, LEDC_RESOLUTION);
        ledcAttachPin(this->motorPins[i], i);
    }
}

void BrickController::setMotor(uint8_t motor, float motor_speed)
{
    if (motor >= 0 && motor < MOTOR_PIN_COUNT / 2)
    {
        float calulated_duty_cycle = max(-100.0f, motor_speed);
        calulated_duty_cycle = min(100.0f, calulated_duty_cycle);
        calulated_duty_cycle = round(((LEDC_WRITE_MAX_VALUE - LEDC_WRITE_MIN_VALUE) / 100.0f) * calulated_duty_cycle);

        Serial.println(calulated_duty_cycle);
        if (motor_speed >= 0)
        {
            ledcWrite(motor * 2, (uint32_t)calulated_duty_cycle);
            ledcWrite(motor * 2 + 1, 0);
        }
        else
        {
            ledcWrite(motor * 2, 0);
            ledcWrite(motor * 2 + 1, (uint32_t)-1 * calulated_duty_cycle);
        }
    }
}

void BrickController::setMotor(uint8_t motor, float motorSpeed, unsigned long duration)
{
    this->setMotor(motor, motorSpeed);
    delay(duration);
    this->setMotor(motor, 0);
}

void BrickController::setMotors(uint8_t *motors, float motorSpeed, uint8_t motorCount)
{
    for (uint8_t i; i < motorCount; i++)
    {
        this->setMotor(motors[i], motorSpeed);
    }
}

void BrickController::haltMotors()
{
    for (uint8_t i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        ledcWrite(i, 0);
    }
}

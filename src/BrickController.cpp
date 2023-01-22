#include "BrickController.h

BrickController::BrickController()
{
    // Setup PWM controllers
    for (int i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        this->pwmInstances[i] = new ESP32_FAST_PWM(this->motorPins[i], PWM_FREQUENCY, DUTY_CYCLE_OFF, i % PWM_CHANNEL_COUNT, PWM_RESOLUTION);
        this->pwmInstances[i]->setPWM();
    }
}

void BrickController::setMotor(uint8_t motor, float motor_speed, uint8_t motor_direction)
{
    if (motor > 0 && motor <= MOTOR_PIN_COUNT / 2)
    {
        float normalized_speed = max(DUTY_CYCLE_OFF, motor_speed);
        normalized_speed = min(DUTY_CYCLE_MAX_ON, normalized_speed);
        // Check if speed is below threshold
        float percentage = DUTY_CYCLE_OFF;
        if (normalized_speed > DUTY_CYCLE_MAX_ZERO_PERCENTAGE)
        {
            percentage = DUTY_CYCLE_GRADIENT * normalized_speed + DUTY_CYCLE_MIN_ON;
        }

        if (motor_direction)
        {
            this->pwmInstances[2 * motor + motor_direction]->setPWM(motorPins[motor * 2], PWM_FREQUENCY, percentage);
            this->pwmInstances[2 * motor]->setPWM(motorPins[motor * 2 + motor_direction], PWM_FREQUENCY, DUTY_CYCLE_OFF);
        }
        else
        {
            this->pwmInstances[2 * motor + motor_direction]->setPWM(motorPins[motor * 2], PWM_FREQUENCY, DUTY_CYCLE_OFF);
            this->pwmInstances[2 * motor + motor_direction]->setPWM(motorPins[motor * 2 + motor_direction], PWM_FREQUENCY, percentage);
        }
    }
}

void BrickController::setMotor(uint8_t motor, float motorSpeed, uint8_t motorDirection, unsigned long duration)
{
    this->setMotor(motor, motorSpeed, motorDirection);
    delay(duration);
    this->setMotor(motor, DUTY_CYCLE_OFF, motorDirection);
}

void BrickController::setMotors(uint8_t *motors, float *motorSpeeds, uint8_t *motorDirections, uint8_t motorCount)
{
    for (uint8_t i = 0; i < motorCount; i++)
    {
        this->setMotor(motors[i], motorSpeeds[i], motorDirections[i]);
    }
}

void BrickController::haltMotors()
{
    for (uint8_t i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        this->pwmInstances[i]->setPWM(this->motorPins[i], PWM_FREQUENCY, DUTY_CYCLE_OFF);
    }
}
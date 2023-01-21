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

void BrickController::setMotor(uint8_t motor, float motor_speed, Direction motor_direction)
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

void BrickController::setMotors(uint8_t *motors, float *speeds, Direction *directions, uint8_t motorCount)
{
    for (uint8_t i = 0; i < motorCount; i++)
    {
        this->setMotor(motors[i], speeds[i], directions[i]);
    }
}

void BrickController::haltMotors()
{
    for (uint8_t i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        this->pwmInstances[i]->setPWM(this->motorPins[i], PWM_FREQUENCY, DUTY_CYCLE_OFF);
    }
}
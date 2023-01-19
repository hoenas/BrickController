#include "BrickController.h

BrickController::BrickController()
{
    // Setup PWM controllers
    for (int i = 0; i < MOTOR_PIN_COUNT; i++)
    {
        this->pwmInstances[i] = new ESP32_FAST_PWM(this->all_motor_pins[i], PWM_FREQUENCY, DUTY_CYCLE_OFF, PWM_CHANNEL, PWM_RESOLUTION);
    }
}

void BrickController::setMotor(uint8_t motor, float speed, Direction direction)
{
    if (motor > 0 && motor <= MOTOR_PIN_COUNT / 2)
    {
        this->pwmInstances[2 * motor]->setPWM(MOTOR_PIN, frequency, dutyCycle);
    }
}

void BrickController::setMotors(uint8_t *motors, float *speeds, Direction *directions, uint8_t motorCount)
{
}

void BrickController::haltMotors()
{
}

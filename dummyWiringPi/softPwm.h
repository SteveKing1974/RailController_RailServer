#ifndef SOFTPWM_H
#define SOFTPWM_H

int  softPwmCreate (int pin, int value, int range);
void softPwmWrite  (int pin, int value);
void softPwmStop   (int pin);

#endif // SOFTPWM_H


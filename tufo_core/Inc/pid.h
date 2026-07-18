#pragma once

#include <stdbool.h>
typedef struct pid_controller
{
    float Kp;
    float Ki;
    float Kd;

    float output_lim_max;
    float output_lim_min;

    float proportional;
    float integral;
    float derivative;

    float prev_error;
    float prev_measurement; //used for derivative on measurement calculation

    float dt;

    float output;

    bool derivative_on_measurement; //flag to enable derivative on measurement
} pid_controller;

//call both setup_pid and reset_pid before calling calculate_pid
void setup_pid(pid_controller *pid, float Kp, float Ki, float Kd, float output_lim_max, float output_lim_min, float dt, bool deriv_on_meas);
void reset_pid(pid_controller *pid);
float calculate_pid(pid_controller *pid, float setpoint, float measurement);
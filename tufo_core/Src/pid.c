#include "pid.h"

void setup_pid(pid_controller *pid, float Kp, float Ki, float Kd, float output_lim_max, float output_lim_min, float dt, bool deriv_on_meas)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->output_lim_max = output_lim_max;
    pid->output_lim_min = output_lim_min;
    pid->dt = dt;
    pid->derivative_on_measurement = deriv_on_meas;
}

void reset_pid(pid_controller *pid)
{
    pid->integral = 0.0f;
    pid->derivative = 0.0f;
    pid->prev_error = 0.0f;
    pid->prev_measurement = 0.0f;
    pid->output = 0.0f;

}

//calculate pid loop output at each timestep
float calculate_pid(pid_controller *pid, float setpoint, float measurement)
{
    float error = setpoint - measurement;
    pid->proportional = pid->Kp * error;

    //conditional integration
    //if output exceeds max output limit and error still > 0 (error causes output to be higher) -> dont integrate
    //if output exceeds min output limit and error still < 0 (error causes output to be lower) -> also dont integrate
    if (!(((pid->output > pid->output_lim_max) && (error > 0)) || ((pid->output < pid->output_lim_min) && (error < 0))))
    {
        pid->integral = pid->integral + pid->Ki * error * pid->dt;
    }

    //use derivative on measurement to prevent derivative kick, else use normal serivative on error
    if (pid->derivative_on_measurement == true)
    {
        pid->derivative = pid->Kd * -(measurement - pid->prev_measurement)/pid->dt;
    } else 
    {
        pid->derivative = pid->Kd * (error - pid->prev_error)/pid->dt;
    }
    
    pid->output = pid->proportional + pid->integral + pid->derivative;
    //output clamping
    if (pid->output > pid->output_lim_max)
    {
        pid->output = pid->output_lim_max;
    } else if (pid->output < pid->output_lim_min)
    {
        pid->output = pid->output_lim_min;
    }
    pid->prev_error = error;
    pid->prev_measurement = measurement;

    return pid->output;
}


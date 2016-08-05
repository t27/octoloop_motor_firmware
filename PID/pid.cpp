/*
 * pid.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 */

#ifndef _PID_SOURCE_
#define _PID_SOURCE_


#include "pid.h"


PID::PID( double dt, double max, double min, double Kp, double Kd, double Ki ) :
    dt_(dt),
    max_(max),
    min_(min),
    Kp_(Kp),
    Kd_(Kd),
    Ki_(Ki),
    pre_error_(0),
    integral_(0)
{
}

double PID::calculate( double setpoint, double pv )
{

    // Calculate error
    double error = setpoint - pv;

    // Proportional term
    double Pout = Kp_ * error;

    // Integral term
    integral_ += error * dt_;
    double Iout = Ki_ * integral_;

    // Derivative term
    double derivative = (error - pre_error_) / dt_;
    double Dout = Kd_ * derivative;

    // Calculate total output
//    double output = Pout + Iout + Dout;
    double output = Pout;

    // Restrict to max/min
    if( output > max_ )
        output = max_;
    else if( output < min_ )
        output = min_;

    // Save error to previous error
    pre_error_ = error;

    return output;
}

PID::~PID()
{
}

#endif



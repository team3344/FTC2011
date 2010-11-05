/*
 *  PID.c
 *
 *
 *  Created by Justin Buchanan on 10/27/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */



typedef struct {
	float Kp, Ki, Kd;	//	gain constants
	float integral;
	float previousTime;
	float previousError;
	float previousSignal;
	float targetSignal;
} PIDController;



void CreateDriveMotorPIDController(PIDController& pidOut);


float PIDControllerCalculate(PIDController& controller, float signal)
{
	float dT = nPgmTime - controller.previousTime;

	float error = signal - controller.targetSignal;
	controller.integral += (error * dT);
	float nextErrorPrediction = (error - controller.previousError) + error;	//	previous change in error added to current error


	float P = -controller.Kp * error;
	float I = -controller.Ki * controller.integral;
	float D = -controller.Kd * nextErrorPrediction / dT;


	//	store info for next iteration
	controller.previousError = error;
	controller.previousSignal = signal;
	controller.previousTime = nPgmTime;	//	set it to the current time

	return P + I + D;
}

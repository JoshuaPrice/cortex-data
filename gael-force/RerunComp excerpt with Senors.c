//separate .dat file (or different part of same file) with encoder data from intial run
originalBRBaseI2C 	= ...; //array of I2C values, can another *data, or within the *data you already have
originalBLBaseI2C 	= ...; //array of I2C values
originalLLiftI2C 		= ...;
originalRIntakeI2C 	= ...;
// you'll need to store large values for the originalI2C arrays above

basefactor = 10; //mess around with these factor values
liftfactor = 5;
intakefactor = 14;
// you wouldn't ever want to run auton at 127 on the motors
// because you won't be able to increase the speed to compensate for falling behind

//this is line 1002 in your RerunComp.c
if( RCFS_GetFile( rerunFile, &data, &datalength ) == RCFS_SUCCESS )
    {
    	nMotorEncoder[BRBase] = 0;
    	nMotorEncoder[BLBase] = 0;

      while(i<datalength){
      	// establish sensor error between initial and current run
      	BRBase_error 	= originalBRBaseI2C(i)-nMotorEncoder[BRBase];
      	BLBase_error 	= originalBLBaseI2C(i)-nMotorEncoder[BLBase];
      	LLift_error 	= originalLLiftI2C(i)-nMotorEncoder[LLift];
      	RIntake_error = originalRIntakeI2c(i)-nMotorEncoder[RIntake];

      	// compensate for error by adding or subtracting speed from motors
        motor[FLBase] = *(data+i) + BLBase_error/factor;
        motor[BLBase] = *(data+i) + BLBase_error/factor;
        motor[FRBase] = *(data+(i+1)) + BRBase_error/factor;
        motor[BRBase] = *(data+(i+1)) + BRBase_error/factor;

        // if you changed motor values to 110 you should also set that as the max in the
        // initial run where you record motor values
        if(*(data+(i+2))==1){
        	motor[LLift] = 110 + LLift_error/liftfactor;
        	motor[RLift] = 110 + LLift_error/liftfactor;
        }
        else if(*(data+(i+3))==1){
        	motor[LLift] = -110 + LLift_error/liftfactor;
        	motor[RLift] = -110 + LLift_error/liftfactor;
        }
        if(*(data+(i+4))==1){
        	motor[LIntake] = 110 + RIntake_error/intakefactor;
        	motor[RIntake] = 110 + RIntake_error/intakefactor;
        }
        else if(*(data+(i+5))==1){
        	motor[LIntake] = -110 + RIntake_error/intakefactor;
        	motor[RIntake] = -110 + RIntake_error/intakefactor;
        }
        i+=6;
        wait1Msec(6);
    	}
    }

// recording sensor values would also allow you to graph how the sensor values
// compare in the runs. by plotting sensor value over time for both runs on the
// same plot, you could easily see at which points the rerun went wrong

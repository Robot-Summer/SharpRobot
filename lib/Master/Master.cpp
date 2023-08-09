#include <Arduino.h>

#include <IR.h>
#include <PID.h>
#include <Motor.h>
#include <Constants.h>
#include <Gyroscope.h>
#include <TiltSensor.h>
#include <ReflectorSensors.h>
#include <MyServo.h>
#include <Sonar.h>

#include <Master.h>

TiltSensor tiltSensor;

MasterState Master::poll() {
    
    switch(currentState){

        case MasterState::IDLE:
            //TODO: write code for the switch (maybe debouncing needed)
            if (true) {//change the part inside the if statment
                advanceState();
            } else {
                stop();
            }
            
            break;

        case MasterState::START:

            goToState(MasterState::DRV_TAPE_NORM);
            break;

        case MasterState::DRV_TAPE_NORM:

            tapeFollow.usePID(MotorNS::MAX_SPEED);

            // if (tiltSensor.readTiltSensor()){
            //     goToState(MasterState::DRV_TAPE_DOWN);
            //     digitalWrite(PC13, LOW);
            // }

            if (millis() - sonarTimer >= TimerNS::SONAR_TIMER) { //limits the sonar to check only every half a second (sonar is slow to take a reading)
                if (!preMarker) { //checks if robot has previously on under something
                    if (sonar.getDistance() < 25) { //checks if the robot is currently under something (bridge or arch)      
                        if (bridgeMarker) { //checks if robot has crossed the bridge
                            goToState(MasterState::AFTER_ARCH);
                            bridgeMarker = false;
                            rampTimer = millis();
                        } else {
                            bridgeMarker = true;
                        }
                    }
                }
                sonarTimer = millis();
            }
            
            break;

        case MasterState::DRV_TAPE_DOWN:
            
            tapeFollow.usePID(MotorNS::DOWN_RAMP_SPEED);

            if (!tiltSensor.readTiltSensor()){
                goToState(MasterState::DRV_TAPE_NORM);
                digitalWrite(PC13, HIGH);
            }

            break;

        case MasterState::SHRP_TURN:
            steeringServo -> write(ServoNS::MAX_ANGLE);

            leftMotor -> speed((MotorNS::MAX_SPEED  + 20));
            rightMotor -> stop();
            
            if (millis() - shrpTimer >= TimerNS::SHRP_TIMER) {
                goToState(MasterState::DRV_TAPE_NORM);
            }

            break;

        case MasterState::AFTER_ARCH:
            steeringServo -> write(ServoNS::MIN_ANGLE);

            leftMotor -> speed(-MotorNS::MAX_SPEED);
            rightMotor -> speed(MotorNS::MAX_SPEED);

            delay(500);

            steeringServo -> write(ServoNS::INITIAL_ANGLE);

            leftMotor -> speed(MotorNS::MAX_SPEED);
            rightMotor -> speed(MotorNS::MAX_SPEED);

            goToState(MasterState::DRV_TAPE_NORM);

            break;

        case MasterState::DONE:                
            stop();
            break;

    }

    return currentState;
}

bool Master::advanceState() {
    if (currentState == MasterState::DONE){
        return false;
    }
    currentState = static_cast<MasterState>(static_cast<int>(currentState) + 1);
    return true;
}

bool Master::goToState(MasterState futureState) {
    if (currentState == MasterState::DONE){
        return false;
    }
    currentState = futureState;
    return true;
}

void Master::stop() {
    if (stopped){ //add the code to stop the motors. 
        leftMotor -> stop();
        rightMotor -> stop();
        return;
    }
    stopped = true;
}

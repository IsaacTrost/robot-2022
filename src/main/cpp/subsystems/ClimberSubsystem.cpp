/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//#include <frc/Joystick.h>
//#include <frc/Relay.h>
#include <Constants.h>

#include "subsystems/ClimberSubsystem.h"
ClimberSubsystem::ClimberSubsystem(
    rev::CANSparkMax *climberMotor,
    frc::DigitalInput *extendedDigitalInput,
    frc::DigitalInput *contractedDigitalInput) {
  m_climberMotor = climberMotor;
  m_contractedDigitalInput = contractedDigitalInput;
  m_extendedDigitalInput = extendedDigitalInput;
  speed = 1;
  startClimb = false;
}


void ClimberSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
  if (m_coDriverController.GetRawButton(buttonStart)) {
    startClimb = true;
  }
  if (startClimb) {
    double climb = m_coDriverController.GetRawAxis(rightJoystickVertical);
    m_climberMotor->Set(climb);
  }
}

void ClimberSubsystem::ClimberForward() {
  m_climberMotor->Set(speed);
}

void ClimberSubsystem::ClimberBackward() {
  m_climberMotor->Set(-1 * speed);
}

void ClimberSubsystem::ClimberStop() {
  m_climberMotor->Set(0);
}

bool ClimberSubsystem::ClimberExtended() {
  return m_extendedDigitalInput->Get();
}

bool ClimberSubsystem::ClimberContracted() {
  return m_contractedDigitalInput->Get();
}
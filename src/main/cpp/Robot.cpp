// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <photonlib/PhotonUtils.h>



void Robot::RobotInit() {
  frc::SmartDashboard::PutNumber("auto_slot", 0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
   frc::SmartDashboard::PutNumber("GyroAngle", (double)m_container.GetDriveSubsystem()->GetHeading());
  photonlib::PhotonPipelineResult result = camera.GetLatestResult();
  if(result.HasTargets()){
    photonlib::PhotonTrackedTarget target = result.GetBestTarget();
    wpi::outs() << "\nyaw:";
    wpi::outs() << std::to_string(target.GetYaw());
    wpi::outs() <<  "\npitch"; 
    wpi::outs() << std::to_string(target.GetPitch());
    wpi::outs() << "\nskew";
    wpi::outs() << std::to_string(target.GetSkew());
    
    wpi::outs() << "dist est";
    wpi::outs() << std::to_string(photonlib::PhotonUtils::CalculateDistanceToTarget(
          Camerapos::cam_height_meters, Camerapos::goal_height_meters, Camerapos::pitch,
          units::degree_t{result.GetBestTarget().GetPitch()}).value());
    frc::SmartDashboard::PutNumber("Yaw", target.GetYaw());
    frc::SmartDashboard::PutNumber("Pitch", target.GetPitch());
    frc::SmartDashboard::PutNumber("Skew", target.GetSkew());
    frc::SmartDashboard::PutNumber("Distance", photonlib::PhotonUtils::CalculateDistanceToTarget(
          Camerapos::cam_height_meters, Camerapos::goal_height_meters, Camerapos::pitch,
          units::degree_t{result.GetBestTarget().GetPitch()}).value());
      
    



  }
  
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif

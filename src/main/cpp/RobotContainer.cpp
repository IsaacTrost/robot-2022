// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <utility>

#include <frc/controller/PIDController.h>
#include <frc/geometry/Translation2d.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/SwerveControllerCommand.h>
#include <frc2/command/button/JoystickButton.h>
#include <units/angle.h>
#include <units/velocity.h>
#include <rev/CANSparkMax.h>

#include "commands/AutoDriving.h"
#include "Constants.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ClimberSubsystem.h"
#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>


using namespace DriveConstants;

RobotContainer::RobotContainer():
    m_autoCommand1_0(&m_drive, 1, 0),
    m_autoCommand1_1(&m_drive, 1, 1),
    m_autoCommand1_2(&m_drive, 1, 2),
    
    m_autoCommand2_0(&m_drive, 2, 0),
    m_autoCommand2_1(&m_drive, 2, 1),
    m_autoCommand2_2(&m_drive, 2, 2),

    m_autoCommand3_0(&m_drive, 3, 0),
    m_autoCommand3_1(&m_drive, 3, 1),
    m_autoCommand3_2(&m_drive, 3, 2),

    m_autoCommand4_0(&m_drive, 4, 0),
    m_autoCommand4_1(&m_drive, 4, 1),
    m_autoCommand4_2(&m_drive, 4, 2)
    
#ifdef COMPETITIONBOT
    ,   
        m_climberMotor {canIDs::kClimberMotorPort, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
        m_extendedDigitalInput {canIDs::kExtendedDigitalInput},
        m_contractedDigitalInput {canIDs::kContractedDigitalInput},
        m_climberSubsystem {&m_climberMotor, &m_extendedDigitalInput, &m_contractedDigitalInput},
        
        m_intakeMotor {canIDs::kIntakeMotor},
        m_intakeSolenoid {frc::PneumaticsModuleType::CTREPCM, solenoidIDs::kIntakeSolenoid}, 
        m_intakeSubsystem {&m_intakeMotor, &m_intakeSolenoid}, 
        
        m_shooterMotor1 {canIDs::kShooterMotor1, rev::CANSparkMaxLowLevel::MotorType::kBrushless}, 
        m_shooterMotor2 {canIDs::kShooterMotor2, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
        m_hoodMotor {canIDs::kHoodMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
        m_turningMotor {canIDs::kTurningMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
        m_shooterSubsystem {&m_shooterMotor1, &m_shooterMotor2, &m_hoodMotor, &m_turningMotor},

        m_hopperMotor {canIDs::kHopperMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless},
        m_hopperSubsystem {&m_hopperMotor},
        m_adjustHoodAngle{25, &m_shooterSubsystem},
        m_turretAngle{90, &m_shooterSubsystem}
#endif
{
       
    m_chooser.SetDefaultOption("Slot 2", &m_slotCommand2);
    m_chooser.AddOption("Slot 1", &m_slotCommand1);
    m_chooser.AddOption("Slot 3", &m_slotCommand3);
    m_chooser.AddOption("Slot 4", &m_slotCommand4);

    frc::SmartDashboard::PutData(&m_chooser);
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Set up default drive command
  // The left stick controls translation of the robot.
  // Turning is controlled by the X axis of the right stick.
  m_drive.SetDefaultCommand(frc2::RunCommand(
      [this] {
        m_drive.Drive(
            units::meters_per_second_t(m_driverController.GetRawAxis(leftJoystickVertical)),
            units::meters_per_second_t(m_driverController.GetRawAxis(leftJoystickHorizontal)),
            units::radians_per_second_t(2.0*m_driverController.GetRawAxis(rightJoystickHorizontal)), true);
      },
      {&m_drive}));
#ifdef COMPETITIONBOT
 m_intakeSubsystem.SetDefaultCommand(frc2::RunCommand(
      [this] {
        m_intakeSubsystem.IntakeSpeed(m_coDriverController.GetRawAxis(leftJoystickVertical));
      },
      {&m_intakeSubsystem}));
#endif
  
}

void RobotContainer::ConfigureButtonBindings() {

//These are the drive controllers

    frc2::Button{[&] {return m_driverController.GetRawButton(buttonStart);}}.WhenPressed(&m_ZeroHeading);
    frc2::Button{[&] {return m_driverController.GetRawButton(rightTrigger);}}.WhenPressed(&m_setSpeedLow);
    frc2::Button{[&] {return m_driverController.GetRawButton(rightTrigger);}}.WhenReleased(&m_setSpeedHigh);
    frc2::Button{[&] {return m_driverController.GetRawButton(rightBumper);}}.WhenPressed(&m_setSpeedMid);
    frc2::Button{[&] {return m_driverController.GetRawButton(rightBumper);}}.WhenReleased(&m_setSpeedHigh);

#ifdef COMPETITIONBOT

//These are also drive controllers

    frc2::Button{[&] {return m_driverController.GetRawButton(buttonX);}}.WhenPressed(&m_zeroIntakeDeploy);
    frc2::Button{[&] {return m_driverController.GetRawButton(buttonY);}}.WhenPressed(&m_zeroIntakeRetreat);

//These are the co-driver controllers
    frc2::Button{[&] {return m_coDriverController.GetRawButton(buttonX);}}.WhenPressed(&m_zeroIntakeDeploy);
    frc2::Button{[&] {return m_coDriverController.GetRawButton(buttonY);}}.WhenPressed(&m_zeroIntakeRetreat);
    frc2::Button{[&] {return m_coDriverController.GetRawButton(rightBumper);}}.WhenPressed(&m_hoodCycleUp);
    frc2::Button{[&] {return m_coDriverController.GetRawButton(leftBumper);}}.WhenPressed(&m_hoodCycleDown);
    frc2::Button{[&] {return m_coDriverController.GetRawButton(leftTrigger);}}.WhenPressed(&m_turretCycleLeft);
    frc2::Button{[&] {return m_coDriverController.GetRawButton(rightTrigger);}}.WhenPressed(&m_turretCycleRight);
#endif
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
   return m_chooser.GetSelected();
    //return new AutoDriving(this);
}

/*
frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed,
                               AutoConstants::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(m_drive.kDriveKinematics);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config);

  frc::ProfiledPIDController<units::radians> thetaController{
      AutoConstants::kPThetaController, 0, 0,
      AutoConstants::kThetaControllerConstraints};

  thetaController.EnableContinuousInput(units::radian_t(-wpi::numbers::pi),
                                        units::radian_t(wpi::numbers::pi));

  frc2::SwerveControllerCommand<4> swerveControllerCommand(
      exampleTrajectory, [this]() { return m_drive.GetPose(); },

      m_drive.kDriveKinematics,

      frc2::PIDController(AutoConstants::kPXController, 0, 0),
      frc2::PIDController(AutoConstants::kPYController, 0, 0), thetaController,

      [this](auto moduleStates) { m_drive.SetModuleStates(moduleStates); },

      {&m_drive});

  // Reset odometry to the starting pose of the trajectory.
  m_drive.ResetOdometry(exampleTrajectory.InitialPose());

  // no auto
  return new frc2::SequentialCommandGroup(
      std::move(swerveControllerCommand),
      frc2::InstantCommand(
          [this]() {
            m_drive.Drive(units::meters_per_second_t(0),
                          units::meters_per_second_t(0),
                          units::radians_per_second_t(0), false);
          },
          {}));
}
*/
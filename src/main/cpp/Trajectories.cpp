// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "trajectories.h"
#include <units/velocity.h>
#include <units/acceleration.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include "Constants.h"

using namespace pathplanner;

trajectories::trajectories() {
    slot1_0 = PathPlanner::loadPath("slot 1.0", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot1_1 = PathPlanner::loadPath("slot 1.1", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot1_2 = PathPlanner::loadPath("slot 1.2", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

    slot2_0 = PathPlanner::loadPath("slot 2.0", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot2_1 = PathPlanner::loadPath("slot 2.1", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot2_2 = PathPlanner::loadPath("slot 2.2", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

    slot3_0 = PathPlanner::loadPath("slot 3.0", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot3_1 = PathPlanner::loadPath("slot 3.1", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot3_2 = PathPlanner::loadPath("slot 3.2", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

    slot4_0 = PathPlanner::loadPath("slot 4.0", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot4_1 = PathPlanner::loadPath("slot 4.1", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);
    slot4_2 = PathPlanner::loadPath("slot 4.2", AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

   //slot_two_first = PathPlanner::loadPath("slot2 first", 4_mps, 4_mps_sq);
   //slot_three_second = PathPlanner::loadPath("slot3 second", 4_mps, 4_mps_sq);
   //test_path = PathPlanner::loadPath("New Path", 4_mps, 4_mps_sq);
}

PathPlannerTrajectory* trajectories::get_auto_trajectory(int slot, int pathNum) {
    //std::cout << "GetNumber start\n";
    //double slot = frc::SmartDashboard::GetNumber("auto_slot", 0);
    if (slot == 1 && pathNum == 0) {
        return &slot1_0;
    } else if (slot == 1 && pathNum == 1) {
        return &slot1_1;
    } else if (slot == 1 && pathNum == 2) {
        return &slot1_2;
    } else if (slot == 2 && pathNum == 0) {
        return &slot2_0;
    } else if (slot == 2 && pathNum == 1) {
        return &slot2_1;
    } else if (slot == 2 && pathNum == 2) {
        return &slot2_2;
    } else if (slot == 3 && pathNum == 0) {
        return &slot3_0;
    } else if (slot == 3 && pathNum == 1) {
        return &slot3_1;
    } else if (slot == 3 && pathNum == 2) {
        return &slot3_2;
    } else if (slot == 4 && pathNum == 0) {
        return &slot4_0;
    } else if (slot == 4 && pathNum == 1) {
        return &slot4_1;
    } else if (slot == 4 && pathNum == 2) {
        return &slot4_2;
    }
    return &slot1_0;

}
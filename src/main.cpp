#include "main.h"
#include "okapi/api.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  using namespace okapi;
  Controller main(ControllerId::master);

  MotorGroup left({{1, false, AbstractMotor::gearset::green,
                    AbstractMotor::encoderUnits::counts},
                   {9, false, AbstractMotor::gearset::green,
                    AbstractMotor::encoderUnits::counts}});

  MotorGroup right({{2, false, AbstractMotor::gearset::green,
                     AbstractMotor::encoderUnits::counts},
                    {10, false, AbstractMotor::gearset::green,
                     AbstractMotor::encoderUnits::counts}});

  auto lGear = static_cast<double>(left.getGearing());
  auto rGear = static_cast<double>(right.getGearing());

  constexpr double dZone = 0.05; // joystick deadzone
  constexpr short loopDelay = 20;

  while (true) {
    double lPow =
        deadband(main.getAnalog(ControllerAnalog::leftY), dZone * -1, dZone) *
        lGear;
    double rPow =
        deadband(main.getAnalog(ControllerAnalog::rightY), dZone * -1, dZone) *
        rGear;

    left.moveVelocity(lPow);
    right.moveVelocity(rPow);

    pros::delay(loopDelay);
  }
}

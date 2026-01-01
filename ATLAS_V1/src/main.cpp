#include "main.h"
#include "liblvgl/display/lv_display.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/image/lv_image.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

LV_IMAGE_DECLARE(configv3);
LV_IMAGE_DECLARE(autonv3);
void display_img_from_c_array() {

	lv_obj_t*img1 = lv_image_create(lv_screen_active());
	lv_image_set_src(img1, &configv3);
	lv_obj_align(img1,LV_ALIGN_TOP_LEFT, 40, 10);

	lv_obj_t*img2 = lv_image_create(lv_screen_active());
	lv_image_set_src(img2, &autonv3);
	lv_obj_align(img2,LV_ALIGN_TOP_LEFT, 40, 130);

}

void display_img_from_file(const void * src){

}

void initialize() {
	display_img_from_c_array();

}

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({-13, -6, 5});
	pros::MotorGroup right_mg({14, 11, -12});
	pros::adi::Pneumatics descore({17, 'a'}, false);   
	pros::adi::Pneumatics double_park({17, 'b'}, false);  
	pros::adi::Pneumatics scraper({17, 'c'}, false);  
	pros::adi::Pneumatics redirect({17, 'd'}, false);  
	right_mg.set_gearing(pros::E_MOTOR_GEARSET_06);
	left_mg.set_gearing(pros::E_MOTOR_GEARSET_06);
	
	while (true) {
	
        int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); 
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

     
        int left = power + turn;
        int right = power - turn;
		
        left_mg.move(left);
        right_mg.move(right);

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			stage1(127);
		}

		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			stage1(-127);
		}

		else{
			stage1(0);
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			stage2(127);
		}

		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			stage2(-127);
		}

		else{
			stage2(0);
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
       		descore.toggle();
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
       		double_park.toggle();
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
       		scraper.toggle();
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
       		redirect.toggle();
		}

	
        // A small delay is necessary to prevent the brain from overloading
        pros::delay(20); 
	} 	                         // Run for 20 ms then update                        // Run for 20 ms then update
	
}
#include "main.h"

pros::Motor A7(15, pros::v5::MotorGears::blue);
pros::Motor A8(16, pros::v5::MotorGears::blue);


pros::adi::Pneumatics descore({17, 'a'}, false);   
pros::adi::Pneumatics double_park({17, 'b'}, false);  
pros::adi::Pneumatics scraper({17, 'c'}, false);  
pros::adi::Pneumatics redirect({17, 'd'}, false);  
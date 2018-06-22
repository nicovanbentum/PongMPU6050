//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "hwlib.hpp"
#include "MPU6050.hpp"
#include <cmath>

int main()
{
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   hwlib::wait_ms(1);
   
   namespace target = hwlib::target;
   
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   MPU6050 MPU_sensor(i2c_bus);
   
   MPU_sensor.init();
   
   MPU_sensor.calibrate(10);
   
   float dt = 0.035;
   
   for(;;)
   {
	   
	   MPU_sensor.readGyro(MPU_sensor.gx, MPU_sensor.gy, MPU_sensor.gz);
	   MPU_sensor.readAccel(MPU_sensor.ax, MPU_sensor.ay, MPU_sensor.az);
	   
	   float gyro_x = (MPU_sensor.gx - MPU_sensor.bgx) / 131;
	   float gyro_y = (MPU_sensor.gy - MPU_sensor.bgy) / 131;
	   
	   //accelerometer angles
	   float accel_angle_x = atan(MPU_sensor.ay/sqrt(MPU_sensor.ax*MPU_sensor.ax + MPU_sensor.az*MPU_sensor.az)) *(180/3.14159);
	   float accel_angle_y = atan(MPU_sensor.ax/sqrt(MPU_sensor.ay*MPU_sensor.ay + MPU_sensor.az*MPU_sensor.az)) *(-180/3.14159);

	   //calc gyro angles
	   float grx = accel_angle_x + (dt * gyro_x);
	   float gry = accel_angle_y + (dt * gyro_y);
	   
	   //complementary filter
	   accel_angle_x = (0.96 * grx) + ((1-0.96) * accel_angle_x);
	   accel_angle_y = (0.96 * gry) + ((1-0.96) * accel_angle_y);
	   
	   hwlib::wait_ms(34);
	   
	   hwlib::cout << " pitch:  " << (int)accel_angle_x << 
						"  roll:  " << (int)accel_angle_y << "\n";
	   
   }
   
   
   
   return 0;
}
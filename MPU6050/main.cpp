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
#include "sensors.hpp"
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
   sensors IMU(i2c_bus);
   
   IMU.init();
   IMU.calibrate(10);
   
   float pitch;
   float yaw;
   float dt = 0.035;
   
   for(;;)
   {
	   IMU.calcAngles(pitch, yaw, dt);
	   
	   hwlib::cout << (int)pitch << "  " << (int)yaw << "\n";
   }
   
   
   
   return 0;
}
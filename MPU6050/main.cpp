#include "hwlib.hpp"
#include "sensors.hpp"

int main()
{
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;

   hwlib::wait_ms(1);
   
   namespace target = hwlib::target;
   
   auto scl_mpu = target::pin_oc( target::pins::d5 );
   auto sda_mpu = target::pin_oc( target::pins::d4 );
   
   auto i2c_bus_mpu = hwlib::i2c_bus_bit_banged_scl_sda(scl_mpu, sda_mpu);
   
   sensors IMU(i2c_bus_mpu);
   
   IMU.init();
   IMU.calibrate(10);
   
   float pitch = 0, roll = 0, dt = 0;
   
   IMU.setSensChip(3, 3);
   IMU.setSensValues(2048, 16.4);
   
   
   
   for(;;)
   {
	   IMU.calcAngles(pitch, roll, dt);
	   
	   
	   hwlib::cout << (int)pitch << "  " << (int)roll << "\n";
   }
}
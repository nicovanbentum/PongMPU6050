#include "hwlib.hpp"
#include "MPU6050.hpp"

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
   
   
   
   for(;;)
   {
	   int ax = MPU_sensor.readAccelX()*1000;
	   int ay = MPU_sensor.readAccelY()*1000;
	   int az = MPU_sensor.readAccelZ()*1000;
	   
		//hwlib::cout << MPU_sensor.readGyroX() << " , " << MPU_sensor.readGyroY() << " , " << MPU_sensor.readGyroZ()  << '\n';
		hwlib::cout << ax << " , " << ay << " , " << az  << '\n';
		hwlib::wait_ms(500);
   }
   
   
   
   return 0;
}
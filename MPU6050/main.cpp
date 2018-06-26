//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "sensors.hpp"
#include "hwlib.hpp"


bool in_range_check(sensors & IMU, float & pitch, float & roll, float & dt)
{
	IMU.calcAngles(pitch, roll, dt);
	
	if(pitch > -90 && pitch < 90 && roll > -90 && roll < 90)
	{
		return 1;
	}
	else {
		return 0;
	}
}


bool init_complete(sensors & IMU, hwlib::i2c_bus_bit_banged_scl_sda & i2cbus)
{
	IMU.init();
	
	uint8_t data[] = {0x6B};
	i2cbus.write(0x68, data, 1);
	i2cbus.read(0x68, data, 1);
	
	if(data[0] == 0x0)
	{
		return 1;
	}
	else {
		return 0;
	}
}


bool check_who_am_I(sensors & IMU)
{
	if(IMU.whoAmI() == 0x68)
	{
		return 1;
	}
	return 0;
}


bool map_tester(sensors & IMU, int value, int min_r, int max_r, int min_r2, int max_r2, int expected_result)
{
	int res = IMU.map(value, min_r, max_r, min_r2, max_r2);
	
	if(res == expected_result)
	{
		return 1;
	}
	else {
		return 0;
	}
}



int main()
{
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;

   hwlib::wait_ms(1);
   
   namespace target = hwlib::target;
   
	auto scl_mpu = target::pin_oc( target::pins::scl );
	auto sda_mpu = target::pin_oc( target::pins::sda );
	auto i2c_bus_mpu = hwlib::i2c_bus_bit_banged_scl_sda(scl_mpu, sda_mpu);
	sensors IMU(i2c_bus_mpu);
	IMU.init();
	IMU.calibrate(10);
	
	float pitch = 0;
	float roll = 0;
	float dt = 0.020;
	
	for(;;)
	{
		bool b = in_range_check(IMU, pitch, roll, dt);
		bool b1 = init_complete(IMU, i2c_bus_mpu);
		bool b2 = check_who_am_I(IMU);
		bool b3 = map_tester(IMU, 2, 0, 4, 10, 50, 30);
		IMU.calcAngles(pitch, roll, dt);
		
		
		hwlib::cout << b << "  " << b1 << "  " << b2 << "  " << b3 << "\n";
		hwlib::cout << (int)pitch << "  " << (int)roll << "\n";
	}
	
	
	
	
	
}
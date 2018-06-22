//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include "MPU6050.hpp"

class sensors : public MPU6050
{
private:
	//base values for calibration.
	float bax = 0, bay = 0, baz = 0, bgx = 0, bgy = 0, bgz = 0;
	
	//raw values.
	float ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;
	
public:
	sensors(hwlib::i2c_bus_bit_banged_scl_sda & i2cbus):
	MPU6050(i2cbus)
	{}
	
	void calibrate(unsigned int n);
	void readAccel(float & ax, float & ay, float & az);
	void readGyro(float & gx, float & gy, float & gz);
	void calcAngles(float & pitch, float & roll, const float & dt);
};

#endif //SENSORS_HPP
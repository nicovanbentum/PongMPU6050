//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "sensors.hpp"
#include <cmath>

///\details
///writes the register values to the sensor class' raw values.
void sensors::readAccel(float & ax, float & ay, float & az)
{
	ax = MPU6050::readAccelX();
	ay = MPU6050::readAccelY();
	az = MPU6050::readAccelZ();
}

///\details
///writes the register values to the sensor class' raw values.
void sensors::readGyro(float & gx, float & gy, float & gz)
{
	gx = MPU6050::readGyroX();
	gy = MPU6050::readGyroY();
	gz = MPU6050::readGyroZ();
}

///\details
///combines the gyro and accelerometer values to output a pitch and roll angle.
void sensors::calcAngles(float & pitch, float & roll, const float & dt)
{
	readGyro(gx, gy, gz);
	readAccel(ax, ay, az);
	
	float gyro_x = (gx - bgx) / GFS_SEL;
	float gyro_y = (gy - bgy) / GFS_SEL;
	   
	//accelerometer angles
	float accel_angle_x = atan(ay/sqrt(ax*ax + az*az)) *(180/3.14159);
	float accel_angle_y = atan(ax/sqrt(ay*ay + az*az)) *(-180/3.14159);

	//calc gyro angles
	float grx = accel_angle_x + (dt * gyro_x);
	float gry = accel_angle_y + (dt * gyro_y);
	   
	//complementary filter
	accel_angle_x = (0.96 * grx) + ((1-0.96) * accel_angle_x);
	accel_angle_y = (0.96 * gry) + ((1-0.96) * accel_angle_y);
	   
	pitch = accel_angle_x;
	roll = accel_angle_y;
}

///\details
///calibrates all 6 axis base values n number of times.
void sensors::calibrate(unsigned int n)
{
	//ugly way to ignore initial register values
	readGyroX(); readGyroY(); readGyroZ(); readAccelX(); readAccelY(); readAccelZ();
	
	for(unsigned int i = 0; i <= n; i++)
	{
		bgx += readGyroX();
		bgy += readGyroY();
		bgz += readGyroZ();
		bax += readAccelX();
		bay += readAccelY();
		baz += readAccelZ();
		hwlib::wait_ms(1);
	}
	
	bgx/=n;
	bgy/=n;
	bgz/=n;
	bax/=n;
	bay/=n;
	baz/=n;
}
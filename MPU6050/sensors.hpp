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

/// \brief
/// Derived sensor interface for the MPU6050 class.
/// \details
/// This class makes it easy to calibrate values, read values, and 
/// ultimately calculate the pitch and roll angles of the sensor.
/// The returned angles are in a range of -90 to 90 degrees.

class sensors : public MPU6050
{
private:
	//base values for calibration.
	float bax = 0, bay = 0, baz = 0, bgx = 0, bgy = 0, bgz = 0;
	
	//raw values.
	float ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;
	
public:
	/// \brief
	/// Sensors class constructor.
	/// \details
	/// Constructs a sensors object, takes a hwlib bit-banged i2c bus
	/// to pass to the MPU6050 class it inherits from.
	sensors(hwlib::i2c_bus_bit_banged_scl_sda & i2cbus):
	MPU6050(i2cbus)
	{}
	
	/// \brief
	/// Calibrates the gyro and accelerometer before use.
	/// \details
	/// Use to calibrate the raw base values, loops 'n' times.
	/// does NOT set chip rotation at call time as offset.
	void calibrate(unsigned int n);
	
	/// \brief
	/// reads the accelerometer's raw values from the chip's registers.
	/// \details
	/// Takes 3 declared floats to store the values in.
	void readAccel(float & ax, float & ay, float & az);
	
	/// \brief
	/// reads the gyroscope's raw values from the chip's registers.
	/// \details
	/// Takes 3 declared floats to store the raw values in.
	void readGyro(float & gx, float & gy, float & gz);
	
	/// \brief
	/// combines the gyro and accel raw values 
	/// to give the pitch and roll angles in degrees.
	/// \details
	/// The \p dt parameter is the time between sensor readings,
	/// this needs to be measured beforehand. E.g if the measured time
	/// is 50 ms, dt is 0.050.
	void calcAngles(float & pitch, float & roll, const float & dt);
};

#endif //SENSORS_HPP
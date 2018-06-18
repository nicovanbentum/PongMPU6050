// ==========================================================================
//
// File      : MPU6050.hpp
// Part of   : MPU6050 library
// Copyright : Nico van Bentum
// Contact	 : nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//
// ==========================================================================

///@FILE

#include "MPU6050.hpp"

///\brief
///Wakes the sensor up.
///\details
///writes 0 to the power management register to turn low power mode off.
void MPU6050::init()
{
	uint8_t data[] = {PWR_MGMT_1, 0x0};
	i2cbus.write(ADDR, data, sizeof(data));
}

///\brief
///Returns the chip's address.
///\details
///reads the WHO_AM_I register at 0x75, which by default returns 0x68.

int8_t MPU6050::whoAmI()
{
	uint8_t data[] = {WHO_AM_I};
	i2cbus.write(ADDR, data, 1);
	i2cbus.read(ADDR, data, 1);
	return data[0];
}

int16_t MPU6050::readGyroX()
{
	uint8_t data_H[1] = {GYRO_XOUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	uint8_t data_L[1] = {GYRO_XOUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	ret /= 131;
	return ret;
}

int16_t MPU6050::readGyroY()
{
	uint8_t data_H[1] = {GYRO_YOUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	uint8_t data_L[1] = {GYRO_YOUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	ret /= 131;
	return ret;
}

int16_t MPU6050::readGyroZ()
{
	uint8_t data_H[1] = {GYRO_ZOUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	uint8_t data_L[1] = {GYRO_ZOUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	ret /= 131;
	return ret;
}

float MPU6050::readAccelX()
{
	uint8_t data_H[1] = {ACC_XOUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	uint8_t data_L[1] = {ACC_XOUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	return (ret/16384.0f);
}

float MPU6050::readAccelY()
{
	uint8_t data_H[1] = {ACC_YOUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	uint8_t data_L[1] = {ACC_YOUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	return ret/16384.0f;
}

float MPU6050::readAccelZ()
{
	uint8_t data_H[1] = {ACC_ZOUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	uint8_t data_L[1] = {ACC_ZOUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	return ret/16384.0f;
}
//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "MPU6050.hpp"

void MPU6050::init()
{
	uint8_t data[] = {PWR_MGMT_1, 0x0};
	i2cbus.write(ADDR, data, sizeof(data));
	
	uint8_t enable_byte = 1 << 6;
	uint8_t data_fifo[] = {USER_CTRL, enable_byte};
	i2cbus.write(ADDR, data_fifo, sizeof(data_fifo));
}

int8_t MPU6050::whoAmI()
{
	uint8_t data[] = {WHO_AM_I};
	i2cbus.write(ADDR, data, 1);
	i2cbus.read(ADDR, data, 1);
	return data[0];
}

void MPU6050::setSensValues(float accel_sens, float gyro_sens)
{
	AFS_SEL = accel_sens;
	GFS_SEL = gyro_sens;
}

void MPU6050::setSensChip(uint8_t afs, uint8_t gfs)
{
	if(afs > 3 || gfs > 3)
	{
		return;
	}
	
	uint8_t data_g[2] = {GYRO_CONFIG, gfs};
	i2cbus.write(ADDR, data_g, 2);
	
	uint8_t data_a[2] = {ACCEL_CONFIG, afs};
	i2cbus.write(ADDR, data_a, 2);
	
}

int16_t MPU6050::readTemp()
{
	uint8_t data_H[1] = {TEMP_OUT_H};
	i2cbus.write(ADDR, data_H, 1);
	i2cbus.read(ADDR, data_H, 1);
	
	uint8_t data_L[1] = {TEMP_OUT_L};
	i2cbus.write(ADDR, data_L, 1);
	i2cbus.read(ADDR, data_L, 1);
	
	int16_t ret = 0;
	ret = (data_H[0] << 8) + data_L[0];
	ret = ret / 340 + 36.53;
	return ret;
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
	return ret/AFS_SEL;
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
	return ret/AFS_SEL;
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
	return ret/AFS_SEL;
}

uint8_t MPU6050::readRegister(uint8_t reg)
{
	uint8_t data[] = {reg};
	i2cbus.write(ADDR, data, 1);
	i2cbus.read(ADDR, data, 1);
	return data[0];
}

float MPU6050::map(float val, float inputMin, float inputMax, float outputMin, float outputMax) 
{
    return ((val - inputMin) * (outputMax - outputMin)) / (inputMax - inputMin) + outputMin;
}
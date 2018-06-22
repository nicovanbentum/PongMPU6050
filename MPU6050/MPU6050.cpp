//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "MPU6050.hpp"

///\details
///writes 0 to the power management register and 1 to the FIFO enable register.
///This turns low power mode off and enables the FIFO buffer for read and write.
void MPU6050::init()
{
	uint8_t data[] = {PWR_MGMT_1, 0x0};
	i2cbus.write(ADDR, data, sizeof(data));
	
	uint8_t enable_byte = 1 << 6;
	uint8_t data_fifo[] = {USER_CTRL, enable_byte};
	i2cbus.write(ADDR, data_fifo, sizeof(data_fifo));
}

///\details
///reads the WHO_AM_I register at 0x75.
///by default returns 0x68.
int8_t MPU6050::whoAmI()
{
	uint8_t data[] = {WHO_AM_I};
	i2cbus.write(ADDR, data, 1);
	i2cbus.read(ADDR, data, 1);
	return data[0];
}

///\details
///Takes 3 declared floats. Assigns the read register values 
///from accel x, y and z to the parameter variables.
void MPU6050::readAccel(float & ax, float & ay, float & az)
{
	
	ax = readAccelX();
	ay = readAccelY();
	az = readAccelZ();
}

///\details
///Takes 3 declared floats. Assigns the int16_t register values 
///from gyro x, y and z to the parameter variables.
void MPU6050::readGyro(float & gx, float & gy, float & gz)
{
	gx = readGyroX();
	gy = readGyroY();
	gz = readGyroZ();
}

void calcAngles(float & pitch, float & yaw, const float & dt)
{
	
}

///\details
///calibrates all 6 axis base values n number of times.
void MPU6050::calibrate(unsigned int n)
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

///\details
///returns an int16 made from the H and L register bytes.
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
///\details
///See readGyroX().
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

///\details
///See readGyroX().
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

///\details
///See readGyroX().
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
	return (ret/AFS_SEL);
}

///\details
///See readGyroX().
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

///\details
///See readGyroX().
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

/// \details
/// Returns a range-based value calculated from a value in another range.
int MPU6050::map(int val, int inputMin, int inputMax, int outputMin, int outputMax) 
{
    return ((val - inputMin) * (outputMax - outputMin)) / (inputMax - inputMin) + outputMin;
}
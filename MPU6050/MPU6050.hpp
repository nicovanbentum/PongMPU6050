//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "hwlib.hpp"

class MPU6050
{
private:
	static constexpr const uint8_t ADDR 			= 0x68;
	static constexpr const uint8_t WHO_AM_I 		= 0x75;
	static constexpr const uint8_t FIFO_EN			= 0x23;
	static constexpr const uint8_t FIFO_R_W			= 0x74;
	static constexpr const uint8_t USER_CTRL 		= 0x6A;
	static constexpr const uint8_t GYRO_CONFIG 		= 0x1B;
	static constexpr const uint8_t GYRO_XOUT_H 		= 0x43;
	static constexpr const uint8_t GYRO_XOUT_L 		= 0x44;
	static constexpr const uint8_t GYRO_YOUT_H 		= 0x45;
	static constexpr const uint8_t GYRO_YOUT_L 		= 0x46;
	static constexpr const uint8_t GYRO_ZOUT_H 		= 0x47;
	static constexpr const uint8_t GYRO_ZOUT_L 		= 0x48;
	static constexpr const uint8_t ACC_XOUT_H		= 0x3B;
	static constexpr const uint8_t ACC_XOUT_L 		= 0x3C;	
	static constexpr const uint8_t ACC_YOUT_H		= 0x3D;
	static constexpr const uint8_t ACC_YOUT_L 		= 0x3E;
	static constexpr const uint8_t ACC_ZOUT_H		= 0x3F;
	static constexpr const uint8_t ACC_ZOUT_L		= 0x40;
	static constexpr const uint8_t PWR_MGMT_1 		= 0x6B;

	
	hwlib::i2c_bus_bit_banged_scl_sda & i2cbus;
	
protected:
	static constexpr const float AFS_SEL 			= 16384;
	static constexpr const float GFS_SEL			= 131;	
	
	//base values for calibration.
	float bax = 0, bay = 0, baz = 0, bgx = 0, bgy = 0, bgz = 0;
	
	//raw values.
	float ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;
	
public:
	
	MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & i2cbus):
	i2cbus(i2cbus)
	{}

	void init();
	void calibrate(unsigned int n);
	int8_t whoAmI();

	void readAccel(float & ax, float & ay, float & az);
	void readGyro(float & gx, float & gy, float & gz);
	
	int16_t readGyroX();
	int16_t readGyroY();
	int16_t readGyroZ();
	float readAccelX();
	float readAccelY();
	float readAccelZ();
	
	int map(int val, int inputMin, int inputMax, int outputMin, int outputMax);
	
};


#endif //MPU6050_HPP
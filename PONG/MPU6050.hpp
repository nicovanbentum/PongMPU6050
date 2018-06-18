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

/// @file

#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "hwlib.hpp"

class MPU6050
{
private:
	static constexpr const uint8_t ADDR 			= 0x68;
	static constexpr const uint8_t WHO_AM_I 		= 0x75;
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
	
public:
	MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & i2cbus):
	i2cbus(i2cbus)
	{}

	void init();
	int16_t readGyroX();
	int16_t readGyroY();
	int16_t readGyroZ();
	float readAccelX();
	float readAccelY();
	float readAccelZ();
	int8_t whoAmI();
};


#endif //MPU6050_HPP
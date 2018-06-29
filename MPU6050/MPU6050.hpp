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

/// \brief
/// MPU6050 6-Axis Gyro/Accelerometer
/// \details
/// This class implements a way to perform actions like reading/writing
/// the MPU6050's registers. The chip uses I2C for these operations.
/// Its' friend the MPU6000 also has SPI.
/// It uses a GY521 driver chip.
/// 
/// Prefered voltage is 5V, it has a resistor that regulates voltage.
/// 3.3V works, but the chip can malfunction if the voltage drops off due
/// to too much hardware.
///
class MPU6050
{
private:
	//MPU6050 register addresses
	static constexpr const uint8_t ADDR 			= 0x68;
	static constexpr const uint8_t WHO_AM_I 		= 0x75;
	static constexpr const uint8_t TEMP_OUT_H		= 0x41;
	static constexpr const uint8_t TEMP_OUT_L		= 0x42;
	static constexpr const uint8_t FIFO_EN			= 0x23;
	static constexpr const uint8_t FIFO_R_W			= 0x74;
	static constexpr const uint8_t USER_CTRL 		= 0x6A;
	static constexpr const uint8_t CONFIG			= 0x1A;
	static constexpr const uint8_t GYRO_CONFIG 		= 0x1B;
	static constexpr const uint8_t GYRO_XOUT_H 		= 0x43;
	static constexpr const uint8_t GYRO_XOUT_L 		= 0x44;
	static constexpr const uint8_t GYRO_YOUT_H 		= 0x45;
	static constexpr const uint8_t GYRO_YOUT_L 		= 0x46;
	static constexpr const uint8_t GYRO_ZOUT_H 		= 0x47;
	static constexpr const uint8_t GYRO_ZOUT_L 		= 0x48;
	static constexpr const uint8_t ACCEL_CONFIG		= 0x1C;
	static constexpr const uint8_t ACC_XOUT_H		= 0x3B;
	static constexpr const uint8_t ACC_XOUT_L 		= 0x3C;	
	static constexpr const uint8_t ACC_YOUT_H		= 0x3D;
	static constexpr const uint8_t ACC_YOUT_L 		= 0x3E;
	static constexpr const uint8_t ACC_ZOUT_H		= 0x3F;
	static constexpr const uint8_t ACC_ZOUT_L		= 0x40;
	static constexpr const uint8_t PWR_MGMT_1 		= 0x6B;

	/// \brief
	/// See Hwlib for more info
	hwlib::i2c_bus_bit_banged_scl_sda & i2cbus;
	
protected:
	/// \brief
	/// Accelerometer sensitivity to calculate angles.
	float AFS_SEL 			= 16384;
	
	/// \brief
	/// Gyroscope sensitivity to calculate angles.
	float GFS_SEL			= 131;
	
public:
	
	/// \brief
	/// MPU6050 class constructor.
	/// \details
	/// Constructs an object of class MPU6050. Takes a bit banged I2C bus
	/// from hwlib for read an write operations.
	MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & i2cbus):
	i2cbus(i2cbus)
	{}

	/// \brief
	/// Wakes up the chip.
	///\details
	/// Writes 0 to the power management register and 1 to the FIFO enable register.
	/// This turns low power mode off and enables the FIFO buffer for read and write.
	void init();
	
	/// \brief
	/// Return the chips' address in hex.
	/// \details
	/// Read the WHO_AM_I register at 0x75.
	/// by default returns 0x68.
	int8_t whoAmI();
	
	/// \brief
	/// Set gyro and accelerometer sensitivity.
	/// \details
	/// Set the class' AFS_SEL and GFS_SEL to the parameter variables.
	/// Use setSensChip() to set the register value.
	/// 
	/// Taken from the datasheet:
	/// Gyro ( FS_SEL = sensitivity )
	/// 0 = 131, 1 = 65.5, 2 = 32.8, 3 = 16.4
	/// 
	/// Accel ( FS_SEL = sensitivity )
	/// 0 = 16384, 1 = 8192, 2 = 4096, 3 = 2048
	void setSensValues(float accel_sens, float gyro_sens);
	
	
	/// \brief
	/// Write to the accel and gyro config registers.
	/// \details
	/// Write the FS_SEL to the internal registers.
	/// Give it either a 0, 1, 2 or 3, anything higher won't write.
	/// 
	/// Taken from the datasheet:
	/// Gyro ( FS_SEL = sensitivity )
	/// 0 = 131, 1 = 65.5, 2 = 32.8, 3 = 16.4
	/// 
	/// Accel ( FS_SEL = sensitivity )
	/// 0 = 16384, 1 = 8192, 2 = 4096, 3 = 2048
	void setSensChip(uint8_t afs, uint8_t gfs);
	
	/// \brief
	/// Read sensor temperature.
	/// \details
	/// Return the sensor temperature in degrees C.
	int16_t readTemp();
	
	/// \brief
	/// Read the gyroscope X registers. 
	/// \details
	/// Read the H and L gyro registers. 
	/// Returns/combines these two bytes into one 16 bit int.
	int16_t readGyroX();
	
	/// \brief
	/// Read the gyroscope Y registers.
	/// \details
	/// See readGyroX().
	int16_t readGyroY();
	
	/// \brief
	/// Read the gyroscope Z registers.
	/// \details
	/// See readGyroX().
	int16_t readGyroZ();
	
	/// \brief
	/// Read the accelerometer X registers.
	/// \details
	/// Read the H and L accel registers.
	/// Return/calculates these two bytes combined, divided by sensitivity.
	float readAccelX();
	
	
	/// \brief
	/// Read the accelerometer Y registers.
	/// \details
	/// See readAccelX().
	float readAccelY();
	
	/// \brief
	/// Read the accelerometer Z registers.
	/// \details
	/// See readAccelX().
	float readAccelZ();
	
	/// \brief
	/// Read a single register.
	/// \details
	/// This function should be used for testing purposes or
	/// extra operations that this library doesn't contain.
	uint8_t readRegister(uint8_t reg);
	
	/// \brief
	/// Range based map function.
	/// \details
	/// Map a value within a given range to a new value in a different range.
	float map(float val, float inputMin, float inputMax, float outputMin, float outputMax);
	
};


#endif //MPU6050_HPP
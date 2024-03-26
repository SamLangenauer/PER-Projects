/**********************************************
 * File: MCP4725_driver.h
 *     Version: 0.1 | Date: 03/25/2024
 * 
 * Description: 
 *  Arduino Library for MCP4725 DAC.
 * 
 *  This library provides functions to use the
 *  MCP4725
 * 
 * Author: samlang2003@gmail.com
**********************************************/


#ifndef MCP4725_DRIVER_H
#define MCP4725_DRIVER_H

/*required libraries*/
#include <Arduino.h>
#include <Wire.h>

// Chip I2C Addresses
#define MCP4725_I2C_ADDRESS_DEFAULT 0x62   // Default I2C Address
#define MCP4725_I2C_ADDRESS_ALT     0x63   // Alternate I2C Address

// Constants
#define MCP4725_MAX_VALUE           4096    // TOP value for the DAC
#define MCP4725_MID_VALUE           2048    // MIDDLE value for the DAC

// Power Down Modes
#define MCP4725_PD_MODE_NORMAL      0x00    // Power down normal mode
#define MCP4725_PD_MODE_1K          0x01    // Power down 1k Resistor Mode
#define MCP4725_PD_MODE_100K        0x02    // Power down 100k resistor mode
#define MCP4725_PD_MODE_500K        0x03    // Power dowmn 500k resistor mode

// Waveform Variables
#define MCP4725_FREQUENCY           1000    // Waveform frequency in Hz
#define MCP4725_SAMPLE_RATE         1       // How oftent to update in ms

// Waveform lookup Tables
#define MCP4725_WAVEGEN_RESOLUTION  12      // Bit resolution for wave generation
uint16_t sine[pow(2, MCP4725_WAVEGEN_RESOLUTION)];
uint16_t triangle[pow(2, MCP4725_WAVEGEN_RESOLUTION)];

/*TCA9548A class definition*/
class MCP4725
{
    public:
        MCP4725(uint8_t addr = MCP4725_I2C_ADDRESS_DEFAULT);
        void begin(bool debug = false);
        void MCP4725_check_connected(bool debug = false);
        void MCP4725_set_max_voltage(float voltage);
        void MCP4725_set_voltage(float voltage, bool writeEEPROM = false);
        void MCP4725_set_power_down(uint8_t mode);
        void MCP4725_init_wavegen(void);
        void MCP4725_generate_sine(void);
        void MCP4725_generate_square(void);
        void MCP4725_generate_triangle(void);


    private:
        uint8_t _i2c_address;
        TwoWire* MCP4725_wire;
};


#endif
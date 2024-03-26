/**********************************************
 * File: MCP4725_driver.c
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
#include "MCP4725_driver.h"

MCP4725::MCP4725(uint8_t addr) : _i2c_address(addr) {}

// Begin I2C communication
void MCP4725::begin(bool debug = false)
{
    this->MCP4725_wire = &wire_input;
    this->MCP4725_wire->begin();
}

// Check whether MCP4725 device is connected
void MCP4725::MCP4725_check_connected(bool debug = false)
{
    this->MCP4725_wire->beginTransmission(_i2c_address);

    if(debug)
    {
        if(!(this->MCP4725_wire->endTransmission()))
        {
            Serial.println("MCP4725 is Connected");
            return true;
        }
        else
        {
            Serial.println("MCP4725 is not Connected");
            return false;
        }
    }

    return (this->MCP4725_wire->endTransmission() == 0);
}

// Set the voltage on the DAC
void MCP4725::MCP4725_set_voltage(uint16_t value, bool writeEEPROM = false)
{
    this->MCP4725_wire->beginTransmission(_i2c_address);

    /*i2c transmission*/
    // EEPROM Logic
    if(writeEEPROM)
    {
        Wire.write(0x60);   // Send write to EEPROM Command
    }
    else
    {
        Wire.write(0x40);   // Send write to DAC Register Command
    }

    // Send upper 8 bits of output and then lower 4 bits
    this->MCP4725_wire->write(value >> 4);
    this->MCP4725_wire->write((value & 0xF) << 4)

    this->MCP4725_wire->endTransmission();
}

// Set the power down status
void MCP4725::MCP4725_set_power_down(uint8_t mode)
{
    this->MCP4725_wire->beginTransmission(_i2c_address);
    
    /*i2c transmission*/
    this->MCP4725_wire->write(0x40 | (mode << 1));
    // Dummy voltage bytes
    this->MCP4725_wire->write(0);
    this->MCP4725_wire->write(0);

    this->MCP4725_wire->endTransmission();
}

// Fill sine wave lookup table
void MCP4725::MCP4725_init_wavegen(void)
{
    uint16_t i;
    uint16_t points = pow(2,MCP4725_WAVEGEN_RESOLUTION);
    uint16_t mid_minus_one = MCP4725_MID_VALUE - 1;
    double angle_inc = (2.0 * M_PI) / points;

    for(i = 0; i < points, i++)
    {
        sine[i] = mid_minus_one + round(mid_minus_one * sin(i * angle increment));
    }
}

// Infinite sine wave
void MCP4725::MCP4725_generate_sine()
{
    // Calculate timer per point for wave in uS
    float period = 1.0 / MCP4725_FREQUENCY;
    float timer_per_point = (period * 1000000.0) / points

    // Infinite sine wave
    while(1)
    {
        for(uint16_t i = 0; i < points; i++)
        {
            MCP4725_set_voltage(sine[i]);
            delayMicroseconds(timer_per_point);
        }
    }
}
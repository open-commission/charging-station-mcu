//
// Created by nebula on 2026/1/13.
//

#ifndef CHARGING_STATION_MB_LOGIC_H
#define CHARGING_STATION_MB_LOGIC_H

void Modbus_Send(UART_HandleTypeDef* uart, uint8_t* data, uint16_t length);
HAL_StatusTypeDef Modbus_Receive(UART_HandleTypeDef* uart, uint8_t* data, uint16_t length, uint32_t timeout);
uint16_t Modbus_CRC16(uint8_t* data, uint16_t length);
void Modbus_Read_Coils(uint8_t slave_address, uint16_t start_address, uint16_t quantity);
void Modbus_Read_Discrete_Inputs(uint8_t slave_address, uint16_t start_address, uint16_t quantity);
void Modbus_Read_Holding_Registers(uint8_t slave_address, uint16_t start_address, uint16_t quantity);
void Modbus_Read_Input_Registers(uint8_t slave_address, uint16_t start_address, uint16_t quantity);
void Modbus_Write_Single_Coil(uint8_t slave_address, uint16_t coil_address, uint16_t value);
void Modbus_Write_Single_Holding_Register(uint8_t slave_address, uint16_t register_address, uint16_t value);
void Modbus_Write_Multiple_Coils(uint8_t slave_address, uint16_t start_address, uint16_t quantity, uint8_t* values);
void Modbus_Write_Multiple_Holding_Registers(uint8_t slave_address, uint16_t start_address, uint16_t quantity,
                                             uint16_t* values);

#endif //CHARGING_STATION_MB_LOGIC_H

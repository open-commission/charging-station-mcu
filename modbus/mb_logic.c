//
// Created by nebula on 2026/1/13.
//

#include <stdint.h>
#include <string.h>
#include "usart.h"
#include "mb_logic.h"

void Modbus_Send(UART_HandleTypeDef* uart, uint8_t* data, uint16_t length)
{
    HAL_UART_Transmit(uart, data, length, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Modbus_Receive(UART_HandleTypeDef* uart, uint8_t* data, uint16_t length, uint32_t timeout)
{
    return HAL_UART_Receive(uart, data, length, timeout);
}

uint16_t Modbus_CRC16(uint8_t* data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

void Modbus_Read_Coils(uint8_t slave_address, uint16_t start_address, uint16_t quantity)
{
    uint8_t request[8];
    request[0] = slave_address;
    request[1] = 0x01;
    request[2] = (start_address >> 8) & 0xFF;
    request[3] = start_address & 0xFF;
    request[4] = (quantity >> 8) & 0xFF;
    request[5] = quantity & 0xFF;
    uint16_t crc = Modbus_CRC16(request, 6);
    request[6] = crc & 0xFF;
    request[7] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 8);

    uint8_t response[256];
    Modbus_Receive(&huart1, response, 5 + (quantity + 7) / 8, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 3 + (quantity + 7) / 8) == (response[3 + (quantity + 7) / 8] | (response[4 + (quantity +
        7) / 8] << 8)))
    {
        // 处理有效响应
        // response[3]开始的数据为线圈状态
    }
}

void Modbus_Read_Discrete_Inputs(uint8_t slave_address, uint16_t start_address, uint16_t quantity)
{
    uint8_t request[8];
    request[0] = slave_address;
    request[1] = 0x02;
    request[2] = (start_address >> 8) & 0xFF;
    request[3] = start_address & 0xFF;
    request[4] = (quantity >> 8) & 0xFF;
    request[5] = quantity & 0xFF;
    uint16_t crc = Modbus_CRC16(request, 6);
    request[6] = crc & 0xFF;
    request[7] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 8);

    uint8_t response[256];
    Modbus_Receive(&huart1, response, 5 + (quantity + 7) / 8, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 3 + (quantity + 7) / 8) == (response[3 + (quantity + 7) / 8] | (response[4 + (quantity +
        7) / 8] << 8)))
    {
        // 处理有效响应
        // response[3]开始的数据为离散输入状态
    }
}

void Modbus_Read_Holding_Registers(uint8_t slave_address, uint16_t start_address, uint16_t quantity)
{
    uint8_t request[8];
    request[0] = slave_address;
    request[1] = 0x03;
    request[2] = (start_address >> 8) & 0xFF;
    request[3] = start_address & 0xFF;
    request[4] = (quantity >> 8) & 0xFF;
    request[5] = quantity & 0xFF;
    uint16_t crc = Modbus_CRC16(request, 6);
    request[6] = crc & 0xFF;
    request[7] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 8);

    uint8_t response[256];
    Modbus_Receive(&huart1, response, 5 + 2 * quantity, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 3 + 2 * quantity) == (response[3 + 2 * quantity] | (response[4 + 2 * quantity] << 8)))
    {
        // 处理有效响应
        for (int i = 0; i < quantity; i++)
        {
            uint16_t value = (response[3 + 2 * i] << 8) | response[4 + 2 * i];
            // 处理读取到的寄存器值
        }
    }
}

void Modbus_Read_Input_Registers(uint8_t slave_address, uint16_t start_address, uint16_t quantity)
{
    uint8_t request[8];
    request[0] = slave_address;
    request[1] = 0x04;
    request[2] = (start_address >> 8) & 0xFF;
    request[3] = start_address & 0xFF;
    request[4] = (quantity >> 8) & 0xFF;
    request[5] = quantity & 0xFF;
    uint16_t crc = Modbus_CRC16(request, 6);
    request[6] = crc & 0xFF;
    request[7] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 8);

    uint8_t response[256];
    Modbus_Receive(&huart1, response, 5 + 2 * quantity, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 3 + 2 * quantity) == (response[3 + 2 * quantity] | (response[4 + 2 * quantity] << 8)))
    {
        // 处理有效响应
        for (int i = 0; i < quantity; i++)
        {
            uint16_t value = (response[3 + 2 * i] << 8) | response[4 + 2 * i];
            // 处理读取到的寄存器值
        }
    }
}

void Modbus_Write_Single_Coil(uint8_t slave_address, uint16_t coil_address, uint16_t value)
{
    uint8_t request[8];
    request[0] = slave_address;
    request[1] = 0x05;
    request[2] = (coil_address >> 8) & 0xFF;
    request[3] = coil_address & 0xFF;
    request[4] = (value ? 0xFF : 0x00);
    request[5] = 0x00;
    uint16_t crc = Modbus_CRC16(request, 6);
    request[6] = crc & 0xFF;
    request[7] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 8);

    uint8_t response[8];
    Modbus_Receive(&huart1, response, 8, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 6) == (response[6] | (response[7] << 8)))
    {
        // 处理有效响应
        // response[4]和response[5]应为0xFF00表示成功写入线圈
    }
}

void Modbus_Write_Single_Holding_Register(uint8_t slave_address, uint16_t register_address, uint16_t value)
{
    uint8_t request[8];
    request[0] = slave_address;
    request[1]

        = 0x06;
    request[2] = (register_address >> 8) & 0xFF;
    request[3] = register_address & 0xFF;
    request[4] = (value >> 8) & 0xFF;
    request[5] = value & 0xFF;
    uint16_t crc = Modbus_CRC16(request, 6);
    request[6] = crc & 0xFF;
    request[7] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 8);

    uint8_t response[8];
    Modbus_Receive(&huart1, response, 8, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 6) == (response[6] | (response[7] << 8)))
    {
        // 处理有效响应
        // response[4]和response[5]应为写入的值
    }
}

void Modbus_Write_Multiple_Coils(uint8_t slave_address, uint16_t start_address, uint16_t quantity, uint8_t* values)
{
    uint8_t request[256];
    uint16_t byte_count = (quantity + 7) / 8;
    request[0] = slave_address;
    request[1] = 0x0F;
    request[2] = (start_address >> 8) & 0xFF;
    request[3] = start_address & 0xFF;
    request[4] = (quantity >> 8) & 0xFF;
    request[5] = quantity & 0xFF;
    request[6] = byte_count;
    memcpy(&request[7], values, byte_count);
    uint16_t crc = Modbus_CRC16(request, 7 + byte_count);
    request[7 + byte_count] = crc & 0xFF;
    request[8 + byte_count] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 9 + byte_count);

    uint8_t response[8];
    Modbus_Receive(&huart1, response, 8, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 6) == (response[6] | (response[7] << 8)))
    {
        // 处理有效响应
        // response[4]和response[5]应为写入的线圈数量
    }
}

void Modbus_Write_Multiple_Holding_Registers(uint8_t slave_address, uint16_t start_address, uint16_t quantity,
                                             uint16_t* values)
{
    uint8_t request[256];
    uint16_t byte_count = quantity * 2;
    request[0] = slave_address;
    request[1] = 0x10;
    request[2] = (start_address >> 8) & 0xFF;
    request[3] = start_address & 0xFF;
    request[4] = (quantity >> 8) & 0xFF;
    request[5] = quantity & 0xFF;
    request[6] = byte_count;
    for (uint16_t i = 0; i < quantity; i++)
    {
        request[7 + 2 * i] = (values[i] >> 8) & 0xFF;
        request[8 + 2 * i] = values[i] & 0xFF;
    }
    uint16_t crc = Modbus_CRC16(request, 7 + byte_count);
    request[7 + byte_count] = crc & 0xFF;
    request[8 + byte_count] = (crc >> 8) & 0xFF;

    Modbus_Send(&huart1, request, 9 + byte_count);

    uint8_t response[8];
    Modbus_Receive(&huart1, response, 8, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 6) == (response[6] | (response[7] << 8)))
    {
        // 处理有效响应
        // response[4]和response[5]应为写入的寄存器数量
    }
}

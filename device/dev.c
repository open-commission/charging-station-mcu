//
// Created by nebula on 2026/1/13.
//

#include "dev.h"

#include "usart.h"
#include "../modbus/mb_logic.h"

#define slave_address 0x01
#define quantity 0x02

uint8_t dianliu = 0;
uint8_t dianya = 0;
uint8_t pinlv = 0;
uint8_t yougonggonglv = 0;
uint8_t wugonggonglv = 0;
uint8_t yanwu = 0;

void Read_Dianliu()
{
    uint16_t start_address = 0x04;
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

    Modbus_Send(&huart3, request, 8);

    uint8_t response[256];
    Modbus_Receive(&huart3, response, 5 + 2 * quantity, HAL_MAX_DELAY);

    if (Modbus_CRC16(response, 3 + 2 * quantity) == (response[3 + 2 * quantity] | (response[4 + 2 * quantity] << 8)))
    {
        Modbus_Send(&huart4, (uint8_t*)&response, 2);
        // 处理有效响应
        for (int i = 0; i < quantity; i++)
        {
            uint16_t value = (response[3 + 2 * i] << 8) | response[4 + 2 * i];
            Modbus_Send(&huart4, (uint8_t*)&value, 2);
            Modbus_Send(&huart4, (uint8_t*)"d\n", 2);
        }
    };
}

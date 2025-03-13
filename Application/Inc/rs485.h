/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-06 10:24:15
 * @LastEditTime: 2025-03-13 11:09:35
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Inc\rs485.h
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#ifndef RS485_H
#define RS485_H

#include "gd32f4xx.h"
#include "crc.h"
#include "analyze_data.h"
#include "gd32f4xx_it.h"
#include <stdio.h>
#include <stdbool.h>

extern bool Getmode; // 读取模式

// 定义一个结构体来包含所有需要传递的参数
typedef struct {
    uint16_t slave_id;
    uint8_t Func_code;
    uint8_t Reg[2];
    uint8_t Reg_Num[2];
    uint8_t data_len;
    uint8_t data[4];
} ModbusWriteParams;


typedef struct {
    uint16_t slave_id;
    uint8_t Func_code;
    uint8_t Reg[2];
    uint8_t Reg_Num[2];
} ModbusReadParams;


#define RS485_COM5_TX_PIN                 GPIO_PIN_6   // TAG 蓝牙或者打印串口 
#define RS485_COM5_RX_PIN                 GPIO_PIN_7

#define RS485_COM5_GPIO_PORT              GPIOC
#define RS485_COM5_GPIO_CLK               RCU_GPIOC
#define RS485_COM5_AF                     GPIO_AF_8    // TAG 复用8

#define COMn                             1U
#define RS485_COM5                        USART5
#define RS485_COM5_CLK                    RCU_USART5


#define float_type_asend     0x01
#define float_type_desend    0x02
#define uint32_t_type_asend  0x03
#define uint32_t_type_desend 0x04
#define double_type_asend    0x05
#define double_type_desend   0x06

/* configure COM port */
void RS485_com_init(uint32_t com);
// 发送函数
void usart_send(uint32_t usart_periph, uint8_t* data, uint16_t len);

void usart_send_string(uint32_t usart_periph, uint8_t *data);

void RS485_power_init (void);

void RS485_power_on(void);

void RS485_power_off(void);

// 读写函数
void send_modbus_write(ModbusWriteParams *params);

void send_modbus_write(ModbusWriteParams *params);

void rs485_buf_clear(void);

#endif // !RS485_H


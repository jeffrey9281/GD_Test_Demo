/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-06 10:24:15
 * @LastEditTime: 2025-03-06 19:18:33
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Inc\rs485.h
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#ifndef RS485_H
#define RS485_H

#include "gd32f4xx.h"

#define RS485_COM5_TX_PIN                 GPIO_PIN_6   // TAG 蓝牙或者打印串口 
#define RS485_COM5_RX_PIN                 GPIO_PIN_7

#define RS485_COM5_GPIO_PORT              GPIOC
#define RS485_COM5_GPIO_CLK               RCU_GPIOC
#define RS485_COM5_AF                     GPIO_AF_8    // TAG 复用8

#define COMn                             1U
#define RS485_COM5                          USART5
#define RS485_COM5_CLK                    RCU_USART5

/* configure COM port */
void RS485_com_init(uint32_t com);
// 发送函数
void usart_send(uint32_t usart_periph, uint8_t* data, uint16_t len);

void RS485_power_init (void);

void RS485_power_on(void);

void RS485_power_off(void);

#endif // !RS485_H


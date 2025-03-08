/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-06 10:24:04
 * @LastEditTime: 2025-03-07 15:39:57
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Src\rs485.c
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#include "rs485.h"

void  RS485_power_init ()
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_15);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_15);

    GPIO_BC(GPIOF) = GPIO_PIN_15;
}

void RS485_power_on()
{
    GPIO_BOP(GPIOF) = GPIO_PIN_15;
}

void RS485_power_off()
{
    GPIO_BC(GPIOF) = GPIO_PIN_15;;
}


void RS485_com_init(uint32_t com)
{
	rcu_periph_clock_enable(RCU_GPIOC); // 使能外设时钟
	rcu_periph_clock_enable(RCU_USART5);
	
	gpio_af_set            (GPIOC, GPIO_AF_8,     GPIO_PIN_6); // 设置GPIO的备用功能
	gpio_af_set            (GPIOC, GPIO_AF_8,     GPIO_PIN_7);
	gpio_mode_set          (GPIOC, GPIO_MODE_AF,  GPIO_PUPD_PULLUP,  GPIO_PIN_6); // 设置GPIO模式
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6); // 设置GPIO输出模式和速度
	gpio_mode_set          (GPIOC, GPIO_MODE_AF,  GPIO_PUPD_PULLUP,  GPIO_PIN_7);
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
	
	usart_deinit                   (USART5);                        // 复位外设USARTx
	usart_word_length_set          (USART5, USART_WL_8BIT);         // 配置USART字长
	usart_stop_bit_set             (USART5, USART_STB_1BIT);        // 配置USART停止位
	usart_parity_config            (USART5, USART_PM_NONE);         // 配置USART奇偶校验
	usart_baudrate_set             (USART5, 9600U);               // 配置USART波特率
	usart_receive_config           (USART5, USART_RECEIVE_ENABLE);  // USART接收器配置
	usart_transmit_config          (USART5, USART_TRANSMIT_ENABLE); // USART发送器配置
	// usart_autobaud_detection_enable(USART5);                        // 使能USART自动波特率检测
	usart_enable                   (USART5);                        // 使能USART
	
	nvic_irq_enable(USART5_IRQn, 0, 1);                // 使能NVIC的中断
	usart_interrupt_enable(USART5, USART_INT_RBNE); // 使能USART中断, USART_INT_RBNE：读数据缓冲区非空中断和过载错误中断
	usart_interrupt_enable(USART5, USART_INT_IDLE); // USART_INT_IDLE：IDLE线检测中断
}

// 串口发送单个字节
void usart_send(uint32_t usart_periph, uint8_t* data, uint16_t len)
{
	// 循环发送数据
	for(int i=0; i<len; i++)
	{
		usart_data_transmit(usart_periph, (uint8_t) (*(data + i)));  // USART发送数据功能
		while(RESET == usart_flag_get(usart_periph, USART_FLAG_TBE));// 获取USART STAT/CHC/RFCS寄存器标志位,USART_FLAG_TBE:发送数据缓冲区空标志
	}
}



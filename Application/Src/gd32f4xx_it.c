/*******************************************************
 * @Author: your name
 * @Date: 2025-03-05 11:07:45
 * @LastEditTime: 2025-03-07 15:13:02
 * @LastEditors: your name
 * @Description:
 * @FilePath: \GD_Test\Application\Src\gd32f4xx_it.c
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
/*!
    \file    gd32f4xx_it.c
    \brief   interrupt service routines

    \version 2024-01-17, V2.6.4, demo for GD32F4xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx_it.h"
#include "systick.h"
#include "rs485.h"
#include <stdio.h>
#include <string.h>
#include "rs485.h"

uint8_t usart_recv_buf[USART_RECV_BUF_SIZE] = {0}; // 接收缓存区
uint16_t usart_recv_count                   = 0;   // 接收数据个数
uint16_t usart_recv_length                  = 0;   // 接收数据长度

/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
    /* if NMI exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
    /* if SVC exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
    /* if DebugMon exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
    /* if PendSV exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    delay_decrement();
}

void USART5_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(USART5, USART_INT_FLAG_RBNE)) { // 获取USART中断标志位状态

        uint8_t ch = (uint8_t)usart_data_receive(USART5); // USART接收数据功能
        if (usart_recv_count < USART_RECV_BUF_SIZE) {
            usart_recv_buf[usart_recv_count++] = ch;
        }
        usart_interrupt_flag_clear(USART5, USART_INT_FLAG_RBNE); // 清除USART中断标志位状态
    }

    if (RESET != usart_interrupt_flag_get(USART5, USART_INT_FLAG_IDLE)) // USART_INT_FLAG_IDLE:IDLE线检测中断标志
    {
        usart_interrupt_flag_clear(USART5, USART_INT_FLAG_IDLE);
        usart_data_receive(USART5); /* 清除接收完成标志位 */ //！！！！！！！！！！！！！！！！！！！不加这个函数退不出中断
        // (void)LOS_EventWrite(&g_shellInputEvent, 0x1); //事件通知接收完成
        if (usart_recv_count > 0) // 接收到一帧数据
        {
            usart_recv_length = usart_recv_count;            // 接收数据长度
            printf ("recv length:%d\r\n", usart_recv_length); // 打印接收数据长度
            usart_recv_count  = 0;                           // 接收数据个数清零
        }
    }

    if(usart_interrupt_flag_get(USART5, USART_INT_FLAG_RBNE_ORERR) != RESET)
    {
        usart_interrupt_flag_clear(USART5, USART_INT_FLAG_RBNE_ORERR);
    }
}

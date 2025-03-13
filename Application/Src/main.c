/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-05 11:07:45
 * @LastEditTime: 2025-03-13 12:18:07
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Src\main.c
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
/*!
    \file    main.c
    \brief   USART printf demo

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
#include "gd32f470z_eval.h"
#include "rs485.h"
#include "gd32f4xx_it.h"
#include "crc.h"
#include "cfg.h"
#include "analyze_data.h"
#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>

void led_init(void);
void led_flash(int times);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* configure systick */
    systick_config();

    /* configure EVAL_COM0 */
    gd_eval_com_init(EVAL_COM0);

    // 485串口检测
    RS485_com_init(RS485_COM5);

    // 水位计电源使能
    RS485_power_init();
    RS485_power_on();

    // 抬头
    Title_printf();

    // 参数设置
    Water_Gauge_Manual();

    while (1) {

        auto_analyze_rs485();  // 读取水位数据
    }

}



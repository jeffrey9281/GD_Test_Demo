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
    /* initialize the LEDs */
    led_init();

    /* configure systick */
    systick_config();

    /* flash the LEDs for 1 time */
    led_flash(1);

    /* configure EVAL_COM0 */
    gd_eval_com_init(EVAL_COM0);

    // 485串口检测
    RS485_com_init(RS485_COM5);

    // 雨量计电源
    RS485_power_init();
    RS485_power_on();

    /* configure TAMPER key */
    // gd_eval_key_init(KEY_TAMPER, KEY_MODE_GPIO);

    /* output a message on hyperterminal using printf function */
    printf("test! \r\n");
    // usart_send(USART5, (uint8_t[]){0x7F, 0x04, 0x0a, 0x0f, 0x00, 0x02, 0x48, 0x0e}, sizeof((uint8_t[]){0x7F, 0x04, 0x0a, 0x0f, 0x00, 0x02, 0x48, 0x0e}));
    /* wait for completion of USART transmission */

    // uint8_t test[] = {0x7F, 0x04, 0x0a, 0x0f, 0x00, 0x02};
    
    while (1) {
        float data_test = 0.0;
        delay_1ms(3000);
        send_modbus_request(0x7f, 0x04, 0x0a, 0x0f);
        delay_1ms(3000);
        printf("test! \r\n");
        data_test = check_received_data(float_type_desend);
        printf ("data_test: %f \r\n", data_test);
        // if (usart_recv_length > 0) {
        //     for (uint8_t i = 0; i < usart_recv_length; i++) {
        //         printf("0x%02x ", usart_recv_buf[i]);
        //     }
        //     usart_recv_length = 0;
        // }
    }
}

/*!
    \brief      initialize the LEDs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_init(void)
{
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);
}

/*!
    \brief      flash the LEDs for test
    \param[in]  times: times to flash the LEDs
    \param[out] none
    \retval     none
*/
void led_flash(int times)
{
    int i;
    for (i = 0; i < times; i++) {
        /* delay 400 ms */
        delay_1ms(400);

        /* turn on LEDs */
        gd_eval_led_on(LED1);
        gd_eval_led_on(LED2);
        gd_eval_led_on(LED3);

        /* delay 400 ms */
        delay_1ms(400);
        /* turn off LEDs */
        gd_eval_led_off(LED1);
        gd_eval_led_off(LED2);
        gd_eval_led_off(LED3);
    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM0, (uint8_t)ch);
    while (RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
    return ch;
}

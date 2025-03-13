/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-11 16:52:38
 * @LastEditTime: 2025-03-13 13:01:28
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Inc\cfg.h
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#ifndef _CFG_H
#define _CFG_H

#include <stdint.h>
#include <stdio.h>
#include  "gd32f4xx_it.h"
#include "gd32f470z_eval.h"
#include "rs485.h"
#include <math.h>
#include "crc.h"
#include "analyze_data.h"
#include "systick.h"

void Water_Gauge_Manual(void);
void analyze_debug_recv_buf_float();
void analyze_debug_recv_buf_uint16();
void Title_printf();
void auto_analyze_rs485(); //自动解析接收缓冲区数据
void transfer_string_to_hex(uint8_t *string_buffer, uint8_t *hex_buffer, int length);
void transfer_string_to_uint16(uint8_t *string_buffer, uint16_t *value, int length);
#endif // DEBUG
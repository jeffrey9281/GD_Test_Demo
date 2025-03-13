/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-08 17:06:56
 * @LastEditTime: 2025-03-13 15:07:43
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Inc\analyze_data.h
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#ifndef _ANALYZE_DATA_H_
#define _ANALYZE_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

#define float_type_asend     0x01
#define float_type_desend    0x02
#define uint32_t_type_asend  0x03
#define uint32_t_type_desend 0x04
#define double_type_asend    0x05
#define double_type_desend   0x06

double parseDouble(uint8_t *data);
float parseFloat(uint8_t *data);
void concatenateArrays(uint8_t *re_data_Buf, uint8_t *re_data_Buf1, uint8_t *re_data_Buf2, uint8_t *result);
double analyze_in_queue_float(uint8_t *data, uint8_t size);
void transfer_string_to_hex(uint8_t *string_buffer, uint8_t *hex_buffer, int length);
void transfer_string_to_uint16(uint8_t *string_buffer, uint16_t *value, int length);
#endif /* _ANALYZE_DATA_H_ */
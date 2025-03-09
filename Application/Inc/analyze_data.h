#ifndef _ANALYZE_DATA_H_
#define _ANALYZE_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define float_type_asend     0x01
#define float_type_desend    0x02
#define uint32_t_type_asend  0x03
#define uint32_t_type_desend 0x04
#define double_type_asend    0x05
#define double_type_desend   0x06

double parseDouble(uint8_t *data);
float parseFloat(uint8_t *data);
void concatenateArrays(uint8_t *re_data_Buf, uint8_t *re_data_Buf1, uint8_t *re_data_Buf2, uint8_t *result);


double analyze_in_queue_uint32(uint8_t *data, uint8_t size);
double analyze_not_in_queue_uint32(uint8_t *data, uint8_t size);
double analyze_not_in_queue_float(uint8_t *data, uint8_t size);
double analyze_in_queue_float(uint8_t *data, uint8_t size);
double analyze_in_queue_double(uint8_t *data, uint8_t size);
double analyze_not_in_queue_double(uint8_t *data, uint8_t size);


#endif /* _ANALYZE_DATA_H_ */
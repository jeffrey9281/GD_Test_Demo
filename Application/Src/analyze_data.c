/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-08 17:06:41
 * @LastEditTime: 2025-03-13 15:04:34
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Src\analyze_data.c
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#include "analyze_data.h"

/**
 * @brief        : 拼接字符
 * @param         {uint8_t} *re_data_Buf: 数组
 * @param         {uint8_t} *re_data_Buf1: 数组2
 * @param         {uint8_t} *re_data_Buf2: 数组3
 * @param         {uint8_t} *result: 拼接结果
 * @return        {*}
 **/
void concatenateArrays(uint8_t *re_data_Buf, uint8_t *re_data_Buf1, uint8_t *re_data_Buf2, uint8_t *result)
{
    memcpy(result, re_data_Buf, 8);
    memcpy(result + 8, re_data_Buf1, 8);
    memcpy(result + 16, re_data_Buf2, 8);
}

/*****************************************
 * @brief        : Transfer uint32_t to float
 * @param         {uint8_t} *data:
 * @return        {*}
 *****************************************/
float parseFloat(uint8_t *data)
{
    uint32_t value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    float result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

/****************************************
 * @description: Transfer uint64_t to double
 * @param {uint8_t} *data
 * @return {*}
 ******************************************/
double parseDouble(uint8_t *data)
{
    uint8_t littleEndianArray[8]; // 用于存储小端格式的字节数组

    // 将大端字节数组转换为小端格式
    for (int i = 0; i < 8; i++) {
        littleEndianArray[i] = data[7 - i];
    }

    double result;
    // 将字节数组复制到 double 变量中
    memcpy(&result, littleEndianArray, sizeof(result));
    return result;
}

/******************************************************* 
 * @description: 解析floaat 最重要优先
 * @param {uint8_t} *data
 * @param {uint8_t} size
 * @return {*}
 *******************************************************/
double analyze_in_queue_float(uint8_t *data, uint8_t size)
{
    float floatdata;
    floatdata = parseFloat(&data[3]);
    // printf("float= %f\r\n", floatdata);
    double SUM = floatdata;
    return SUM;
}

/******************************************************* 
 * @description: string转换为float
 * @param {uint8_t} *string_buffer
 * @param {uint8_t} *hex_buffer
 * @param {int} length
 * @return {*}
 *******************************************************/
void transfer_string_to_hex(uint8_t *string_buffer, uint8_t *hex_buffer, int length)
{
    char str[length];
    memcpy(str, &string_buffer[0], length); // 将数组中的数据复制到str缓冲区
    str[length] = '\0';          // 添加字符串结束符
    float f                = atof(str);     // 将字符串转换为浮点数
    memcpy(hex_buffer, &f, sizeof(f));             // 将浮点数转换为16进制数组
}

/******************************************************* 
 * @description: string转换为uint16
 * @param {uint8_t} *string_buffer
 * @param {uint16_t} *value
 * @param {int} length
 * @return {*}
 *******************************************************/
void transfer_string_to_uint16(uint8_t *string_buffer, uint16_t *value, int length)
{
    for (int i = 0; i < length; i++) {
        string_buffer[i] = string_buffer[i] - '0';                                                 // 将字符转换为对应的数字
        *value    += (string_buffer[i] * pow(10, length - i - 1)); // 16位数据格式       
    }
}
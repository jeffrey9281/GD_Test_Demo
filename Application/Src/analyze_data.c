/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-08 17:06:41
 * @LastEditTime: 2025-03-09 17:04:37
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

double analyze_in_queue_uint32(uint8_t *data, uint8_t size)
{
    uint32_t uint32;
    uint32 = (data[3] << 24) | (data[4] << 16) | (data[5] << 8) | data[6];
    // printf("uint32= %d\r\n", uint32);
    double SUM = uint32;
    return SUM;
}

/******************************************************* 
 * @description: 解析长整型 最重要优先
 * @param {uint8_t} *data
 * @param {uint8_t} size
 * @return {*}
 *******************************************************/
double analyze_not_in_queue_uint32(uint8_t *data, uint8_t size)
{
    uint32_t uint32;
    uint32 = (data[5] << 24) | (data[6] << 16) | (data[3] << 8) | data[4];
    // printf("uint32= %d\r\n", uint32);
    double SUM = uint32;
    return SUM;
}

/******************************************************* 
 * @description: 解析float
 * @param {uint8_t} *data
 * @param {uint8_t} size
 * @return {*}
 *******************************************************/
double analyze_not_in_queue_float(uint8_t *data, uint8_t size)
{
    float floatdata;
    uint8_t floatdata_buf[256] = {0};
    floatdata_buf[0]           = data[5];
    floatdata_buf[1]           = data[6];
    floatdata_buf[2]           = data[3];
    floatdata_buf[3]           = data[4];
    floatdata                  = parseFloat(&floatdata_buf[0]);
    printf("float= %f\r\n", floatdata);
    double SUM = floatdata;
    return SUM;
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
 * @description: 解析double 
 * @param {uint8_t} *data
 * @param {uint8_t} size
 * @return {*}
 *******************************************************/
double analyze_not_in_queue_double(uint8_t *data, uint8_t size)
{
    double doubledata;
    uint8_t doubledata_buf[256] = {0};
    doubledata_buf[0]           = data[9];
    doubledata_buf[1]           = data[10];
    doubledata_buf[2]           = data[7];
    doubledata_buf[3]           = data[8];
    doubledata_buf[4]           = data[5];
    doubledata_buf[5]           = data[6];
    doubledata_buf[6]           = data[3];
    doubledata_buf[7]           = data[4];
    doubledata                  = parseDouble(&doubledata_buf[0]);
    // printf("double= %f\r\n", doubledata);
    double SUM = doubledata;
    return SUM;
}

/******************************************************* 
 * @description: 解析double 最重要优先
 * @param {uint8_t} *data
 * @param {uint8_t} size
 * @return {*}
 *******************************************************/
double analyze_in_queue_double(uint8_t *data, uint8_t size)
{
    double doubledata;
    doubledata = parseDouble(&data[3]);
    // printf("double= %f\r\n", doubledata);
    double SUM = doubledata;
    return SUM;
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

/**
 * @description: Transfer uint64_t to double
 * @param {uint8_t} *data
 * @return {*}
 */
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

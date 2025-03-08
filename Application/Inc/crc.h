/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-07 16:26:46
 * @LastEditTime: 2025-03-08 14:38:50
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Inc\crc.h
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
/******************************************************* 
 * @Author: your name
 * @Date: 2025-03-07 16:26:46
 * @LastEditTime: 2025-03-07 17:23:33
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \GD_Test\Application\Inc\crc.h
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#ifndef _CRC_H
#define _CEC_H

#include "stdint.h"


uint16_t CRC16_Send(uint8_t *puchMsg, uint8_t usDataLen);
uint32_t CRC16_Rec(uint8_t *puchMsg, uint8_t usDataLen);

#endif /* _CRC_H */
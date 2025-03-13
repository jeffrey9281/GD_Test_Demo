/*******************************************************
 * @Author: your name
 * @Date: 2025-03-11 16:52:30
 * @LastEditTime: 2025-03-12 16:27:00
 * @LastEditors: your name
 * @Description:
 * @FilePath: \GD_Test\Application\Src\cfg.c
 * @可以输入预定的版权声明、个性签名、空行等
 *******************************************************/
#include "cfg.h"

#define Water_Gauge_Adrr     0x7F
#define Water_Gauge_Function 0x04
bool Getmode; // true:自动获取数据  false:手动设置数据

ModbusWriteParams writeParams_FixHeight = {
    // 安装高度
    .slave_id  = 0x7F,                     // 从机地址
    .Func_code = 0x10,                     // 功能码
    .Reg       = {0x20, 0x48},             // 寄存器地址
    .Reg_Num   = {0x00, 0x02},             // 寄存器数量
    .data      = {0x00, 0x00, 0x00, 0x00}, // 数据
    .data_len  = 4                         // 数据长度
};

ModbusWriteParams writeParams_Period = {
    // 推送周期
    .slave_id  = 0x7F,         // 从机地址
    .Func_code = 0x10,         // 功能码
    .Reg       = {0x20, 0x53}, // 寄存器地址
    .Reg_Num   = {0x00, 0x02}, // 寄存器数量
    .data      = {0x00, 0x00}, // 数据
    .data_len  = 2             // 数据长度
};

ModbusReadParams readParams_Height = {
    .slave_id  = 0x0F,         // 从机地址
    .Func_code = 0x10,         // 功能码
    .Reg       = {0x00, 0x10}, // 寄存器地址
    .Reg_Num   = {0x00, 0x02}  // 寄存器数量
};

// send_modbus_read(&readParams);

/******************************************************* 
 * @description: 设置title
 * @return {*}
 *******************************************************/
void Title_printf(void)
{

    printf("-------------  RTU_Test  -------------\n");

    printf("\r\n");
    printf("1.雷达水位计安装高度配置\r\n");
    printf("2.雷达水位计推送周期配置\r\n");
    printf("3.待定\r\n");
    printf("4.待定\r\n");
    printf("\r\n");
}

// 单片机是小端模式 网页转换的是大端数据
/******************************************************* 
 * @description: 串口setting配置函数
 * @return {*}
 *******************************************************/
void Water_Gauge_Manual()
{

    uint8_t flag_set_total  = 1; // 配置标志
    uint8_t flag_set_height = 1; // 配置高度标志
    uint8_t flag_set_period = 1; // 配置周期标志
    uint8_t flag_set_quit   = 1; // 配置模式标志
    while (flag_set_total) {

        if (flag_set_quit) {

            if (debug_recv_length > 0) {

                switch (debug_recv_buf[0]) {

                    case '1':
                        // 串口设置安装高度
                        debug_buf_clear();
                        flag_set_height = 1;
                        printf("请输入安装高度(单位m)\r\n");
                        while (flag_set_height) {
                            if (debug_recv_length > 0) {
                                // 测试
                                analyze_debug_recv_buf_float();
                                flag_set_height = 0;
                            }
                        }
                        break;

                    case '2':
                        // 串口设置推送周期
                        debug_buf_clear();
                        flag_set_period = 1;
                        printf("请输入推送周期(单位ms)\r\n");
                        while (flag_set_period) {
                            if (debug_recv_length > 0) {
                                // 测试
                                analyze_debug_recv_buf_uint16();
                                flag_set_period = 0;
                            }
                        }
                        break;
                    case '0':
                        // 退出
                        debug_buf_clear();
                        flag_set_total = 0;
                        flag_set_quit  = 0;
                        printf("\r\n");
                        printf("参数配置已退出\r\n");
                        printf("\r\n");
                        break;
                }
            }
        } else {
            break;
        }
    }
}

/******************************************************* 
 * @description: 安装高度配置函数
 * @return {*}
 *******************************************************/
void analyze_debug_recv_buf_float()
{
    uint8_t buffer[4]; // 缓存数组
    float f = 0;
    transfer_string_to_hex(debug_recv_buf, buffer, debug_recv_length); // 将串口接收的string转换为四字节16进制数组
    // 485配置安装高度
    writeParams_FixHeight.data[0] = buffer[1];
    writeParams_FixHeight.data[1] = buffer[0];
    writeParams_FixHeight.data[2] = buffer[3];
    writeParams_FixHeight.data[3] = buffer[2];
    memcpy(&f, buffer, sizeof(float));
    printf("设置安装高度为: %f\n", f);
    printf("\r\n");
    printf("\r\n");
    send_modbus_write(&writeParams_FixHeight);
    delay_1ms(1500);
    if (usart_recv_length > 0) // 485串口接收到一帧数据
    {
        if (CRC16_Rec(usart_recv_buf, usart_recv_length) == 1) // CRC校验通过
        {
            printf("设置成功\r\n");
        } else {
            printf("设置失败\r\n");
        }
    }
    debug_buf_clear();
}

/******************************************************* 
 * @description: 发送周期配置函数
 * @return {*}
 *******************************************************/
void analyze_debug_recv_buf_uint16()
{
    uint16_t period_value = 0;
    transfer_string_to_uint16(debug_recv_buf, &period_value, debug_recv_length);
    printf("推送周期：%d设置成功\r\n", period_value);
    uint8_t high_byte          = (period_value >> 8) & 0xFF; // 获取高8位
    uint8_t low_byte           = period_value & 0xFF;        // 获取低8位
    writeParams_Period.data[0] = high_byte;
    writeParams_Period.data[1] = low_byte;
    send_modbus_write(&writeParams_Period);
    delay_1ms(1500);
    if (usart_recv_length > 0) // 485串口接收到一帧数据
    {
        if (CRC16_Rec(usart_recv_buf, usart_recv_length) == 1) // CRC校验通过
        {
            printf("设置成功\r\n");
        } else {
            printf("设置失败\r\n");
        }
    }
    debug_buf_clear();
    // 增加修改文本协议为modbus协议
    uint8_t str[] = "AT+PROTOCOLTYPE=0\n";
    usart_send_string(USART5, str);
    // 开启自动解析
    Getmode = true;
}

/******************************************************* 
 * @description: 自动解析水位
 * @return {*}
 *******************************************************/
void auto_analyze_rs485()
{
    if (Getmode) {
        double waterline = 0;
        if (usart_recv_length > 0) // 485串口接收到一帧数据
        {
            if (CRC16_Rec(usart_recv_buf, usart_recv_length) == 1) // CRC校验通过
            {
                waterline = analyze_in_queue_float(usart_recv_buf, usart_recv_length);
                printf("读取成功\r\n");
                printf("水位高度为: %f\n", waterline);
            } else {
                printf("读取失败\r\n");
            }
            rs485_buf_clear();
        }
    }
}


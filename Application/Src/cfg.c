/*******************************************************
 * @Author: your name
 * @Date: 2025-03-11 16:52:30
 * @LastEditTime: 2025-03-12 16:27:00
 * @LastEditors: your name
 * @Description:
 * @FilePath: \GD_Test\Application\Src\cfg.c
 * @��������Ԥ���İ�Ȩ����������ǩ�������е�
 *******************************************************/
#include "cfg.h"

#define Water_Gauge_Adrr     0x7F
#define Water_Gauge_Function 0x04
bool Getmode; // true:�Զ���ȡ����  false:�ֶ���������

ModbusWriteParams writeParams_FixHeight = {
    // ��װ�߶�
    .slave_id  = 0x7F,                     // �ӻ���ַ
    .Func_code = 0x10,                     // ������
    .Reg       = {0x20, 0x48},             // �Ĵ�����ַ
    .Reg_Num   = {0x00, 0x02},             // �Ĵ�������
    .data      = {0x00, 0x00, 0x00, 0x00}, // ����
    .data_len  = 4                         // ���ݳ���
};

ModbusWriteParams writeParams_Period = {
    // ��������
    .slave_id  = 0x7F,         // �ӻ���ַ
    .Func_code = 0x10,         // ������
    .Reg       = {0x20, 0x53}, // �Ĵ�����ַ
    .Reg_Num   = {0x00, 0x02}, // �Ĵ�������
    .data      = {0x00, 0x00}, // ����
    .data_len  = 2             // ���ݳ���
};

ModbusReadParams readParams_Height = {
    .slave_id  = 0x0F,         // �ӻ���ַ
    .Func_code = 0x10,         // ������
    .Reg       = {0x00, 0x10}, // �Ĵ�����ַ
    .Reg_Num   = {0x00, 0x02}  // �Ĵ�������
};

// send_modbus_read(&readParams);

/******************************************************* 
 * @description: ����title
 * @return {*}
 *******************************************************/
void Title_printf(void)
{

    printf("-------------  RTU_Test  -------------\n");

    printf("\r\n");
    printf("1.�״�ˮλ�ư�װ�߶�����\r\n");
    printf("2.�״�ˮλ��������������\r\n");
    printf("3.����\r\n");
    printf("4.����\r\n");
    printf("\r\n");
}

// ��Ƭ����С��ģʽ ��ҳת�����Ǵ������
/******************************************************* 
 * @description: ����setting���ú���
 * @return {*}
 *******************************************************/
void Water_Gauge_Manual()
{

    uint8_t flag_set_total  = 1; // ���ñ�־
    uint8_t flag_set_height = 1; // ���ø߶ȱ�־
    uint8_t flag_set_period = 1; // �������ڱ�־
    uint8_t flag_set_quit   = 1; // ����ģʽ��־
    while (flag_set_total) {

        if (flag_set_quit) {

            if (debug_recv_length > 0) {

                switch (debug_recv_buf[0]) {

                    case '1':
                        // �������ð�װ�߶�
                        debug_buf_clear();
                        flag_set_height = 1;
                        printf("�����밲װ�߶�(��λm)\r\n");
                        while (flag_set_height) {
                            if (debug_recv_length > 0) {
                                // ����
                                analyze_debug_recv_buf_float();
                                flag_set_height = 0;
                            }
                        }
                        break;

                    case '2':
                        // ����������������
                        debug_buf_clear();
                        flag_set_period = 1;
                        printf("��������������(��λms)\r\n");
                        while (flag_set_period) {
                            if (debug_recv_length > 0) {
                                // ����
                                analyze_debug_recv_buf_uint16();
                                flag_set_period = 0;
                            }
                        }
                        break;
                    case '0':
                        // �˳�
                        debug_buf_clear();
                        flag_set_total = 0;
                        flag_set_quit  = 0;
                        printf("\r\n");
                        printf("�����������˳�\r\n");
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
 * @description: ��װ�߶����ú���
 * @return {*}
 *******************************************************/
void analyze_debug_recv_buf_float()
{
    uint8_t buffer[4]; // ��������
    float f = 0;
    transfer_string_to_hex(debug_recv_buf, buffer, debug_recv_length); // �����ڽ��յ�stringת��Ϊ���ֽ�16��������
    // 485���ð�װ�߶�
    writeParams_FixHeight.data[0] = buffer[1];
    writeParams_FixHeight.data[1] = buffer[0];
    writeParams_FixHeight.data[2] = buffer[3];
    writeParams_FixHeight.data[3] = buffer[2];
    memcpy(&f, buffer, sizeof(float));
    printf("���ð�װ�߶�Ϊ: %f\n", f);
    printf("\r\n");
    printf("\r\n");
    send_modbus_write(&writeParams_FixHeight);
    delay_1ms(1500);
    if (usart_recv_length > 0) // 485���ڽ��յ�һ֡����
    {
        if (CRC16_Rec(usart_recv_buf, usart_recv_length) == 1) // CRCУ��ͨ��
        {
            printf("���óɹ�\r\n");
        } else {
            printf("����ʧ��\r\n");
        }
    }
    debug_buf_clear();
}

/******************************************************* 
 * @description: �����������ú���
 * @return {*}
 *******************************************************/
void analyze_debug_recv_buf_uint16()
{
    uint16_t period_value = 0;
    transfer_string_to_uint16(debug_recv_buf, &period_value, debug_recv_length);
    printf("�������ڣ�%d���óɹ�\r\n", period_value);
    uint8_t high_byte          = (period_value >> 8) & 0xFF; // ��ȡ��8λ
    uint8_t low_byte           = period_value & 0xFF;        // ��ȡ��8λ
    writeParams_Period.data[0] = high_byte;
    writeParams_Period.data[1] = low_byte;
    send_modbus_write(&writeParams_Period);
    delay_1ms(1500);
    if (usart_recv_length > 0) // 485���ڽ��յ�һ֡����
    {
        if (CRC16_Rec(usart_recv_buf, usart_recv_length) == 1) // CRCУ��ͨ��
        {
            printf("���óɹ�\r\n");
        } else {
            printf("����ʧ��\r\n");
        }
    }
    debug_buf_clear();
    // �����޸��ı�Э��ΪmodbusЭ��
    uint8_t str[] = "AT+PROTOCOLTYPE=0\n";
    usart_send_string(USART5, str);
    // �����Զ�����
    Getmode = true;
}

/******************************************************* 
 * @description: �Զ�����ˮλ
 * @return {*}
 *******************************************************/
void auto_analyze_rs485()
{
    if (Getmode) {
        double waterline = 0;
        if (usart_recv_length > 0) // 485���ڽ��յ�һ֡����
        {
            if (CRC16_Rec(usart_recv_buf, usart_recv_length) == 1) // CRCУ��ͨ��
            {
                waterline = analyze_in_queue_float(usart_recv_buf, usart_recv_length);
                printf("��ȡ�ɹ�\r\n");
                printf("ˮλ�߶�Ϊ: %f\n", waterline);
            } else {
                printf("��ȡʧ��\r\n");
            }
            rs485_buf_clear();
        }
    }
}


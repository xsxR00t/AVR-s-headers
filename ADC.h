/*
 * ADC.h
 *
 * Created: 2013/02/27 22:23:47
 * Author: Yamaguchi Katsuya
 */ 
#ifndef ADC_H_
#define ADC_H_

#define ADPC0  0b01000000
#define ADPC1  0b01000001
#define ADPC2  0b01000010
#define ADPC3  0b01000011
#define ADPC4  0b01000100
#define ADPC5  0b01000101
#define ADPCT  0b01001000  // ���x
#define ADPC11 0b01001110  // �����d��1.1V

/**
 * AD�ϊ����s�����߂̏������֐�
 * �ŏ��ɂ��̊֐���錾����
 *@param �ϊ��������s�����w�肷��B1�ŕϊ��������s��0�͂Ȃ��B��F0x04
 */
void initADC(uint8_t ADPIN);

/**
 * AD�ϊ����s���֐�
 * initADC�œn�����s���Ɠ�������n������
 *@param �ϊ��������s���idefine�Ő錾����Ă��钆����I�����ēn�����Ɓj
 *@return �ϊ�����
 */
int startADC(uint8_t ADPIN);

#endif /* ADC_H_ */

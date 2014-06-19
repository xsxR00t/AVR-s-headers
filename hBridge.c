/*
 * Hbridge.c
 *
 * Created: 2013/02/25 22:17:30
 *  Author: kubrick
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hBridge.h"

void initHbridge(void) {
	// �o�͐ݒ�
	DDRD = 0xFF;
	DDRB = 0xFF;
	// �|�[�g������
	PORTD = D_FREE;
	PORTB = B_FREE;
	
	TCCR0A = FREE; // PWM�o�͒�~
	TCCR0B = 0x02; // D�|�[�g�̎����ݒ�
	
	TCCR2A = FREE; // PWM�o�͒�~
	TCCR2B = 0x20; // B�|�[�g�̎����ݒ�
	
	OCR0A = OCR0B = 0; // D�|�[�g�o�͔�
	OCR2A = OCR2B = 0; // B�|�[�g�o�͔�
}

void D_pwmControl(uint8_t direction, uint8_t speed) {
	if( pre_Dinput == direction ) // �O��̓��͂Ɖ�]����������
		OCR0A = OCR0B = speed;// speed�ɉ�������]���x
	else { // ��]�������ς��Ƃ�
		pre_Dinput = direction;            // ����̓��͂��L�^
		D_portDirectionChange(&direction); // ��]�����̕ω�
		// speed�ɉ�������]���x
		OCR0A = OCR0B = speed;
	}
}

void D_portDirectionChange(uint8_t * direction) {
	OCR0A  = OCR0B = 0; // PWM���0�ɂ���
	TCCR0A = FREE;      // PWM���I�t
	PORTD  = D_FREE;    // �|�[�g������
	
	switch( *(direction) ) { // ��]�����e��
		default:
		case 0x00:
		  PORTD  = D_FREE;
		  TCCR0A = FREE;
		  break;
		case 0x01:
		  PORTD  = D_STOP;
		  TCCR0A = STOP;
		  break;
		case 0x02:
		  PORTD  = D_ADVANCE;
		  TCCR0A = ADVANCE;
		  break;
		case 0x03:
		  PORTD  = D_RETREAT;
		  TCCR0A = RETREAT;
		  break;
	}
}

void B_pwmControl(uint8_t direction, uint8_t speed) {
	if( pre_Binput == direction )
		OCR2A = OCR2B = speed; // speed�ɉ�������]���x
	else {
		pre_Binput = direction;
		B_portDirectionChange(&direction);
		OCR2A = OCR2B = speed;
	}
}

void B_portDirectionChange(uint8_t * direction) {
	OCR2A  = OCR2B = 0; // PWM���0�ɂ���
	TCCR2A = FREE;      // PWM���I�t
	PORTB  = B_FREE;    // �|�[�g������
	
	switch( *(direction) ) { // ��]�����e��
		default:
		case 0x00:
		  PORTB  = B_FREE;
		  TCCR2A = FREE;
		  break;
		case 0x01:
		  PORTB  = B_STOP;
		  TCCR2A = STOP;
		  break;
		case 0x02:
		  PORTB  = B_ADVANCE;
		  TCCR2A = ADVANCE;
		  break;
		case 0x03:
		  PORTB  = B_RETREAT;
		  TCCR2A = RETREAT;
		  break;
	} 
}
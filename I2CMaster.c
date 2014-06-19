/*
 * I2CMaster.c
 *
 * Created: 2012/08/09 16:34:00
 * Author: Yamaguchi Katsuya
 */ 
#include <avr/io.h>
#include "I2CMaster.h"

/**
 * I2C�����������܂��B�����ŒʐM�̑��x��ݒ肵�܂��B�ʐM�̃N���b�N����
 * [ �N���b�N = (CPU�N���b�N���g��) / (16 + 2 * bitRate * prescaler) ]�Őݒ肳��܂��B
 * @param bitRate TWI�̑��x�̕����l
 * @param prescaler TWI�̃r�b�g���x�̑O�u�����l
 */
void I2CMaster_init(uint8_t bitRate, uint8_t prescaler) {
    // �v���X�P�[���͉���2bit�݂̂Őݒ肳��܂��B
    // ���̂��߁A���6bit�̒l��0�ɂ��܂��B
	prescaler &= 0x03;
	TWBR = bitRate;
	TWSR = prescaler;
	TWCR = _BV(TWEN);
}

/**
 * �X�^�[�g�R���f�B�V�����𔭍s���A�X���[�u�̃A�h���X�𑗐M���܂��B
 * (���M�̏ꍇ�ł��r�b�g�V�t�g�����X���[�u�A�h���X��n���K�v�͂���܂���)
 * @param address �ʐM����X���[�u�A�h���X
 * @param mode  ���M:WRITE(0) or ��M:READ(1)���w��
 */
void I2CMaster_start(unsigned char address, I2CMode mode) {
	// �X�^�[�g�R���f�B�V�����̔��s
    TWCR = I2CMaster_START_CONDITION;
    // �X�^�[�g�R���f�B�V�����̔��s�����҂�
    while(!I2CMaster_isTWINT()) {
    }

	// �܂��A�A�h���X��1�r�b�g���ɃV�t�g���A
	// ��M�̏ꍇ�͉���1�r�b�g��1�ɂ���B
	// ���M�̏ꍇ�͉���1�r�b�g��0�ɂ���B
    address <<= 1;
	
	switch(mode) {
		case WRITE:
		    address &= 0b11111110;  // address = 0bxxxxxxx0 ��
		    break;
	    case READ:
		    address |= 0b00000001;   // address = 0bxxxxxxx1��
		    break;
	}
	
	// �X���[�u�A�h���X�̑��M
    I2CMaster_write(address);
}

/**
 * �X�g�b�v�R���f�B�V�����𔭍s���܂��B
 */
void I2CMaster_stop() {
	// �X�g�b�v�R���f�B�V�����̔��s
	TWCR = I2CMaster_STOP_CONDITION;
}

/**
 * �f�[�^�𑗐M���܂��B
 * @param dat ���M����f�[�^
 * @return 1:ACK / 0:NOACK
 */
unsigned char I2CMaster_write(unsigned char dat) {
    // ���M����f�[�^��ݒ�
    TWDR = dat;
    // ���M�J�n
    TWCR = I2CMaster_CLEAR_TWINT;
    // ���M�����҂�
    while(!I2CMaster_isTWINT()){
    }
	// ACK�̎�M�����҂�
	// while(!(TWCR & 1<<TWINT)) {} ����s�v�H �v�m�F
	
    // ACK�l���`�F�b�N
    if(I2CMaster_isACK()) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * �f�[�^����M���܂�
 * @param ack
 * @return ��M�f�[�^
 */
unsigned char I2CMaster_read(unsigned char ack) { //0�Ŏ�M���邪�A�P��n���ƏI���̍��}�ɂȂ�
    if(ack == 0) {
        // ACK����
        TWCR = (I2CMaster_CLEAR_TWINT | 1<<TWEA);
    } else {
        // NOACK����
        TWCR = I2CMaster_CLEAR_TWINT;
    }
	
    // �f�[�^�̎�M�����҂�
    while(!(TWCR & _BV(TWINT))){
    }
    return TWDR;
}

/**
 * TWCR���W�X�^��TWINT�̒l��Ԃ��܂��B
 * @return TWINT��1�Ȃ�1, 0�Ȃ�0
 */
unsigned char I2CMaster_isTWINT() {
    if(TWCR & _BV(TWINT)) {
        return 1;
    } else {
        return 0;
    }
}

unsigned char I2CMaster_isACK() {
	if((TWSR & 0xF8) == I2CMaster_TWSR_DAT_ACK) {
	    return 1;
	} else {
		return 0;
	}
	/*
    switch(TWSR & 0xF8) {
        case I2CMaster_TWSR_SLA_W_ACK:
        case I2CMaster_TWSR_SLA_R_ACK:
        case I2CMaster_TWSR_DAT_ACK:// ACK
            return 1;
        default:// NOACK
            return 0;
    } */
}

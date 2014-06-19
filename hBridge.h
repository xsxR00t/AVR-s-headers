/*
 * hBridge.h
 *
 * Created: 2013/02/25 22:01:20
 *  Author: Katsuya
 */ 

#ifndef HBRIDGE_H_
#define HBRIDGE_H_

/*=== PWM�ݒ� ===*/
#define ADVANCE 0x83
#define RETREAT 0x23
#define FREE    0x03
#define STOP    0xA3

/*=== D�|�[�g�ݒ� ===*/
#define D_FREE    0x90
#define D_STOP    0x90
#define D_ADVANCE 0x80
#define D_RETREAT 0x10

/*=== B�|�[�g�ݒ� ===*/
#define B_FREE    0x14
#define B_STOP    0x14
#define B_ADVANCE 0x04
#define B_RETREAT  0x10

typedef union MotorStatus {
	uint8_t byte: 8;
	struct {
		unsigned char direction: 1;
		unsigned char speed: 7;
	};
} MotorStatus;

MotorStatus D_motordata, B_motordata;

// ��]�����L�^�̂��߂̕ϐ�
static uint8_t pre_Dinput = 0;
static uint8_t pre_Binput = 0;

/**
 *  �������֐�
 * @param  none
 */
void initHbridge(void);

/**
 *  D�|�[�g��PWM����
 * @param ��]��������:direction, �X�s�[�h����:speed
 */
void D_pwmControl(uint8_t direction, uint8_t speed);

/**
 *  D�|�[�g�̉�]��������
 * @param ��]��������:direction�̃|�C���^
 */
void D_portDirectionChange(uint8_t * direction);

/**
 *  D�|�[�g��PWM�𑀍�
 * @param ��]��������:direction, �X�s�[�h����:speed
 */
void B_pwmControl(uint8_t direction, uint8_t speed);

/**
 *  B�|�[�g�̉�]��������
 * @param ��]��������:direction�̃|�C���^
 */
void B_portDirectionChange(uint8_t * direction);

#endif /* HBRIDGE_H_ */
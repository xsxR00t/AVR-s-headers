/** TWI(I2C�ʐM)�ŃX���[�u��������邽�߂̊֐��Q�������C�u�����ł��B
 * I2CSlave.h
 * I2C�X���[�u�̃w�b�_�[�t�@�C���A�l�[���X�y�[�X�Ƃ���I2CSlave_�Ŏn�܂�܂��B
 * ���ӁF���荞�ݓ��삪�ł��܂���I
 *
 * Created: 2011/12/07 17:18:39
 * @author Hirokazu Yokoyama, Gifu university Robocon circle
 *
 */

/**
 * @example �g���� (��
 * �}�X�^�[����擾�����f�[�^��PORTD�ɏo�͂��܂��B�܂��A1bit�V�t�g�����l��Ԃ��܂�
 *
 * #include <avr/io.h>
 * #include "I2CSlave.h"
 *
 * // �X���[�u�A�h���X
 * static const unsigned char ADDRESS = 0x20;
 *
 * // �X���[�u�E�C�x���g�n���h��
 * void slaveInitHandler(uint8_t dat);
 * void slaveRecieveHandler(uint8_t dat);
 * void slaveStopHandler(void);
 * unsigned char slaveSendHandler(void);
 * 
 * unsigned char shift(unsigned char dat);
 * 
 * 
 * int main(void)
 * {
 *  // ���o�͂̏�����
 *  DDRD = 0xFF;
 *  PORTD = 0x00;
 * 
 *  // I2C�X���[�u���������܂��B�X���[�u�A�h���X��n���܂��B
 *  I2CSlave_init(ADDRESS);
 * 
 *  // �X���[�u�����̃C�x���g��ݒ�
 *  I2CSlave_setInitEvent(slaveInitHandler);        // �������C�x���g
 *  I2CSlave_setReceiveEvent(slaveRecieveHandler);  // ��M���C�x���g
 *  I2CSlave_setStopEvent(slaveStopHandler);        // ��~���C�x���g
 *  I2CSlave_setSendEvent(slaveSendHandler);        // ���M���C�x���g

 *  while(1)
 *  {
 *    // �X���[�u������s��
 *    I2CSlave_com(); 
 *  }
 * }

 * /** 8bit�̐����1bit���ɂ��炵�A8bit�ڂ̒l��1bit�ڂɓ���܂��B
 *  * @param dat 8bit�̐���
 *  * @return 1bit�V�t�g�����l    
 * unsigned char shift(unsigned char dat) {
 *     unsigned topBit = ((dat>>7) & 0x01);
 *  return ((dat<<1)|topBit);
 * }
 * 
 * 
 * void slaveInitHandler(uint8_t dat) {
 *  // ��
 * }

 * // ��M���C�x���g�A�}�X�^�[�����M�����l��PORTD�ɏo�͂��܂��B
 * void slaveRecieveHandler(uint8_t dat) {
 *  PORTD = dat;
 * }
 * 
 * // ���M���C�x���g�A�}�X�^�[�ɑ���f�[�^��return���܂��B
 * unsigned char slaveSendHandler(void) {
 *     return shift(PIND);
 * }
 * 
 * // �ʐM��~���̃C�x���g
 * void slaveStopHandler(void) {
 * }

*/

#ifndef I2CSLAVE_H_
#define I2CSLAVE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "grip.h"

typedef InterruptSwitch I2CSlave_Interrupt;

static void (*I2CSlave_initEventListener)(uint8_t dat);
static void (*I2CSlave_receiveEventListener)(uint8_t dat);
static void (*I2CSlave_stopEventListener)(void);
static unsigned char (*I2CSlave_sendEventListener)(void);

static const uint8_t I2CSlave_ENABLE_ACK = (1<<TWEA)|(1<<TWEN);
static const uint8_t I2CSlave_CLEAR_TWINT = (1<<TWEA)|(1<<TWEN)|(1<<TWINT);

void I2CSlave_init(unsigned char address, I2CSlave_Interrupt param);
void I2CSlave_setInitEvent(void (*func)(uint8_t dat));
void I2CSlave_setReceiveEvent(void (*func)(uint8_t dat));
void I2CSlave_setStopEvent(void (*func)(void));
void I2CSlave_setSendEvent(unsigned char (*func)(void));
unsigned char I2CSlave_isTWINT();

/**
 * I2C���X���[�u�ŏ��������܂��B
 * ���荞�ݏ������s���ꍇ�́Aparam��INTERRUPT_ON���w�肵�A
 * �ʓrsei()�Ŋ��荞�݋����s���K�v������܂��B
 * @param address I2C�X���[�u�A�h���X
 * @param param �X���[�u��������荞�ݏ����ɂ���ꍇ��INTERRUPT_ON���w��
 */
void I2CSlave_init(unsigned char address, I2CSlave_Interrupt param) {
  address <<= 1;
  // address |= 1;    // �W�F�l�����E�R�[���E�A�h���X����
  TWAR = address;
  
  switch(param) {
    case INTERRUPT_ON:
        TWCR = I2CSlave_ENABLE_ACK | _BV(TWIE);
        break;
    default:
      case INTERRUPT_OFF:
        TWCR = I2CSlave_ENABLE_ACK;
        break;
  } 
}


static void I2CSlave_do() {
switch(TWSR) {
    case 0x60:  // CB(W)��M
        // --- CB(W)��M ---
            I2CSlave_initEventListener(TWDR);       // CB��M�C�x���g�n���h��
      TWCR = I2CSlave_CLEAR_TWINT;            // INT�v���t���O�̃N���A
        break;

    case 0x80:  // �f�[�^��M
        // --- �X���[�u��M ---
      I2CSlave_receiveEventListener(TWDR);    // ��M�C�x���g�n���h��
      TWCR = I2CSlave_CLEAR_TWINT;            // INT�v���t���O�̃N���A
        break;
     
    case 0xA8:  // CB(R)��M
        // --- CB(R)��M ----
      I2CSlave_initEventListener(TWDR);       // CB��M�C�x���g�n���h��
      TWDR = I2CSlave_sendEventListener();    // �X���[�u���M�C�x���g�n���h��
                                              // ���M�f�[�^�擾
      TWCR = I2CSlave_CLEAR_TWINT;            // INT�v���t���O�̃N���A
        break;

    case 0xB8:  // �f�[�^���M(ACK��M)
        TWDR = I2CSlave_sendEventListener();    // �X���[�u���M�C�x���g�n���h��
                                              // ���M�f�[�^�擾
      TWCR = I2CSlave_CLEAR_TWINT;            // INT�v���t���O�̃N���A
        break;

    case 0xC0:  // �f�[�^���M(NOACK��M)�@�̏W�f�[�^�@�X���[�u���M�I��

    case 0xA0:  // �X���[�u��M���̃X�g�b�v�R���f�B�V����
      I2CSlave_stopEventListener();
        TWCR = I2CSlave_CLEAR_TWINT;            // INT�v���t���O�̃N���A
        break;
  } 
}

/**
 * I2C����(���C�����[�v�ɓ����)
 * ���̊֐������s����O�ɂ��ꂼ��̃C�x���g�n���h����ݒ肵�Ă��������B
 */
void I2CSlave_com() {
    if(!I2CSlave_isTWINT()) {   
    return;
  }    
    I2CSlave_do();  
}

/**
* ���荞�ݏ��� TWSR���W�X�^���X�V���ꂽ�Ƃ��ɌĂяo����܂�
*/
ISR(TWI_vect) {
  cli();
  I2CSlave_do();
  sei();
}

void I2CSlave_setInitEvent(void (*func)(uint8_t dat)) {
  I2CSlave_initEventListener = func;
}
void I2CSlave_setReceiveEvent(void (*func)(uint8_t dat)) {
  I2CSlave_receiveEventListener = func;
}
void I2CSlave_setStopEvent(void (*func)(void)) {
  I2CSlave_stopEventListener = func;
}
void I2CSlave_setSendEvent(unsigned char (*func)(void)) {
    I2CSlave_sendEventListener = func;
}

/**
 * TWCR���W�X�^��TWINT�r�b�g��Ԃ��܂�
 * @return 1 or 0
*/
unsigned char I2CSlave_isTWINT() {
  if((TWCR & (1<<TWINT))) {
    return 1;
  } else {
    return 0;
  }
}
#endif /* I2CSLAVE_H_ */

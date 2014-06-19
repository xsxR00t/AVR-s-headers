/*
 * connect.c
 *
 * Created: 2013/02/20 14:27:50
 *  Author: Katsuya
 */ 
#include <avr/io.h>
#include "I2CMaster.h"
#include "motor_structure.h"
#include "slave_address.h"
#include "connect.h"

/************************************************************************/
/* ����胂�[�^�ʐM                                                     */
/************************************************************************/
void connect_legmotor( AllMotorStatus * motordata ) {
	I2CMaster_start(LEG_MOTOR_ADDRESS, WRITE);
	I2CMaster_write(motordata -> leg_motor_right.byte);
	I2CMaster_write(motordata -> leg_motor_left.byte);
	I2CMaster_stop();
}

/************************************************************************/
/* ���[�t�A�[���E�T�C�h�i���ړ��j                                       */
/************************************************************************/
void connect_leafArmSideAndHide_motor( AllMotorStatus * motordata ) {
	I2CMaster_start(LEAFARM_MOTOR_SIDEHIDE_ADDRESS, WRITE);
	I2CMaster_write(motordata -> leafArm_motor_side.byte);
	I2CMaster_write(motordata -> leafArm_motor_hide.byte);
	I2CMaster_stop();
}

/************************************************************************/
/* ���[�t�A�[���E�n���h�i�L�т���A�͂񂾂肷��                         */
/************************************************************************/
void connect_leafArmExtendAndCatch_motor( AllMotorStatus * motordata ) {
  I2CMaster_start(LEAFARM_MOTOR_EXTENDCATCH_ADDRESS, WRITE);
	I2CMaster_write(motordata -> leafArm_motor_extend.byte);
	I2CMaster_write(motordata -> leafArmHand_motor_catch.byte);
	I2CMaster_stop();
}

/************************************************************************/
/* �t�@�b�L���A�[��                                                     */
/************************************************************************/
void connect_fuckinArmMotor( AllMotorStatus * motordata ) {
	I2CMaster_start(FUCKINARM_MOTOR_ADDRESS, WRITE);
	I2CMaster_write(motordata -> fuckinArm_motor_catch.byte);
	I2CMaster_write(motordata -> fuckinArm_motor_lift.byte);
	I2CMaster_stop();
}

/************************************************************************/
/* �ˏo�@�\                                                             */
/************************************************************************/
void connect_shootingMotor( AllMotorStatus * motordata ) {
	I2CMaster_start(SHOOTING_MOTOR_ADDRESS, WRITE);
	I2CMaster_write(motordata -> shooting_motor.byte);
	I2CMaster_stop();
}
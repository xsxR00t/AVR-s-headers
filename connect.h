/*
 * connect.h
 *
 * Created: 2012/08/19 23:12:30
 *  Author: Katsuya
 */ 

#ifndef CONNECT_H_
#define CONNECT_H_

// ����胂�[�^
void connect_legmotor( AllMotorStatus * motordata );
// ���[�t�A�[���E�T�C�h
void connect_leafArmSideAndHide_motor( AllMotorStatus * motordata );
// ���[�t�A�[���E�n���h
void connect_leafArmExtendAndCatch_motor( AllMotorStatus * motordata );
// �t�@�b�L���A�[��
void connect_fuckinArmMotor( AllMotorStatus * motordata );
// �ˏo
void connect_shootingMotor( AllMotorStatus * motordata );

#endif /* CONNECT_H_ */
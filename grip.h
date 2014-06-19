/*
 * grip.h
 *
 * GRIP (Gifu university Robocon circle Interface Protocol)
 *
 * �}�C�R���ԃV���A���ʐM�̃v���g�R�����`���܂��B
 * Created: 2011/12/30 5:28:30
 *  Author: Gifu university Robocon circle
 */ 



#ifndef GRIP_H_
#define GRIP_H_

/**
 * ���荞�݂��������� or ���Ȃ�
 */
typedef enum InterruptSwitch {
	/** ���荞�݂������Ȃ� */
	INTERRUPT_OFF = 0,
	/** ���荞�݂������� */
	INTERRUPT_ON = 1
} InterruptSwitch;

/**
 * �i�s����
 */
typedef enum MovementDirection {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT_ROTATION = 2,
	RIGHT_ROTATION = 3,
	STOP = 4
} MovementDirection;

/**
 * ���E
 */
typedef enum TurnDirection {
    RIGHT = 0,
    LEFT = 1    
} TurnDirection;


/**
 * �㉺
 */
typedef enum VerticalDirection {
    UPPER = 0,
    LOWER = 1
} VerticalDirection;

/**
 * ����
 */
typedef enum PlusMinus {
    PLUS = 0,
    MINUS = 1
} PlusMinus;

/**
 * �I���E�I�t
 */
typedef enum OnOff {
	OFF = 0,
	ON = 1
} OnOff;


/************************************************************************/
/* ���[�^�h���C�o�ɓ`���郂�[�^�̉�]�����ƃX�s�[�h
 * direction: ��]����(FORWARD or BACKWARD)(UPPER or LOWER)�Ȃ�
 * speed: �X�s�[�h(7bit��)                                                                      
/************************************************************************/
typedef union RightMotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} RightMotorSignal;

typedef union LeftMotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} LeftMotorSignal;

typedef union UpDownSignal {
	uint8_t key: 8;
	struct {
		VerticalDirection direction: 1;
		uint8_t speed: 7;
	};
} UpDownSignal;

typedef union MotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} MotorSignal;

/**
 * ��]
 * direction: �E��] or ����]
 * speed: �X�s�[�h(0-127)
 */
typedef union TurnSignal {
	TurnDirection direction: 1;
	uint8_t speed: 7;
};


#endif /* GRIP_H_ */
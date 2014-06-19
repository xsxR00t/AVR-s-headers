/*
 * motor_structure.h
 *
 * Created: 2012/08/09 17:00:28
 *  Author: Katsuya
 */

#ifndef MOTOR_STRUCTURE_H_
#define MOTOR_STRUCTURE_H_

/*** モータの共用体 ***/
typedef union MotorStatus {
  uint8_t byte: 8;
  struct {
    unsigned char direction: 1;
    unsigned char speed: 7;
  };
} MotorStatus;

/*** 各モータの構造体 ***/
typedef struct AllMotorStatus{
  MotorStatus leg_motor_left;
  MotorStatus leg_motor_right;
  MotorStatus leafArm_motor_side;
  MotorStatus leafArm_motor_hide;
  MotorStatus leafArm_motor_extend;
  MotorStatus leafArmHand_motor_catch;
  MotorStatus fuckinArm_motor_catch;
  MotorStatus fuckinArm_motor_lift;
  MotorStatus shooting_motor;
} AllMotorStatus;

/*===== モータパラメータ =====*/
#define FORWARD 0
#define BACK 1
static const uint8_t MAX_SPEED  = 85;
static const uint8_t TURN_SPEED = 40;
static const uint8_t STOP_SPEED = 0;

/*===== スレーブに指定するためのパラメータ =====*/
// リーフアームの開閉のための角度指定
static const uint8_t leafArmAngle_open  = 150;
static const uint8_t leafArmAngle_close = 20;
// ファッキンアームの位置指定
static const uint8_t fuckinArmAngle_act1 = 20;
static const uint8_t fuckinArmAngle_act2 = 100;

#endif /* MOTOR_STRUCTURE_H_ */
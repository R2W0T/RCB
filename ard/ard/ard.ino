#include <Servo.h>

Servo fservo, sservo;

//////////////////////////////
#define rrpwm 3
//////////////////////////////
#define rlpwm 11

#define rren 12
#define rlen 13

#define lrpwm 5
#define llpwm 6

#define lren 2
//////////////////////
#define llen 4
////////////////////////
#define fservopin 10
#define sservopin 9

enum {
  VELOCITY_REQ = 0,
  SERVO_REQ = 1,
};

typedef union {
  int8_t rpwm;
  uint8_t angle;
}fval_t;

typedef union {
  int8_t lpwm;
  uint8_t angle;
}sval_t;

typedef struct {
  uint8_t type;
  fval_t fval;
  sval_t sval;
}req_t;

volatile static req_t req = {
  .type = VELOCITY_REQ,
  .fval = { .rpwm = 0 },
  .sval = { .lpwm = 0 },
};

void motors_init() {
  pinMode(rrpwm, OUTPUT);
  pinMode(rlpwm, OUTPUT);
  pinMode(rren, OUTPUT);
  pinMode(rlen, OUTPUT);
  pinMode(lrpwm, OUTPUT);
  pinMode(llpwm, OUTPUT);
  pinMode(lren, OUTPUT);
  pinMode(llen, OUTPUT);
}

void motors_enable() {
  digitalWrite(rren, HIGH);
  digitalWrite(rlen, HIGH);
  digitalWrite(lren, HIGH);
  digitalWrite(llen, HIGH);
}
void servos_init() {
  fservo.attach(fservopin);
  sservo.attach(sservopin);
}

void setup() {
  Serial.begin(9600);
  motors_init();
  motors_enable();
  servos_init();  
}

void loop() {
  Serial.readBytes((char*)(&req), 3);
  switch(req.type) {
    case VELOCITY_REQ:
      if(req.fval.rpwm > 0) {
        analogWrite(rrpwm, req.fval.rpwm);
        analogWrite(rlpwm, 0);
      } else {
        analogWrite(rrpwm, 0);
        analogWrite(rlpwm, -req.fval.rpwm);
      }
      if(req.sval.lpwm > 0) {
        analogWrite(lrpwm, req.sval.lpwm);
        analogWrite(llpwm, 0);
      } else {
        analogWrite(lrpwm, 0);
        analogWrite(llpwm, -req.sval.lpwm);
      }
      break;
    
    case SERVO_REQ:
      fservo.write(req.fval.angle);
      sservo.write(req.sval.angle);
      break;
    
    default:
      break;
  }
}

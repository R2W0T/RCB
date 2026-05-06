#define rrpwm 10
#define rlpwm 11

#define rren 12
#define rlen 13

#define lrpwm 5
#define llpwm 6

#define lren 2
#define llen 3

typedef struct {
  uint8_t rfpwm;  
  uint8_t rbpwm;  
  uint8_t lfpwm;  
  uint8_t lbpwm;  
}vel_t;

volatile static vel_t vel = {
  .rfpwm = 0,
  .rbpwm = 0,
  .lfpwm = 0,
  .lbpwm = 0,
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


void setup() {
  Serial.begin(9600);
  motors_init();
  motors_enable();  
}

void loop() {
  Serial.readBytes((char*)(&vel), 4);
  analogWrite(rrpwm, vel.rfpwm);
  analogWrite(rlpwm, vel.rbpwm);
  analogWrite(lrpwm, vel.lfpwm);
  analogWrite(llpwm, vel.lbpwm);

}

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

#define CLANCH_MODE 0
#define SWEEP_MODE 1
#define CONTROL_MODE 2

/* Mode set */
#define MODE CONTROL_MODE

uint8_t index = 0;

void setup() {
  Serial.begin(115200);
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {

#if MODE == CLANCH_MODE
  clenchServos();
#endif

#if MODE == SWEEP_MODE
  sweepServos();
#endif


#if MODE == CONTROL_MODE
// 1600 is 90
int degree = 1600;

 pwm.writeMicroseconds(12, 1200);

//  for (int i = 0; i < 16; i++) {
//    if(i == 12) {
//          pwm.writeMicroseconds(i, 1500);
//          continue;
//    }
//    if(i == 15) {
//          pwm.writeMicroseconds(i, 1000);
//          continue;
//    }
//    pwm.writeMicroseconds(i, degree);
//  }
#endif  
}

void clenchServos() {
  int i, j;
  int numOfServos = 16;

  for (i = 1100; i < 1600; ++i) {
    for (j = 0; j < numOfServos; j++) {
      pwm.writeMicroseconds(j, i);
    }
  }

  for (i = 1600; i >= 1100; --i) {
    for (j = numOfServos; j >= 0; j--) {
      pwm.writeMicroseconds(j, i);
    }
  }
}

void sweepServos() {
  int i, j;
  int numOfServos = 16;

  for (i = 0; i < numOfServos; i++) {
    for (j = 1100; j < 1600; ++j) {
      pwm.writeMicroseconds(i, j);
    }

    for (j = 1600; j >= 1100; --j) {
      pwm.writeMicroseconds(i, j);
    }
  }
}

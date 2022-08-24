//======================================================================
//
// system name    : Sleve for ESP32
// date/author    : 2022/08/24 @chrmlinux03
// update/author  : 2022/08/24 @chrmlinux03
// LICENSE        : MIT
//----------------------------------------------------------------------
// World's easiest i2c Slave and Master
//
//       Master                        Slave
//   +--------------------+        +--------------------+
//   |                    |        |                    |
//   |3V3                 |        |3V3                 |
//   |G22              G21+---+    |G22              G21+---+
//   |G19              G25+-+ |    |G19              G25+-+ |
//   |G23   G   G G     5V| | |    |G23   G   G G     5V| | |
//   |G33   N 5 2 3    GND| | |    |G33   N 5 2 3    GND| | |
//   |      D V 6 2       | | |    |      D V 6 2       | | |
//   +--------------------+ | |    +--------------------+ | |
//                          +-----------------------------+ |
//                            |       SDA                   |
//                            +-----------------------------+
//                                    SCL
//======================================================================

//============================================
// i2c WorkArea/define
//============================================
#include <Wire.h>
#define I2C_ADRS ((uint8_t)0x12)
#define I2C_SDA ((int)25)
#define I2C_SCL ((int)21)
#define I2C_FREQ ((uint32_t)1000 * 1024)

//============================================
// timer WorkArea/define
//============================================
#define TIMERUSEC (1000 * 1) // 1msec
hw_timer_t *timer = NULL;

//============================================
// regDt WorkArea/define
//--------------------------------------------
// Allocate a 16-byte area and set data
// The last byte is rewritten with a timer 
//============================================
#define I2C_MAXREG (16)
volatile static uint8_t regDt[I2C_MAXREG] = {
  0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 
  0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0x00, 
};
volatile uint8_t regPos = 0;

//============================================
// onTimer Func
// The last byte is rewritten with a timer 
//============================================
void IRAM_ATTR onTimer(void) {
  static uint8_t cnt = 0;
  regDt[I2C_MAXREG - 1] = cnt;
  cnt++;
}

//============================================
// onRequest Func
//============================================
void onRequest() {
  Serial.printf("onRequest send[%02x]\n", regDt[regPos]);
  Wire.write(regDt[regPos]); // Returns the contents of the specified register number
}

//============================================
// onReceive Func
//============================================
void onReceive(int len) {
  Serial.printf("onRecieve [");
  uint8_t c;
  while (Wire.available()) {
    c = Wire.read();
    Serial.printf("%02x", c);
  }
  Serial.println("]");
  regPos = c; // get register number
}

//============================================
// setup
//============================================
void setup() {
  Serial.begin( 115200 ); while(!Serial);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, onTimer, true);
  timerAlarmWrite(timer, TIMERUSEC, true);
  timerAlarmEnable(timer);
  Wire.begin(I2C_ADRS, I2C_SDA, I2C_SCL, I2C_FREQ);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
}

//============================================
// loop
//============================================
void loop() {}

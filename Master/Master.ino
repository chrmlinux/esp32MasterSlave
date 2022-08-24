//======================================================================
//
// system name    : Master for ESP32
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
//======================================================================//======================================================================

//============================================
// i2c WorkArea/define
//============================================
#include <Wire.h>
#define I2C_ADRS ((uint8_t)0x12)
#define I2C_SDA ((int)25)
#define I2C_SCL ((int)21)
#define I2C_FREQ ((uint32_t)400 * 1024)
#define I2C_MAXREG (16)

//============================================
// One byte write to Slave
//============================================
bool i2cWriteByte(int adrs, uint8_t dt) {
  Wire.beginTransmission(adrs);
  Wire.write((int)dt);
  Wire.endTransmission();
  return true;
}

//============================================
// One byte read from Slave
//============================================
uint8_t i2cReadByte(int adrs) {
  int rtn = 0;
  Wire.requestFrom(adrs, 1);
  if (Wire.available() >= 1) {
    rtn = Wire.read();
  }
  Wire.endTransmission();
  return lowByte(rtn);
}

//============================================
// setup
//============================================
void setup() {
  Serial.begin( 115200 ); while(!Serial);
  Wire.begin(I2C_SDA, I2C_SCL, I2C_FREQ);
}

//============================================
// loop
//============================================
void loop() {
  uint8_t c;
  i2cWriteByte(I2C_ADRS, I2C_MAXREG - 1);
  c = i2cReadByte(I2C_ADRS);
  Serial.printf("i2cReadByte:%02x \n", c);
  delay(10);
}

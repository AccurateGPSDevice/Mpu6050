#include "Wire.h" // This library allows you to communicate with I2C devices.

#define X 0.90f
#define Y 0.90f
#define Z 0.90f

const int MPU_ADDR = 0x68; // I2C address of the MPU6050
int16_t accelerometer_filter_x, accelerometer_filter_y, accelerometer_filter_z;
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i)
{
  // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board) or (MPU6050 sensor)
//  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}


void loop()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  // print out Acc Raw Data
  //Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  //Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));/



  // Basic Integrated filter for MPU6050
/*  accelerometer_filter_x = accelerometer_filter_x * X + accelerometer_x * (1.0f - X);
  accelerometer_filter_y = accelerometer_filter_y * Y + accelerometer_y * (1.0f - Y);
  accelerometer_filter_z = accelerometer_filter_z * Z + accelerometer_z * (1.0f - Z);
*/
// print Intefrated filter out put
//  Serial.print("aX-filter = "); Serial.print(convert_int16_to_str(accelerometer_filter_x));
//  Serial.print(" | aY-filter = "); Serial.print(convert_int16_to_str(accelerometer_filter_y));
//  Serial.print(" | aZ-filter = "); Serial.print(convert_int16_to_str(accelerometer_filter_z));




//  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
//  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
//  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)


  //  // print out Gyro Raw Data
  //  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  //  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  //  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));



  Serial.println();

  // 100 milliseconds
  delay(100);
}

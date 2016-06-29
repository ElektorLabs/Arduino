/*
 * Connect FTDI cable to pins 
 *   - 11 (yellow, R4 TXD1, FTDI RXD)
 *   - 12 (orange, R4 RXD1, FTDI TXD) 
 *   - GND (black)
 * Setup a terminal program for FTDI cable at 115200n81
 * Check for welcome message in terminal program
 * Check for PWM signals on pins 0, 1, 2 & 3
 */
 
int pwm = 127;

void setup(void)
{
  Serial1.begin(115200);
  Serial1.println("Elektor Uno R4 on Serial1");
  Serial1.println("You should now see PWM on pins 0, 1, 2 & 3");
}

void loop(void)
{
  analogWrite(0,pwm&0xff);
  analogWrite(1,pwm&0xff);
  analogWrite(2,pwm&0xff);
  analogWrite(3,pwm&0xff);
  pwm++;
  delay(10);
}

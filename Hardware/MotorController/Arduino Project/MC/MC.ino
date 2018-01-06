#include <Encoder.h>  // encoder library: "Encoder by Paul Stoffregen"
#include <PWM.h>
#include <SPI.h>

//#define debug_mode_setup    // debug_mode_setup
//#define debug_mode_spi    

/************************* Declaration ******************************/
unsigned char CalcCRC(unsigned char* data, unsigned char size);
void clr_data(void);
void set_speed_dir(void);
void get_status(void);
void get_position(void);
void set_reset_position(void);

long getPosition(void);
void resetPostion(void);

void motor_stop(void);
bool set_direction(unsigned char dir);
void set_speed(unsigned char v);
/********************** End of Declaration **************************/

/************************* Encoder ******************************/
#define intPin1 2     // interrupt pins (2 and 3 er the two intertupt pins on Atmega328)
#define intPin2 3

Encoder myEnc(intPin1, intPin2);  // Create encoder object and connect interrupt pins

unsigned int encPos  = 0;
long getPosition(void)  // function returns accumulated postion as long
{
  return myEnc.read();
}

void resetPostion(void) // function resets accumulated postion to zero
{
  myEnc.write(0);
}
/************************* End of Encoder ************************/

/************************* H-Bridge ******************************/
int32_t frequency = 10000; //frequency (in Hz)

/************* H-bridge drive pins and values definition *****************/
const byte  csPin = A0;
const byte  tmPin = 6;
const byte  brakePin = 7;
const byte  dirPin = 8;
const byte  pwmPin = 9;

/************* limit switches pins and values definition *****************/
const byte  sw1Pin = 5;
const byte  sw2Pin = 4;

#define goNone 0
#define goLeft 1
#define goRight 2

unsigned char pwmDuty = 200;
unsigned char motorDir = goNone;

#define brake_motor() digitalWrite(brakePin, HIGH)
#define activate_motor() digitalWrite(brakePin, LOW)

void motor_stop(void)
{
  brake_motor();
  pwmWrite(pwmPin, 0);
#ifdef debug_mode
  delay(1000);
  Serial.println("Motor Stopped!");
#endif
}

bool set_direction(unsigned char dir)
{
  if ((!digitalRead(sw1Pin)) && (dir == goLeft))
  {
    digitalWrite(dirPin, HIGH);
#ifdef debug_mode
    Serial.println("Dir set to Left");
#endif
    return true;
  }

  if ((!digitalRead(sw2Pin)) && (dir == goRight))
  {
    digitalWrite(dirPin, LOW);
#ifdef debug_mode
    Serial.println("Dir set to Right");
#endif
    return true;
  }
  return false;
}
void set_speed(void)
{
  //convert speed to duty
  pwmWrite(pwmPin, pwmDuty);
  activate_motor();
}
/************************* End of H-Bridge ***********************/

/************************* SPI ******************************/
#define SOT 0x96
enum STATE {WaitForSOT, SOTRev, WaitForProc, SendDATA, ClrDATA};
volatile STATE spi_state = WaitForSOT;

volatile unsigned char recvIdx = 0;
volatile unsigned char sendIdx = 0;
#define recvLength 4
#define sendLength 5
volatile unsigned char recvData[recvLength] = { NULL };
volatile unsigned char sendData[sendLength] = { SOT, 4, 0, 0, 146 };

#define MTRCTRL_SET_SPEED_DIR   0
#define MTRCTRL_GET_STATUS    1
#define MTRCTRL_GET_POSITION  2
#define MTRCTRL_SET_RESET_POS 3
#define MTRCTRL_NOT_DEFINED 4

unsigned char CalcCRC(unsigned char* data, unsigned char size)
{
  unsigned char crc = 0;
  while (size--)
    crc ^= *data++;
  return crc;
}

void clr_data(void)
{
  sendData[1] = MTRCTRL_NOT_DEFINED;
  sendData[2] = 0;
  sendData[3] = 0;
  sendData[4] = CalcCRC(sendData, sendLength - 1);
}

void set_speed_dir(void)
{
  unsigned char val = recvData[2];
  sendData[1] = MTRCTRL_SET_SPEED_DIR;
  sendData[2] = 0;
  sendData[3] = 0;
  sendData[4] = CalcCRC(sendData, sendLength - 1);
  spi_state = SendDATA;

  motorDir = ((val & 0x80) >> 7) + 1;
  pwmDuty = val & 0x7F;

  if(pwmDuty > 0) pwmDuty = 20 + (pwmDuty << 1);

#ifdef debug_mode_spi
  Serial.println("MTRCTRL_SET_SPEED_DIR!");
  Serial.print("Dir: ");
  Serial.println(motorDir);
  Serial.print("Speed: ");
  Serial.println(pwmDuty);
#endif

  //  if (set_direction(motorDir))
  //  {
  //    set_speed(pwmDuty);
  //  }
  //  else
  //  {
  //    motor_stop();
  //#ifdef debug_mode
  //    Serial.print("Not able to set dir to (1. left; 2. right): ");
  //    Serial.println(motorDir);
  //#endif
  //  }
}
void get_status(void)
{
  unsigned char val = 0;
  if (digitalRead(sw1Pin))
    val = 0x80;
  if (digitalRead(sw2Pin))
    val |= 0x40;

  sendData[1] = MTRCTRL_GET_STATUS;
  sendData[2] = val;
  sendData[3] = 0;
  sendData[4] = CalcCRC(sendData, sendLength - 1);
  spi_state = SendDATA;

#ifdef debug_mode_spi
  Serial.println("MTRCTRL_GET_STATUS!");
#endif

}
void get_position(void)
{
  sendData[1] = MTRCTRL_GET_POSITION;
  sendData[2] = encPos % 256;
  sendData[3] = encPos / 256;
  sendData[4] = CalcCRC(sendData, sendLength - 1);
  spi_state = SendDATA;

#ifdef debug_mode_spi
  Serial.println("MTRCTRL_GET_POSITION!");
  Serial.print("Position: ");
  Serial.println(encPos);
#endif


}
void set_reset_position(void)
{
  sendData[1] = MTRCTRL_SET_RESET_POS;
  sendData[2] = 0;
  sendData[3] = 0;
  sendData[4] = CalcCRC(sendData, sendLength - 1);
  spi_state = SendDATA;


#ifdef debug_mode_spi
  Serial.println("MTRCTRL_SET_RESET_POS!");
#endif

  resetPostion();
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  switch (spi_state)
  {
    case WaitForSOT:
      if (SOT == SPDR)
      {
        spi_state = SOTRev;
        recvIdx = 1;
      }
      break;
    case SOTRev:
      recvData[recvIdx++] = SPDR;
      if (recvIdx == recvLength)
        spi_state = WaitForProc;
      break;
    case WaitForProc:
      break;
    case SendDATA:
      SPDR = sendData[sendIdx++];
      if (sendIdx == sendLength)
        spi_state = ClrDATA;
      break;
    case ClrDATA:
      break;
    default: break;
  }
}  // end of interrupt service routine (ISR) SPI_STC_vect
/********************** End of SPI **************************/

void setup() {
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe();
  /************* H-bridge drive initialization *****************/
  pinMode(tmPin, INPUT);
  pinMode(brakePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  brake_motor();
  bool success = SetPinFrequencySafe(pwmPin, frequency); //to check if we set the frequency correctly

  /************* Limit switch initialization *****************/
  pinMode(sw1Pin, INPUT);
  pinMode(sw2Pin, INPUT);

  /************* SPI initialization *****************/
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SS, INPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);// turn on SPI in slave mode
  SPCR |= _BV(SPIE);// turn on interrupts
  recvData[0] = SOT;

#ifdef debug_mode_setup
  Serial.begin(115200);
  if (!success) Serial.println("PWM setting failed.");
  Serial.println("Debug Mode:");
#endif
}
unsigned int encPosBf = 0;
void loop() {
  encPosBf = (unsigned int) getPosition();
  if(encPosBf < 10000) encPos = encPosBf;
#ifdef debug_mode
  Serial.print("Encoder: ");
  Serial.println(encPos);
#endif

  if (spi_state == ClrDATA)
  {
    sendIdx = 0;
    clr_data();
    spi_state = WaitForSOT;
  }
  if (spi_state == WaitForProc)
  {
#ifdef debug_mode_spi
    Serial.println("-------------------------");
    for (unsigned char i = 0; i < recvLength; i++ )
    {
      Serial.print(recvData[i], HEX);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println("----------");
#endif
    if (CalcCRC(recvData, recvLength - 1) == recvData[recvLength - 1])
    {
#ifdef debug_mode_spi
      Serial.println("CRC succeed!");
#endif
      switch (recvData[1])
      {
        case MTRCTRL_SET_SPEED_DIR:
          set_speed_dir();
          break;
        case MTRCTRL_GET_STATUS:
          get_status();
          break;
        case MTRCTRL_GET_POSITION:
          get_position();
          break;
        case MTRCTRL_SET_RESET_POS:
          set_reset_position();
          break;
        default:
          spi_state = WaitForSOT;
          break;
      }
    }
    else
    {
#ifdef debug_mode_spi
      Serial.println("CRC failed!");
#endif
      spi_state = WaitForSOT;
    }
  }

#ifdef debug_mode
  if (Serial.available() > 0) motorDir = Serial.read() - 48;
  if (motorDir == goNone)
  {
    motor_stop();
    return;
  }
#endif  
  if (set_direction(motorDir))
  {
    set_speed();
  }
  else
  {
    motor_stop();
#ifdef debug_mode
    Serial.print("Not able to set dir to (1. left; 2. right): ");
    Serial.println(motorDir);
    if(motorDir == 1) motorDir = 2;
    else motorDir = 1;
#endif

  }
  //delay(100);
}

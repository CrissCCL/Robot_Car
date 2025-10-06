/*Control robot*/
/*Cristian Castro Lagos*/
#include <Wire.h>
#include <PulsePosition.h>
PulsePositionInput ReceiverInput(RISING);
float Rx_Val[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int ChannelNumber = 0;
float PwR_prop;
float SwA;
float SwB;
float Rotar;
float refYaw;
float uSig=0.0;
float uYaw=0.0,uYaw_1=0.0;
float tiempo=0.0;
float K0=-11.8271;
float K1=11.3794;
void read_Rx(void) {
  ChannelNumber = ReceiverInput.available();
  if (ChannelNumber > 0) {
    for (int i = 1; i <= ChannelNumber; i++) {
      Rx_Val[i - 1] = ReceiverInput.read(i);
    }
  }
}
int ledPin = 13;
// Definición de pines del puente H (L298N)
// Motor 1
#define IN1 2  // Dirección 1 del Motor 1
#define IN2 3  // Dirección 2 del Motor 1
#define ENA 4  // PWM para controlar velocidad del Motor 1

// Motor 2
#define IN3 5  // Dirección 1 del Motor 2
#define IN4 6  // Dirección 2 del Motor 2
#define ENB 7  // PWM para controlar velocidad del Motor 2
float uA = 0.0;
float uB = 0.0;
float RateRoll, RatePitch, RateYaw;
float e=0.0,e_1=0.0;
float AccX,AccY,AccZ;
float AngleRoll,AnglePitch;
float RateCalibrationRoll, RateCalibrationPitch,RateCalibrationYaw;
int RateCalibrationNumber;
float AccCalibrationX, AccCalibrationY,AccCalibrationZ;
int AccCalibrationNumber;
uint32_t LoopTimer;

void gyro_signals(void) {
  Wire.beginTransmission(0x68); // inicializacion comm
  Wire.write(0x1A); // activacion de configuraciones filtro
  Wire.write(0x05); // filtro pasabajos
  Wire.endTransmission(); 
  // acelerometro
  Wire.beginTransmission(0x68); // inicializacion comm
  Wire.write(0x1C); //activacion de configuracione sensibilidad y factor de escala
  Wire.write(0x10); // factor de escala +/- 8g
  Wire.endTransmission(); 
  Wire.beginTransmission(0x68);// inicializacion comm
  Wire.write(0x3B); // direccion 3B a 40 medicion acelerometro
  Wire.endTransmission();
  Wire.requestFrom(0x68,6); // requerimiento de 6 registros
  int16_t AccXLSB=Wire.read()<<8 | Wire.read();// formacion de digito de 16 bits MSB y luego LSB 2 bytes ACCEL_XOUT_H & ACCEL_XOUT_L
  int16_t AccYLSB=Wire.read()<<8 | Wire.read();
  int16_t AccZLSB=Wire.read()<<8 | Wire.read();
  // giroscopio
  Wire.beginTransmission(0x68); // inicializacion comm
  Wire.write(0x1B); //activacion de configuracione sensibilidad y factor de escala
  Wire.write(0x8); // factor de escala +/- 500 °/s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0x68);// inicializacion comm
  Wire.write(0x43); // direccion 43 a 48 medicion giroscopio, se parte en 43
  Wire.endTransmission();
  Wire.requestFrom(0x68,6); // requerimiento de 6 registros
  int16_t GyroX=Wire.read()<<8 | Wire.read();// formacion de digito de 16 bits MSB y luego LSB 2 bytes GYRO_XOUT_H & GYRO_XOUT_L
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();
  //conversion
  RateRoll=(float)GyroX/65.5;
  RatePitch=(float)GyroY/65.5;
  RateYaw=(float)GyroZ/65.5;
  AccX=(float)AccXLSB/4096-0.05;
  AccY=(float)AccYLSB/4096+0.01;
  AccZ=(float)AccZLSB/4096-0.11;
}
void setup() {
  Serial1.begin(57600);
  pinMode(ledPin, OUTPUT);       // LED
    // Configura los pines de dirección como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configura los pines de velocidad (PWM) como salidas
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configuración del PWM
  analogWriteFrequency(ENA, 250);  // Frecuencia: 250 Hz
  analogWriteFrequency(ENB, 250);
  analogWriteResolution(12);  // Resolución: 12 bits (4096 niveles)
  ReceiverInput.begin(14);
  delay(250);
  while (Rx_Val[2] < 998 || Rx_Val[2] > 1050) {
    read_Rx();
    delay(4);
  }
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  for(RateCalibrationNumber=0;RateCalibrationNumber<3000;RateCalibrationNumber++) {
    gyro_signals();
    RateCalibrationRoll+=RateRoll;
    RateCalibrationPitch+=RatePitch;
    RateCalibrationYaw+=RateYaw;
    delay(1);
 }
  RateCalibrationRoll/=3000;
  RateCalibrationPitch/=3000;
  RateCalibrationYaw/=3000;
  digitalWrite(ledPin, HIGH);
  LoopTimer=micros();
}


void loop() {
  read_Rx();
  gyro_signals();
  PwR_prop = Rx_Val[2];
  SwA = Rx_Val[4];
  SwB = Rx_Val[5];
  RateYaw-=RateCalibrationYaw;
  // Configuración del Motor 2 hacia adelante
  if (SwA<= 1000) {
  Rotar= -(Rx_Val[0]-1500);
  }
  // Configuración del Motor 2 hacia atras
  if (SwA>= 1990) {
  Rotar= (Rx_Val[0]-1500);
  }
if (SwB<= 1000){
// control manual
refYaw=RateYaw;
}
if (SwB>= 1990){
// control automatico
refYaw=Rotar*0.15; // microseg a °/s  -> rotar*0.15  1000 a 2000 a -75 °/s y 75 °/s
}
e=refYaw-RateYaw; 
uYaw=uYaw_1+K0*e+K1*e_1;
uYaw_1=uYaw;
e_1=e;
if (SwB<= 1000){
// control manual
uSig=-Rotar;
}
if (SwB>= 1990){
// control automatico
uSig=uYaw;
}
if (PwR_prop>1800){
  PwR_prop=1800;
}
if (SwA<= 1000) {
// Configuración del Motor 1 hacia adelante
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
// Configuración del Motor 1 hacia adelante
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
uA=PwR_prop+uSig;
uB=PwR_prop-uSig;
}
if (SwA>= 1990) {
  // Configuración del Motor 1 hacia atras
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Configuración del Motor 2 hacia atras
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  uA=PwR_prop-uSig;
  uB=PwR_prop+uSig;
}  


  if(uA>2000){
    uA=1999;
  }
  if(uA<1180){
    uA=1180;
  }
  
  if(uB>2000){
    uB=1999;
  }
  if(uB<1180){
    uB=1180;
  }
    if(PwR_prop<1050){
    uA=1000;
    uB=1000;
    e_1=0;
    uYaw_1=0;

  }

  analogWrite(ENA, map(uA, 1000, 2000, 0, 4095)); 
  analogWrite(ENB, map(uB, 1000, 2000, 0, 4095));

  Serial1.print(Rotar);  
  Serial1.print(","); 
  Serial1.print(RateYaw);
  Serial1.print(",");
  Serial1.print(uA);
  Serial1.print(",");
  Serial1.println(tiempo);
  while ( micros() - LoopTimer< 4000); // el codigo se bloquea o no avanza hasta que se cumpla la condicion
  LoopTimer=micros();
  tiempo=tiempo+0.004;
}
#include <Servo.h>
#include <SoftwareSerial.h>
int sekali;
String Arsp, Grsp;
SoftwareSerial gsm(2, 3); // RX, TX
Servo servo1;

const int trigPin = 6;
const int echoPin = 5;
const int trigPin2 = 11;
const int echoPin2 = 10;
const int pinServo = 9;
const int led = 13;

long duration;
long duration2;
int distance;
int distance2;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(pinServo);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  gsm.begin(4800);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance = duration * 0.034 / 2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  Serial.print("Jarak : ");
  Serial.println(distance);
  Serial.print("Jarak2 : ");
  Serial.println(distance2);

  if (gsm.available() != 0)
  {
    Grsp = gsm.readString();
    Serial.println(Grsp);
  }
  if (Serial.available() != 0)
  {
    Arsp = Serial.readString();
    gsm.println(Arsp);
  }

  if (distance < 30 && distance2 > 10)
  {
    servo1.write(35);
    delay(3000);
  }
  else {
    servo1.write(0);
  }

  if (distance2 >0 && distance2 < 8 && sekali == 0) {
    gsm.println("AT+CMGF=1"); //AT command for text mode of gsm module
    delay(1000);
    gsm.println("AT+CMGS=\"087872700313\"\r"); //  x is your mobile number
    delay(1000);
    gsm.println("TS001 di lokasi A telah penuh. Harap diambil. Terimakasih...");// the text you want to send
    delay(100);
    gsm.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println(gsm.readString());
    sekali = 1;
  }
}

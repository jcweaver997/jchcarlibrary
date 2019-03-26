#include <pca9685.h>
#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)

int fd = 0;

int servo_percent(float p){
  return (int)(min(max(p,0),1)*150+240);
}

extern void init_rchcar(){
  wiringPiSetup();
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  fd = pca9685Setup(300, 0x40, 50);
  pca9685PWMReset(fd);
}

extern void set_servo(float p){
  pca9685PWMWrite(fd,1,0,servo_percent(p));
}

extern void set_drive(float p){
  float val = max(min(fabsf(p),1),0)*4095;
  if(p<0){
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }else if(p>0){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }else{
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  pca9685PWMWrite(fd,2,0,(int)val);
}

extern void close_rchcar(){
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  pca9685PWMWrite(fd,2,0,0);
  pca9685PWMWrite(fd,1,0,servo_percent(.5f));
}

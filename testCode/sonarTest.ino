#include <SPI.h>



#define WRITE_STROBE  3

int intToBinary(char *str, unsigned int n );
int setParallel(char *str);


int a=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(1, INPUT);
  pinMode(3, INPUT);
  
  int i = 0;
  for(i=0; i<8; i++){
   pinMode(4+i, OUTPUT);
 }
  
  Serial.println("Sonar enable\n");
}







void loop() {
  // put your main code here, to run repeatedly: 
  unsigned int data;
  unsigned int timeStart;
  unsigned int timeEnd;
  char str[9];
  int i =0;

  for(i=0; i<8; i++){
    str[i] = '0'; 
  }
  
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2,HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  while(digitalRead(1) == LOW);
  timeStart = micros();
  while(digitalRead(1) == HIGH);
  timeEnd = micros();
  if(digitalRead(WRITE_STROBE) == 1){
    Serial.println((timeEnd - timeStart)/80);
    intToBinary(str, ((timeEnd - timeStart)/80));
    //intToBinary(str, a++);
    Serial.println(str);
    setParallel(str);

  }
  //delay(500);
}



int intToBinary(char *str, unsigned int n )
{
  int i = 8;
  *(str+i) = '\0';

  do str[ --i ] = '0' + (n & 1);
  while (n >>= 1);

  //return string( result + index );
  return 0;
}


int setParallel(char *str){
  int pin = 4;
  int i =0;

  for(i=0; i<8; i++){
    if(str[7-i] == '0'){
      //Serial.print('x'); 
      digitalWrite(pin+i, LOW);
    } 
    else {
      //Serial.print('1');
      digitalWrite(pin+i, HIGH);

    }


  }

}



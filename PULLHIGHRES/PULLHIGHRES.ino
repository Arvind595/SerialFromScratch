#define datain_clock_pin 2 //output1
#define datain_pin 4 //output 2
#define datain_enable_pin 7 //output 3

#define dataout_clock_pin 3 //input 5
#define dataout_pin 5 //input 4
#define dataout_enable_pin 6 //input 3
#define spare_pin1 9 //input 2
#define spare_pin2 10 //input 1

void setup(){
  pinMode(datain_clock_pin, INPUT_PULLUP);
  pinMode(datain_pin, INPUT_PULLUP);
  pinMode(datain_enable_pin, INPUT_PULLUP);

  pinMode(dataout_clock_pin, OUTPUT);
  pinMode(dataout_pin, OUTPUT);
  pinMode(dataout_enable_pin, OUTPUT);
  pinMode(spare_pin1, OUTPUT);
  pinMode(spare_pin2, OUTPUT);
  

  digitalWrite(dataout_clock_pin, 0);
  digitalWrite(dataout_enable_pin, 0);
  digitalWrite(dataout_pin, 0);
  digitalWrite(spare_pin1, 0);
  digitalWrite(spare_pin2, 0);

   Serial.begin(115200);

}

void loop(){
/*
Serial.print("DigitalSet 0 : Digitalread :  ");
digitalWrite(spare_pin2, 0);
Serial.println(digitalRead(datain_clock_pin));

Serial.print("DigitalSet 1 :  DigitalRead : ");
digitalWrite(spare_pin2, 1);
Serial.println(digitalRead(datain_clock_pin));
*/

}
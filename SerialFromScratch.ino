#define clock_pin 1
#define dataout_pin 2
#define enable_pin 3
#define datain_pin 4

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(clock_pin,OUTPUT);
pinMode(dataout_pin, OUTPUT);
pinMode(enable_pin,OUTPUT);
pinMode(datain_pin,INPUT);

delay(1);

digitalWrite(clock_pin,0);
digitalWrite(dataout_pin,0);
digitalWrite(enable_pin,0);

delay(1);

Serial.println("Set");


}

void pulse_clock(short time=10){

  digitalWrite(clock_pin,1);
  delay(time);
  digitalWrite(clock_pin,0);
  delay(time);
}

uint8_t send_data(uint8_t data){

for (uint8_t i =0 ; i<8; i++){
  if ((data & 0x80) == 1){
    digitalWrite(dataout_pin,1);
  }
  else digitalWrite(dataout_pin,0);
}

  data=data<<1;
  pulse_clock(50);

}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t txbuffer =0;

digitalWrite(enable_pin,1);
send_data(txbuffer);
digitalWrite(enable_pin,0);

delay(100);


}

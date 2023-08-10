//to recieve
#define datain_clock_pin 2 //output1
#define datain_pin 4 //output 2
#define datain_enable_pin 7 //output 3

//to send
#define dataout_clock_pin 3 //input 5
#define dataout_pin 5 //input 4
#define dataout_enable_pin 6 //input 3
#define spare_pin1 9 //input 2
#define spare_pin2 10 //input 1

uint8_t rxbuffer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(dataout_clock_pin, OUTPUT);
  pinMode(dataout_pin, OUTPUT);
  pinMode(dataout_enable_pin, OUTPUT);
  pinMode(spare_pin1, OUTPUT);
  pinMode(spare_pin2, OUTPUT);

  pinMode(datain_clock_pin, INPUT_PULLUP);
  pinMode(datain_pin, INPUT_PULLUP);
  pinMode(datain_enable_pin, INPUT_PULLUP);

  delayMicroseconds(1);

  digitalWrite(dataout_clock_pin, 0);
  digitalWrite(dataout_enable_pin, 0);
  digitalWrite(dataout_pin, 0);


  delayMicroseconds(1);

  Serial.println("Set");
}

void pulse_clock(short time = 1) {
  //rising edge
  digitalWrite(dataout_clock_pin, 1);
  delayMicroseconds(time);
  digitalWrite(dataout_clock_pin, 0);
  delayMicroseconds(time);
}

uint8_t read_data(void) {

  uint8_t data = 0;
  uint8_t count = 8;

  while (count) {

    if ( pulseIn(datain_clock_pin, ((count %2 == 0)? HIGH : LOW)) < 200) {
      count -= 1;
      data = digitalRead(datain_pin);
      data = data << 1;
    }
  }
  return data;
}

void send_data(uint8_t data, uint8_t time) {

  for (uint8_t i = 0; i < 8; i++) {
    if ((data & 0x80)>>7 == 1) {
      digitalWrite(dataout_pin, 1);
    } else digitalWrite(dataout_pin, 0);
    pulse_clock(time);
    //delayMicroseconds(time); //
    data = data << 1;
  }
  digitalWrite(dataout_pin, 0);
}

void loop() {
  // To Send
  uint8_t txbuffer = 0xaa;

  digitalWrite(dataout_enable_pin, 1);
  send_data(txbuffer,1);
  digitalWrite(dataout_enable_pin, 0);

  delay(1);

 Serial.println("rxbuffer");
  // To Reviece
  while (digitalRead(datain_enable_pin)) {
    //Serial.println("dataincoming : ")
    rxbuffer = read_data();
    
    Serial.print(rxbuffer);
  }
}

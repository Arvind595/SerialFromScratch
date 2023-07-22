//to recieve
#define datain_clock_pin 1
#define datain_pin 5
#define datain_enable_pin 6

//to send
#define dataout_clock_pin 2
#define dataout_pin 3
#define dataout_enable_pin 4

uint8_t rxbuffer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(dataout_clock_pin, OUTPUT);
  pinMode(dataout_pin, OUTPUT);
  pinMode(dataout_enable_pin, OUTPUT);

  pinMode(datain_clock_pin, INPUT);
  pinMode(datain_pin, INPUT);
  pinMode(datain_enable_pin, INPUT);

  delay(1);

  digitalWrite(dataout_clock_pin, 0);
  digitalWrite(dataout_enable_pin, 0);
  digitalWrite(dataout_pin, 0);


  delay(1);

  Serial.println("Set");
}

void pulse_clock(short time = 10) {
  //rising edge
  digitalWrite(dataout_clock_pin, 1);
  delay(time);
  digitalWrite(dataout_clock_pin, 0);
  delay(time);
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

void send_data(uint8_t data) {

  for (uint8_t i = 0; i < 8; i++) {
    if ((data & 0x80) == 1) {
      digitalWrite(dataout_pin, 1);
    } else digitalWrite(dataout_pin, 0);
  }

  data = data << 1;
  pulse_clock(50);
}

void loop() {
  // To Send
  uint8_t txbuffer = 0;

  digitalWrite(dataout_enable_pin, 1);
  send_data(txbuffer);
  digitalWrite(dataout_enable_pin, 0);

  delay(100);

  Serial.println("rxbuffer");

  // To Reviece
  while (digitalRead(datain_enable_pin)) {
    //Serial.println("dataincoming : ")
    rxbuffer = read_data();
    Serial.println("rxbuffer");
  }
}

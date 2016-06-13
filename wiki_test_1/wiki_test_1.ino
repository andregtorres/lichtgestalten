//André Torres JUN2016

int led[] = {13};					//LED output pins
int brightness=0;
int fade=0;
int fade_rate =1;
int flag_t1=0;

/* TMR1 OC interrupt vector */
ISR(TIMER1_COMPA_vect){
  flag_t1=1;          
}

void setup() {
  Serial.begin(9600); 				// open the serial port
  pinMode(led[0], OUTPUT);			//LED pin declaration

  //TIMER1 SETUP
  TCNT1  = 0;                     //reset
  TCCR1A = 0;                     //clear register
  TCCR1B = 0;                     //clear register
  OCR1A = 12500;                   // 6250 for 100 ms w\ ps=256
  TCCR1B |= (1 << WGM12);         // CTC mode
  TCCR1B |= (1<<CS10);            //PS=256
  TCCR1B &= ~(1<<CS11);           //PS
  TCCR1B &= ~(1<<CS12);           //PS
  TIMSK1 |= (1 << OCIE1A);        // enable timer compare interrupt
  TIMSK1 &= ~(1 << ICIE1);        // disable IC interrupt
}

void loop() {
  if (Serial.available() > 0) {		// check for incoming serial data
    char inChar = Serial.read();	// read incoming serial data
    brightness=255;
    fade=0;
    Serial.println(Serial.available());
  }
  
  if (flag_t1==1){
  	if(fade <= 255-fade_rate){
  		fade = fade + fade_rate;
      flag_t1=0;
      Serial.println(brightness);
  }
    if (brightness >= fade_rate)
  	  brightness = brightness - fade;
    else
      brightness=0;
      
  	analogWrite(led[0], brightness);
    
  }
}

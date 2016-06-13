//André Torres JUN2016

int led[] = {11,10};					//LED output pins
int brightness[]={0,0};
int fade_rate[] = {1,1};

void setup() {
  Serial.begin(9600); 				// open the serial port
  pinMode(led[0], OUTPUT);			//LED pin declaration
  pinMode(led[1], OUTPUT);      //LED pin declaration

}

void loop() {
  if (Serial.available() > 0) {		// check for incoming serial data
    char inChar = Serial.read();	// read incoming serial data
    brightness[inChar-'0']=255;
    fade_rate[inChar-'0']=20;
  }

   //Serial.println(brightness[0]);
   for (int i=0; i<2; i++){
     if(brightness[i] > 0){
       brightness[i] = brightness[i] - fade_rate[i];
       if (fade_rate[i] > 1)
         fade_rate[i]--;
       analogWrite(led[i], brightness[i]);
     }
     else
     brightness[i]=0;
    }
  delay(10);
}

#define line_left A4 // The IO pins connected to sensor
#define line_right A5
 
int irleft_reflect = 0; // Readings stored here
int irright_reflect = 0;
 
void setup() { 
   Serial.begin (9600); // Set the baud rate
} 
 
 

void loop() { 
 
  // Read the reflectance sensors
  // Values range from 0 to 1023, representing
  // analog voltage from 0 to 5 volts
  // 0 = solid white; 1023 = solid black
  irleft_reflect = analogRead(line_left);
  irright_reflect = analogRead(line_right);
 
  Serial.print ("Left:");      
  Serial.print ("\t");        
  Serial.print (irleft_reflect);
  Serial.print ("\t");
  Serial.print ("Right:");
  Serial.println (irright_reflect);
   
  delay(100);
}

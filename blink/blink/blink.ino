
 
 #define RELAY 1 // relay connected to  GPIO0

 
void setup() 
{
  
  pinMode(RELAY,OUTPUT);



 
 

  
 
 
}
 
void loop() 
{
  
    
    digitalWrite(RELAY,LOW);
    delay(1000);
    digitalWrite(RELAY,HIGH);
    delay(1000);
   
   
}

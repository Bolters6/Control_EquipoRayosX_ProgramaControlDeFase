int zero = 5; //Detector de cruce por cero
int opto = 4;//Optotriac
int disparo = 6; // Bobina rele
int foco = 5;
int ledalto = 7, ledbajo = 8;
int READY = 0;
float ma, t, voltaje;
void setup() {
  
  Serial.begin(9600);
  pinMode(zero, INPUT);
  pinMode(opto, OUTPUT);
  pinMode(disparo, OUTPUT);
  pinMode(foco, OUTPUT);
  pinMode(ledalto, OUTPUT);
  pinMode(ledbajo, OUTPUT);

}

void loop() {
  
if ( ma == 50 ) {
  voltaje = 59.3;
}
if ( ma == 100 ) {
  voltaje = 63.8;
}
if ( ma == 200 ) {
  voltaje = 86;
}
if ( ma == 300 ) {
  voltaje = 90;
}

if ( ma <= 100 ) {
  digitalWrite(ledalto , LOW);
  digitalWrite(ledbajo , HIGH);
  digitalWrite(foco, LOW);
} else {
  digitalWrite(ledbajo , LOW);
  digitalWrite(ledalto , HIGH);
  digitalWrite(foco, HIGH);
}

      float t1 = (-0.0187+ sqrt( sq(0.0187)-4 * -8 * pow(10, -8) * (150.18 - voltaje))) / ( 2 * -8 * pow(10, -8));
     float t2 = (-0.0187 - sqrt( sq(0.0187)-4 * -8 * pow(10, -8) * (150.18 - voltaje))) / ( 2 * -8 * pow(10, -8)); // Linealizacion 
    
     if (t1 < 0 ){
       t = t1 * -1;
     }else{
       t = t2 * -1;
     }
    
 if ( ma <= 100 )&&(foco == LOW ){
  READY = 1;
 }
  
 if ( ma >= 100 )&&(foco == HIGH ){
  READY = 1;
 }

 if ( READY == 1) {
    
     digitalWrite(disparo, HIGH);
  
 
int  m = 0;
int  n = 0;
     
      do {
         bool cruce = digitalRead(zero);
          if ((cruce == HIGH) && ( m == 0)){ // Detector de cruce por cero
             digitalWrite(opto, LOW); 
             delayMicroseconds(t);
             digitalWrite(opto, HIGH);
          m = 1;
          }
          
    }while ((m == 0));
      
    do {
         bool cruce = digitalRead(zero); 
          if ((cruce == HIGH) && (n == 0)){ // Detector de cruce por cero   
            digitalWrite(opto, LOW);  
            delayMicroseconds(t);
            digitalWrite(opto, HIGH);
       
            
            n = 1;
        }
    }while (n==0);
    
  
  digitalWrite(disparo, LOW);
  
 }
   }

}}

  

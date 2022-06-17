int zero = 9, KVPlus = 3, KVMinus = 4, TPlus = 5, TMinus = 6, mAPlus = 7, mAMinus = 8; //Detector de cruce por cero
int opto = 11;//Optotriac
int disparo = 12; // Bobina rele
float ton, disc, KVSolicitado, TSolicitado, Voltajeprimario; 
int cruce, propte;
char val, ret, u;
double t1, t2, tm, t;
int rotacion= 13, Ready = 10;
int unidad, decena, centena, flag1, valor1, valor2,pre, flagReady, decenaMili, centenaMili, segundo, pre;
char buttom, buttom1, shoot;
 
 

void setup() {
  pinMode(pre, INPUT);
 pinMode(rotacion, OUTPUT);
 pinMode(READY , OUTPUT);
 unidad = 0;
 decena = 4;
 centena = 0;
 flag1 = 0;
 flagReady = 0;
 decenaMili = 0;
 centenaMili = 1;
 segundo = 0;
 pinMode(zero, INPUT);
 pinMode(opto, OUTPUT);
 pinMode(disparo, OUTPUT);
 Serial.begin(9600);
}
 
  

void loop() {

buttom = Serial.read();
valor2 = analogRead(A1);
pre = analogRead(A2);  
if ((buttom == '1'  || KVPlus == HIGH )&& pre <= 100 ){// leo el pulso del boton y me aseguro que no este en pre  
    if (decena < 8){// evaluo que la decena sea menor a  para hacer el cambio de pendiente
      if (centena == 0){//aseguro que no se halla sobrepasado la centena
      unidad = unidad +5;
      if (unidad == 10){// considero amentar la decena despues de sobrepasar 9 en la unidad
        decena = decena + 1;
        unidad = 0;
        }
      }
    }
   if( flag1 == 1){// aumento de 10 en 10 con la bandera
    decena = decena + 1 ;
      if (decena == 10){
        centena = 1;
        decena = 0; 
       ;
      }
   }
  if(decena == 7){
    if (unidad == 5){// en esta seccion del codigo hago que el contador cambio la pendiente de 5 a 10 y activo la bandera de cuenta
      decena = 8;
      unidad = 0;
      flag1 = 1;// bandera de suma de 10
    }
  }
  if (centena == 1){
    if (decena > 2){
      centena = 0;
      decena = 4;
      unidad = 0;
      flag1= 0;
      }
    
    }

     Serial.println(" la cantidad es: ");
  Serial.print(centena, DEC);
  Serial.print(decena, DEC);
  Serial.println(unidad, DEC);
    
 
 }

 if ((buttom == '0'  || KVMinus == HIGH)&& pre < 100){// leo el pulso del boton
  if (decena < 8){
    if (centena == 0){
      unidad = unidad - 5;
      if (unidad < 0){
        unidad = 5;
        decena = decena -1;
        }
      }
    }
   if (decena == 8){
    flag1 = 0;
    decena = 7;
    }
   if(flag1 == 1){
    decena = decena - 1;
    if (decena < 0){
      decena = 9;
      centena= centena -1;
      }
    }
  if (centena == 0){
    if (decena <4 ){
      centena = 1;
      decena=2;
      unidad= 0; 
      flag1=1;
      } 
    }
  Serial.println(" la cantidad es: ");
  Serial.print(centena, DEC);
  Serial.print(decena, DEC);
  Serial.println(unidad, DEC);
  delay(100);  
    }
if ((buttom == '2' || TPlus == HIGH)&& (pre < 100)){
  if (segundo == 2){
    segundo= 0;
    centenaMili = 0;
    decenaMili = 5;
    }
  if(segundo < 2){
    decenaMili = decenaMili + 5;
    if (decenaMili == 10){
      decenaMili =0;
      centenaMili = centenaMili + 1;
      if (centenaMili == 10){
        centenaMili = 0;
        segundo= segundo + 1;

        }
      }
    }

 Serial.println(" la cantidad de tiempo es: ");
  Serial.print(segundo, DEC);
  Serial.print(".");
  Serial.print(centenaMili, DEC);
  Serial.println(decenaMili, DEC);
  }
if ((buttom == '3' || TMinus == HIGH)&& (pre < 100)){
 
  
  if (segundo > 0 || centenaMili > 0 ){
    decenaMili = decenaMili - 5;
    if (decenaMili < 0){
      centenaMili = centenaMili - 1;
      decenaMili =  5;
      if (centenaMili< 0){
        segundo= segundo - 1;
        centenaMili= 9;
        }
      }

  if (segundo ==  0 && centenaMili == 0 && decenaMili == 5){
    segundo= 2;
    centenaMili = 0;
    decenaMili = 0;
    }
    
    }

 Serial.println(" la cantidad de tiempo es: ");
  Serial.print(segundo, DEC);
  Serial.print(".");
  Serial.print(centenaMili, DEC);
  Serial.println(decenaMili, DEC);
  }

  KVSolicitado = centena*100 + decena*10 + unidad;
  TSolicitado = segundo*1000 + centenaMili*100 + decenaMili*10;
  if (buttom == '9'){
    Serial.println( KVSolicitado, DEC);
    Serial.println( TSolicitado, DEC);
    //delay(500);

    }
  
Voltajeprimario = KVSolicitado; 

        
     t1 = (-0.0083+ sqrt( sq(0.0083)-4 * -2 * pow(10, -6) * (234.48 - Voltajeprimario))) / ( 2 * -2 * pow(10, -6));
     t2 = (-0.0083 - sqrt( sq(0.0083)-4 * -2 * pow(10, -6) * (234.48 - Voltajeprimario))) / ( 2 * -2 * pow(10, -6));   
     
     if (t1 < 0 ){
       t = t1 * -1;
     }else{
       t = t2 * -1;
     }
    
    }
    //tm = t / 1000;  paso a milisegundos el tiempo
 
     propte = TSolicitado / 16.6;
     
bool rot = digitalRead(pre);

     if ( rot == HIGH ) {
  digitalWrite(rotacion, HIGH);
  marcarotacion = 1;
 } else {
  digitalWrite(rotacion, LOW);
   digitalWrite(READY , LOW);
   q = 0;
  marcarotacion = 0;
  marcamarca = 0;
 }
 if ( marcarotacion == 1 && marcamarca == 0 ){
 while( rot  == 1) {
  rot = digitalRead(puls);
  delay(1);
  q = q + 1;
  if ( q == 3000 ) {
  digitalWrite(READY , HIGH);
  marcarotacion = 0;
  marcamarca = 1;
 }
 }
 } 
 if (marcamarca == 1) {
 shoot = Serial.read();
 }
     if ( marcamarca == 1 && shoot == 's'){
     digitalWrite(disparo, HIGH);
     
  for ( i = 0; i<=propte; i++){
 
  m = 0;
  n = 0;
     
      do {
          cruce = digitalRead(zero);
          if ((cruce == HIGH) && ( m == 0)){ // Detector de cruce por cero
             digitalWrite(opto, LOW); 
             delayMicroseconds(t);
             digitalWrite(opto, HIGH);
          m = 1;
          }
          
    }while ((m == 0));
      
    do {
          cruce = digitalRead(zero); 
          if ((cruce == HIGH) && (n == 0)){ // Detector de cruce por cero   
            digitalWrite(opto, LOW);  
            delayMicroseconds(t);
            digitalWrite(opto, HIGH);
       
            
            n = 1;
        }
    }while (n==0);
    
  }
  digitalWrite(disparo, LOW);
  
  
 }
 */
 }

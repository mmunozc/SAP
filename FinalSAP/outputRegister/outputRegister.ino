int unidades;
int unidades2;
int decenas;
int temp;
byte display[10]={63,6,91,79,102,109,125,7,127,103};

int ZERODIV = 53;

void setup() {
  DDRA = B11111111; //Del pin 29 al pin 22
  DDRF = B11111111; //Del pin A7 al pin A0
  DDRL = B00000000; //Del pin 42 al pin 49
  DDRK = B11111111;//Del pin A15 al pin A8

  pinMode(ZERODIV, INPUT);

  Serial.begin(9600);
}




void loop() {
  //Convertir el numero a decimal
  int num = PINL;
  if(digitalRead(ZERODIV) == 1){
    PORTA = 0B01111001;
    PORTF = 0B01111001;
    while(true);
  }
  if (num > 99){
   unidades = (num/10)/10;
   unidades2 = (num/10)%10;
   decenas = num%10;
   PORTA = display[unidades]; //primer display
   PORTF = display[unidades2]; //segundo display
   PORTK = display[decenas]; //tercer display
  }else {
    unidades = num / 10;
    decenas = num %10;
    PORTA = display[unidades]; //primer display
    PORTF = display[decenas]; //segundo display
  }
}

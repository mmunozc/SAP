int wait_time = 50;

//Instrucciones
int LDA = 22;
int ADD	= 23;
int SUB = 24;
int MUL = 25;
int DIV = 26;
int CALL = 27;
int GOTO = 28;
int RETURN = 29;
int EXP = 30;
int OPC1 = 31;
int OPC2 = 32;
int OUT = 33;
int HLT	= 34;

//Pines del SAP
int MOD = 50;
int DECR = 49;
int INC = 48;
int LM = 47;
int ER = 46;
int LI = 45;
int EI = 44;
int LA = 43;
int EA = 42;
int ALU_ADD = 41;
int ALU_SUB = 40;
int ALU_MUL = 39;
int ALU_DIV = 38;
int EU = 37;
int LB = 36;
int LO = 35;


int EP = 53;
int DIVZERO = 51;
int UNDEFINED = 7;

/* El bus se maneja con el puerto F */

int PC = 0;
int PC_stored = 0;

void setup() {
  DDRA = B00000000; // Del pin 29 al pin 22
  DDRC = B00000111; // Del pin 30 al pin 37
  DDRL = B11111100; // Del pin 42 al pin 49
  DDRF = B00001111; // Del pin A7 al pin A0. El bus
  pinMode(ALU_ADD, OUTPUT);
  pinMode(ALU_SUB, OUTPUT);
  pinMode(ALU_MUL, OUTPUT);
  pinMode(ALU_DIV, OUTPUT);
 
  pinMode(DIVZERO, OUTPUT);
  pinMode(EP, OUTPUT);
  pinMode(UNDEFINED, OUTPUT);

  PC = 0;
  PC_stored = 0;
  Serial.begin(9600);
}

void loop() {
  PORTF = PC; //Se envia el PC por el bus

  digitalWrite(EP, 1);
  digitalWrite(LM, 1);
  delay(wait_time);
  digitalWrite(LM, 0);
  digitalWrite(EP, 0);

  digitalWrite(ER, 1);
  digitalWrite(LI, 1);
  delay(wait_time);
  digitalWrite(LI, 0);
  digitalWrite(ER, 0);

  if (digitalRead(LDA) == HIGH) {
    digitalWrite(EI, 1);
    digitalWrite(LM, 1);
    delay(wait_time);
    digitalWrite(LM, 0);
    digitalWrite(EI, 0);

    digitalWrite(ER, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(ER, 0);
    PC++;
  }

  else if (digitalRead(ADD) == HIGH) {
    digitalWrite(EI, 1);
    digitalWrite(LM, 1);
    delay(wait_time);
    digitalWrite(LM, 0);
    digitalWrite(EI, 0);

    digitalWrite(ER, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(ER, 0);

    digitalWrite(ALU_ADD, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_ADD, 0);
    PC++;
  }

  else if (digitalRead(SUB) == HIGH) {
    digitalWrite(EI, 1);
    digitalWrite(LM, 1);
    delay(wait_time);
    digitalWrite(LM, 0);
    digitalWrite(EI, 0);

    digitalWrite(ER, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(ER, 0);

    digitalWrite(ALU_SUB, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_SUB, 0);
    PC++;
  }

  else if (digitalRead(MUL) == HIGH) {
    digitalWrite(EI, 1);
    digitalWrite(LM, 1);
    delay(wait_time);
    digitalWrite(LM, 0);
    digitalWrite(EI, 0);

    digitalWrite(ER, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(ER, 0);

    digitalWrite(ALU_MUL, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_MUL, 0);
    PC++;
  }

  else if (digitalRead(DIV) == HIGH) {
    digitalWrite(EI, 1);
    digitalWrite(LM, 1);
    delay(wait_time);
    digitalWrite(LM, 0);
    digitalWrite(EI, 0);

    //Control division por cero
    digitalWrite(ER, 1);
    int num = PINF >> 4;// Cambia los bits para que se lea el número como es
    delay(wait_time);
    digitalWrite(ER, 0);
    if (num == 0) {
      digitalWrite(UNDEFINED, 1);
      digitalWrite(DIVZERO, 1);
      while(true);
      }
    

    digitalWrite(ER, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(ER, 0);

    digitalWrite(ALU_DIV, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_DIV, 0);
    PC++;
  }

  else if (digitalRead(CALL) == HIGH) {
    PC_stored = PC + 1;
    digitalWrite(EI, 1);
    PC = PINF >> 4;// Cambia los bits para que se lea el número como es
    delay(wait_time);
    digitalWrite(EI, 0);
  }

  else if (digitalRead(RETURN) == HIGH) {
    PC = PC_stored;
  }

  else if (digitalRead(GOTO) == HIGH) {
    digitalWrite(EI, 1);
    PC = PINF >> 4;// Cambia los bits para que se lea el número como es
    delay(wait_time);
    digitalWrite(EI, 0);
  }
  else if (digitalRead(EXP) == HIGH) {
    //Cargo el numero al registro B
    digitalWrite(EI, 1);
    digitalWrite(LM, 1);
    delay(wait_time);
    digitalWrite(LM, 0);
    digitalWrite(EI, 0);
    digitalWrite(ER, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(ER, 0);
    //Capturo el numero que tiene el acumulador
    digitalWrite(EA, 1);
    int accumulator = PINF >> 4;
    delay(wait_time);
    digitalWrite(EA, 0);
    //Capturo el numero que tiene el b register
    digitalWrite(EI, 1);
    int bReg = PINF >> 4;
    delay(wait_time);
    digitalWrite(EI, 0);
    //Cargo el numero del acumulador al registro b
    PORTF = accumulator;
    digitalWrite(EP, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(EP, 0);
    //hago el ciclo de sumas
    for (int temp = 1; temp < bReg; temp++) {
      digitalWrite(ALU_MUL, 1);
      digitalWrite(EU, 1);
      digitalWrite(LA, 1);
      delay(wait_time);
      digitalWrite(LA, 0);
      digitalWrite(EU, 0);
      digitalWrite(ALU_MUL, 0);
    }

    PC++;
  }

  //Si el número del acumulador es par, se carga un 1 en el acumulador; 0 en caso contrario
  else if (digitalRead(OPC1) == HIGH) {
    digitalWrite(EA, 1);
    int accumulator = PINF >> 4;// Cambia los bits para que se lea el número como es
    delay(wait_time);
    digitalWrite(EA, 0);

    if (accumulator % 2 == 0) {
      PORTF = 1;
    } else {
      PORTF = 0;
    }

    digitalWrite(EP, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EP, 0);

    PC++;
  }

  /* Si el valor del acumulador es mayor que 5,
     se le resta la mitad de este valor.
     En caso contrario, se le resta 1.
  */
  else if (digitalRead(OPC2) == HIGH) {
    digitalWrite(EA, 1);
    int accumulator = PINF >> 4;
    delay(wait_time);
    digitalWrite(EA, 0);

    if (accumulator > 5) {
      PORTF = 2;
      digitalWrite(EP, 1);
      digitalWrite(LB, 1);
      delay(wait_time);
      digitalWrite(LB, 0);
      digitalWrite(EP, 0);

      digitalWrite(ALU_DIV, 1);
      digitalWrite(EU, 1);
      digitalWrite(LB, 1);
      delay(wait_time);
      digitalWrite(LB, 0);
      digitalWrite(EU, 0);
      digitalWrite(ALU_DIV, 0);
    } else {
      //Esto
      PORTF = 1;
      digitalWrite(EP, 1);
      digitalWrite(LB, 1);
      delay(wait_time);
      digitalWrite(LB, 0);
      digitalWrite(EP, 0);
    }

    digitalWrite(ALU_SUB, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_SUB, 0);

    PC++;
  }

  else if (digitalRead(OUT) == HIGH) {
    digitalWrite(EA, 1);
    digitalWrite(LO, 1);
    delay(wait_time);
    digitalWrite(LO, 0);
    digitalWrite(EA, 0);
    PC++;
  }

  else if (digitalRead(HLT) == HIGH) {
    while (true); //Detiene todo
  }


  else if (digitalRead(MOD) == HIGH) {
    //Obtenr valores de b register infinitamente hasta llegar a condicion de parada
    int temp = 0;
    while (true) {
      //Cargo el numero al registro B
      digitalWrite(EI, 1);
      digitalWrite(LM, 1);
      delay(wait_time);
      digitalWrite(LM, 0);
      digitalWrite(EI, 0);
      digitalWrite(ER, 1);
      digitalWrite(LB, 1);
      delay(wait_time);
      digitalWrite(LB, 0);
      digitalWrite(ER, 0);
      //Capturo el numero que tiene el acumulador
      digitalWrite(EA, 1);
      int accumulator = PINF >> 4;
      delay(wait_time);
      digitalWrite(EA, 0);
      //Le cargo un 0 al acumulador
      PORTF = 0;
      digitalWrite(EP, 1);
      digitalWrite(LA, 1);
      delay(wait_time);
      digitalWrite(EP, 0);
      digitalWrite(LA, 0);
      //Cargo el numero que hay en el registro B al acumulador
      digitalWrite(ALU_ADD, 1);
      digitalWrite(EU, 1);
      digitalWrite(LA, 1);
      delay(wait_time);
      digitalWrite(LA, 0);
      digitalWrite(EU, 0);
      digitalWrite(ALU_ADD, 0);
      //Captura el numero que tiene registroB
      digitalWrite(EA, 1);
      int bReg = PINF >> 4;
      delay(wait_time);
      digitalWrite(EA, 0);

      if (bReg == 0 and temp == 0) {
        digitalWrite(UNDEFINED, 1);
        //Cargo un 0 en el acumulador
        PORTF = 0;
        digitalWrite(EP, 1);
        digitalWrite(LA, 1);
        delay(wait_time);
        digitalWrite(LA, 0);
        digitalWrite(EP, 0);
        //Cargo 14 en el registro B
        PORTF = 14;
        digitalWrite(EP, 1);
        digitalWrite(LB, 1);
        delay(wait_time);
        digitalWrite(LB, 0);
        digitalWrite(EP, 0);
        //Resto para que me de -14
        digitalWrite(ALU_SUB, 1);
        digitalWrite(EU, 1);
        digitalWrite(LA, 1);
        delay(wait_time);
        digitalWrite(LA, 0);
        digitalWrite(EU, 0);
        digitalWrite(ALU_SUB, 0);
        //Hago el out del -14
        digitalWrite(EA, 1);
        digitalWrite(LO, 1);
        delay(wait_time);
        digitalWrite(LO, 0);
        digitalWrite(EA, 0);
        //Paro el programa
        while (true);
      }
      //Le devuelvo el numero original al acumulador
      PORTF = accumulator;
      digitalWrite(EP, 1);
      digitalWrite(LA, 1);
      delay(wait_time);
      digitalWrite(LA, 0);
      digitalWrite(EP, 0);
      if (accumulator < bReg) {
        //resultado de modulo
        break;
      }
      else if (accumulator >= bReg) {
        //Le resto el valor de bReg a accumulator
        digitalWrite(ALU_SUB, 1);
        digitalWrite(EU, 1);
        digitalWrite(LA, 1);
        delay(wait_time);
        digitalWrite(LA, 0);
        digitalWrite(EU, 0);
        digitalWrite(ALU_SUB, 0);
      }
      temp++;
    }
    PC++;
  }

  else if (digitalRead(INC) == HIGH) {
    PORTF = 1;
    digitalWrite(EP, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(EP, 0);

    digitalWrite(ALU_ADD, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_ADD, 0);
    PC++;
  }  else if (digitalRead(DECR) == HIGH) {
    PORTF = 1;
    digitalWrite(EP, 1);
    digitalWrite(LB, 1);
    delay(wait_time);
    digitalWrite(LB, 0);
    digitalWrite(EP, 0);

    digitalWrite(ALU_SUB, 1);
    digitalWrite(EU, 1);
    digitalWrite(LA, 1);
    delay(wait_time);
    digitalWrite(LA, 0);
    digitalWrite(EU, 0);
    digitalWrite(ALU_SUB, 0);
    PC++;
  }
}

#include <SoftwareSerial.h>
#include <math.h> //necessaria para calculos matemáticos dos ângulos

// Values of 0 being sent over serial write have to be cast as a byte so they arent misinterpreted as NULL
// This is a bug with arduino 1.0
#define CMD        (byte)0x00            // MD49 command address of 0                                 
#define GET_SPEED1       0x21 
#define GET_SPEED2       0x22
#define GET_VER          0x29
#define GET_ENC1         0x23
#define GET_ENC2         0x24
#define GET_VI           0x2C
#define GET_ERROR        0x2D
#define SET_ACCEL        0x33
#define SET_SPEED1       0x31
#define SET_SPEED2       0x32
#define RESET_ENCODERS   0x35
                                        
#define PI 3.1415926535897932384626433832795             // definicao do numero PI


uint32_t encoder, encoder1, encoder2 = 0;
byte enc1a, enc1b, enc1c, enc1d = 0;
byte enc2a, enc2b, enc2c, enc2d = 0;
byte bat_volt, mot1_cur, mot2_cur = 0;
byte ver = 0;
byte error = 0;
byte speed1a = 0;
byte speed1b = 0;
byte speed2a = 0;
byte speed2b = 0;
int led = 13;


//=====Variáveis do Robô======
uint32_t pulsoporvolta = 980;
float pulsopormetro = 2516;
float diametro = 0.124;
float perimetro = 0;
float baseline = 0.455;
float Cdistancia = 0; //distancia do percorrida do ponto central

//=====Variáveis de posição======
float x, y, theta; //posição inicial 
float xf = 0; 
float yf = 0;
float thetaf = 0; //próxima posição
int objetivo = 0;
int quadrante = 0;
int n = 0;
int numerovoltas = 0;

//=====Variáveis de odometria======
float Rdistancia = 0;                                    
int Rtick = 0;                                           
int RtickAnt = 0;                                        
int deltaRtick = 0;                                      
float Ldistancia = 0;                                    
int Ltick = 0;                                           
int LtickAnt = 0;                                        
int deltaLtick = 0;                                      
int count = 0;
float Phi = 0;

void odometria(){ 
  deltaRtick = Rtick - RtickAnt;                                 // comparação dos TICKS percorridos da roda direitadesde o ultimo calculo
  Rdistancia = ((PI*diametro*deltaRtick)/980);                   // distancia percorrida pela roda direita 
  
  deltaLtick = Ltick - LtickAnt;                                 // comparação dos TICKS percorridos da roda esquerda desde o ultimo calculo      
  Ldistancia = ((PI*diametro*deltaLtick)/980);                    // distancia percorrida pela roda esquerda   
  
  Cdistancia = (Rdistancia + Ldistancia)/2;                      // distancia percorrida pelo ponto central
  
  x = x + Cdistancia*cos(theta);                                 // posição atual do ponto X
  y = y + Cdistancia*sin(theta);                                 // posição atual do ponto Y

  theta = theta + ((Rdistancia - Ldistancia)/baseline);          // posição atual de phi
  
  RtickAnt = Rtick;                                              // atualização da variavel RtickAnt com os valores de Rtick
  LtickAnt = Ltick;                                              // atualização da variavel LtickAnt com os valores de Ltick  

  delay(300);
    
  Serial.print("VALOR DE X =  ");
  Serial.println(x);
  Serial.print("VALOR ATUAL DE Y  = ");
  Serial.println(y);
  Serial.print("VALOR ATUAL DE THETA = ");
  Serial.println((theta*180)/PI);    
}

void encoderdireito(){ 
  // Le o encoder 1 
  Serial1.write(CMD);
  Serial1.write(GET_ENC1);  
  
  // Recebe os valores do encoder 1 
  delay(50);
  if(Serial1.available() > 3)
  {
    enc1a = Serial1.read();
    enc1b = Serial1.read();
    enc1c = Serial1.read();
    enc1d = Serial1.read();
  }
  
  //Le os valores do Encoder 1 e converte para decimal
  int count = sizeof(enc1a);
  char* chars;
  encoder1 = (((uint32_t)enc1a << 24) + 
    ((uint32_t)enc1b << 16) + 
    ((uint32_t)enc1c << 8) + 
    ((uint32_t)enc1d << 0));
}


void encoderesquerdo(){
  //Le o Encoder 2 
  Serial1.write(CMD);
  Serial1.write(GET_ENC2);                   
  
  //Recebe os valores do encoder 1
  delay(50);
  if(Serial1.available() > 3)
  {
    enc2a = Serial1.read();
    enc2b = Serial1.read();
    enc2c = Serial1.read();
    enc2d = Serial1.read();
  }
  //Le os valores do Encoder 2 e converte para decimal
  count = sizeof(enc2a); // enc1a?
  char* chars;
  encoder2 = (((uint32_t)enc2a << 24) + ((uint32_t)enc2b << 16) + ((uint32_t)enc2c << 8) + ((uint32_t)enc2d << 0));
}

void setup(){
   Serial.begin(9600);
   Serial1.begin(9600);
  
  //Reseta os valores dos encoders
  Serial1.write(CMD);
  Serial1.write(RESET_ENCODERS);
  
  quadrante = 1;  //Cada quadrante e um ponto para mexer o robo
  numerovoltas = 2;
}

void loop(){
     
  encoderdireito(); 
  encoderesquerdo();
  Rtick = encoder1;
  Ltick = encoder2;

  for (int n = 1; n < numerovoltas; n++) {
    if (quadrante == 1) {
      if (x < 1) {
        Serial1.write(CMD);
        Serial1.write(SET_SPEED1);
        Serial1.write(140);
        Serial1.write(CMD);
        Serial1.write(SET_SPEED2);
        Serial1.write(140);
      } else {
        Serial1.write(CMD);
        Serial1.write(SET_SPEED1);
        Serial1.write(128);
        Serial1.write(CMD);
        Serial1.write(SET_SPEED2);
        Serial1.write(128);
        quadrante = 2;
        delay(300);
      } 
    }
    
    if ((quadrante == 2)){
      if (theta < ((90*PI)/180)){
        Serial1.write(CMD);
        Serial1.write(SET_SPEED1);
        Serial1.write(132);
        Serial1.write(CMD);
        Serial1.write(SET_SPEED2);
        Serial1.write(125);  
      }else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 3;
          delay(300);
        }
    }
    
    if ((quadrante == 3)){
        if ( y < 1) {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(140);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(140);
        } else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 4;
          delay(300);
        }
    }

    if ((quadrante == 4)){
      if (theta < ((180*PI)/180)){
        Serial1.write(CMD);
        Serial1.write(SET_SPEED1);
        Serial1.write(132);
        Serial1.write(CMD);
        Serial1.write(SET_SPEED2);
        Serial1.write(125);  
      }else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 5;
          delay(300);
        }
    }

    if ((quadrante == 5)){
        if ( x > 0) {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(140);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(140);
        } else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 6;
          delay(300);
        }
    }

    if ((quadrante == 6)){
      if (theta < ((270*PI)/180)){
        Serial1.write(CMD);
        Serial1.write(SET_SPEED1);
        Serial1.write(132);
        Serial1.write(CMD);
        Serial1.write(SET_SPEED2);
        Serial1.write(125);  
      }else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 7;
          delay(300);
        }
    }

    if ((quadrante == 7)){
        if ( y > 0) {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(140);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(140);
        } else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 8;
          delay(300);
        }
    }
    
    if ((quadrante == 8)){
      if (theta < ((360*PI)/180)){
        Serial1.write(CMD);
        Serial1.write(SET_SPEED1);
        Serial1.write(132);
        Serial1.write(CMD);
        Serial1.write(SET_SPEED2);
        Serial1.write(125);  
      }else {
          Serial1.write(CMD);
          Serial1.write(SET_SPEED1);
          Serial1.write(128);
          Serial1.write(CMD);
          Serial1.write(SET_SPEED2);
          Serial1.write(128);
          quadrante = 1;
          theta = 0;
          x = 0;
          y = 0;
          n = n + 1;
          delay(300);
        }
    }
    /*odometria();
    delay(300);*/
    Serial.print("NUMERO DA VOLTA =  ");
    Serial.println(n);
    Serial.println("--------------------------------------------------------");
  }//Fim laço for  
  
  odometria();
  delay(300); 
}

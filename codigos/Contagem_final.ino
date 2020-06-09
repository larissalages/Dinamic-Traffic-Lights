#include <virtuabotixRTC.h>

#define trigPinSen1 13
#define echoPinSen1 12
#define trigPinSen2 2
#define echoPinSen2 11
#define trigPinSen3 13
#define echoPinSen3 10
#define trigPinSen4 2
#define echoPinSen4 9
#define verdePin1 8
#define amareloPin1 7
#define vermelhoPin1 6
#define verdePin2 5
#define amareloPin2 4
#define vermelhoPin2 3
#define CLKpin A0
#define DATApin A1
#define RESETpin A2
#define eps 1e-7

#define T 30
#define y 3
#define MAXDIST 10	//distancia ate o fim da faixa
#define MINREPcarro 6	//numero minimo de repeticoes para considerar que é um carro passando
#define MINREPnada 2	//numero minimo de repeticoes para considerar que é não há nada passando
#define limiarTempo 3

virtuabotixRTC myRTC(CLKpin, DATApin, RESETpin);
int cont1 = 0, rep1 = 0, cont2 = 0, rep2 = 0, inicio = 0, iniCarro1, iniCarro2;		//numero de carros e numero de repetições
int trigPin1, echoPin1, trigPin2, echoPin2, via1 = 0, via2 = 2, tverde1 = (T-2*y)/2, tverde2 = (T-2*y)/2;
double fluxo1, fluxo2, duracao, duracao1, duracao2;
/*
flag = true, se ultima detecçao indica carro passando; false se ultima detecçao indica que não há nada passando
flag2 = true, se está confirmado um carro passando; false se está confirmado que não há nada passando
verde = 0
amarelo = 1
vermelho = 2
*/
boolean flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPinSen1, OUTPUT);
  pinMode(echoPinSen1, INPUT);
  pinMode(trigPinSen2, OUTPUT);
  pinMode(echoPinSen2, INPUT);
  pinMode(trigPinSen3, OUTPUT);
  pinMode(echoPinSen3, INPUT);
  pinMode(trigPinSen4, OUTPUT);
  pinMode(echoPinSen4, INPUT);
  pinMode(verdePin1, OUTPUT);
  pinMode(amareloPin1, OUTPUT);
  pinMode(vermelhoPin1, OUTPUT);
  pinMode(verdePin2, OUTPUT);
  pinMode(amareloPin2, OUTPUT);
  pinMode(vermelhoPin2, OUTPUT);
  myRTC.setDS1302Time(0, 0, 0, 6, 10, 1, 2014);
}

void loop() {
  if(via1 == 0) digitalWrite(verdePin1, HIGH);
  else digitalWrite(verdePin1, LOW);
  
  if(via1 == 1) digitalWrite(amareloPin1, HIGH);
  else digitalWrite(amareloPin1, LOW);
  
  if(via1 == 2) digitalWrite(vermelhoPin1, HIGH);
  else digitalWrite(vermelhoPin1, LOW);
  
  if(via2 == 0) digitalWrite(verdePin2, HIGH);
  else digitalWrite(verdePin2, LOW);
  
  if(via2 == 1) digitalWrite(amareloPin2, HIGH);
  else digitalWrite(amareloPin2, LOW);
  
  if(via2 == 2) digitalWrite(vermelhoPin2, HIGH);
  else digitalWrite(vermelhoPin2, LOW);
  
  if(via1 < 2){ //verde ou amarelo
    trigPin1 = trigPinSen1;
    echoPin1 = echoPinSen1;
    trigPin2 = trigPinSen2;
    echoPin2 = echoPinSen2;
  }else{
    trigPin1 = trigPinSen3;
    echoPin1 = echoPinSen3;
    trigPin2 = trigPinSen4;
    echoPin2 = echoPinSen4;
  }
 
  long duration, distance;
  
  digitalWrite(trigPin1, LOW);  	  //seta o trigger para baixo
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);		  //seta o trigger para alto, para acionar o sensor
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);			//seta o trigger para baixo
  duration = pulseIn(echoPin1, HIGH);	  //pega a duracao do sinal de resposta do sensor
  distance = (duration/2) / 29;			//calcula a distancia a partir da duracao
  if(distance <= MAXDIST){				//se o carro está na faixa correspondente ao sensor 
    if(flag1) rep1++;						//se foi detectado um carro na iteração anterior, incrementa rep
    else rep1 = 1;						//se foi detectado nada na iteração anterior, esta é a primeira repetição
    flag1 = true;
    if(rep1 == MINREPcarro){
      flag2 = true;    //se chegou a MINREPcarro repetições, confirma a presença de um carro
       myRTC.updateTime();
       iniCarro1 = myRTC.hours*3600 + myRTC.minutes*60 + myRTC.seconds;
    }
  }else{								//se o carro está fora da faixa correspondente ao sensor 
    if(!flag1) rep1++;					//se foi detectado nada na iteração anterior, incrementa rep
    else rep1 = 1;						//se foi detectado um carro na iteração anterior, esta é a primeira repetição
    if(rep1 == MINREPnada){				//se chegou a MINREPnada repetições
      if(flag2){
        cont1++;							//contabiliza novo carro 
        Serial.print(cont1);
        Serial.print(" carros | echo:");
        Serial.println(echoPin1);
        myRTC.updateTime();
        int tempo = myRTC.hours*3600 + myRTC.minutes*60 + myRTC.seconds;
        duracao += tempo-iniCarro1;
      }
      flag2 = false;					//confirma que não está passando nada
    }
    flag1 = false;
  }
  
  delay(6);
  
  digitalWrite(trigPin2, LOW);  			//seta o trigger para baixo
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);			//seta o trigger para alto, para acionar o sensor
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);			//seta o trigger para baixo
  duration = pulseIn(echoPin2, HIGH);	//pega a duracao do sinal de resposta do sensor
  distance = (duration/2) / 29;			//calcula a distancia a partir da duracao
  if(distance <= MAXDIST){				//se o carro está na faixa correspondente ao sensor 
    if(flag3) rep2++;						//se foi detectado um carro na iteração anterior, incrementa rep
    else rep2 = 1;						//se foi detectado nada na iteração anterior, esta é a primeira repetição
    flag3 = true;
    if(rep2 == MINREPcarro){
      flag4 = true;//se chegou a MINREPcarro repetições, confirma a presença de um carro
       myRTC.updateTime();
       iniCarro2 = myRTC.hours*3600 + myRTC.minutes*60 + myRTC.seconds;
    }
  }else{								//se o carro está fora da faixa correspondente ao sensor 
    if(!flag3) rep2++;					//se foi detectado nada na iteração anterior, incrementa rep
    else rep2 = 1;						//se foi detectado um carro na iteração anterior, esta é a primeira repetição
    if(rep2 == MINREPnada){				//se chegou a MINREPnada repetições
      if(flag4){
        cont2++;	//contabiliza novo carro 
        Serial.print(cont2);
        Serial.print(" carros | echo:");
        Serial.println(echoPin2);
        myRTC.updateTime();
        int tempo = myRTC.hours*3600 + myRTC.minutes*60 + myRTC.seconds;
        duracao += tempo-iniCarro2;
      }
      flag4 = false;					//confirma que não está passando nada
    }
    flag3 = false;
  }
  
  myRTC.updateTime();
  int tempo = myRTC.hours*3600 + myRTC.minutes*60 + myRTC.seconds;
 // Serial.print(tempo);
 // Serial.println(" segs");
  
  if(via1 == 0){
    if(tempo - inicio >= tverde1){
       via1 = 1;
       inicio = tempo;
       Serial.println("amarelo/vermelho");
    }
  }else if(via1 == 1){
      if(tempo - inicio >= y){
       Serial.print(duracao);
       Serial.println(" segs");
       via1 = 2;
       via2 = 0;
       fluxo1 = ((double)(cont1+cont2))/(tverde1+y);
       if(cont1+cont2 == 0) duracao1 = 0.0;
       else duracao1 = duracao/(cont1+cont2);
       cont1 = cont2 = flag1 = flag2 = flag3 = flag4 = rep1 = rep2 = 0;
       duracao = 0.0;
       inicio = tempo;
       Serial.print(fluxo1);
       Serial.println(" carros/segs");
       Serial.println("vermelho/verde");
      }
  }else if(via2 == 0){
   if(tempo - inicio >= tverde2){
       via2 = 1;
       inicio = tempo;
       Serial.println("vermelho/amarelo");
    }
  }else if(via2 == 1){
     if(tempo - inicio >= y){
       Serial.print(duracao);
       Serial.println(" segs");
       
       via1 = 0;
       via2 = 2;
       fluxo2 = ((double)(cont1+cont2))/(tverde2+y);
       if(cont1+cont2 == 0) duracao2 = 0.0;
       else duracao2 = duracao/(cont1+cont2);
       cont1 = cont2 = flag1 = flag2 = flag3 = flag4 = rep1 = rep2 = 0;
       duracao = 0.0;
       if(fluxo1 < eps && fluxo2 < eps){
         tverde1 = (T-2*y)/2;
         tverde2 = (T-2*y)/2; 
       }else if(fluxo1 < eps){
         tverde1 = 0;
         tverde2 = T-2*y;
       }else if(fluxo2 < eps){
         tverde1 = T-2*y;
         tverde2 = 0;
       }else{
         if(duracao1 < eps){
           duracao1 = 0.1;
         }
         if(duracao2 < eps){
           duracao2 = 0.1;
         }
         double k = (fluxo1*duracao1)/(fluxo2*duracao2);
         tverde2 = (int)((T-2*y)/(k+1));
         tverde1 = (int)((k*(T-2*y))/(k+1));
       }
       
       if(tverde1 < limiarTempo){
         tverde1 = limiarTempo;
         tverde2 = T-2*y-limiarTempo;
       }else if(tverde2 < limiarTempo){
         tverde2 = limiarTempo;
         tverde1 = T-2*y-limiarTempo;
       }
       
       myRTC.setDS1302Time(0, 0, 0, 6, 10, 1, 2014);
       inicio = 0;
       Serial.print(fluxo2);
       Serial.println(" carros/segs");
       
       Serial.print("tverde1: ");
       Serial.println(tverde1);
       Serial.print("tverde2: ");
       Serial.println(tverde2);
       Serial.println("verde/vermelho");
    }
  }
  delay(6);
}


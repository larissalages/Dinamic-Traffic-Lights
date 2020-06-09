#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
#define MAXDIST 20		//distancia ate o fim da faixa
#define MINREPcarro 6	//numero minimo de repeticoes para considerar que é um carro passando
#define MINREPnada 2	//numero minimo de repeticoes para considerar que é não há nada passando

int cont = 0, rep = 0;			//numero de carros e numero de repetições
/*
flag = true, se ultima detecçao indica carro passando; false se ultima detecçao indica que não há nada passando
flag2 = true, se está confirmado um carro passando; false se está confirmado que não há nada passando
*/
boolean flag = 0, flag2 = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  			//seta o trigger para baixo
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);			//seta o trigger para alto, para acionar o sensor
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);			//seta o trigger para baixo
  duration = pulseIn(echoPin, HIGH);	//pega a duracao do sinal de resposta do sensor
  distance = (duration/2) / 29;			//calcula a distancia a partir da duracao
  if(distance <= MAXDIST){				//se o carro está na faixa correspondente ao sensor 
    if(flag) rep++;						//se foi detectado um carro na iteração anterior, incrementa rep
    else rep = 1;						//se foi detectado nada na iteração anterior, esta é a primeira repetição
    flag = true;
    if(rep == MINREPcarro) flag2 = true;//se chegou a MINREPcarro repetições, confirma a presença de um carro
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
  }else{								//se o carro está fora da faixa correspondente ao sensor 
    if(!flag) rep++;					//se foi detectado nada na iteração anterior, incrementa rep
    else rep = 1;						//se foi detectado um carro na iteração anterior, esta é a primeira repetição
    if(rep == MINREPnada){				//se chegou a MINREPnada repetições
      if(flag2){
        cont++;							//contabiliza novo carro 
        Serial.print(cont);
        Serial.println(" carros");
      }
      flag2 = false;					//confirma que não está passando nada
    }
    flag = false;
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  delay(12);
}

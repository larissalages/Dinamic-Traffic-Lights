int verde = 13;
int amarelo = 12;
int vermelho = 11;
int verde2 = 10;
int amarelo2 = 9;
int vermelho2 = 8;

int tverde = 17;
int tamarelo = 3;
int tvermelho = 20;
int tverde2 = 17;
int tamarelo2 = 3;
int tvermelho2 = 20;

void setup () {
  pinMode (verde, OUTPUT);
  pinMode (amarelo, OUTPUT);
  pinMode (vermelho, OUTPUT);
   pinMode (verde2, OUTPUT);
  pinMode (amarelo2, OUTPUT);
  pinMode (vermelho2, OUTPUT);
}

void loop () {
  digitalWrite (verde, HIGH);
  digitalWrite (amarelo, LOW);
  digitalWrite (vermelho, LOW);
  digitalWrite (verde2, LOW);
  digitalWrite (amarelo2, LOW);
  digitalWrite (vermelho2, HIGH);
  delay (tverde*1000);
  
  digitalWrite (verde, LOW);
  digitalWrite (amarelo, HIGH);
  digitalWrite (vermelho, LOW);
  digitalWrite (verde2, LOW);
  digitalWrite (amarelo2, LOW);
  digitalWrite (vermelho2, HIGH);
  delay (tamarelo*1000);
  
  digitalWrite (verde, LOW);
  digitalWrite (amarelo, LOW);
  digitalWrite (vermelho, HIGH);
  digitalWrite (verde2, HIGH);
  digitalWrite (amarelo2, LOW);
  digitalWrite (vermelho2, LOW);
  delay (tverde2*1000);
  
  digitalWrite (verde, LOW);
  digitalWrite (amarelo, LOW);
  digitalWrite (vermelho, HIGH);
  digitalWrite (verde2, LOW);
  digitalWrite (amarelo2, HIGH);
  digitalWrite (vermelho2, LOW);
  delay (tamarelo2*1000);
  
}

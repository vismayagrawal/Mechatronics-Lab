int prox = 0;
int proxPin = A2;

void setup() {
  // put your setup code here, to run once:
  pinMode(proxPin, INPUT);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  prox = digitalRead(proxPin);
  Serial.println(prox);
  delay(50);
}

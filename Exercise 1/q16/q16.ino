int led2 = 11;
int led1 = 12;
int led0 = 13;

void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  reset();
  for (int i = 0; i < 8; ++i)
  {
    Serial.print("index ");
    Serial.println(i);

    signal( led2, ((i >> 2) % 2) == 1);
    signal( led1, ((i >> 1) % 2) == 1);
    signal( led0, ((i >> 0) % 2) == 1);
    delay(2000);
  }
}


void reset()
{
  Serial.println("reset");
  signal( led2, 0);
  signal( led1, 0);
  signal( led0, 0);
}

void signal(int led, bool on)
{
  if (on)
  {
    digitalWrite(led, HIGH);
    Serial.println(" on");
  }
  else
  {
    digitalWrite(led, LOW);
    Serial.println(" off");
  }
}

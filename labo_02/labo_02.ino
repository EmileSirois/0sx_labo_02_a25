const int ledTab[4] = {8, 9, 10, 11};
const int buttonPin = 2;
const int potPin = A1;
const int delais = 150;
const int minBoucles = 0;

void setup() {
  // put your setup code here, to run once
  pinMode(ledTab[0], OUTPUT);
  pinMode(ledTab[1], OUTPUT);
  pinMode(ledTab[2], OUTPUT);
  pinMode(ledTab[3], OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void printBar(int adjustedValue, int percentValue){
  
  Serial.print("[");

  for(int i = minBoucles; i < adjustedValue; i++){
    Serial.print("£");
  }
  int maxSpaces = 20;
  int remainingSpace = maxSpaces - adjustedValue;

  for(int i = minBoucles; i < remainingSpace; i++){
    Serial.print(".");
  }

  Serial.print("] ");

  Serial.print(percentValue);
  Serial.println(" % ");
}

void progressTask(int buttonInput, int adjustedValue, int previousButtonInput, int percentValue){
  static int lastTime = minBoucles;
  int currentTime = millis();
  //si il n'y a pas de bounce ni de spam
  bool noBounce = (currentTime - lastTime > delais);

  if(!buttonInput && noBounce && (buttonInput != previousButtonInput)){
    lastTime = currentTime;
    previousButtonInput = buttonInput;
    printBar(adjustedValue, percentValue);
  }
}

void ledTask(int ledIndex){
  int ledTabLength = 4;

  for(int i = minBoucles; i < ledTabLength; i++){
    if(i == ledIndex){
      digitalWrite(ledTab[i], HIGH);
    }
    else{
      digitalWrite(ledTab[i], LOW);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 static int adjustedValue;
 static int ledIndex;
 static int previousButtonInput = true;
 
 int potInput = analogRead(potPin);
 int buttonInput = digitalRead(buttonPin);

 adjustedValue = map(potInput, 0, 1023, 0, 20);
 ledIndex = map(potInput, 0, 1023, 0, 3);
 int percentValue = map(potInput, 0, 1023, 0, 100);


 progressTask(buttonInput, adjustedValue, previousButtonInput, percentValue);
 ledTask(ledIndex);
}

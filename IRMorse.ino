int bg; // Global background value ; defined in calibrate()
int c; // Global timer
int a; // Global ajuster ; defined by A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT); // IR receiver
  pinMode(A1, INPUT); // Difference ajuster ; potenciometer
  pinMode(3, OUTPUT); // Digital indicator ; speaker
  bg = calibrate(A0);
}

void loop() {
  // put your main code here, to run repeatedly:
  a = analogRead(A1)/(1024/100);
  int Read = analogRead(A0); bool Sig;
  Serial.print("COUNTER = "+String(c)+"; RAW = "+String(Read)+"; DIF = "+String(a)+"; SIGNAL = ");
  if(Read > (bg+a)) { Serial.print(true); Sig = true; } else { Serial.print(false); Sig = false; }
  Serial.println();
  c++;
  //delay(10);
  if(Sig == true) { tone(3,500); } else { noTone(3); }
}

int calibrate(int pin) {
  Serial.println(" >>> Calibrating <<< ");
  long int sum = 0;
  for(int i=0; i<100; i++){
    sum += analogRead(pin);
    delay(10);
  }
  int bg = sum/100;
  Serial.println(" >>> Calibrated <<<");
  Serial.println(" >>> Background value set to "+String(bg)+" <<< ");
  delay(2000);
  return bg;
}

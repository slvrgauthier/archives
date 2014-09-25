int led[9] = {4,5,6,7,8,9,10,11,12};

void setup() {
  for(int i=0;i<9;i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
}

void loop() {
  for(int i=0;i<10;i++) {
    digitalWrite(led[0],LOW);
    digitalWrite(led[8],LOW);
    delay(100);
    digitalWrite(led[0],HIGH);
    digitalWrite(led[8],HIGH);
    delay(100);
  }
  digitalWrite(led[1],LOW);
  digitalWrite(led[7],LOW);
    for(int i=2;i<7;i++) {
      digitalWrite(led[i],LOW);
      delay(100);
    } 
    for(int i=2;i<7;i++) {
      digitalWrite(led[i],HIGH);
      delay(100);
    }
    for(int i=6;i>1;i--) {
      digitalWrite(led[i],LOW);
      delay(100);
    } 
    for(int i=6;i>1;i--) {
      digitalWrite(led[i],HIGH);
      delay(100);
    }
    for(int i=2;i<7;i++) {
      digitalWrite(led[i],LOW);
      delay(100);
    } 
    for(int i=6;i>1;i--) {
      digitalWrite(led[i],HIGH);
      delay(100);
    }
    for(int i=6;i>1;i--) {
      digitalWrite(led[i],LOW);
      delay(100);
    } 
    for(int i=2;i<7;i++) {
      digitalWrite(led[i],HIGH);
      delay(100);
    }
  for(int j=0;j<3;j++) {
    for(int i=0;i<3;i++) {
      digitalWrite(led[4+i],LOW);
      digitalWrite(led[4-i],LOW);
      delay(100);
    } 
    for(int i=0;i<3;i++) {
      digitalWrite(led[4+i],HIGH);
      digitalWrite(led[4-i],HIGH);
      delay(100);
    }
  }
}

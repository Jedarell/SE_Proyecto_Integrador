
int button_pin [] = {5, 6, 7, 8, 9, 10}; 

int btn0_state;            
int btn0_last_state = HIGH; 
int btn1_state;
int btn1_last_state = LOW;
int btn2_state;
int btn2_last_state = LOW;
int btn3_state;
int btn3_last_state = LOW;
int btn4_state;
int btn4_last_state = LOW;
int btn5_state;
int btn5_last_state = LOW;

unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;    

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 6; i++){
    pinMode(button_pin, INPUT);
  }
}

String cad;

void loop() {
  int btn0_reading = digitalRead(button_pin[0]);
  int btn1_reading = digitalRead(button_pin[1]);
  int btn2_reading = digitalRead(button_pin[2]);
  int btn3_reading = digitalRead(button_pin[3]);
  int btn4_reading = digitalRead(button_pin[4]);
  int btn5_reading = digitalRead(button_pin[5]);
 
  if (btn0_reading != btn0_last_state) {
    lastDebounceTime = millis();
  }
  if (btn1_reading != btn1_last_state) {
    lastDebounceTime = millis();
  }
  if (btn2_reading != btn2_last_state) {
    lastDebounceTime = millis();
  }
  if (btn3_reading != btn3_last_state) {
    lastDebounceTime = millis();
  }
  if (btn4_reading != btn4_last_state) {
    lastDebounceTime = millis();
  }
  if (btn5_reading != btn5_last_state) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btn0_reading != btn0_state) {
      btn0_state = btn0_reading;
      if (btn0_reading == LOW){
        cad.concat("r" + String(btn0_reading));
      }
    }
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btn1_reading != btn1_state) {
      btn1_state = btn1_reading;
      if (btn1_reading == LOW){
        cad.concat("l" + String(btn0_reading));
      }
    }
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btn2_reading != btn2_state) {
      btn2_state = btn2_reading;
    }
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btn3_reading != btn3_state) {
      btn3_state = btn3_reading;
    }
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btn4_reading != btn4_state) {
      btn4_state = btn4_reading;
    }
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (btn5_reading != btn5_state) {
      btn5_state = btn5_reading;
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  btn0_last_state = btn0_reading;
  btn1_last_state = btn1_reading;
  btn2_last_state = btn2_reading;
  btn3_last_state = btn3_reading;
  btn4_last_state = btn4_reading;
  btn5_last_state = btn5_reading;
  Serial.println(cad);
}

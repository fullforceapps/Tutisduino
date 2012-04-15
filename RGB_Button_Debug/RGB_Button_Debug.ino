// For 2x4 button pad. Prints message and toggles door lock on each press.
// Set your serial console to 19200
// Written by Will O'Brien, Modified by Braden Licastro, based on various others works.

// Define the number of buttons in their respective locations.
#define ROWS 2
#define COLS 4

// Pins for the Vin of the buttons.
const byte buttonWrite[2] = {
  2, 3};
// Pins for reading the state of the buttons.
const byte buttonRead[4] = {
  6, 7, 8, 9};
  
boolean pressed[ROWS][COLS] = {
  0};
  
// Set up the lock.
const byte lock_pin = 4;
boolean lockState = 0;

//Set up the code.
void setup(){
  //Initialize output
  Serial.begin(19200);
  pinMode(lock_pin, OUTPUT);
  digitalWrite(lock_pin, LOW);

// Setup the button inputs and outputs
  for(int i = 0; i < ROWS; ++i){
    pinMode(buttonWrite[i], OUTPUT);
    digitalWrite(buttonWrite[i],LOW);
  }
  for(int j = 0; j<COLS; ++j) {
    pinMode(buttonRead[j], INPUT);
  }
}

// Main program loop.
void loop(){
  Serial.print(".");
  
  // Read button presses.
  for(byte r = 0; r < ROWS; ++r){
    digitalWrite(buttonWrite[r], HIGH);
    for(byte c = 0; c < COLS; ++c){
      if(pressed[r][c] != digitalRead(buttonRead[c])){
        pressed[r][c] = digitalRead(buttonRead[c]);
        if(pressed[r][c]){
          on_press(r, c);
        } 
      } 
    }
    delay(5);
    digitalWrite(buttonWrite[r], LOW); 
  }
  delay(10);
}

// Button pressed.
void on_press(byte r, byte c){
  Serial.print(r, DEC);
  Serial.print(", ");
  Serial.println(c, DEC);
  set_lock();
}

// Trigger the lock.
void set_lock(){
 if(lockState){
   unlock(); 
 }
  else
   lock(); 
}
void unlock(){
  Serial.print("Unlock door");
  digitalWrite(lock_pin, HIGH);
  lockState = !lockState;
}
void lock(){
  Serial.print("Lock door");
  digitalWrite(lock_pin, LOW);
  lockState = !lockState;
}

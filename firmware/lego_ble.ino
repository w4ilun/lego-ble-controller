#define INPUT_SIZE 30 //input buffer size

//motor channel struct
struct Channel {
    int en1;
    int en2;
    int pwm;
    int value;
};

Channel m1 = { 2 , 4 , 3 , 0 }; // en1 , en2 , pwm , value
Channel m2 = { 7 , 8 , 5 , 0 };
Channel m3 = { 15 , 14 , 6 , 0 };
Channel m4 = { 16 , 10 , 9 , 0 };

//standby, pin must be HIGH to enable motor drivers
int standby = 18;

//serial input buffer
char inputBuffer[INPUT_SIZE + 1];

void setup() {
    
    pinMode(m1.en1, OUTPUT);
    pinMode(m1.en2, OUTPUT);
    pinMode(m1.pwm, OUTPUT);
    pinMode(m2.en1, OUTPUT);
    pinMode(m2.en2, OUTPUT);
    pinMode(m2.pwm, OUTPUT);
    pinMode(m3.en1, OUTPUT);
    pinMode(m3.en2, OUTPUT);
    pinMode(m3.pwm, OUTPUT);
    pinMode(m4.en1, OUTPUT);
    pinMode(m4.en2, OUTPUT);
    pinMode(m4.pwm, OUTPUT);
    pinMode(standby, OUTPUT);

    digitalWrite(standby, HIGH);

    Serial1.begin(115200); //hardware Serial1 - default HM-10 baud rate is 9600, mine was changed e.g. AT+BAUD
    Serial1.setTimeout(10);
    while(!Serial1);
}

void loop() {
    if(Serial1.available() > 0){
        byte size = Serial1.readBytes(inputBuffer, INPUT_SIZE);
        Serial.println(inputBuffer); //print input for debugging
        inputBuffer[size] = 0; //null terminate input
        
        //tokenize input commands with '#' as the deliminator
        char* command = strtok(inputBuffer, "#");
        m1.value = atoi(command);
        command = strtok(0, "#");
        m2.value = atoi(command);
        command = strtok(0, "#");
        m3.value = atoi(command);
        command = strtok(0, "#");
        m4.value = atoi(command);
        updatePWM();

        //print parsed values
        Serial.print("M1 Speed is ");
        Serial.println(m1.value);
        Serial.print("M2 Speed is ");
        Serial.println(m2.value);
        Serial.print("M3 Speed is ");
        Serial.println(m3.value);
        Serial.print("M4 Speed is ");
        Serial.println(m4.value);             
    }
}

void updatePWM(){
    //Channel 1
    if(m1.value < 0){
        digitalWrite(m1.en1, LOW);
        digitalWrite(m1.en2, HIGH);
    }else{
        digitalWrite(m1.en1, HIGH);
        digitalWrite(m1.en2, LOW);   
    }
    analogWrite(m1.pwm, abs(m1.value));
    //Channel 2
    if(m2.value < 0){
        digitalWrite(m2.en1, LOW);
        digitalWrite(m2.en2, HIGH);
    }else{
        digitalWrite(m2.en1, HIGH);
        digitalWrite(m2.en2, LOW);   
    }
    analogWrite(m2.pwm, abs(m2.value));
    //Channel 3
    if(m3.value < 0){
        digitalWrite(m3.en1, LOW);
        digitalWrite(m3.en2, HIGH);
    }else{
        digitalWrite(m3.en1, HIGH);
        digitalWrite(m3.en2, LOW);   
    }
    analogWrite(m3.pwm, abs(m3.value));
    //Channel 4
    if(m4.value < 0){
        digitalWrite(m4.en1, LOW);
        digitalWrite(m4.en2, HIGH);
    }else{
        digitalWrite(m4.en1, HIGH);
        digitalWrite(m4.en2, LOW);   
    }
    analogWrite(m4.pwm, abs(m4.value));
}
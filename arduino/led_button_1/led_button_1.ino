/**
 * Arduino controlled by Serilal
 * K.OHWADA 2014-08-01
 */

// command
// "Lx" : trun on/off LED
// "Pxxx" : fade LED

// message
// "Bx" : buton status
// "Axxxx" : analog value

#define PIN_BUTTON 2
#define PIN_PWM 10
#define PIN_LED 13
#define PIN_ANALOG A0
#define SPEED 9600

#define MAX_PWM_VALUE  255
#define MAX_MSG_WAIT  100
#define MAX_SERIAL_WAIT  100
#define ERR  -1

int loop_cnt = 0;

/**
 * setup
 */
void setup() {
    Serial.begin( SPEED );
    pinMode( PIN_LED, OUTPUT );  
    pinMode( PIN_PWM, OUTPUT );
    pinMode( PIN_BUTTON, INPUT );  
}

/**
 * loop
 */
void loop() {
    // if recieve serial 
    if ( Serial.available() ) {
        int c = Serial.read();
        Serial.write( c );
        if ( c == 'L' ) {
            execLed();
        } else 	if ( c == 'P' ) {
            execPwm();
        }
    }
    // when 0.1 sec pass
    if ( loop_cnt > MAX_MSG_WAIT ) {
        loop_cnt = 0;
        execDigitalRead();
        execAnalogRead();
    }
    loop_cnt ++;
    delay( 1 ); 
}

/**
 * read Digital Pin and send value
 */
void execDigitalRead() {
    int value = digitalRead( PIN_BUTTON );
    Serial.print( "B" );
    Serial.println( value );
}

/**
 * read Analog Pin and send value
 */
void execAnalogRead() {
    int value = analogRead( PIN_ANALOG );
    Serial.print( "A" );
    Serial.println( value );
}

/**
 * recieve data and wirte Digital Pin
 */
void execLed() {
    int value = recvOneDigit();
    if ( value == 0 ) {
        // LED on if "0"
        digitalWrite( PIN_LED, LOW ); 
    } else if ( value == 1 ) {
        // LED on if "1"
        digitalWrite( PIN_LED, HIGH ); 
    } 
}

/**
 * recieve data and wirte PWM Pin
 */	
void execPwm() {
    int value = recvThreeDigit( MAX_PWM_VALUE );
    if ( value != ERR ) {
        // fade LED
        Serial.print( "#" );
        Serial.println( value );
        analogWrite( PIN_PWM, value ); 
    }
}

/**
 * recieve ThreeDigit
 */	
int recvThreeDigit( int max ) {
    // 1st
    int c = recvOneDigit();
    if ( c == ERR ) {
        return ERR;
    }
    int value = c * 100;
    // 2nd
    c = recvOneDigit();
    if ( c == ERR ) {
        return ERR;
    }
    value += c * 10;
    // 3rd
    c = recvOneDigit();
    if ( c == ERR ) {
        return ERR;
    }
    value += c;
    if ( value > max ) {
        return ERR;
    }
    return value;
}

/**
 * recieve OneDigit
 */
int recvOneDigit() {
    int cnt = 0;
    // wait next char
    while( true ) {
        // if recieve serial 
        if ( Serial.available() ) {
            int c = Serial.read();
            Serial.write( c );
            int value = c - '0';
            if ( value < 0 || 9 < value ){
                return ERR;
            }
            return value;
        }
        // when wait 100 msec
        if ( cnt > MAX_SERIAL_WAIT ) {
            return ERR;
        }
        cnt ++;
        delay( 1 );
    }   
}

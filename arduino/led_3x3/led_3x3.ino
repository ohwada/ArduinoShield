// 2014-05-05 K.OHWADA

// pin define
int ANODE_PIN[3]   = { 2, 3, 4 };
int CATHODE_PIN[3] = { 5, 6, 7 };

// LED Pattern 3x3
int led_pattern[ 3 ][ 3 ];
// return array of getTmpRow
int tmp_row[ 3 ];

/**
 * setup
 */
void setup() {
	// set low to all anodes
	for( int i = 0; i < 3; i++ ) {
		pinMode( ANODE_PIN[ i ], OUTPUT );
		digitalWrite( ANODE_PIN[ i ], LOW );
	}
	// set high to all cathodes
	for( int j = 0; j < 3; j++ ) {
		pinMode( CATHODE_PIN[ j ], OUTPUT );
		digitalWrite( CATHODE_PIN[ j ], HIGH );
	}
	randomSeed( analogRead(0) );
	getNewLedPattern();
}

/**
 * loop
 */
void loop() {
	// 0.45 sec
	writeLedN( 30 );
	shiftLedPattern();
}

/**
 * write to LED N loop
 * @param n
 */
void writeLedN( int n ) {
	for( int i = 0; i < n; i++ ) {
		writeLed();
	}
}

/**
 * write to LED
 * @param led_pattern
 */
void writeLed() {
	// 15 msec
	for( int i = 0; i < 3; i++ ) {
		// set low to row (cathode)
		digitalWrite( CATHODE_PIN[ i ], LOW );	
		for( int j = 0; j < 3; j++ ) {
			// set high to anode, if pattern = 1
			if ( led_pattern[ i ][ j ] == 1 ) {
				digitalWrite( ANODE_PIN[ j ], HIGH );
			}
		}
		// led on 5 msec
		delay( 5 );
		// set low to all anodes
		for( int j = 0; j < 3; j++ ) {
			digitalWrite( ANODE_PIN[ j ], LOW );	
		}
		// set high to row (cathode)
		digitalWrite( CATHODE_PIN[ i ], HIGH );
	}
}

/**
 * shift LED pattern
 * @param led_pattern
 * @return led_pattern
 */
void shiftLedPattern() {
	// shift row ( 0 <- 1, 1 <- 2 )
	for ( int i=0; i<2; i++ ) {
		for ( int j=0; j<3; j++ ) {
			led_pattern[ i ][ j ] = led_pattern[ i + 1 ][ j ]; 
		}
	}
	// set new pattern to row 2
	getTmpRow();
	for ( int j=0; j<3; j++ ) {
		led_pattern[ 2 ][ j ] = tmp_row[ j ]; ; 
	}	
} 

/**
 * new random pattern (at first)
 * @return led_pattern
 */
void getNewLedPattern() {
	for ( int i=0; i<3; i++ ) {
		getTmpRow();
		for ( int j=0; j<3; j++ ) {
			led_pattern[ i ][ j ] = tmp_row[ j ]; 
		}
	}	
}   

/**
 * random pattern row
 * @return tmp_row
 */
void getTmpRow() { 
	int rand;  
	for ( int i=0; i<3; i++ ) {
		rand = random( 2 );
		tmp_row[ i ] = 0;
		// set 1, if rand value = 1
		if ( rand == 1 ) {
			tmp_row[ i ] = 1;
		}
	}
}

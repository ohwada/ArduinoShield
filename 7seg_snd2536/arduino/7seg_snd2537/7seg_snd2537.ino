/*
 * 7 Segment LED - SND2537
 * 2014-12-14 K.OHWADA
 */

#define SERIAL_SPEED  9600 
#define SEG_NUM  7
#define ROW_NUM  3
#define FIG_NUM  10
#define DELAY_SEG  3
#define DELAY_TEST  500
#define MAX_LOOP  30

// 7 Seg        A   B   C   D   E   F   G
// Ardunino  3  5 A1 A2 A3 A0 A4
// Anode      1  2  3 
// Ardunino  2  4  6
const int CATHODE[ SEG_NUM ] = {3, 5, A1, A2, A3, A0, A4};
const int ANODE[ ROW_NUM ] = {2, 4, 6};

// test pattern
char SEG[ SEG_NUM ][ SEG_NUM ] = {
	{1,0,0,0, 0,0,0},	// A
	{0,1,0,0, 0,0,0},	// B
	{0,0,1,0, 0,0,0},	// C
	{0,0,0,1, 0,0,0},	// D
	{0,0,0,0, 1,0,0},	// E
	{0,0,0,0, 0,1,0},	// F
	{0,0,0,0, 0,0,1},	// G
};

// 7 Seg Font
char PAT[ FIG_NUM ][ SEG_NUM ] = {	
	{1,1,1,1, 1,1,0},	// 0
	{0,1,1,0, 0,0,0},	// 1
	{1,1,0,1, 1,0,1},	// 2
	{1,1,1,1, 0,0,1},	// 3
	{0,1,1,0, 0,1,1},	// 4	
	{1,0,1,1, 0,1,1},	// 5	
	{1,0,1,1, 1,1,1},	// 6
	{1,1,1,0, 0,1,0},	// 7				
	{1,1,1,1, 1,1,1},	// 8		
	{1,1,1,1, 0,1,1},	// 9			
};

// pattern buffer	
int pat_index[ ROW_NUM ];

// display pattern
int digit_cnt = 0;

// loop count
int loop_cnt = 0;

/**
 * === setup ===
 */ 
void setup() {  
	Serial.begin( SERIAL_SPEED );
	Serial.println( "7 Seg - SND2537" );
	int i;
	// set output all cathode ports 
	for ( i=0; i<SEG_NUM; i++ ) {
		pinMode( CATHODE[i], OUTPUT ); 
	}
	// set output all anode ports 
	for ( i=0; i<ROW_NUM; i++ ) {
		pinMode( ANODE[i], OUTPUT );  
	}
	reset_anode( -1 );		  	  	  	  	  	  	  	  	  	  	  	  	  	  	             
}

/**
 * === loop ===
 */ 
void loop() {
//	loop_test();
	loop_digit();
}

/**
 * count up 000 -  999
 */
void loop_digit() {
	int i;
	int index = 0;
	// trun on one 7seg at a time
	for ( i=0; i<ROW_NUM; i++ ) {
		reset_anode( i );
		turn_on_7seg( PAT[ pat_index[ i ] ] );
		delay( DELAY_SEG );
		loop_cnt ++;
	}
	// 0.1 sec elapse
	if ( loop_cnt > MAX_LOOP ) {
		loop_cnt = 0;
		digit_cnt ++;
		if ( digit_cnt > 999 ) {
			digit_cnt = 0;
		}
		int d2 =  digit_cnt / 100;
		int r1 =  digit_cnt - 100 * d2;
		int d1 = r1 / 10;
		int d0 = r1 - 10 * d1;
		pat_index[ 2 ] = d2;
		pat_index[ 1 ] = d1;
		pat_index[ 0 ] = d0;		
	}
}

/**
 * test segment one by one
 */
void loop_test() {
	int i,j;
	// trun on one 7seg at a time
	for ( i=0; i<ROW_NUM; i++ ) {
		reset_anode( i );
		for ( j=0; j<SEG_NUM; j++ ) {
			turn_on_7seg( SEG[  j  ] );
			delay( DELAY_TEST );
		}
	}
}

/**
 * reset anode
 */
void reset_anode( int n ) {
	int i;
	// trun on or off 7seg
	for ( i=0; i<ROW_NUM; i++ ) { 
		if ( i == n ) {
			digitalWrite( ANODE[ i ], HIGH ); 
		} else {
			digitalWrite( ANODE[ i ], LOW ); 
		}				
	}
}

/**
 * turn on/off one 7seg
 */
void turn_on_7seg( char p[] ) {
	int i;
  	for ( i=0; i<SEG_NUM; i++ ) {
		// turn on at LOW
  		if ( p[i] == 1 ) {
  			digitalWrite( CATHODE[ i ], LOW ); 
  		} else {
  		  	digitalWrite( CATHODE[ i ], HIGH ); 
  		}
	}  
}	

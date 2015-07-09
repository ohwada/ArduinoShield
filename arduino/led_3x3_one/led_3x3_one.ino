/*
 * LED 3x3 : one by one pattern
 * 2015-07-01 K.OHWADA
 */

// LED martix 3x3
#define ANO 3
#define CAT 3
// LED number of pattern
#define PAT_MAX 22

// pin define
const int PIN_ANODE[ ANO ]   = { 2, 3, 4 };
const int PIN_CATHODE[ CAT ] = { A2, A1, A0 };

// array of LED pattern
const int PAT[ PAT_MAX ][ ANO*CAT ] = 
{
    { 0,0,0, 0,0,0, 0,0,0 },
    { 1,0,0, 0,0,0, 0,0,0 },
    { 0,1,0, 0,0,0, 0,0,0 },
    { 0,0,1, 0,0,0, 0,0,0 },
    { 0,0,0, 1,0,0, 0,0,0 },
    { 0,0,0, 0,1,0, 0,0,0 },
    { 0,0,0, 0,0,1, 0,0,0 },
    { 0,0,0, 0,0,0, 1,0,0 },
    { 0,0,0, 0,0,0, 0,1,0 },
    { 0,0,0, 0,0,0, 0,0,1 },
    { 0,0,0, 0,0,0, 0,0,0 },
    { 1,1,1, 1,1,1, 1,1,1 },
    { 0,1,1, 1,1,1, 1,1,1 },
    { 1,0,1, 1,1,1, 1,1,1 },
    { 1,1,0, 1,1,1, 1,1,1 },
    { 1,1,1, 0,1,1, 1,1,1 },
    { 1,1,1, 1,0,1, 1,1,1 },
    { 1,1,1, 1,1,0, 1,1,1 },
    { 1,1,1, 1,1,1, 0,1,1 },
    { 1,1,1, 1,1,1, 1,0,1 },
    { 1,1,1, 1,1,1, 1,1,0 },
    { 1,1,1, 1,1,1, 1,1,1 },
};

// value of LED martix
int matrix[ ANO ][ CAT ];

// pattern counter
int pat_cnt = 0;

/**
 * setup
 */
void setup() {
    // set low to all anodes
    for( int i = 0; i < ANO; i++ ) {
        pinMode( PIN_ANODE[ i ], OUTPUT );
        digitalWrite( PIN_ANODE[ i ], LOW );
    }
    // set high to all cathodes
    for( int j = 0; j < CAT; j++ ) {
        pinMode( PIN_CATHODE[ j ], OUTPUT );
        digitalWrite( PIN_CATHODE[ j ], HIGH ); 
    }
}

/**
 * loop
 */
void loop() {
    setPattern();
    writeLedN( 60 ); // 0.9 sec
}

/**
 * set Pattern
 */
void setPattern() {
    for ( int i=0; i<ANO; i++ ) {
        for ( int j=0; j<CAT; j++ ) {
            matrix[ i ][ j ] = PAT[ pat_cnt ][ CAT*i + j ];
        }
    }
    pat_cnt ++;
    if ( pat_cnt >= PAT_MAX ) {
        pat_cnt = 0;
    } 
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
 * write to LED using matrix
 */
void writeLed() {
    // 15 msec
    for( int i = 0; i < ANO; i++ ) {
        // set low to row (cathode)
        digitalWrite( PIN_CATHODE[ i ], LOW );	
        for( int j = 0; j < CAT; j++ ) {
            // set high to anode, if pattern = 1
            if ( matrix[ i ][ j ] == 1 ) {
                digitalWrite( PIN_ANODE[ j ], HIGH );
            }
        }
        // led on 5 msec
        delay( 5 );
        // set low to all anodes
        for( int j = 0; j < CAT; j++ ) {
            digitalWrite( PIN_ANODE[ j ], LOW );	
        }
        // set high to row (cathode)
        digitalWrite( PIN_CATHODE[ i ], HIGH );
    }
}

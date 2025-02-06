//
// Created by madan on 1/22/2025.
//

#include <iostream>
#include <vector>
using namespace std;

// Returns the 4-bit Excess-3 encoding of bcd, where bcd is 0..9 in standard BCD
// but given as a 4-bit value (LSB is bit 0).
// The function does bit-serial addition of +3 using the state machine.
vector<int> bcdToExcess3(int bcd) {
    // State encoding (as integers):
    // S0=0, S1=1, S2=2, S3=3, S4=4, S5=5, S6=6
    int state = 0;    // start in S0
    vector<int> result(4,0);  // will hold the 4 output bits LSB..MSB

    for(int i = 0; i < 4; i++){
        // Extract the i-th bit of the BCD digit
        int X = (bcd >> i) & 1;

        // Determine next state and output bit Z based on (state, X)
        int nextState;
        int Z;
        switch(state){
            case 0: // S0
                if(X==0){ nextState=1; Z=1; } else { nextState=2; Z=0; }
                break;
            case 1: // S1
                if(X==0){ nextState=3; Z=1; } else { nextState=4; Z=0; }
                break;
            case 2: // S2
                if(X==0){ nextState=4; Z=1; } else { nextState=5; Z=1; }
                break;
            case 3: // S3
                if(X==0){ nextState=5; Z=0; } else { nextState=5; Z=1; }
                break;
            case 4: // S4
                if(X==0){ nextState=5; Z=1; } else { nextState=6; Z=0; }
                break;
            case 5: // S5
                if(X==0){ nextState=0; Z=0; } else { nextState=0; Z=1; }
                break;
            case 6: // S6
                // Typically we never feed S6 an X=1 in valid BCD+3, so handle only X=0
                if(X==0){ nextState=0; Z=1; }
                else     { nextState=0; Z=0; } // fallback
                break;
        }
        result[i] = Z;
        state = nextState;
    }

    return result;
}

// A small "main" to illustrate its use
int main(){
    // Test all BCD digits 0..9
    for(int bcd = 0; bcd < 10; bcd++){
        auto excess3 = bcdToExcess3(bcd);
        cout << "BCD=" << bcd
             << " (bin=" << ((bcd>>3)&1) << ((bcd>>2)&1)
             << ((bcd>>1)&1) << (bcd&1) << ")  ->  ";
        // Print out the Excess-3 bits from MSB down to LSB
        for(int i=3; i>=0; i--) cout << excess3[i];
        cout << endl;
    }
    return 0;
}

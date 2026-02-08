#include <iostream>     // for use of cin, cout, endl
#include <string>       // for use of strings, string member functions
#include <cmath>        // for use of pow(x,y) function
// NO OTHER LIBRARIES ARE ALLOWED!

using namespace std;

// function: disassemble takes in a string representing
//          an assembled MIPS instruction as a string
//          and returns the instruction itself
//
//          This is a limited disassembler: we can safely assume the input is:
//          a) legitimate (an actual MIPS instruction)
//          b) is ONLY an I-type and ONLY one of: addi, addiu, andi, ori, slti, sltiu
//          c) has ONLY registers $t0 thru $t7, or $s0 thru $s7 in the instruction
//
string disassemble( string hex ) {

    // You want to retrieve all the separate fields of an I-type instruction
    //      to help you figure out what the assembly instruction is.
    //
    // HINT: Use bitwise masking and bit-shifting to isolate the 
    //      different parts of the hex instruction!
    
    // YOUR CODE GOES HERE!!
    //hex -> unit32
    unsigned int num = 0;

    for(char c : hex){
        unsigned int current = 0;
        if(c >= '0' && c <= '9') current = c - '0';
        else if(c >= 'a' && c <= 'f') current = 10 + c - 'a';
        else if(c >= 'A' && c <= 'F') current = 10 + c - 'A';
        num = num * 16 + current;
    }

    unsigned int op = (num >> 26) & 0x3F;
    unsigned int rs = (num >> 21) & 0x1F;
    unsigned int rt = (num >> 16) & 0x1F;
    unsigned int immed = num & 0xFFFF;

    //match op code
    string op_code;
    if(op == 8){
        op_code = "addi";
    }
    else if (op == 9)
    {
        op_code = "addiu";
    }
    else if(op == 12){
        op_code = "andi";
    }
    else if(op == 13){
        op_code = "ori";
    }
    else if(op == 10){
        op_code = "slti";
    }
    else if(op == 11){
        op_code = "sltiu";
    }
    
    //match rs
    string rs_code;

    if(rs >= 8 && rs <= 15){
        rs_code = string("$t") + char('0' + (rs - 8));
    }
    if(rs >= 16 && rs <= 23){
        rs_code = string("$s") + char('0' + (rs - 16));
    }

    //match rt
    string rt_code;

    if(rt >= 8 && rt <= 15){
        rt_code = string("$t") + char('0' + (rt - 8));
    }
    if(rt >= 16 && rt <= 23){
        rt_code = string("$s") + char('0' + (rt - 16));
    }

    // compute immediate
    int simm = (int)((short)immed);
    bool neg = (simm < 0);
    unsigned int simm_s = neg ? (unsigned int)(-simm) : (unsigned int)simm;
    string immed_code; 
    if(simm_s == 0){
        immed_code = "0";
    }
    else{
        while(simm_s > 0){
            char d = char('0' + (simm_s % 10));
            immed_code = d + immed_code;
            simm_s /= 10;
        }
        if(neg) immed_code = "-" + immed_code;
    }
    string out = op_code + " " + rt_code + ", " + rs_code + ", " + immed_code;
    return out;  // remove stub and replace it with correct variable
}

int main() {
// Do NOT change ANY code in main() function!!
//      or you will fail this task (get a zero)

    string hex, inst;
    
    cout << "Enter your assembled instruction as a hex number: 0x";
    cin >> hex;
    
    
    inst = disassemble( hex );
    cout << "Your instruction is:\n" << inst << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <bitset>

using namespace std;


void parse_src()
{

    fstream input_file,output_file;
    string line,temp;

    unsigned int newstart = 0,oldstart = 0,addr,opcode, inc,bmask;

    
    cout << "Enter the actual starting address" << endl;
    cin >>hex>>newstart;

    
    input_file.open("reloc.txt", ios::in );
    output_file.open("reloc_output.txt", ios::out);

    while(getline(input_file,line)) 
    {
       stringstream tokens; 
       addr = 0;
       tokens<<line;
       if(line[0] == 'H'){
            tokens>>temp>>temp;
            tokens>>hex>>oldstart;
            inc = newstart-oldstart;
            continue;
        }
        if(line[0]== 'E')
        {
            break;
        }
        else if(line[0] == 'T')
        {
            tokens>>temp;
            
            tokens>>hex>>addr;
            tokens>>hex>>bmask;
            
            addr+=inc;
            while(tokens>>hex>>opcode)
            {
                
                if(bmask & 0x800)
                {
                    
                    opcode+=inc;
                }
                output_file<<uppercase<<hex<<addr<<"\t"<<hex<<opcode<<endl;
                
                stringstream hexdigit;
                hexdigit<<hex<<opcode;
                addr+=hexdigit.str().length()/2;

                bmask= bmask<<1;
            }
        }
    }
    input_file.close();
    output_file.close();
}



int main()
{
    parse_src();
}

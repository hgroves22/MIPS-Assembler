#ifndef __PROJECT1_CPP__
#define __PROJECT1_CPP__

#include "project1.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) // Checks that at least 3 arguments are given in command line
    {
        std::cerr << "Expected Usage:\n ./assemble infile1.asm infile2.asm ... infilek.asm staticmem_outfile.bin instructions_outfile.bin\n" << std::endl;
        exit(1);
    }
    //Prepare output files
    std::ofstream inst_outfile, static_outfile;
    static_outfile.open(argv[argc - 1], std::ios::binary);
    inst_outfile.open(argv[argc - 1], std::ios::binary);
    std::vector<std::string> instructions;

    /**
     * Phase 1:
     * Read all instructions, clean them of comments and whitespace DONE
     * TODO: Determine the numbers for all static memory labels
     * (measured in bytes starting at 0)
     * TODO: Determine the line numbers of all instruction line labels
     * (measured in instructions) starting at 0
    */

    //For each input file:
    for (int i = 1; i < argc - 2; i++) {
        std::ifstream infile(argv[i]); //  open the input file for reading
        if (!infile) { // if file can't be opened, need to let the user know
            std::cerr << "Error: could not open file: " << argv[i] << std::endl;
            exit(1);
        }
        
        std::string str;
        while (getline(infile, str)){ //Read a line from the file
            int lineCounter = 0;
            str = clean(str); // remove comments, leading and trailing whitespace
            if (str == "") { //Ignore empty lines
                continue;
            }
            if(str.find("beq") != string::npos || str.find("bne") != string::npos)
            {   
                int labelLineNumber = -1;
                //find the label:
                
                int firstComma = str.find(",");
                string sub1 = str.substr(firstComma+1, str.length()-firstComma);
                int secondComma = sub1.find(",");
                string labelP1 = str.substr(secondComma+2, sub1.length()-secondComma+1);
                
                string colon = ":";
                string label = labelP1 + colon;
                ifstream infile(argv[i]);
                int labelLineCounter = 0;
                string labelLine;
                bool labelFound = false;
                while (getline(infile, labelLine) && !labelFound){ 
                    if(labelLine.find(label) != string::npos)
                    {
                        labelLineNumber = labelLineCounter;
                        labelFound = true;
                    }
                    else labelLineCounter++;
                }
                if(labelFound==false || labelLineNumber==-1)
                {
                    cerr << "Label not found. Please enter a valid label.";
                    return -1;
                }
            int labelOffset = labelLineNumber - lineCounter +1;
            string lblOffStr = "";
            lblOffStr = labelOffset;
            string fixedString = str.substr(0,firstComma+secondComma+1) + lblOffStr;
            str = fixedString;
            }
            instructions.push_back(str); // TODO This will need to change for labels
            lineCounter++;
        }
        infile.close();
    }
    



    /** Phase 2
     * Process all static memory, output to static memory file
     * TODO: All of this
     */

    /** Phase 3
     * Process all instructions, output to instruction memory file
     * TODO: Almost all of this, it only works for adds
     */
    for(std::string inst : instructions) {
        std::vector<std::string> terms = split(inst, WHITESPACE+",()");
        std::string inst_type = terms[0];

        // Rtype instructions
        if (inst_type == "add") {   
            write_binary(encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 32), inst_outfile);
        }
        else if (inst_type == "sub") {
            write_binary(encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 34), inst_outfile);
        }
        else if (inst_type == "mult") {
            write_binary(encode_Rtype(0, registers[terms[2]], registers[terms[3]], 0, 0, 24), inst_outfile);
        }
        else if (inst_type == "div") {
            write_binary(encode_Rtype(0, registers[terms[2]], registers[terms[3]], 0, 0, 26), inst_outfile);
        }
        else if (inst_type == "mflo") {
            write_binary(encode_Rtype(0, 0, 0, registers[terms[1]], 0, 18), inst_outfile);
        }
        else if (inst_type == "mfhi") {
            write_binary(encode_Rtype(0, 0, 0, registers[terms[1]], 0, 17), inst_outfile);
        }
        else if (inst_type == "sll") {
            write_binary(encode_Rtype(0, 0, registers[terms[2]], registers[terms[1]], stoi(terms[3]), 00), inst_outfile);
        }
        else if (inst_type == "srl") {
            write_binary(encode_Rtype(0, 0, registers[terms[2]], registers[terms[1]], stoi(terms[3]), 02), inst_outfile);
        }
        else if (inst_type == "slt") {
            write_binary(encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42), inst_outfile);
        }
        else if (inst_type == "jr") {
            write_binary(encode_Rtype(0, registers[terms[1]], 0, 0, 0, 8), inst_outfile);
        }
        else if (inst_type == "jalr") {
            write_binary(encode_Rtype(0, registers[terms[2]], 0, registers[terms[1]], 0, 9), inst_outfile);
        }
        else if (inst_type == "syscall") {
            write_binary(encode_Rtype(0, 0, 0, 26, 0, 12), inst_outfile);
        }
        //I-Type instructions
        else if(inst_type == "addi"){   
            write_binary(encode_Itype(8,registers[terms[2]],registers[terms[1]],stoi(terms[3])), inst_outfile);
        }
        else if(inst_type == "lw"){
            write_binary(encode_Itype(35,registers[terms[1]],registers[terms[3]],stoi(terms[2])), inst_outfile);
        }
        else if(inst_type == "sw"){
            write_binary(encode_Itype(43,registers[terms[1]],registers[terms[3]],stoi(terms[2])), inst_outfile);
        }
        else if(inst_type == "beq"){
            write_binary(encode_Itype(4,registers[terms[1]],registers[terms[2]],stoi(terms[3])), inst_outfile);
        }
        else if(inst_type == "bne"){
            write_binary(encode_Itype(5,registers[terms[1]],registers[terms[2]],stoi(terms[3])), inst_outfile);
        }
    }
}

#endif
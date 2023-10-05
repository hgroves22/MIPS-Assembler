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

   unordered_map<string, int> labels;
    //For each input file:
    for (int i = 1; i < argc - 2; i++) {
        std::ifstream infile(argv[i]); //  open the input file for reading
        if (!infile) { // if file can't be opened, need to let the user know
            std::cerr << "Error: could not open file: " << argv[i] << std::endl;
            exit(1);
        }
        bool pastText = false;
        std::string str;
        int lineCounter = 1;
        while (getline(infile, str)){ //Read a line from the file
            
            str = clean(str); // remove comments, leading and trailing whitespace
            if (str == "") { //Ignore empty lines
                continue;
            }
            instructions.push_back(str); // TODO This will need to change for labels
            if(str == ".text") pastText = true;
            if(pastText && str.find(":") != string::npos){   
                string label = str.substr(0,str.length()-1);
                labels[label] = lineCounter;
            }       
            lineCounter++;
        }
        infile.close();
    }
    /** Phase 2
     * Process all static memory, output to static memory file
     * TODO: All of this
     */
    unordered_map<string, string> static_labels;
    //For each input file:
    for (int i = 1; i < argc - 2; i++) {
        std::ifstream infile(argv[i]); //  open the input file for reading
        if (!infile) { // if file can't be opened, need to let the user know
            std::cerr << "Error: could not open file: " << argv[i] << std::endl;
            exit(1);
        }
        bool pastText = false;
        bool pastData = false;
        std::string str;
        
        while (getline(infile, str)){ //Read a line from the file
            
            str = clean(str); // remove comments, leading and trailing whitespace
            if (str == "") { //Ignore empty lines
                continue;
            }
            if(str == ".text") pastText = true;
            if(pastData && !pastText){   

                
                int colonLocation = str.find(":");
                string label = str.substr(0,colonLocation);

                string afterFirstSpace = str.substr(colonLocation + 1);
                string afterSecondSpace = afterFirstSpace.substr(afterFirstSpace.find(" ")+1); 
                string afterThirdSpace = afterSecondSpace.substr(afterSecondSpace.find(" ")+1);              
                static_labels[label] = afterThirdSpace;
            }       
            if(str == ".data") pastData = true;
        }
        infile.close();
    }

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
            write_binary(encode_Rtype(0, 0, 0, 0, 0, 12), inst_outfile);
        }
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
            int lab = labels[terms[3]];
            write_binary(encode_Itype(4,registers[terms[1]],registers[terms[2]], lab), inst_outfile);
        }
        else if(inst_type == "bne"){
            int lab = labels[terms[3]];
            write_binary(encode_Itype(5,registers[terms[1]],registers[terms[2]], lab), inst_outfile);
        }
        // Jtype Instructions
        else if(inst_type == "j"){
            int lab = labels[terms[1]];
            write_binary(encode_Jtype(2,lab), inst_outfile);
        }
        else if(inst_type == "jal"){
            int lab = labels[terms[3]];
            write_binary(encode_Jtype(3,lab), inst_outfile);
        }
        //Other
        else if(inst_type == "la")
        {
            string stat_lab_string = static_labels[terms[2]];
            cout << stat_lab_string << endl;
            int stat_lab = stoi(stat_lab_string);
            write_binary(encode_Itype(8,0,registers[terms[1]],stat_lab), inst_outfile);
        }
    }
}

#endif
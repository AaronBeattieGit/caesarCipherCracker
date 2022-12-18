//============================================================================
// Name        : Assignment.cpp
// Author      : Aaron Beattie
// Version     :
// Copyright   : Your copyright notice
// Description : A program to take two file names and decrypt the encrypted text
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include "ceaser_ab.hpp"
using namespace std;

int main(int argc, char *argv[]) {
	string e_file_name = argv[1];
	string d_file_name = argv[2];
	ifstream in_file { e_file_name };
	if (in_file.fail()) {
		throw std::runtime_error("Failed to open file");
	}
	string encrypted_in((istreambuf_iterator<char>(in_file)),
			istreambuf_iterator<char>());	//
	Cipher cipher_obj(encrypted_in, "", 0, 0, 0);  //calls constructor
	cipher_obj.character_count(cipher_obj);
	cipher_obj.print_analysis_array(cipher_obj);
	cipher_obj.max_index(cipher_obj);
	cipher_obj.decrypt(cipher_obj);
	string decrypted = cipher_obj.getDecrypted();
	ofstream out(d_file_name);
	out << cipher_obj.getDecrypted(); //writes out the decrypted string to a file
	out.close();
	cout << "Your decrypted text is waiting for you in " << d_file_name << endl;
	return 0;
}


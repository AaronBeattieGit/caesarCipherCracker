/*
 * enc_library_ab.cpp
 *
 *  Created on: 12 Jan 2021
 *      Author: abeattie
 */
#include <iostream>
#include <string>
#include "ceaser_ab.hpp"
//Constructor method
Cipher::Cipher(std::string encrypted, std::string decrypted, int key,
		char letter, int letter_freq) {
	this->encrypted = encrypted;
	this->decrypted = decrypted;
	this->key = key;
	this->letter = letter;
	this->letter_freq = letter_freq;
}
//Deconstructor method
Cipher::~Cipher() {
	std::cout << "Destroying object..." << std::endl;
}
std::string Cipher::getEncrypted() {
	return this->encrypted;
}
std::string Cipher::getDecrypted() {
	return this->decrypted;
}
void Cipher::setDecrypted(std::string d) {
	decrypted = d;
}
int Cipher::getKey() {
	return this->key;
}
void Cipher::set_key(int k) {
	key = k;
}
int Cipher::getAnalysisArray(int index) {
	return this->analysis_array[index];
}
void Cipher::setAnalysisArray(int count, int index) {
	this->analysis_array[index] = count;
}
char Cipher::getLetter() {
	return letter;
}

void Cipher::setLetter(char letter) {
	this->letter = letter;
}

int Cipher::getLetterFreq() {
	return letter_freq;
}

void Cipher::setLetterFreq(int letterFreq) {
	letter_freq = letterFreq;
}
/*takes a encrypted string and counts the freqency of letters
 * before setting the analyisis_array
 * @author A Beattie
 * @param[in] the cipher object to get the encrypted string
 * @return void, sets analysis_array to the count array
 * @date 7/1/21
 * @test character_count(&cipher_obj), encrypted = "MZEU O, rudef efmzpmdpulqp uz"
 * @cipher_obj.analysis_array = {0, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 1, 3, 0, 1, 3, 1, 1, 0, 0, 4, 0, 0, 0, 0, 3 } = expected
 * @test character_count(&cipher_obj), encrypted = "aaAAaaAAaa"
 * @cipher_obj.analysis_array = {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } = expected
 */
void Cipher::character_count(Cipher &cipher_obj) {
	std::string encrypt_count = cipher_obj.getEncrypted();
	char alphabet[26];
	int count[26];
	int largest = 0;
	char most_common_letter;
	for (int i = 0; i < 26; i++) { //setting an alphabet and clearing count array
		alphabet[i] = 97 + i;
		count[i] = 0;
	}
	for (int i = 0; i < encrypt_count.length(); i++) {
		if (is_upper(encrypt_count[i]) != true) {
			encrypt_count[i] = to_upper(encrypt_count[i]); //Converts the encrypted text to upper case for counting
		}
		for (int j = 0; j < 26; j++) {
			if ((encrypt_count[i] == alphabet[j] - 32)) { //counts the frequency of each letter
				count[j] = count[j] + 1;
			}
			if (count[j] > largest) { //compares each letter to find the most common
				largest = count[j];
				most_common_letter = alphabet[j];
			}
		}
	}

	cipher_obj.setLetter(most_common_letter);
	cipher_obj.setLetterFreq(largest);
	for (int i = 0; i < 26; i++) {
		cipher_obj.setAnalysisArray(count[i], i);
	}
}
/*Takes the object and gets the most common letter to work out the most likely key
 * it then asks the user what key they would like to use
 * @author A Beattie
 * @param[in] a Cipher object to get the letter frequency and most common letter from it
 * @return value the integer key that the user has chosen
 * @date 8/1/21
 * @test max_index(&cipher_obj) letter_freq = 22 most_common_letter = a
 * @cout << the most common letter is a at 22
 * @cout << the suggested key is 22
 * @cout << what do you wish the key to be?
 * @cin >> 22
 * @cipher_obj key set to 22
 * @return 22 = expected
 */
int Cipher::max_index(Cipher &cipher_obj) {
	int largest = cipher_obj.getLetterFreq();
	int s_key1 = 0;
	char most_common_letter = cipher_obj.getLetter();
	int usr_key;
	s_key1 = most_common_letter - 101; //takes away the value of e to find the key
	if (s_key1 < 5) { //ensures that if the most common letter is smaller than e that it provides the correct suggested key
		s_key1 = 26 + s_key1;
	}
	std::cout << "The most common letter is " << most_common_letter << " at "
			<< largest << std::endl;
	std::cout << "The suggested key is " << s_key1 << std::endl;
	std::cout << "What do you wish the key to be? " << std::endl;
	std::cin >> usr_key; // allows the user to choose a key
	while (std::cin.fail()) { //ensurest that the key is a number
		std::cout << "Error please input a number " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> usr_key;
	}
	cipher_obj.set_key(usr_key);
	return usr_key;
}
/**takes the objects analysis array and prints it out
 * @author A Beattie
 * @param[in] the Cipher object with anyalsis array set
 * @return value void, cout the array
 * @date 9/1/21
 * @test print_analysis_array(cipher_obj) analysis_array={12, 21, 24, 6, 9, 6, 11, 0, 19, 10, 24, 1, 21, 22, 18, 9, 15, 6, 1, 11, 5, 16, 21, 25, 23, 19, 16, 21}
 * @cout << A : 12
 * 		    B : 21
 * 		    C : 24
 * 		    D : 6
 * 		    E : 11
 * 		    F : 0
 * 		    G : 19
 * 		    H : 10
 * 		    I : 24
 * 		    J : 1
 * 		    K : 21
 * 		    L : 22
 * 		    M : 18
 * 		    N : 9
 * 		    O : 15
 * 		    P : 6
 * 	  	    Q : 1
 * 		    R : 11
 * 		    S : 5
 * 		    T : 16
 * 		    U : 21
 * 		    V : 25
 * 		    W : 23
 * 		    X : 19
 * 		    Y : 16
 * 		    Z : 21
 * @ = expected
 */
void Cipher::print_analysis_array(Cipher cipher_obj) {
	char alphabet[26];

	for (int i = 0; i < 26; i++) {

		alphabet[i] = 97 + i;
		std::cout << alphabet[i] << " : " << cipher_obj.getAnalysisArray(i)
				<< std::endl;
	}
}
/* Takes the cipher object and decrypts a portion of cipher_obj.encrypted and then asks the user if
 * they would like to continue following this sets cipher_obj.decrypted to plain
 * @author A Beattie
 * @param[in] cipher_obj for encrypted text and the key, file name of the output file
 * @return void, sets cipher_obj.decrypt to decrypted text and writes text to a file
 * @date 11/1/21
 * @test decrypt(&cipher_obj, file_name), encrypted = "MZEU O, rudef efmzpmdpulqp uz" key = 16
 * @cout << "WJOE Y, benop opwjzw"
 * @cout << "Do you wish to continue with the decryption? y/n"
 * @cin >> y
 * @ciper_obj.decrypt = "WJOE Y, benop opwjzwnzevaz ej" = expected
 * @test decrypt(&cipher_obj, file_name), encrypted = "MZEU O, rudef efmzpmdpulqp uz" key = 16
 * @cout << "WJOE Y, benop opwjzw"
 * @cout << "Do you wish to continue with the decryption? y/n"
 * @cin >> n
 * @cipher_obj.key = 12
 * @cout << "ANSI C, first standa"
 * @cout << "Do you wish to continue with the decryption? y/n"
 * @cin >> y
 * @ciper_obj.decrypt = "ANSI C, first standardized in" = expected
 */
void Cipher::decrypt(Cipher &cipher_obj) {
	int i;
	int ascii_z;
	bool ext_flg = false;
	std::string cipher = cipher_obj.getEncrypted();
	std::string plain;
	int s_size = 20; // sample text length
	char usr_chk = 0;
	if (cipher.length() < 20) {
		s_size = cipher.length();
	}
	std::ofstream d_file(std::string file_name);
	do {
		int key = cipher_obj.getKey();
		std::cin.clear();
		for (i = 0; i < s_size; i++) {
			if (is_alpha(cipher[i]) != 0) {
				ascii_z = 122;
				if (is_upper(cipher[i]) == true) {
					ascii_z = 90;
				}
				plain += (cipher[i] - key - ascii_z) % 26 + ascii_z;
			} else {
				plain += cipher[i];
			}
		}
		if (ext_flg == true) {
			break;
		}
		std::cout << plain;

		std::cout << "\nDo you wish to continue with decryption?  y/n"
				<< std::endl;
		std::cin >> usr_chk;
		if (usr_chk == 121) {
			plain.clear(); //clears plain for the next loop
			s_size = cipher.length();

			ext_flg = true;
		} else if (usr_chk == 110) {
			plain.clear();  //clears plain for the next loop
			cipher_obj.max_index(cipher_obj);
		} else {
			plain.clear();  //clears plain for the next loop
			std::cout << "Please select y/n" << std::endl;
		}
	} while (true);
	cipher_obj.setDecrypted(plain);
}
/**takes a char input and converts it to uppercase
 * @author A Beattie
 * @param[in] a char of a letter that needs converting
 * @return a char that is now upper case
 * @date 10/1/21
 * @test to_upper('a')->'A' = expected
 * @test to_upper('x')->'X' = expected
 * @test to_upper('A')->'!' = expected
 */
char Cipher::to_upper(char letter) {
	letter -= 32;
	return letter;
}
/**takes a char input and check if it is and alphabetical character
 * @author A Beattie
 * @param[in] a char of a letter that needs checking
 * @return a bool to indicated true or false
 * @date 10/1/21
 * @test is_alpha('a')->true = expected
 * @test is_alpha('x')->true = expected
 * @test is_alpha('A')->true = expected
 * @test is_alpha('!')->false = expected
 */
bool Cipher::is_alpha(char letter) {
	bool flag = false;
	if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122)) {
		flag = true;
	}
	return flag;
}
/**takes a char input and check to see if it is upper case
 * @author A Beattie
 * @param[in] a char of a letter that needs checking
 * @return a bool to indicate that it is upper case
 * @date 10/1/21
 * @test is_upper('a')->false = expected
 * @test is_upper('x')->false = expected
 * @test is_upper('A')->true = expected
 * @test is_upper('!')->false = expected
 */
bool Cipher::is_upper(char letter) {
	bool flag = false;
	if (letter >= 65 && letter <= 90) {
		flag = true;
	}
	return flag;
}


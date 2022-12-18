/*
 * ceaser_ab.hpp
 *
 *  Created on: 12 Jan 2021
 *      Author: abeattie
 */

#ifndef CEASER_AB_HPP_
#define CEASER_AB_HPP_

class Cipher {
	int analysis_array[26] = { 0 };
	std::string encrypted;
	std::string decrypted;
	char letter;
	int letter_freq;
	int key;
public:
	Cipher(std::string encrypted, std::string decrypted, int key, char letter,
			int letter_freq); //constructor declaration
	~Cipher();

	void character_count(Cipher&);
	void print_analysis_array(Cipher);
	int max_index(Cipher&);
	void decrypt(Cipher&);
	char to_upper(char);
	bool is_alpha(char);
	bool is_upper(char);
	std::string getEncrypted();
	std::string getDecrypted();
	void setDecrypted(std::string);
	int getKey();
	void set_key(int);
	int getAnalysisArray(int);
	void setAnalysisArray(int, int);
	char getLetter();
	void setLetter(char);
	int getLetterFreq();
	void setLetterFreq(int);
};

#endif /* CEASER_AB_HPP_ */

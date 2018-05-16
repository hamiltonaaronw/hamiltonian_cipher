/*

Author: Aaron William Hamilton
*/

#pragma once

#include "Monolith.h"

class HamiltonianCipher
{
private:
	// variables for encrypting or decrypting
	int mCrypt;
	bool mIsEncrypt;

	// read from file
	int mInputMethod;
	bool mIsManualInput;

	// strip spaces from specified string
	string stripSpaces(string s);

	// alphabet
	string mFullAlphabet;

	// axes
	string mXAxis,
		mYAxis,
		mZAxis;

	// encryption/decryption key, 
	string mKey;

	// ciphertext variables
	string mCiphertextOrig;

	// plaintext variables
	string mPlaintextOrig;

	// populaters
	void populateAlphabet();
	string populateAxisWithKey(char axis);
	void populateXAxis();
	void populateYAxis();
	void populateZAxis();

	// private input getters
	void getKeyInput();
	void getPlaintextInput();
	void getCiphertextInput();

	// read in key and cipher/plaintext from file
	string getFilePathInput();
	void getInformationFromFile(string path, bool isEncrypt);

	// private variable getters
	string getAlphabet() { return mFullAlphabet; };
	string getKey() { return mKey; };

	// private setters
	void setAlphabet(string s) { mFullAlphabet = s; };
	void setKey(string s) { mKey = s; };

	// case setter
	string setCase(string s, char sCase);

	// exit program
	void exitProgram();

public:
	HamiltonianCipher(int crypt, int input);
	~HamiltonianCipher();

	void debug();
	void encrypt();

	void init();
};

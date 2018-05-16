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
	string mCiphertextEncrypted;

	// plaintext variables
	string mPlaintextOrig;
	string mPlaintextDecrypted;

	// strip spaces from specified string
	string stripSpaces(string s);

	// populaters
	void populateAlphabet();
	string populateAxisWithKey();
	void populateAxes();

	// scramble the axes
	void scrambleYAxis();
	void scrambleZAxis();

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

	// encrypt a message
	void encrypt();

	// decrypt a message
	void decrypt();

	// exit program
	void exitProgram();

	// plaintext/ciphertext setters
	void setPlaintext(string s) { mPlaintextOrig = s; };
	void setPlaintextDecrypted(string s) { mPlaintextDecrypted = s; };
	void setCiphertext(string s) { mCiphertextOrig = s; };
	void setCiphertextEncrypted(string s) { mCiphertextEncrypted = s; };

	// plaintext/ciphertext getters
	string getPlaintextOrig() { return mPlaintextOrig; };
	string getPlaintextDecrypted() { return mPlaintextDecrypted; };
	string getCiphertextOrig() { return mCiphertextOrig; };
	string getCiphertextEncrypted() { return mCiphertextEncrypted; };


public:
	HamiltonianCipher(int crypt, int input);
	~HamiltonianCipher();

	// initialize
	void init();

	// output axis information
	void debug();

	// update
	void update();
};

/*

Author: Aaron William Hamilton
*/

#pragma once

#include "Monolith.h"

class HamiltonianCipher
{
private:
	int mCrypt,
		mInputMethod;

	void populateAlphabet();
	void setAlphabet(string s) { mFullAlphabet = s; };
	string stripSpaces(string s);

	string mFullAlphabet;

	string mXAxis,
		mYAxis,
		mZAxis;

	string populateAxisWithKey(char axis);
	void populateXAxis();
	void populateYAxis();
	void populateZAxis();

public:
	HamiltonianCipher(int crypt, int input);
	~HamiltonianCipher();

	void init();
};

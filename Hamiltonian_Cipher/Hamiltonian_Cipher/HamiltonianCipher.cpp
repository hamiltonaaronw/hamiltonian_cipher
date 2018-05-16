/*

Author: Aaron William Hamilton

*/

#include "HamiltonianCipher.h"

HamiltonianCipher::HamiltonianCipher(int crypt, int input)
	:mCrypt(crypt),
	mInputMethod(input)
{}

void HamiltonianCipher::init()
{
	populateAlphabet();
}

/*
*****NOTE:
I only used 3 different strings brought together by a stringstream
to make it easier for people to read and see the three different
components that make up the alphabet used in the cipher
*/
void HamiltonianCipher::populateAlphabet()
{
	stringstream ss;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string numbers = "0123456789";
	string ascii = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	ss << alphabet << numbers << ascii;
	setAlphabet(ss.str());
}

string HamiltonianCipher::populateAxisWithKey(char axis)
{

	return "";
}

void HamiltonianCipher::populateXAxis()
{

}

void HamiltonianCipher::populateYAxis()
{

}

void HamiltonianCipher::populateZAxis()
{

}

string HamiltonianCipher::stripSpaces(string s)
{
	stringstream ss;
	string tmp;
	ss << s;
	s = "";

	while (!ss.eof())
	{
		ss >> tmp;
		s = s + tmp;
	}
	return s;
}

HamiltonianCipher::~HamiltonianCipher()
{}
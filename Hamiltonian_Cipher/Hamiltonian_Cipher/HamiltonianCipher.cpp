/*

Author: Aaron William Hamilton

*/

#include "HamiltonianCipher.h"

HamiltonianCipher::HamiltonianCipher(int crypt, int input)
	:mCrypt(crypt),
	mInputMethod(input)
{}

void HamiltonianCipher::debug()
{
	cout << endl << "\t\t\t AXES" << endl;
	cout << endl << "X\t\t\tY\t\t\tZ" << endl;
	for (size_t i = 0; i < mXAxis.length(); i++)
	{
		cout << mXAxis[i] << "\t("
			<< i << ", " << 0 << ", " << 0 << ")\t"
			<< mYAxis[i] << "\t("
			<< 0 << ", " << i << ", " << 0 << ")\t"
			<< mZAxis[i] << "\t("
			<< 0 << ", " << 0 << ", " << i << ")" << endl;
	}
	cout << endl;
}

void HamiltonianCipher::decrypt()
{

}

void HamiltonianCipher::encrypt()
{

}

// exits the program
void HamiltonianCipher::exitProgram()
{
	cout << "Thank you for using my cipher!" << endl;
	cin.get();
	exit(-1);
}

// get the ciphertext from console input (if decrypting)
void HamiltonianCipher::getCiphertextInput()
{
	string ciphertext;
	cout << "Enter ciphertext: ";
	getline(cin, ciphertext);
	mCiphertextOrig = setCase(ciphertext, 'u');
}

string HamiltonianCipher::getFilePathInput()
{
	bool validPath = false;
	string path;
	// to ensure that the file path is valid
	while (!validPath)
	{
		cout << "Enter File Path (enter x to exit): ";
		getline(cin, path);

		if (path == "x")
			exitProgram();

		fstream tmpFile;
		tmpFile.open(path);
		if (!tmpFile)
			cout << "Error: invalid file path" << endl;
		else
		{
			validPath = true;
			break;
		}
		tmpFile.close();
	}

	return path;
}

void HamiltonianCipher::getInformationFromFile(string path, bool isEncrypt)
{

}

// get key from console input (for both encrypting and decrypting)
void HamiltonianCipher::getKeyInput()
{
	cout << "Enter key: ";
	getline(cin, mKey);
}

// get plaintext from console input (for encrypting)
void HamiltonianCipher::getPlaintextInput()
{
	string plaintext;
	cout << "Enter plaintext: ";
	getline(cin, plaintext);
	mPlaintextOrig = setCase(plaintext, 'l');
}

void HamiltonianCipher::init()
{
	populateAlphabet();

	if (mCrypt == 1) // if encrypting
		mIsEncrypt = true;
	if (mCrypt == 2) // if decrypting
		mIsEncrypt = false;
	switch (mInputMethod)
	{
	case 1: // manual input via console
		mIsManualInput = true;
		getKeyInput();
		if (mIsEncrypt)
			getPlaintextInput();
		else
			getCiphertextInput();
		break;

	case 2: // read in key, ciphertext/plaintext from a file
		mIsManualInput = false;
		getFilePathInput();
		break;
	}

	// populate the axes
	populateAxes();

	// scramble the Y and Z axes
	scrambleYAxis();
	scrambleZAxis();
}

/*
*****NOTE:
I only used 3 different strings brought together by a stringstream
to make it easier for people to read and see the three different
components that make up the alphabet used in the cipher
*****NOTE: order of ASCII characters is according to ASCII table
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

string HamiltonianCipher::populateAxisWithKey()
{
	bool repeat = false;
	stringstream ss;
	string key = getKey();
	string alphabet = getAlphabet();

	// run through entirety of key as read in from input or file
	for (size_t i = 0; i < key.length(); i++)
	{
		if (repeat)
			repeat = !repeat;
		char c = key[i];

		// check for repeats in existing key
		for (size_t j = 0; j < ss.str().length(); j++)
		{
			if (c == ss.str()[j])
			{
				repeat = true;
				break;
			}
		}

		if (!repeat)
			ss << key[i];
		else
			continue;
	}

	key = stripSpaces(ss.str());

	return key;
}

/*
populates the X axis by:
-	populating it with the key first
-	insert rest of alphabet (without repeating any letters that
		were in the key)
-	insert numbers (without repeating any numbers that were in the
		key)
-	insert ASCII characters (without repeating any ASCII characters
		that were in the key)
		*****NOTE: order of ASCII characters is according to ASCII table
*/
void HamiltonianCipher::populateAxes()
{
	// stripped key without repeats
	string tmp = populateAxisWithKey();

	// begin populating axes
	int keyOffset = (int)tmp.length();

	stringstream ssAxis;
	ssAxis << tmp;
	bool repeat = false;

	// full alphabet
	string alphabet = getAlphabet();

	// run through each letter of the full alphabet
	for (size_t i = 0; i < alphabet.size(); i++)
	{
		if (repeat)
			repeat = !repeat;

		// run through the axis
		for (size_t j = 0; j < ssAxis.str().length(); j++)
		{
			// if letter is a repeat
			if (ssAxis.str()[j] == alphabet[i])
			{
				repeat = true;
				break;
			}
		}

		// if current alphabet letter is not a repeat
		// add it to the axis stringstream
		if (!repeat)
			ssAxis << alphabet[i];
	}

	// set all axes to the completed axis stringstream
	mXAxis = mYAxis = mZAxis = ssAxis.str();
}

/*
scrambles the Y axis by:
-	reversing the X axis
*/
void HamiltonianCipher::scrambleYAxis()
{
	string tmp;
	for (size_t i = 0; i < mYAxis.length(); i++)
		tmp.insert(0, 1, mYAxis[i]);
	mYAxis = tmp;
}

/*
populates the Z axis by:
-	starting off the same as the X axis
-	cut it in half
-	swap the two halves
-	run through swapping every two letters

*/
void HamiltonianCipher::scrambleZAxis()
{
	string tmp = mZAxis;

	// cut the axis in half and swap the two halves
	for (size_t i = 0; i < mZAxis.length() / 2; i++)
	{
		int j = i + (mZAxis.length() / 2);
		if (j < (int)mZAxis.length())
		{
			char tmpC = tmp[i];
			tmp[i] = tmp[j];
			tmp[j] = tmpC;
		}
	}

	// run through again swapping every two letters
	for (size_t i = 0; i < mZAxis.length(); i += 2)
	{
		if (i < tmp.length() - 1)
		{
			char tmpC = tmp[i];
			tmp[i] = tmp[i + 1];
			tmp[i + 1] = tmpC;
		}
	}

	mZAxis = tmp;
}

// set all the letters in the specified string to the specified case
string HamiltonianCipher::setCase(string s, char sCase)
{
	stringstream ss;
	switch (sCase)
	{
	case 'l':
	case 'L':
		for (size_t i = 0; i < s.length(); i++)
			ss << tolower(s[i]);

	case 'u':
	case 'U':
		for (size_t i = 0; i < s.length(); i++)
			ss << toupper(s[i]);
		break;
		break;

	}
	return ss.str();
}

// take a string input and output the same string without any spaces
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

void HamiltonianCipher::update()
{
	if (mIsEncrypt)
		encrypt();
	else
		decrypt();
}

HamiltonianCipher::~HamiltonianCipher()
{}
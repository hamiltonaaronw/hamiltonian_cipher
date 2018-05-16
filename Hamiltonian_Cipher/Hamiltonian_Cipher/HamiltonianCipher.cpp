/*

Author: Aaron William Hamilton

*/

#include "HamiltonianCipher.h"

HamiltonianCipher::HamiltonianCipher(int crypt, int input)
	:mCrypt(crypt),
	mInputMethod(input)
{}

// output axis information
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

/*
Decrypt a message by:
-	making sure the length of the message being decrypted
	fits the %3 requirement
-	divvie up padded ciphertext into trigrams
-	decrypt each trigram by:
	+	find position of each letter of the trigram in the full alphabet
	+	decrypt 1st trigram letter by:
		#	finding the element on the X Axis at the 
			third letter's alphabet position
	+	decrypt 2nd trigram letter by:
		#	finding the element on the Y Axis at the
			first letter's alphabet position
	+	decrypt 3rd trigram letter by:
		#	finding the element on the Z Axis at the
			second letter's alphabet position
*/
void HamiltonianCipher::decrypt()
{
	// strip spaces from ciphertext
	string cText = setCase(stripSpaces(mCiphertextOrig), 'l');
	cout << "decrypt() line 51 stripped lower case ciphertext: " << cText << endl;
	
	string alphabet = getAlphabet();

	stringstream ssPlain;
	int textLength = (int)cText.length();

	// pad ciphertext to fit %3 length requirement
	stringstream ssPaddedCiphertext;
	while (textLength % 3 != 0)
		textLength++;
	// go through initial ciphertext
	for (int i = 0; i < textLength; i++)
	{
		// if i is greater than padded textlength - 2
		if (i > textLength - 2)
		{
			// pad ciphertext stringstream with an x if 
			// i is greater thant the ciphertext length
			if (i > (int)cText.length())
				ssPaddedCiphertext << 'x';
			else // populate it with the current ciphertext letter otherwise
				ssPaddedCiphertext << cText[i];
		}
		else // populate it with the current ciphertext letter otherwise
			ssPaddedCiphertext << cText[i];
	}

	// reset cText to new padded ciphertext
	// and textlength to length of new cText
	cText = ssPaddedCiphertext.str();
	textLength = cText.length();

	// divvie up ciphertext into trigrams
	vector<string> trigrams;
	// go through cText in increments of 3
	for (int i = 0; i < textLength; i += 3)
	{
		char c0 = cText[i],
			c1 = (cText[i + 1] != NULL) ? cText[i + 1] : 'x', // double checking to make sure the
			c2 = (cText[i + 2] != NULL) ? cText[i + 2] : 'x'; // letters in the trigram are valid

		stringstream ss;
		// create string from the three letters
		ss << c0 << c1 << c2;
		// add string to trigram vector
		trigrams.push_back(ss.str());
	}

	// encrypt each trigram
	// run through the trigrams vector
	for (size_t i = 0; i < trigrams.size(); i++)
	{
		string t = trigrams[i];

		// position of each letter of the trigram in the full alphabet
		int xLetterPos = alphabet.find(t[0]),
			yLetterPos = alphabet.find(t[1]),
			zLetterPos = alphabet.find(t[2]);

		// plaintext decryption position of each letter of the trigram
		char p0 = mXAxis.at(zLetterPos),
			p1 = mYAxis.at(xLetterPos),
			p2 = mZAxis.at(yLetterPos);

		// add decrypted characters to the plaintext stringstream
		ssPlain << p0 << p1 << p2;
	}

	trigrams.clear();
	// set the decrypted plaintext to the final stringstream
	setPlaintextDecrypted(setCase(ssPlain.str(), 'l'));

	// ***TO-DO: output decrypted message to a file
}

/*
Encrypt a message by:
-	making sure the length of the message being encrypted
	fits the %3 requirement
-	divvie up padded plaintext into trigrams
-	encrypt each trigram by:
	+	finding the index element of each trigram on the succeeding axes
	+	encrypt 1st trigram letter by:
		#	finding the index first trigram letter on the Y Axis
		#	find the element at that index on the full alphabet
	+	encrypt 2nd trigram letter by:
		#	finding the index of second trigram letter on the Z Axis
		#	find element at that index on the full alphabet
	+	encrypt 3rd trigram letter by:
		#	finding the index of third trigram letter on the X Axis
		#	find element at that index on the full alphabet
*/
void HamiltonianCipher::encrypt()
{
	// strip spaces from plaintext
	string pText = setCase(stripSpaces(getPlaintextOrig()), 'l');
	
	string alphabet = getAlphabet();

	stringstream ssCipher;
	int textLength = pText.length();

	// pad plaintext to fit %3 length requirement
	while (textLength % 3 != 0)
		textLength++;
	stringstream ssPaddedPlaintext;
	// go through initial plaintext
	for (int i = 0; i < textLength; i++)
	{
		// if i is greater than padded textlength - 2
		if (i > textLength - 2)
		{
			// pad plaintext stringstream with an x if 
			// i is greater thant the plaintext length
			if (i > (int)pText.length())
				ssPaddedPlaintext << 'x';
			else // populate it with the current plaintext letter otherwise
				ssPaddedPlaintext << pText[i];
		}
		else // populate it with the current plaintext letter otherwise
			ssPaddedPlaintext << pText[i];
	}

	// reset pText to new padded plaintext
	// and reset textLength to new pText length
	pText = ssPaddedPlaintext.str();

	// divvie up plaintext into trigrams
	vector<string> trigrams;
	// run through padded plaintext in increments of 3
	for (int i = 0; i < textLength; i += 3)
	{
		char p0 = pText[i],
			p1 = (pText[i + 1] != NULL) ? pText[i + 1] : 'x',	// double check that the trigram
			p2 = (pText[i + 2] != NULL) ? pText[i + 2] : 'x';	// contains valid elements
	
		stringstream ss;
		// add characters to a string of length three
		ss << p0 << p1 << p2;
		// add new trigram to the vector
		trigrams.push_back(ss.str());
	}

	// encrypt each trigram
	// run through the trigram vector
	for (size_t i = 0; i < trigrams.size(); i++)
	{
		// current trigram
		string t = trigrams[i];
	
		// indices of each letter on their respective axes
		int xLetterPos = mXAxis.find(t[0]),
			yLetterPos = mYAxis.find(t[1]),
			zLetterPos = mZAxis.find(t[2]);

		// ciphertext letters
		// each letter encrypts to the element at its index on the succeeding axis
		// on the full alphabet
		char c0 = alphabet.at(yLetterPos),
			c1 = alphabet.at(zLetterPos),
			c2 = alphabet.at(xLetterPos);

		// add new ciphertext letters to the ciphertext stringstream
		ssCipher << c0 << c1 << c2 << " ";
	}

	// clear trigrams vector
	trigrams.clear();

	// set the encrypted ciphertext to the new string
	setCiphertextEncrypted(setCase(ssCipher.str(), 'u'));

	// ****TO-DO: output to a file
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
	setCiphertext(ciphertext);
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
	// ****TODO:	read in file from file path
	//				get key and ciphertext or plaintext
	//				from the file
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
	setPlaintext(plaintext);
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
	string alphabet = "abcdefghijklmnopqrstuvwxyz";			// letters
	string numbers = "0123456789";							// numbers
	string ascii = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";	// ASCII characters
	// add them all to the same stringstream
	ss << alphabet << numbers << ascii;		
	// set full alphabet to the new string
	setAlphabet(ss.str());						
}

// strips spaces and repeats from the key
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
populates axes by
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
	string key = populateAxisWithKey();

	stringstream ssAxis;
	ssAxis << key;
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
	switch (sCase)
	{
	case 'l':
	case 'L':
		for (size_t i = 0; i < s.length(); i++)
			s[i] = tolower(s[i]);
		break;

	case 'u':
	case 'U':
		for (size_t i = 0; i < s.length(); i++)
			s[i] = toupper(s[i]);
		break;

	}
	return s;
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
	{
		encrypt();
		cout << endl << endl << "Key: " << getKey() << endl;
		cout << "Plaintext: " << getPlaintextOrig() << endl;
		cout << "Ciphertext: " << getCiphertextEncrypted() << endl;
	}
	else
	{
		decrypt();
		cout << endl << endl << "Key: " << getKey() << endl;
		cout << "Ciphertext: " << getCiphertextOrig() << endl;
		cout << "Plaintext: " << getPlaintextDecrypted() << endl;
	}
}

HamiltonianCipher::~HamiltonianCipher()
{}
/*

Author: Aaron William Hamilton

*/

#include "HamiltonianCipher.h"

void intro();
int encryptOrDecrypt();
int inputOrFile();

int main()
{
	intro();
	int crypt = encryptOrDecrypt(),
		input = inputOrFile();

	HamiltonianCipher *pCipher = new HamiltonianCipher(crypt, /*input*/ 1);

	pCipher->init();
	pCipher->debug();
	pCipher->update();

	delete pCipher;
	pCipher = NULL;

	cin.get();
	cin.get();
}

void intro()
{
	cout << "******************************************************************" << endl;
	cout << "* WELCOME TO MY HAMILTONIAN CIPHER ENCRYPTION/DECRYPTION PROGRAM *" << endl;
	cout << "******************************************************************" << endl;
}

int encryptOrDecrypt()
{
	int sel;
	cout << "Would you like to" << endl
		<< "1) Encrypt" << endl
		<< "2) Decrypt" << endl
		<< "Selection: ";
	cin >> sel;
	cout << endl;
	return sel;
}

int inputOrFile()
{
	int sel;
	cout << "Would you like to" << endl
		<< "1) Input key and text manually" << endl
		<< "2) Read in key and text from file" << endl
		<< "Selection: ";
	cin >> sel;
	cin.get();
	cout << endl;
	return sel;
}
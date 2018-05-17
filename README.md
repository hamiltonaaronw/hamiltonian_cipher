# Hamiltonian Cipher

## What it is
The *Hamiltonian Cipher* is an original **polyalphanumeric block substitution cipher** I developed. It is a 3-Dimensional variation of the *Playfair Cipher*. The *Playfair Cipher* is a polyalphabetic block substitution cipher with a keyspace of **25!**, which is **~1.5 * 10^25**, or **15 septillion** possible keys. The *Hamiltonian Cipher* has a keyspace of **68!**, which is **~2 * 10^96**, or **2 untrigintillion** possible keys.

## How the cipher works
In order to encrypt or decrypt messages using the Hamiltonian Cipher, you first need a keyword, like most other substitution ciphers. The cipher populates three axes, and scrambles them differently. 
### The alphabet
Instead of just the regular 26 letter alphabet, the *Hamiltonian Cipher* utilizes numbers and ASCII characters as well.

** **Note** The order of the ASCII characters is based on their order on the ASCII table
### The axes
The **X-Axis** is populated the same as a Playfair grid: begin with the keyword without repeating any letters, and once the keyword is used up, fill begin filling in the rest of the alphabet without repeating any letters, then numbers without repeating any numbers, and finally ASCII characters without repeating any characters. 

The **Y-Axis** is the reverse of the **X-Axis**

The **Z-Axis** is populated the same as the **X-Axis**, however it is cut in half, and the two halves are swapped. Then it is ran through once more, swapping every two letters.

### Encryption
To encrypt a message using the *Hamiltonian Cipher*, the plaintext is separated into *trigrams* (blocks of three letters), padding the very last one if needed (encryption will not work with grams of less than 3 letters).

**To encrypt the first letter** of the trigram, you find the index of that letter on the **Y-Axis**, and the encryption of that letter is the element at the aforementioned index on the full alphabet.

**To encrypt the second letter** of the trigram, you find the index of that letter on the **Z-Axis**, and the encryption of that letter is the element at the aforementioned index on the full alphabet.

**To encrypt the third letter** of the trigram, you find the index of that letter on the **X-Axis**, and the encryption of that letter is the element at the aforementioned index on the full alphabet.

### Decryption
Much like any substitution cipher, the decryption is simply the reverse of the encryption. 

**To decrypt the first letter** of the trigram, find the index of the third letter of the trigram on the full alphabet, and the decryption is the element at that position on the **X-Axis**

**To decrypt the second letter** of the trigram, find the index of the first letter of the trigram on the full alphabet, and the decryption is the element at that position on the **Y-Axis**

**To decrypt the third letter** of the trigram, find the index of the second letter of the trigram on the full alphabet, and the decryption is the element at that position on the **Z-Axis**

## How the program works
The program will prompt the user to select whether you would like to encrypt or decrypt a message. After the user has made a selection, the program will then prompt the user to select their input method: either manually input the key and plaintext or ciphertext right in the console, or to read it all in from a file. 

If the user has selected manual input, the program will the prompt the user for the key, then the plaintext (if encrypting) or the ciphertext (if decrypting). The program will then display each axis, as well as the key, then the plaintext and then the ciphertext (if encrypting), or the ciphertext and then the plaintext (if decrypting).

If the user has selected file input (recommended for longer messages), then the program will not need to prompt the user for any input, and will go straight to displaying all of the aforementioned information, as well as outputting the encryption or decryption to the file it initially read the information from.

#### Important note
If the user chooses to have the key and plaintext/ciphertext read in from a file, the file must contain the information in the following format:

*key*

*empty line*

*message to be encrypted or decrypted........*

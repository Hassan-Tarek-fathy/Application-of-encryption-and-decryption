using namespace std;
#include<iostream>
#include<string>
#include<math.h>
#include<cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>
/////////////////////////////////*1-caeser algorithm *//////////////////////////////////////////

string caesar_encrypt(const string& text, int key)
{
	string encryptedtext = "";
	char c;

	for (int i = 0; i < text.size(); i++)
	{
		c = text[i];
		if (isalpha(c))
		{
			char base = islower(c) ? 'a' : 'A';
			encryptedtext += static_cast<char>((c - base + key) % 26 + base);

		}
		else {
			encryptedtext += c;

		}

	}
	return encryptedtext;


}

string caesar_decrypt(const string& text, int key)
{
	string decryptedtext = "";
	char c;

	for (int i = 0; i < text.size(); i++)
	{
		c = text[i];
		if (isalpha(c))
		{
			char base = islower(c) ? 'a' : 'A';
			decryptedtext += static_cast<char>((c - base - key + 26) % 26 + base);

		}
		else {
			decryptedtext += c;

		}

	}
	return decryptedtext;


}
////////////////////////////////////////2-monoalphabitc algorithm////////////////////////////////////////////////////

string map(const string& key) {
	string newkey = "";
	char ch;
	for (int i = 0;i < key.size();i++) {
		ch = key[i];
		if (isalpha(ch)) {
			char upperCh = toupper(ch);
			if (newkey.find(upperCh) == -1) {
				newkey += upperCh;
			}
		}
	}
	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		if (newkey.find(ch) == -1) {
			newkey += ch;
		}
	}
	return newkey;
}
string monoalphabetic_encrypt(const string& plaintext, const string& key) {
	string ciphertext = "";
	char ch;

	for (int i = 0;i < plaintext.size();i++)
	{
		ch = plaintext[i];

		if (isalpha(ch)) {
			char upperCh = toupper(ch);
			int index = upperCh - 'A';
			ciphertext += key[index];
		}
		else {
			ciphertext += ch;
		}
	}
	return ciphertext;
}

string monoalphabetic_decrypt(const string& ciphertext, const string& key) {
	string plaintext = "";
	char ch;
	for (int i = 0;i < ciphertext.size();i++)
	{
		ch = ciphertext[i];
		if (isalpha(ch)) {
			char upperCh = toupper(ch);
			int index = key.find(upperCh);
			plaintext += isupper(ch) ? 'A' + index : 'a' + index;
		}
		else {
			plaintext += ch;
		}
	}
	return plaintext;
}
////////////////////////////////////////3-playfair algorithm////////////////////////////////////////////////////


void FindPosition(char keySquare[][5], char ch, int* row, int* col) {
	*row = *col = 0;
	if (ch == 'J')
		ch = 'I';
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (keySquare[i][j] == ch) {
				*row = i;
				*col = j;
				return;
			}
		}
	}
}
string ToUpper(string str) {
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

void Mapinng(string key, char keySquare[][5]) {
	string defaultAlphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	key = ToUpper(key);
	vector<char> uniqueKey;
	for (char item : key) {
		if (find(uniqueKey.begin(), uniqueKey.end(), item) == uniqueKey.end())
			uniqueKey.push_back(item);
	}

	int c = 0;
	for (char item : uniqueKey) {
		defaultAlphabet.insert(c++, 1, item);
	}

	vector<char> newDistinctUpperAlphabetic;
	for (char ch : defaultAlphabet) {
		if (find(newDistinctUpperAlphabetic.begin(), newDistinctUpperAlphabetic.end(), ch) == newDistinctUpperAlphabetic.end())
			newDistinctUpperAlphabetic.push_back(ch);
	}

	int n = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			keySquare[i][j] = newDistinctUpperAlphabetic[n++];
		}
	}
}


string RemoveX(string str) {
	str.erase(remove(str.begin(), str.end(), 'X'), str.end());
	return str;
}
string  playfair_Encrypt(string key, string plaintext) {
	char keySquare[5][5];
	Mapinng(key, keySquare);
	plaintext = ToUpper(plaintext);
	string ciphertext = "";
	for (size_t i = 0; i < plaintext.length(); i += 2) {
		char firstChar = plaintext[i];

		char secondChar;
		if (i + 1 < plaintext.length()) {
			secondChar = plaintext[i + 1];
			if (secondChar == firstChar) {
				secondChar = 'X';
				i--;
			}
		}
		else {
			secondChar = 'X';
		}

		int row1, col1, row2, col2;
		FindPosition(keySquare, firstChar, &row1, &col1);
		FindPosition(keySquare, secondChar, &row2, &col2);

		if (row1 == row2) {
			ciphertext += keySquare[row1][(col1 + 1) % 5];
			ciphertext += keySquare[row2][(col2 + 1) % 5];
		}
		else if (col1 == col2) {
			ciphertext += keySquare[(row1 + 1) % 5][col1];
			ciphertext += keySquare[(row2 + 1) % 5][col2];
		}
		else {
			ciphertext += keySquare[row1][col2];
			ciphertext += keySquare[row2][col1];
		}
	}
	return ciphertext;
}
string playfair_Decrypt(string key, string ciphertext) {
	char keySquare[5][5];
	Mapinng(key, keySquare);
	ciphertext = ToUpper(ciphertext);
	string plaintext = "";
	for (size_t i = 0; i < ciphertext.length(); i += 2) {
		char firstChar = ciphertext[i];
		char secondChar = ciphertext[i + 1];

		int row1, col1, row2, col2;
		FindPosition(keySquare, firstChar, &row1, &col1);
		FindPosition(keySquare, secondChar, &row2, &col2);

		if (row1 == row2) {
			plaintext += keySquare[row1][(col1 - 1 + 5) % 5];
			plaintext += keySquare[row2][(col2 - 1 + 5) % 5];
		}
		else if (col1 == col2) {
			plaintext += keySquare[(row1 - 1 + 5) % 5][col1];
			plaintext += keySquare[(row2 - 1 + 5) % 5][col2];
		}
		else {
			plaintext += keySquare[row1][col2];
			plaintext += keySquare[row2][col1];
		}
	}
	return RemoveX(plaintext);
}

////////////////////////////////////////4-hill algorithm////////////////////////////////////////////////////


double Determinant(double matrix[][3]) {
	return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
		matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
		matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

void CheckNegativity(double matrix[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] < 0) {
				matrix[i][j] += 26;
			}
		}
	}
}
vector<int> MultiplyMatrices(double matrixA[], double matrixB[][3]) {
	int colsA = 3;
	int rowsB = 3;
	int colsB = 3;
	if (colsA != rowsB) {
		throw invalid_argument("Number of columns in Matrix A must be equal to the number of rows in Matrix B for matrix multiplication.");
	}

	vector<int> resultMatrix(colsB);

	for (int j = 0; j < colsB; j++) {
		int sum = 0;
		for (int k = 0; k < colsA; k++) {
			sum += static_cast<int>(matrixA[k] * matrixB[k][j]);
		}
		resultMatrix[j] = sum;
	}

	return resultMatrix;
}

void InvertMatrix(double matrix[][3], double invertedMatrix[][3]) {
	double det = (int)Determinant(matrix) % 26;

	if (det < 0)
		det += 26;

	det = 17;

	if (det == 0) {
		throw invalid_argument("Matrix is singular and cannot be inverted.");
	}
	invertedMatrix[0][0] = ((int)(((matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])) * det) % 26);
	invertedMatrix[0][1] = ((int)(((matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2])) * det) % 26);
	invertedMatrix[0][2] = ((int)(((matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1])) * det) % 26);
	invertedMatrix[1][0] = ((int)(((matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2])) * det) % 26);
	invertedMatrix[1][1] = ((int)(((matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0])) * det) % 26);
	invertedMatrix[1][2] = ((int)(((matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2])) * det) % 26);
	invertedMatrix[2][0] = ((int)(((matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) * det) % 26);
	invertedMatrix[2][1] = ((int)(((matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1])) * det) % 26);
	invertedMatrix[2][2] = ((int)(((matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0])) * det) % 26);

	CheckNegativity(invertedMatrix);
}


string Encrypt(double key[][3], const string& plainText) {
	string upperAlphabetic = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int plaintextLength = plainText.length();
	int rows = 3;
	string plainTextUpper = plainText;
	for (char& c : plainTextUpper) {
		c = toupper(c);
	}

	vector<int> plainTextIndexArray;
	for (char item : plainTextUpper) {
		int newCharIndex = (upperAlphabetic.find(item)) % 26;
		if (newCharIndex < 0)
			newCharIndex += 26;
		plainTextIndexArray.push_back(newCharIndex);
	}

	string cipherText;
	vector<int> newCharIndexs;
	for (int i = 0; i < plaintextLength; i += 3) {
		double matrixA[3];
		for (int j = 0; j < 3; ++j) {
			matrixA[j] = static_cast<double>(plainTextIndexArray[i + j]);
		}
		newCharIndexs = MultiplyMatrices(matrixA, key);

		for (int newCharIndex : newCharIndexs) {
			cipherText += upperAlphabetic[newCharIndex % 26];
		}
	}

	return cipherText;
}

string Decrypt(double key[][3], const string& cipherText) {
	double invertedKey[3][3];
	InvertMatrix(key, invertedKey);
	return Encrypt(invertedKey, cipherText);
}
////////////////////////////////////////5-vigenere algorithm////////////////////////////////////////////////////
string veencrypt(string text, string key)
{
	string encrypted = "";
	char c;
	int keyIndex = 0;
	for (int i = 0; i < text.size(); ++i)
	{
		int c = text[i];
		if (isalpha(c))
		{
			char shift = isupper(key[keyIndex]) ? 'A' : 'a';
			int keyChar = key[keyIndex] - shift;
			encrypted += (c + keyChar - shift) % 26 + shift;
			keyIndex = (keyIndex + 1) % key.length();
		}

		else
		{
			encrypted += c;
		}
	}
	return encrypted;
}

string vedecrypt(string text, string key) {
	string decrypted = "";
	int keyIndex = 0;
	char c;
	for (int i = 0; i < text.length(); ++i)
	{
		c = text[i];
		if (isalpha(c))
		{
			char shift = isupper(key[keyIndex]) ? 'A' : 'a';
			int keyChar = key[keyIndex] - shift;
			decrypted += (c - shift - keyChar + 26) % 26 + shift;
			keyIndex = (keyIndex + 1) % key.length();
		}
		else {
			decrypted += c;
		}
	}
	return decrypted;
}


////////////////////////////////////////6-Autokey algorithm////////////////////////////////////////////////////
string autokey_Encrypt(const string& plaintext, string& key) {
	string completedKey = key;
	int keyIndex = 0;


	for (int i = key.length(); i < plaintext.length(); ++i) {
		completedKey += toupper(plaintext[i - key.length()]);
	}

	string encrypted = "";
	char det;

	for (int i = 0; i < plaintext.size(); ++i) {
		char c = plaintext[i];
		if (isalpha(c))
		{
			det = isupper(completedKey[keyIndex]) ? 'A' : 'a';
			int keyChar = completedKey[keyIndex] - det;
			encrypted += (c + keyChar - det) % 26 + det;
			keyIndex = (keyIndex + 1) % key.length();
		}
		else {
			encrypted += c;
		}
	}
	return encrypted;
}
string autokey_Decrypt(string ciphertext, string& key) {
	string decrypted = "";
	char det;
	int keyIndex = 0;
	char c;
	for (int i = 0; i < ciphertext.length(); ++i)
	{
		c = ciphertext[i];
		if (isalpha(c))
		{
			det = isupper(key[keyIndex]) ? 'A' : 'a';
			int keyChar = key[keyIndex] - det;
			decrypted += (c - det - keyChar + 26) % 26 + det;
			keyIndex = (keyIndex + 1) % key.length();

		}
		else {
			decrypted += c;
		}
	}
	return decrypted;
}
////////////////////////////////////////7-railfence algorithm//////////////////////////////////////////////////// 
string  railfence(string  plaintext, int key)
{
	int l = plaintext.length();
	int rows = key;
	int index = 0;
	int col;

	if (l % key != 0)
		col = (l / key) + 1;
	else
		col = l / key;



	char  mat[10][10];

	for (int i = 0;i < col;i++)
	{
		for (int j = 0;j < rows;j++)
		{
			mat[j][i] = plaintext[index++];


		}
	}

	string ciphertext;
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < col;j++)
		{
			ciphertext += mat[i][j];


		}
	}
	return ciphertext;



}
string decryptRailfence(const string& ciphertext, int key) {
	int l = ciphertext.length();
	int rows = key;
	int col;
	if (l % key != 0)
		col = (l / key) + 1;
	else
		col = l / key;


	char mat[6][10];


	int index = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < col; j++)
		{
			mat[i][j] = (index < l) ? ciphertext[index++] : ' ';
		}
	}


	string originalText;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < rows; j++) {
			if (mat[j][i] != ' ')
			{
				originalText += mat[j][i];
			}
		}
	}
	return originalText;
}
//////////////////////////////main//////////////////////////////////////////////////////////////////////////////////////////////// 
int main()
{
	cout << "welcome in our APP" << endl;
	cout << "" << endl;


	int choice1;
	int choice;


	do {
		cout << "    " << "Choose the  algorithm:" << endl;
		cout << "" << endl;
		cout << "    " << "1. Caesar " << endl;
		cout << "" << endl;
		cout << "    " << "2. Monoalphabetic " << endl;
		cout << "" << endl;
		cout << "    " << "3. Playfair " << endl;
		cout << "" << endl;
		cout << "    " << "4. Hill " << endl;
		cout << "" << endl;
		cout << "    " << "5. Vigenere " << endl;
		cout << "" << endl;
		cout << "    " << "6. Autokey " << endl;
		cout << "" << endl;
		cout << "    " << "7. Railfence " << endl;
		cout << "" << endl;
		cout << "    " << "8. Exit" << endl;
		cout << "" << endl;
		cout << "    " << "Enter number of algorithm you want to use: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			// Caesar Cipher
			string text, encryptedText, decryptedText;
			int key;
			cout << "   Enter the text: ";
			cin >> text;
			cout << "    Enter the key: ";
			cin >> key;
			cout << "enter 1 to encrypt and 2 to decrypt \n" << endl;

			cin >> choice1;
			




			switch (choice1)
			{
			case 1:
			{

				encryptedText = caesar_encrypt(text, key);
				cout << " -------------------------->  " << "Encrypted text: " << encryptedText << endl;
				break;

			}
			case 2:
			{
				decryptedText = caesar_decrypt(text, key);
				cout << " -------------------------->  " << "Decrypted text: " << decryptedText << endl;
				break;

			}
			}



			break;
		}
		case 2:
		{
			// Monoalphabetic Cipher

			string text, key, encryptedText, decryptedText;
			cout << "    Enter the text: ";
			cin >> text;
			cout << "    Enter the key: ";
			cin >> key;
			cout << "enter 1 to encrypt and 2 to decrypt";

			cin >> choice1;

			switch (choice1)
			{
			case 1:
			{
				encryptedText = monoalphabetic_encrypt(text, map(key));
				cout << " -------------------------->" << "Encrypted text: " << encryptedText << endl;
				break;
			}
			case 2:
			{
				decryptedText = monoalphabetic_decrypt(text, map(key));
				cout << " -------------------------->  " << "Decrypted text: " << decryptedText << endl;
				break;
			}
			

			}

			break;


		}
	

		case 3: {
			// Playfair Cipher

			string key;
			cout << "    Enter Key" << endl;
			cin >> key;

			string plaintext;
			cout << "    Enter  text" << endl;
			cin >> plaintext;
			cout << "enter 1 to encrypt and 2 to decrypt  " << endl;

			cin >> choice1;

			switch (choice1)
			{
			case 1:
			{
				string encrypted = playfair_Encrypt(key, plaintext);
				cout << " -------------------------->  " << "Encrypted: " << encrypted << endl;
				break;
			}
			case 2:
			{

				string decrypted = playfair_Decrypt(key, plaintext);
				cout << " -------------------------->  " << "Decrypted: " << decrypted << endl;
				break;
			}

			}
			break;


		}
		case 4:
		{
			//hill
			string plainText;
			cout << "    Enter text: ";
			cin >> plainText;
			double key[3][3];
			cout << "    Enter the 3x3 key matrix values: " << endl;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					cout << "   Enter value at position " << i << ", " << j << ": ";
					cin >> key[i][j];
				}
			}
			cout << "enter 1 to encrypt and 2 to decrypt" << endl;

			cin >> choice1;

			switch (choice1)
			{
			case 1:
			{
				string cipherText = Encrypt(key, plainText);
				cout << " -------------------------->  " << "Cipher Text: " << cipherText << endl;
				break;

			}
			case 2:
			{
				string decryptedText = Decrypt(key, plainText);
				cout << " -------------------------->  " << "Decrypted Text: " << decryptedText << endl;
				break;
			}
			}

			break;

		}
		case 5:
		{
			// Vigenere Cipher
			string text, key, encryptedText, decryptedText;
			cout << "    Enter the text: ";
			cin.ignore();
			getline(cin, text);
			cout << "    Enter the key: ";
			getline(cin, key);
			cout << "enter 1 to encrypt and 2 to decrypt" << endl;

			cin >> choice1;

			switch (choice1)
			{
			case 1:
			{
				encryptedText = veencrypt(text, key);
				cout << " -------------------------->  " << "Encrypted text: " << encryptedText << endl;
				break;
			}
			case 2:
			{
				decryptedText = vedecrypt(text, key);
				cout << " -------------------------->  " << "Decrypted text: " << decryptedText << endl;
				break;
			}

			}


			break;


		}

		case 6:
		{

			string plaintext, key;
			cin.ignore();
			cout << "    Enter text: ";
			getline(cin, plaintext);
			cout << "    Enter key: ";
			getline(cin, key);
			cout << "enter 1 to encrypt and 2 to decrypt" << endl;

			cin >> choice1;

			switch (choice1)
			{
			case 1:
			{
				string ciphertext = autokey_Encrypt(plaintext, key);
				cout << " -------------------------->  " << "Ciphertext: " << ciphertext << endl;
				break;
			}
			case 2:
			{
				string decryptedText = autokey_Decrypt(plaintext, key);
				cout << " -------------------------->  " << "Decrypted text: " << decryptedText << endl;
				break;
			}
			}

			break;


		}
		case 7:
		{

			// Railfence Cipher
			string plaintext, ciphertext;
			int key1;
			cout << "    Enter the text: ";
			cin.ignore();
			getline(cin, plaintext);
			cout << "    Enter the key: ";
			cin >> key1;
			cout << "enter 1 to encrypt and 2 to decrypt "<< endl;

			cin >> choice1;

			switch (choice1)
			{
			case 1:
			{
				ciphertext = railfence(plaintext, key1);
				cout << " -------------------------->  " << "Encrypted text: " << ciphertext << endl;
				break;
			}
			case 2:
			{
				cout << " -------------------------->  " << "Decrypted text: " << decryptRailfence(plaintext, key1) << endl;
				break;
			}

			}

			break;


		}


		case 8:
		{
			cout << "Exiting..." << endl;
			break;
		}
		default:
		{
			cout << " -------------------------->  " << "Invalid choice. Please try again." << endl;
		}
		}

	}

	 while (choice != 8);
	
	return 0;
}


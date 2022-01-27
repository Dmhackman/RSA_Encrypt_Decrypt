// Name: Derek Hackman
// Partner Name: Ben Abbott
// Class: Network Security
// Assignment: Project 2 - RSA encryption/decryption
// Description: This program will perform RSA encryption and decrytion.
// It can deal with "large" exponents, using the techinques discussed in class
//--------------------------------------------------------------------------------------------------------------------------


#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <sstream> 

using namespace std;

string Encryption(unsigned long long int e, unsigned long long int n, string message);
void convertText(string& text, int nums[]);
int decToBinary(unsigned long long int x, int binaryNum[]);
string removeSpaces(string str);
int digitsOfN(unsigned long long int n);
unsigned long long int FastModArithmetic(unsigned long long int num, unsigned long long int exp, unsigned long long int n);
string Decryption(unsigned long long int d, unsigned long long int n, string ciphertext);
void convertNums2(string& text, string digits);


int main() {

    unsigned long long int d, e, n; 
    string message, ciphertext;
    int choice = 0;
    

    while (choice == 0 || choice == 1)
    {   
        //Gets choice from user to encrypt or decrypt
        cout << "Would you like to encrypt or decrypt?" << endl
        << "Enter 0 to encrypt, enter 1 to decrypt, any other number to end program: ";
        cin >> choice;
        string output = "";


        if (choice == 0)
        {
            cout << "Enter value for e: ";
            cin >> e;
            cout << "Enter value for n: ";
            cin >> n;
            cout << "Enter the message to be encrypted (as words and letters): ";
            cin.ignore();
            getline(cin, message, '\n');

            output = Encryption(e, n, message);

        }
        else if (choice == 1)
        {
            cout << "Enter value for d: ";
            cin >> d;
            cout << "Enter value for n: ";
            cin >> n;
            cout << "Enter the ciphertext to be decrypted (as numbers): ";
            cin.ignore();
            getline(cin, ciphertext, '\n');

            output = Decryption(d, n, ciphertext);

        }

        cout << endl;
    }


    return 0;
}

string Encryption(unsigned long long int e, unsigned long long int n, string message)
{
    int nums[250] = { 0 };
    convertText(message, nums);

    int len = message.length();
    int blocks, digitsN, chunkSz;

    digitsN = digitsOfN(n);

    if (digitsN % 3 == 0)
    {
        chunkSz = digitsN / 3 - 1;
    }
    else
    {
        chunkSz = digitsN / 3;
    }

    if (len % chunkSz == 0)
    {
        blocks = len / chunkSz;
    }
    else
    {
        blocks = len / chunkSz + 1;
    }
    //cout << digitsN << ' ' << blocks << ' ' << chunkSz;

    int cText[250];

    for (int i = 0; i < blocks; i++)
    {
        int inNum = 0;
        int k = chunkSz - 1; 
        int power; 
        for (int j = 0; j < chunkSz; j++)
        {
            //cout << chunkSz << ' ' << j << ' ' << i << endl;

            inNum += nums[i * chunkSz + j];
            //    (k * 1000); // this needs to be 1000 ^ j
            power = (int)(pow(1000, k));

            inNum = inNum * power; 

            k--; 
        }

        //cout << endl << inNum << ' ';

        int cipher;

        cipher = FastModArithmetic(inNum, e, n);

        //cout << cipher << ' ';
        cText[i] = cipher;
        
    }

    string digits = "";
    string work;
    for (int i = 0; i < blocks; i++)
    {
        int digs = 0;

        digs = digitsOfN(cText[i]);

        while (digs < digitsN)
        {
            cout << "0";
            digits += "0";
            digs++;
        }
        cout << cText[i] << ' ';

        work = to_string(cText[i]);

        digits += work;

    }

    return digits;
}

string Decryption(unsigned long long int d, unsigned long long int n, string ciphertext)
{
    int nums[250] = { 0 };

    ciphertext = removeSpaces(ciphertext);

    int len = ciphertext.length();
    int blocks, digitsN, chunkSz;

    digitsN = digitsOfN(n);

    chunkSz = digitsN;

    if (len % chunkSz == 0)
    {
        blocks = len / chunkSz;
    }
    else
    {
        blocks = len / chunkSz + 1;
    }

    string subNum;

    int cText[250];

    for (int i = 0; i < blocks; i++)
    {
        
        if ((digitsN * i) <= len && digitsN <= len)
        {
            subNum = ciphertext.substr(i * digitsN, digitsN);
            //cout << subNum << ' ';
        }

        stringstream number(subNum);
        
        number >> nums[i];
            //= stoi(subNum);

        //cout << nums[i] << endl;

        int cipher;

        cipher = FastModArithmetic(nums[i], d, n);

        cText[i] = cipher;

    }

    if (digitsN % 3 == 0)
    {
        chunkSz = digitsN / 3 - 1;
    }
    else
    {
        chunkSz = digitsN / 3;
    }

    string digits = "";
    string work;

    for (int i = 0; i < blocks; i++)
    {
        int digs = 0;

        digs = digitsOfN(cText[i]);


        while (digs < (chunkSz * 3))
        {

            cout << "0";
            digits += "0";

            digs++;
        }
        cout << cText[i] << ' ';
        work = to_string(cText[i]);

        digits += work; 

    }
    //cout << digits; 
    string outputText;

    convertNums2(outputText, digits);
    cout << endl << "Numbers Converted to plaintext: " << endl << outputText << endl;

    return outputText;

}

void convertNums2(string& text, string digits)
{
    text = "";
    int a;
    int num;
    int len = digits.length();
    
    num = len / 3;
    string subNum;
    int asc;
        
    for (int i = 0; i < num; i++)
    {
        
        subNum = digits.substr(i * 3, 3);

        asc = stoi(subNum);
        text += asc;
        //text += b;
        //text += c + ' ';

    }
}

unsigned long long int FastModArithmetic(unsigned long long int num, unsigned long long int exp, unsigned long long int n)
{
    int binaryNum[64];
    unsigned long long int answer = num;

    int startP;
    startP = decToBinary(exp, binaryNum);

    for (int j = startP - 2; j >= 0; j--)
    {
        
        if (binaryNum[j] == 1)
        {
            answer = (answer * answer) % n;
            answer = (answer * num) % n;
          
        }
        else
        {
            answer = (answer * answer) % n;
        }
        //cout << binaryNum[j] << ' ' << answer << ' '; 

    }
    return answer;
}

void convertText(string& text, int nums[])
{
    text = removeSpaces(text);
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    //cout << text;

    int x = 0;
    for (char& c : text)
    {
        nums[x] = c;
        x++;
    }

}

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

// function to convert decimal to binary 
int decToBinary(unsigned long long int x, int binaryNum[])
{
    // array to store binary number 
    //int binaryNum[64];
    //cout << "running...";
    // counter for binary array 
    int i = 0;
    while (x > 0) {

        // storing remainder in binary array 
        binaryNum[i] = x % 2;
        x = x / 2;
        i++;
    }

    return i;

}

int digitsOfN(unsigned long long int n)
{
    int digits = 0;

    while (n != 0)
    {
        n = n / 10; 
        digits++;
    }

    return digits;
}
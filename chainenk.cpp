#include <iostream>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <string>
using namespace std;


int numextractor(string methodofcheese)// stringstream seemed off the table so now im here, this marvel of engineering turns strings to ints
{
    int length = methodofcheese.length();
    int mathizer = 0;
    int errorcoder = 4040401;
    for (int i = 0; i<length; i++)
    {
        char x = methodofcheese[i];
        if (isdigit(methodofcheese[i]))
        {
            mathizer = mathizer * 10 + (x - '0');// this form of black magic lets you have an input of '12' (never try mathizer = x-0 again)
        }
        else
        {
            return errorcoder;
        }
    }
    return mathizer;
}
char shiftChar(char letter, int shifffter)// had to be fixed due to its mysterious nature, don't touch again.

{
    if (isupper(letter)){
        shifffter = shifffter % 26;
        letter = (letter - 'A' + shifffter) % 26 + 'A';
        if (letter < 'A'){letter = ('Z'+1) - ('A'-letter);}
    }
    else if (islower(letter))
    {
        shifffter = shifffter % 26;
        letter = (letter - 'a' + shifffter) % 26 + 'a';
        if (letter < 'a'){letter = ('z'+1) - ('a'-letter);}
    }
    return letter;
}
string keymanager(string key_phrase) // DOES EVERY ANNOYING THING THE KEY REQUIRES
{
        int length5 = key_phrase.length();
        string refinedkey = "";
        refinedkey += key_phrase[0]; // first value is always part of refinedkey because im really not creative
        
         
        for (int i = 1; i < length5; i++)
        // if letter in keyphrase is 'space' and if the next i is less than the total length of keyphrase and if the next char in keyphrase is a letter, add it to refinedkey
        {
                if (isalpha(key_phrase[i]) && key_phrase[i-1] == ' ')
                {
                    refinedkey += key_phrase[i];
                }
        }

        // needs to still meake everything capital letters (1-26 range)
        int length6 = refinedkey.length();
        for (int g = 0; g < length6; g++)
        {
                if (islower((refinedkey[g])))
                {
                        refinedkey[g] = toupper(refinedkey[g]); // questionable use of toupper
                }
        }
        return refinedkey;        
}
int getDoubleKeyShiftValue(string key1, string key2)
{
    const int length1 = key1.length();
    const int length2 = key2.length();
    int i;
    int j;
    int counter1;
    for (i = 0; i < length1; i++)
    {
        for (j = 0; j < length2; j++)
        {
           if (key1[i] == key2[j])
           {
            counter1++;
           }
        }    
    }
    return counter1%26;
}
string getLayer1MessageDecryption(string message, int method_choice, string key1, string key2)
{
    if(method_choice == 1)                                  // meathod choice 1
    {
        int shift = 13;
        const int length3 = message.length();
        int i; // it doesnt work otherwise
        for (i = 0; i<length3; i++)
        {
            message[i] = shiftChar(message[i], -(shift)); // LITERALLY THE ONLY IMPORTANT PART (look here if doesnt work)
        }
        return message;
    }
    else if(method_choice == 2)                                  // meathod choice 2
    {
        int shift = getDoubleKeyShiftValue(key1, key2);
        const int length3 = message.length();
        int i; // it doesnt work otherwise
        for (i = 0; i<length3; i++)
        {
            message[i] = shiftChar(message[i], -(shift)); // LITERALLY THE ONLY IMPORTANT PART (look here if doesnt work)
        }
        return message;
    }
    else // if something goes wrong/bad input
    {
        return message;
    }
}
string getLayer2MessageEncryption(string message, string key_phrase) // works fine now, hope for the best and don't touch it
{
    // time to fix edge cases :0
    if (!(isalpha(key_phrase[0]))){return message;}// nice and easy, should fix all o dat
    //end of bugfix. (my real code is in the next castle)
    int lengthofmessage = message.length();
    int keylength = keymanager(key_phrase).length();
    string tempkey = keymanager(key_phrase);
    string refined; // for some reason you can't use message directly. Keep this in mind
    int j = 0;
    for (int i = 0; i < lengthofmessage; i++)
    {
        char messenger = message[i]; // Same deal, wont worrk otherwise. for some reason you can't use message directly. Keep this in mind
        char keychar = tempkey[j];

        if (isalpha(messenger))
        {
            int shift_value = keychar - 'A'; // most recent way to keep it in 1-26 range, we'll see if it works
            refined += shiftChar(messenger, shift_value);
            j = (j + 1) % keylength; // look to this like the rosetta stone, thanks to this there is no longer infinite if statements. Thanks bro :]
        }
        else
        {
            refined += messenger;
        }
    }
    return refined;
}
string getLayer1MessageEncryption(string message, int method_choice, string key1, string key2) // too old for me to remember what it does besides meathod1/2; hopefully no errors
{
    if(method_choice == 1)                                  // meathod choice 1
    {
        int shift = 13;
        const int length3 = message.length();
        int i; // it doesnt work otherwise
        for (i = 0; i<length3; i++)
        {
            message[i] = shiftChar(message[i], shift); // LITERALLY THE ONLY IMPORTANT PART (look here if doesnt work). I cannot me from yesterday thought this was cool, it isn't.
        }
        return message;
    }
    else if(method_choice == 2)                                  // meathod choice 2
    {
        int shift = getDoubleKeyShiftValue(key1, key2);
        const int length3 = message.length();
        int i; // it doesnt work otherwise
        for (i = 0; i<length3; i++)
        {
            message[i] = shiftChar(message[i], shift); // LITERALLY THE ONLY IMPORTANT PART (look here if doesnt work)
        }
        return message;
    }
    else // if something goes wrong/bad input
    {
        return message;
    }
}
string getChainEncryption(string message, int method_choice, string key1, string key2, string key_phrase) // for method 2/chain method. Too simple, errors unlikely to rise here
{
    string message1 = message;
    string messageLayer1 = getLayer1MessageEncryption(message1, 2, key1, key2);
    string messagecomp = getLayer2MessageEncryption(messageLayer1, key_phrase);
    return messagecomp; // seems quiet, too quiet. At times like these everything doesn't work worse than b4
}
string tehooperator(string message, int method_choice, string key1, string key2, string key_phrase)// in theory, this big boy allocates inputs to outputs for meathod-choice and correctly points it towards the nessesary funktionz EMPTY
{
    if (method_choice == 1)
    {
        string meathod1 = getLayer1MessageEncryption(message, 1, key1, key2);
        return meathod1;

    }
    else if (method_choice == 2)
    {
        string meathod2 = getChainEncryption(message, method_choice, key1, key2, key_phrase);
        return meathod2;
    }
    else if (method_choice == 3)
    {
    }
        return message; 
}

int main() {
    // to keep track: STRING(message[message to encrypt], methodofcheese[which encryptor], keyphrase[that thing with king, by how much are we giving me problems], key1,2[baby stuff for babbies])
    string message;
    string meathodofcheese;
    string key1;
    string key2;
    string key_phrase;
    cout << "input string message"  << endl;
    getline (cin, message);

    cout << "meathod of choice" << endl;
    getline(cin, meathodofcheese);
    int method_choice = numextractor(meathodofcheese); // use validate int instead, apparently stoi bricks the tests
    if (method_choice == 4040401) {cout << "Bad Input" << endl; return 1;} // if validate int finds a non number

    cout << "input key 1" << endl;
    getline (cin, key1);

    cout << "input key 2" << endl;
    getline (cin, key2);

    cout << "input keyphrase" << endl;
    getline (cin, key_phrase);
    // TIME FOR MORE ERROR HANDLING!!!!! I LOVE THIS PART SO MUCHHHH!!!!!! :|
    if (!(method_choice == 1 || method_choice == 2)) // tests for outliers for method choice 1/2
    {
        cout << "The encrypted message : " << message << endl;
        return 1;
    }
    
    string encrypted_message = tehooperator(message, method_choice, key1, key2, key_phrase);
    cout << "The encrypted message : " << encrypted_message << endl;
    return 0;
}
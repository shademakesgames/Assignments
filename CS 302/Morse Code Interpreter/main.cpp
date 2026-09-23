#include "bst.h"
#include <iostream>
#include <fstream>


using namespace std;

void encrypt(string filename, bst<char, string>& bin)
{
    //get character one by one and use the bin tree lookup
    //then cout #
    ifstream iFile(filename);
    char c;
    while (iFile.get(c))
    {
        cout << bin.getValue(c);
        cout << "#";
    }
}
void decrypt(string filename, bst<string, char>& bin)
{
    //get large encompassing string, then break it up
    //based off of the #
    ifstream iFile(filename);
    string s;
    int pos;
    getline(iFile, s);
    while (s.find('#') != string::npos)
    {
        pos = s.find('#');
        string key = s.substr(0, pos);
        cout << bin.getValue(key);
        s.erase(0, pos + 1);
    }
}

int main()
{   
    //command vars
    string commands;
    string letterFile;
    string reTxt;
    char option;
    //get commands
    getline(cin, commands);
    //break the commands string
    int pos = commands.find(' ');
    letterFile = commands.substr(0, pos);
    commands = commands.substr(pos+1);
    pos = commands.find(' ');
    reTxt = commands.substr(0, pos);
    commands = commands.substr(pos+1);
    option = commands[0];
    //file vars
    ifstream iFile1;
    ifstream iFile2;
    iFile1.open(letterFile);
    iFile2.open(reTxt);
    //error handling
    if (!iFile1.is_open())
    {
        cout << "Input file 1 does not exist.";
        return 0;
    }
    if (!iFile2.is_open())
    {
        cout << "Input file 2 does not exist.";
        return 0;
    }
    iFile2.close();

    //create the bst
    bst<char, string> binTree;
    bst<string, char> reverseBinTree;
    char c;
    while (iFile1.get(c))
    {
        binTree.insert(c, "");
        binTree.update(c, binTree.getPath(c));
        iFile1.get(c);
    }
    iFile1.close();
    //reverse the bst, loops used from output morse
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        reverseBinTree.insert(binTree.getPath(ch), ch);
        reverseBinTree.insert(binTree.getPath(tolower(ch)), tolower(ch));
    }
    for (char ch = '0'; ch <= '9'; ch++)
        reverseBinTree.insert(binTree.getPath(ch), ch);
    //reverse for the comma, space, newline, and dot
    reverseBinTree.insert(binTree.getPath(','), ',');
    reverseBinTree.insert(binTree.getPath(' '), ' ');
    reverseBinTree.insert(binTree.getPath('\n'), '\n');
    reverseBinTree.insert(binTree.getPath('.'), '.');
    //get choice, read in, then either encrypt or decrypt
    if (option == 'e' || option == 'E')
        encrypt(reTxt, binTree);
    else if (option == 'd' || option == 'D')
    {
        decrypt(reTxt, reverseBinTree);
    }
    else
        //invalid option case
        cout << "Invalid option.";

    return 0;
}
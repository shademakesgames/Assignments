#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "menuType.h"
#include "hashMap.h"


using namespace std;

int insensitive(string s, vector<string> keys)
{
    //returns the index of the key
    //turns the string to all uppercase
    string key;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] > 96)
            key.push_back(s[i] - 32);
        else
            key.push_back(s[i]);
    }
    //see if any of keys matches the key
    for (int i = 0; i < keys.size(); i++)
    {
        if (key == keys[i])
        {
            return i;
        }
    }
    return -1;
}


int main()
{
    hashMap <string, menuType> menuMap;
    ifstream iFile;
    string file_name;
    vector<string> keys;

    
    //get the file
    cout << "Enter Krusty Krab Menu: ";
    
    cin >> file_name;
    cout << endl;

    //open the file
    iFile.open(file_name);
    //error check file
    if (!iFile.is_open())
    {
        cout << "invalid file!";
        return 0;
    }
    //store csv data into the map
    string header;
    getline(iFile, header);
    string line;
    while (getline(iFile, line))
    {
        //get all the variables
        int pos = line.find(',');
        string itemName = line.substr(0, pos);
        line.erase(0, pos+1);
        pos = line.find(',');
        double price = stod(line.substr(0, pos));
        line.erase(0, pos+1);
        pos = line.find(',');
        int quantity  = stoi(line.substr(0, pos));
        //create the menutype object
        menuType entry = menuType(itemName, price, quantity);
        //insert to the map
        menuMap.insert(itemName, entry);
        //push the keys back
        keys.push_back(itemName);
    }
    iFile.close();

    //take the key vector and store them in a copy vector but change all
    //lowercase letters to uppercase for the insensitive function
    vector<string> copy;
    for (int i = 0; i < keys.size(); i++)
    {
        string key = "";
        for (int j = 0; j < keys[i].length(); j++)
        {
            if (keys[i][j] > 96)
                key.push_back(keys[i][j] - 32);
            else
                key.push_back(keys[i][j]);

        }
        copy.push_back(key);
    }

    //the menu / ordering loop
    bool ordering = true;
    double order_total = 0.0;
    while(ordering)
    {
        //cout the whole map, excluding entries that are less than or equal to 0
        for(int i = 0; i < keys.size(); i++)
        {
            if (menuMap.getValue(keys[i]).getQuantity() > 0)
            {
                cout << fixed << setprecision(2) << left << setw(43) << menuMap.getValue(keys[i]).getName()
                     << setw(13) << menuMap.getValue(keys[i]).getPrice()
                     << menuMap.getValue(keys[i]).getQuantity() << endl;
            }
        }
        //hurry up and order something!
        string entry;
        cout << endl;
        cout << "Hurry up and order something: ";
        cin.ignore();
        getline(cin, entry);
        //get the case insensitive version
        int index = insensitive(entry, copy);
            if (index == -1)
                entry = " ";
            else
                if (menuMap.getValue(keys[index]).getQuantity() > 0)
                    entry = keys[index];
                else
                    entry = " ";

        //loop to check if food exists
        while (!menuMap.find(entry))
        {
            cout << endl << "We serve food here..." << endl;
            cout << "Hurry up and order something: ";
            getline(cin, entry);
            //get the case insensitive version
            int index = insensitive(entry, copy);
            if (index == -1)
                entry = " ";
            else
                if (menuMap.getValue(keys[index]).getQuantity() > 0)
                    entry = keys[index];
                else
                    entry = " ";
        }
        menuType item = menuMap.getValue(entry);
        //How much of this do you want?
        int entry_num;
        cout << "How much of this stuff do you want? ";
        //error check cin
        //loop to check if the given amount is valid
        while (!(cin >> entry_num) || !(item.getQuantity() - entry_num >= 0))
        {

            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n Ahem ... can we please move this order along ?" << endl;
            //typo in the test.
            cout << "How of this stuff do you want? ";
        }
        item.updateQuantity(entry_num);
        menuMap.update(entry, item);
        //calculate order total
        order_total += entry_num * item.getPrice();
        //will this complete the order?
        char option;
        cout << "Will this complete your order...barnaclehead? ";
        cin >> option;
        //simple switch statement
        switch (option)
        {
            case 'Y':
                ordering = false;
                break;
            case 'y':
                ordering = false;
                break;
            case 'N':
                ordering = true;
                break;
            case 'n':
                ordering = true;
                break;
            default:
                ordering = true;
                break;  
        }
        //check if there is still stuff in the menu
        if (ordering == true)
        {
            int menuCount = 0;
            for(int i = 0; i < keys.size(); i++)
            {
                if (menuMap.getValue(keys[i]).getQuantity() > 0)
                {
                    menuCount++;
                }
            }
            if (menuCount == 0)
                ordering = false;
        }
        cout << endl;
    }
    //print the order total
    cout << "Order Total " << order_total;

    return 0;
}
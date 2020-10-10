//
//  main.cpp
//  hw2
//
//  Created by cavitcakir on 05/07/2018.
//  Copyright © 2018 cavitcakir. All rights reserved.
//

#include <iostream>
#include <string>
#include "linkedList.h"
#include <sstream>
#include "strutils.h"
using namespace std;

string input() // converts inputs into ordered and uppercased strings
{
    string name="", input, line;
    cin.ignore();
    getline(cin, input);
    stringstream ss(input);
    while(ss >> line)
    {
        name = name + " " + line;
    }
    name = name.substr(1);
    ToUpper(name);
    return name;
}

bool classCaller(int select, linkedlist & list) // according to selection calls members of class
{
    bool flag = true;
    
    if(select == 1) // to add in order
    {
        
        int quantity, price;
        cout << "---\n"<<"Enter name for the item: ";
        string name = input();
        if(list.checkExist(name))
        {
            cout <<"Enter quantity for the item: ";
            cin >> quantity;

            cout << "---\nThe quantity of the item "<<name<<" is increased by "<<quantity;
            node * temp = new node;
            temp = list.returnNode(name);
            
            quantity = temp->quantity + quantity;
            price = temp ->price;
            cout << ". The final quantity is "<<quantity<<"."<< endl;
            list.deleteOneNode(name);
            
            list.AddInOrder(name, quantity, price,0);
            
        }
        else
        {
            cout <<"Enter quantity for the item: ";
            cin >> quantity;
            cout <<"Enter estimated price for the item: ";
            cin >> price;
            list.AddInOrder(name, quantity, price,1);
        }
    }
    else if (select == 2) // to delete smth
    {
        int flag = 0;
        cout << "---"<<endl<<"Enter an item name to delete from the list: ";
        string name = input();
    
       flag= list.deleteOneNode(name);
        if (flag == 0)
        {
            cout<<"---"<<endl<<"The item "<<name<< " could not be found in the list."<< endl;
        }
        else if(flag ==1)
            cout << "---"<<endl<<"The item "<<name<<" is deleted from the list."<< endl;
        else
            cout <<"---"<< endl<< "The item "<<name<<" could not be found in the list." << endl;
    
    }
    else if(select == 3) // to print list
    {
        list.printList();
    }
    else if(select == 4) // to print list inverse
    {
        list.printListInverse();
    }
    else if(select == 5) // to print total cost
    {
        list.totalCost();
    }
    else if(select == 6) // to close the program
    {

        cout<<"---\n" << "Clearing the shopping list...\nExiting the program...\n";
        flag = false;
    }
    else
        cout<< "---\n" << "This is not a valid option!\n";
    return flag;
}



int main()
{
    cout << "This program helps Alan with gathering the shopping list for his psychedelic breakfast."<< endl;

    bool flag = true;
     linkedlist list;
    
     while(flag)
    {
            int select = 0;
        cout << "---\nMENU\n1. Add item to the shopping list\n2. Delete item from the shopping list\n3. Print the shopping list\n4. Print the shopping list in reverse order\n5. Show total estimated cost of the list\n6. Exit\n---\nEnter your choice: ";
        
       
        cin >> select;
        if(!cin.fail())
       {
           flag = classCaller(select, list);
        }
     else
       {
        cout << "---\n" << "This is not a valid option!\n";
        cin.clear();
        cin.ignore(1024, '\n');
         
       }
    }
    list.deleteAll(); // to delete linked list
    
    return 0;
}


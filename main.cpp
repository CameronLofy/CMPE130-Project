#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stdio.h>

using namespace std;

class contact_node{     // Creating the node for each entry
public:
    string num;         // String for phone number
    string name;        // String for name (basically the key)
    contact_node *next;      // Node for chaining

    //initializing the contact_node
    contact_node(string name, string num){
        this->num = num;
        this->name = name;
        this->next = NULL;
    };

};


class hashtable{
private:
    contact_node **hash_table;      //double pointer to hash table entry at start of chain
public:

        // Size of table assigned to large prime number
    unsigned int size = 8963;

    // Initializing hash table with an empty hash table and no chaining at nodes yet
    hashtable() {
        hash_table = new contact_node*[size];
        // Create empty hash table
        for(int i=0; i<size; i++){
            hash_table[i] = NULL;
        }
    }

    // Function to return a hash value for each entry
    // Adds up ASCII values o each number
    int hash_func(std::string name){
        int hash_value;
        for(int i=0; i<name.length(); i++){
            // Add each ASCII value cubed to hash value
            // Cubed to ensure entire table is used
            hash_value = (hash_value + (name.at(i)^3));
        }

        return hash_value%size;
    }

    void insert(string name, string num){
        string parsed_name = name_parse(name);
        string parsed_num = num_parse(num);

        int hash_val = hash_func(parsed_name);

        contact_node *entry = hash_table[hash_val];
        contact_node *prev = NULL;

        // Iterate through chain until an empty node is found
        while(entry != NULL){
            prev = entry;
            entry = entry->next;
        }

        // An empty node has been found
        entry = new contact_node(parsed_name, parsed_num);

        if(prev == NULL){
            // Insert node at location in array space
            hash_table[hash_val] = entry;
        }

        else{
            // Link previous node's next value to the new node
            prev->next = entry;
        }

        cout<< parsed_name<< ", "<< parsed_num <<" inserted!"<<endl;

    }

    void delete_entry(string name){

    }

    string get(string name){        // TODO: fix this function
        bool retrieved = false;

        string parsed_name = name_parse(name);

        int hash_val = hash_func(parsed_name);

        contact_node *entry = hash_table[hash_val];
        if(entry == NULL){
            return "could not find entry. Please try a different name.";
        }

        while(entry->name != parsed_name){
            entry = entry->next;
            if(entry == NULL){
                return "Could not find entry. Please try again.";
            }
        }

        // Entry found
        return (entry->num);


    }


    string num_parse(string num){
        string out;
        for(int i=0; i<num.size(); i++){
            if(is_num(num[i])){
                out += num[i];
            }
        }
        return out;
    }

    string name_parse(string name){
        string out;
        string upper_out;
        for(int i=0; i<name.size(); i++){
            if(is_letter(name[i])){
                out += name[i];
            }
        }
        for(int i=0; i<out.size(); i++){
            upper_out += toupper(out[i]);
        }
        return upper_out;
    }

    // Format the name string stored to tha hash table to be "First Last" output
    string format_name(string name){

    }


    // Format the number string to be (xxx) xxx-xxxx output
    string format_num(string num){

    }

    // Check whether character in number input is a number
    bool is_num(char n){
        if(n >= '0' && n <= '9'){
            return true;
        }
        return false;
    }

    // Check whether character name input is a letter or other valid name character such as "-"
    bool is_letter(char l){
        if((l >='a' && l <= 'z') || (l >= 'A' && l<= 'Z')){
            return true;
        }
        if(l == ' ' || l == '-' ){
            return true;
        }

        // TODO: if two spaces in entry
        return false;
    }
};


int main(){
    hashtable hash;
    string name, num, c;
    string parsed_num;

    while(1) {
        cout << "Choose Option:" << endl;
        cout << " (1) Insert Entry\n" << " (2) Get Phone Number of Contact\n" << " (3) Delete Contact\n" << " (4) Exit"
             << endl;
        getline(cin, c);
        if (c == "1") {
            cout<<"Enter name to insert: ";
            getline(cin, name);
            cout<<endl;
            cout<<"Enter Number: ";
            getline(cin, num);
            hash.insert(name, num);
        } else if (c == "2") {
            cout<<"Enter Name: ";
            getline(cin, name);
            parsed_num = hash.get(name);
            cout<< "Name: "<< name << endl;
            cout<< "Number: "<< parsed_num<< endl;
        } else if (c == "3") {
            cout<<"Enter Name: ";
            getline(cin, name);
            hash.delete_entry(name);
        } else if (c == "4") {
            cout << "Exiting" << endl;
            exit(1);
        }
    }




}





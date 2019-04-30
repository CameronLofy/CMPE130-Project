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
    contact_node *next, *prev;      // Nodes for chaining

    //initializing the contact_node
    contact_node(string num, string name){
        this->num = num;
        this->name = name;
        this->prev = NULL;
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
            hash_value = hash_value + (name.at(i)^3);
        }

        return hash_value;
    }

    void insert(string name, string num){

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
        return false;
    }
};


int main(){
    hashtable hash;
    string name, num;

    // Just testing toupper function
    cout<< hash.name_parse("Cameron Lofy")<< endl;

    cout<< hash.num_parse("(209) 479-8832")<< endl;

}





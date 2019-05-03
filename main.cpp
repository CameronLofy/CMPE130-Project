#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stdio.h>

/*To Do:
-Functions to make:
-format_name
-format_num
-double_size?
-Testbench with decent sized data set.

Functions to fix:
-get

Functions to research:
-Hash function
*/
using namespace std;

class info_node{            // Linked List of all corresponding numbers to contact
public:
    string num;
    info_node *next_num;

};

class contact_node{     // Creating the node for each entry
public:
    info_node *num_node;         // String for phone number
    /*
        Could be made into a 2d list.
        1st axis to store each number entry associated with the name.
        2nd axis to store other info associated to that specific number.
        If there are multiple numbers associated with the same unique person,
            you could make sure the numbers were always first in the linklist.
            That way once it hit a non-numeric character, it would know it got all the numbers for display.
        Alternately, if the fields of data are static, use an array for each.
            Depends if most entries are mostly filled out, making an array best,
            or if a lot of entries have missing data, then linklist might be more efficent.
    */
    string name;        // String for name (basically the key)
    contact_node *next;      // Node for chaining

    //initializing the contact_node
    contact_node(string name, string num){
        this->num_node->num = num;
        this->name = name;
        this->next = nullptr;
    };

    void print_all(){
        contact_node *entry = this;
        while(next != nullptr)
        {
            cout<< name << ", "<< num_node->num << endl;
            entry = entry->next;
        }
        cout<< name << ", "<< num_node->num << endl;
    }
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
            hash_table[i] = nullptr;
        }
    }

    ~hashtable(){
        for(int i=0; i<size; i++){
            contact_node *entry = hash_table[i];

            while(entry != nullptr){
                contact_node *prev = entry;
                while(entry->num_node != nullptr){
                    info_node *info_prev = entry->num_node;
                    entry->num_node = entry->num_node->next_num;
                    delete info_prev;
                }
                entry = entry->next;
                delete prev;
            }
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
        contact_node *prev = nullptr;

        // Iterate through chain until an empty node is found
        while(entry != nullptr){
            prev = entry;
            entry = entry->next;
        }

        // An empty node has been found
        entry = new contact_node(parsed_name, parsed_num);

        if(prev == nullptr){
            // Insert node at location in array space
            hash_table[hash_val] = entry;
        }

        else{
            // Link previous node's next value to the new node
            prev->next = entry;
        }

        cout<< parsed_name<< ", "<< parsed_num <<" inserted!"<<endl;

    }


    //Requires a number to identify the specific target for deletion,
    //since name keys are not unique.
    void delete_entry(string name, string num){
        string parsed_name = name_parse(name);
        string parsed_num = num_parse(num);

        int hash_val = hash_func(parsed_name);

        contact_node *entry = hash_table[hash_val];
        contact_node *prev = nullptr;

        if(entry == nullptr)
        {
            cout<< parsed_name<< ", "<< parsed_num <<" was not found."<<endl;
            return;
        }

        // Iterate through chain until an empty node is found
        while(entry->name != parsed_name && entry -> num_node->num != parsed_num){
            prev = entry;
            entry = entry->next;
            if(entry == nullptr)
            {
                cout<< parsed_name<< ", "<< parsed_num <<" was not found."<<endl;
                return;
            }
        }

        if(prev == nullptr){
            // Insert node at location in array space
            hash_table[hash_val] = nullptr;
        }

        // Correct Node has been found.
        else prev -> next = entry -> next;

        cout<< parsed_name<< ", "<< parsed_num <<" was deleted."<<endl;

        return;
    }

    contact_node* get(string name){
        string parsed_name = name_parse(name);
        int hash_val = hash_func(parsed_name);

        contact_node *entry = hash_table[hash_val];

        contact_node *result;
        contact_node *temp;

        if(entry == nullptr) return nullptr; //This part keeps segment faulting.
        // Iterate through chain until an empty node is found

        do {

            if(entry->name == parsed_name){
                // TODO: shouldn't create a new node, only reading values of existing node
                temp = new contact_node(entry->name, entry->num_node->num);
                if(result == nullptr) result = temp;
                else{
                    result = temp; //Need to check this is copying and not pointing to the same thing.
                    result = result->next;
                }
            }
            entry = entry->next;
        } while(entry->next != nullptr);

        return result;
    }



/*
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
*/

    void list_all(){
        contact_node *entry = nullptr;
        int count = 0;
        for(int i = 0; i < size; i++)
        {
            entry = hash_table[i];
            while(entry != nullptr)
            {
                cout<< "Entry:"<< entry->name << endl;
                if(entry->num_node->next_num != nullptr){
                    cout<<"All numbers related to contact:" <<endl;
                    info_node *temp = entry->num_node;

                    while(temp != nullptr){
                        cout<<"     "<< format_num(temp->num)<<endl;
                        temp = temp->next_num;
                    }
                }
                else if(entry->num_node->next_num == nullptr){
                    cout<<"Number: "<< format_num(entry->num_node->num)<<endl;
                }
                entry = entry->next;
                count++;
            }
        }
        cout<< "Contact Count:"<< count << endl;
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

    // Format the name string stored to the hash table to be "First Last" output
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
    contact_node* cnode;

    while(1) {
        cout << "Choose Option:" << endl;
        cout << " (1) Insert Entry\n" << " (2) Get Phone Number of Contact\n" << " (3) Delete Contact\n" << " (4) List All\n" << " (5) Exit"
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
            cnode = hash.get(name);
            if(cnode) cnode->print_all();
        } else if (c == "3") {
            cout<<"Enter name to delet: ";
            getline(cin, name);
            cout<<endl;
            cout<<"Enter Number: ";
            getline(cin, num);
            hash.delete_entry(name, num);
        } else if (c == "4"){
            hash.list_all();
        } else if (c == "5") {
            cout << "Exiting" << endl;
            exit(1);
        }
    }
}
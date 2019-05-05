#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <chrono> 

using namespace std;
using namespace std::chrono; 

class info_node{	//Stores numbers associated to a specific name. 
public:
    string num;
    info_node *next_num;
	//Store any additional info here.
	//Second number would require slight modification
	
	//Linklist to store each number.
   info_node(string num){
        this->num = num;
        this->next_num = nullptr;
    }
};

class contact_node{     // Node used to store each name added to hashtable
public:
    info_node *num_node;	// String for phone number
    string name;			// String for name (basically the key)
    contact_node *next;		// Node for chaining

    //initializing the contact_node
    contact_node(string name, string num){
        this->num_node = new info_node(num); //Stores numbers associated to the name.
        this->name = name;
        this->next = nullptr;
    };
    void print_all();

	//Helper function to print entire node's contents

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

	//Deconstructor
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

    int hash_func(string name);

    // Function to return a hash value for each entry
    // Adds up ASCII values of each number
    /*
    int hash_func(string name){
        int hash_value=0;
        for(int i=0; i<name.length(); i++){
            // Add each ASCII value cubed to hash value
            // Cubed to ensure entire table is used
            hash_value = (hash_value + (name.at(i)^3));
        }
        return hash_value%size;
    }
     */
    // DJB2 Hashing function


    void insert(string name, string num);

    //Requires a number to identify the specific target for deletion, since name keys are not unique.
    void delete_entry(string name, string num);

    contact_node* get(string name);

	//Just iterates through entire hashtable, contact_node, and info_node, printing out info.
    void list_all();

    string num_parse(string num);
    string name_parse(string name);

    // Format the name string stored to the hash table to be "First Last" output
    string format_name(string name);
    // Format the number string to be (xxx) xxx-xxxx output
    string format_num(string num);

    // Check whether character in number input is a number
    bool is_num(char n);

    // Check whether character name input is a letter or other valid name character such as "-"
    bool is_letter(char l);
};

int hashtable::hash_func(string name)
{
    unsigned long hash = 5381;
    int c;

    for(int i=0; i<name.length(); i++) {

        hash = ((hash << 5) + hash) + name.at(i); /* hash * 33 + c */
    }

    return (hash%size);
}

// Function to return a hash value for each entry
// Adds up ASCII values of each number
/*
int hash_func(string name){
    int hash_value=0;
    for(int i=0; i<name.length(); i++){
        // Add each ASCII value cubed to hash value
        // Cubed to ensure entire table is used
        hash_value = (hash_value + (name.at(i)^3));
    }
    return hash_value%size;
}
 */
// DJB2 Hashing function


void hashtable::insert(string name, string num){
    string parsed_name = name_parse(name);
    string parsed_num = num_parse(num);

    int hash_val = hash_func(parsed_name);

    contact_node *entry = hash_table[hash_val];
    contact_node *prev = nullptr;

    info_node *info = nullptr;
    info_node *iprev = nullptr;

    // Iterate through chain until it finds a matching name or reaches the end of the linklist
    while(entry != nullptr && entry->name != parsed_name){
        prev = entry;
        entry = entry->next;
    }

    // Found a match.
    if(entry != nullptr)
    {
        // Could this if be taken out? Could have been to protect from a nullptr comparison bug.
        if(entry->name == parsed_name)
        {
            info = entry->num_node;
            // Need to traverse contact_node's info_node, looking for a match or end of the info_node linklist
            while(info != nullptr)
            {
                if(info->num == parsed_num) // Found matching num, info is already present.
                {
                    cout<< format_name(parsed_name)<< ", "<< format_num(parsed_num) <<" Already Exists!"<<endl;
                    return;
                }
                if(info->next_num == nullptr) // Add number to the linklist
                {
                    info->next_num = new info_node(num);
                    cout<< format_name(parsed_name)<< ", "<< format_num(parsed_num) <<" inserted!"<<endl;
                    return;
                }
                iprev = info;
                info = info->next_num;
            }

            info = new info_node(num); //Catch all
            iprev->next_num = info;

        }
    }
        // Did not find a name match, prepare entry with new contact_node for insertion
    else
        entry = new contact_node(parsed_name, parsed_num);

    if(prev == nullptr)
        hash_table[hash_val] = entry; // Insert node at location in array space
    else
        prev->next = entry; // Link previous node's next value to the new node

    cout<< "Name: " << format_name(parsed_name) << "\nNumber: " << format_num(parsed_num) <<"\n" << format_name(parsed_name) <<" Has been inserted!"<<endl;

}

//Requires a number to identify the specific target for deletion, since name keys are not unique.
void hashtable::delete_entry(string name, string num){
    string parsed_name = name_parse(name);
    string parsed_num = num_parse(num);

    int hash_val = hash_func(parsed_name);

    contact_node *entry = hash_table[hash_val];
    contact_node *prev = nullptr;

    info_node *info = nullptr;
    info_node *iprev = nullptr;

    // No nodes exist, name is not in hashtable.
    if(entry == nullptr)
    {
        cout<< format_name(parsed_name) << ", "<< format_num(parsed_num) <<" was not found."<<endl;
        return;
    }

    // Iterate through chain until list ends
    while(entry != nullptr){
        if(entry->name == parsed_name) //Found matching name
        {
            info = entry->num_node;
            // Iterate through info_nodes until list ends
            while(info != nullptr)
            {

                if(info->num == parsed_num) //Found matching number
                {
                    if(iprev == nullptr && info->next_num == nullptr) //Only number in list, delete contact_node
                    {
                        if(prev == nullptr && entry->next == nullptr) //Only contact_node, set array space to null
                            hash_table[hash_val] = nullptr;
                        else if(prev == nullptr)	//First contact node, set it's next to be first.
                            hash_table[hash_val] = entry->next;
                        else //in the middle or end of contact_node list
                            prev->next = entry->next;
                        cout<< format_name(parsed_name) << ", "<< format_num(parsed_num) <<" was deleted."<<endl;
                        return;
                    }
                    else if(iprev == nullptr) //First number in info_node linklist, set second node to be first.
                    {
                        entry->num_node = info->next_num;
                        cout<< format_name(parsed_name) << ", "<< format_num(parsed_num)<<" was deleted."<<endl;
                        return;
                    }
                    else //Node in the middle or end, delete it from list.
                    {
                        iprev->next_num = info->next_num;
                        cout<< format_name(parsed_name) << ", "<< format_num(parsed_num) <<" was deleted."<<endl;
                        return;
                    }
                }
                iprev = info;
                info = info->next_num;
            }
        }
        prev = entry;
        entry = entry->next;
    }
    //Could not find, must not exist.
    cout<< format_name(parsed_name)<< ", "<< format_num(parsed_num)<<" was not found."<<endl;
}

contact_node* hashtable::get(string name){
    string parsed_name = name_parse(name);
    int hash_val = hash_func(parsed_name);

    contact_node *entry = hash_table[hash_val];

    //contact_node *result;
    //contact_node *temp;

    if(entry == nullptr) return nullptr;

    // Iterate through chain, checking for matches
    while(entry != nullptr)
    {
        if(entry->name == parsed_name)
            return entry;
        else
            entry = entry->next;
    }
    return nullptr;
}

//Just iterates through entire hashtable, contact_node, and info_node, printing out info.
void hashtable::list_all(){
    contact_node *entry = nullptr;
    info_node *info = nullptr;
    int count = 0;
    for(int i = 0; i < size; i++)
    {
        entry = hash_table[i];
        while(entry != nullptr)
        {
            info = entry->num_node;
            while(info != nullptr)
            {
                cout<< format_name(entry->name) << ":" << format_num(info->num) << endl;
                info = info->next_num;
                count++;
            }
            entry = entry->next;
        }
    }
    cout<< "Contact Count:"<< count << endl;
}

string hashtable::num_parse(string num){
    string out;
    for(int i=0; i<num.size(); i++){
        if(is_num(num[i])){
            out += num[i];
        }
    }
    return out;
}

string hashtable::name_parse(string name){
    string out;
    string upper_out;
    char space;
    bool prev_space = false;
    for(int i=0; i<name.size(); i++){
        if(is_letter(name[i])){
            out += (name[i]);
            prev_space = false;
        }
        if(name[i] == ' ' && prev_space == false){
            out += (name[i]);
            prev_space = true;
        }
    }
    for(int i=0; i<out.size(); i++){
        upper_out += toupper(out[i]);
    }
    return upper_out;
}

// Format the name string stored to the hash table to be "First Last" output
string hashtable::format_name(string name){    //Input name must be parsed already
    string formatted_name;
    formatted_name += (toupper(name[0]));
    for(int i=1; i<name.size(); i++){
        if(name[i-1] == ' '){
            formatted_name += toupper(name[i]);
        }
        else {
            formatted_name += tolower(name[i]);
        }
    }
    return formatted_name;
}

// Format the number string to be (xxx) xxx-xxxx output
string hashtable::format_num(string num){      //Input number must be parsed already
    num.insert(0, 1, '+');
    num.insert(1, 1, '1');
    num.insert(2, 1, ' ');
    num.insert(3, 1, '(');
    num.insert(7, 1, ')');
    //num.insert(5, 1, ' ');
    num.insert(11, 1, '-');

    return num;

}

// Check whether character in number input is a number
bool hashtable::is_num(char n){
    if(n >= '0' && n <= '9'){
        return true;
    }
    return false;
}

// Check whether character name input is a letter or other valid name character such as "-"
bool hashtable::is_letter(char l){
    if((l >='a' && l <= 'z') || (l >= 'A' && l<= 'Z') || l == '-'){
        return true;
    }
    return false;
}



void contact_node::print_all(){
    hashtable hashtable;
    contact_node *entry = this;
    info_node *info = entry->num_node;
    while(info != nullptr)
    {
        cout<< hashtable.format_name(name) << ", "<< info->num << endl;
        info = info->next_num;
    }
}


int main(){
    hashtable hash;
    string name, num, c;
    string parsed_num;
    contact_node* cnode;

    ifstream inFile("TestFile.txt");
    ofstream outFile("Results.txt");
    string strOneLine;

    while (inFile)
    {
        getline(inFile, strOneLine);
        cout << strOneLine << endl;
       
        auto start = high_resolution_clock::now(); 
        hash.insert(strOneLine, to_string((rand() % 9999999999) + 1));
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        outFile << strOneLine << ", " << duration.count() << ", ";
        cout << "Time taken by insert function: " << duration.count() << " microseconds" << endl; 
       
        start = high_resolution_clock::now(); 
        hash.get(strOneLine);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        outFile << duration.count() << "\n";
        cout << "Time taken by get function: " << duration.count() << " microseconds" << endl; 
       
    }

    inFile.close();

    return 0;

    while(1) {
        cout << "Choose Option:" << endl;
        cout << " (1) Insert Entry\n" << " (2) Get Phone Number(s) of Contact\n" << " (3) Delete Contact\n" << " (4) List All\n" << " (5) Exit"
             << endl;
        getline(cin, c);
        if (c == "1") {
            cout<<"Enter name to insert: \n";
            getline(cin, name);
            cout<<endl;
            cout<<"Enter Number: \n";
            getline(cin, num);
            hash.insert(name, num);
        } else if (c == "2") {
            cout<<"Enter Name: \n";
            getline(cin, name);
            cnode = hash.get(name);
            if(cnode) cnode->print_all();
        } else if (c == "3") {
			cout<<"Enter name to delete: \n";								
            getline(cin, name);
            cout<<endl;

            cnode = hash.get(name);
            if(cnode->num_node->next_num != nullptr){

            }
            cout<<"Enter Number: \n";
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

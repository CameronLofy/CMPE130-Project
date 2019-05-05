//
// Created by camer on 5/3/2019.
//

#include "hashtable.h"
#include "contact_node.h"
#include <string>

//using namespace std;  //Not sure why this is getting errors
namespace lib {
    hashtable::hashtable() {                    // Not sure why hashtable is undeclared
        hash_table = new contact_node *[size];
        // Create empty hash table
        for (int i = 0; i < size; i++) {
            hash_table[i] = nullptr;
        }
    }

    contact_node* hashtable::get(string name){
        string parsed_name = name_parse(name);
        int hash_val = hash_func(parsed_name);

        contact_node *entry = hash_table[hash_val];


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

    hashtable::~hashtable() {
        for (int i = 0; i < size; i++) {
            contact_node *entry = hash_table[i];

            while (entry != nullptr) {
                contact_node *prev = entry;
                while (entry->num_node != nullptr) {
                    info_node *info_prev = entry->num_node;
                    entry->num_node = entry->num_node->next_num;
                    delete info_prev;
                }
                entry = entry->next;
                delete prev;
            }
        }
    }

    int hashtable::hash_func(string name) {
        int hash_value;
        for (int i = 0; i < name.length(); i++) {
            // Add each ASCII value cubed to hash value
            // Cubed to ensure entire table is used
            hash_value = (hash_value + (name.at(i) ^ 3));
        }
        return hash_value % size;
    }

    void hashtable::insert(string name, string num) {
        string parsed_name = name_parse(name);
        string parsed_num = num_parse(num);

        int hash_val = hash_func(parsed_name);

        contact_node *entry = hash_table[hash_val];
        contact_node *prev = nullptr;

        info_node *info = nullptr;
        info_node *iprev = nullptr;

        // Iterate through chain until it finds a matching name or reaches the end of the linklist
        while (entry != nullptr && entry->name != parsed_name) {
            prev = entry;
            entry = entry->next;
        }

        // Found a match.
        if (entry != nullptr) {
            // Could this if be taken out? Could have been to protect from a nullptr comparison bug.
            if (entry->name == parsed_name) {
                info = entry->num_node;
                // Need to traverse contact_node's info_node, looking for a match or end of the info_node linklist
                while (info != nullptr) {
                    if (info->num == parsed_num) // Found matching num, info is already present.
                    {
                        cout << parsed_name << ", " << parsed_num << " Already Exists!" << endl;
                        return;
                    }
                    if (info->next_num == nullptr) // Add number to the linklist
                    {
                        info->next_num = new info_node(num);
                        cout << parsed_name << ", " << parsed_num << " inserted!" << endl;
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

        if (prev == nullptr)
            hash_table[hash_val] = entry; // Insert node at location in array space
        else
            prev->next = entry; // Link previous node's next value to the new node

        cout << "Name: " << parsed_name << "\nNumber: " << parsed_num << "\n" << parsed_name << " Has been inserted!"
             << endl;

    }
}
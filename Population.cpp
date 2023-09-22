/***********************************************************************
// OOP244 Workshop #2 DIY (part 2):
//
// File  Population.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//   To completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Population.h"
#include "File.h"


namespace sdds {
    int noOfPost;
    int noOfPopul;
    PostalCode* postcode;

    void sort()
    {
        int i, j;
        PostalCode key;

        for (i = 1; i < noOfPost; i++) {
            key = postcode[i];

            for (j = i - 1; j >= 0 && postcode[j].population > key.population; j--) {
                postcode[j + 1] = postcode[j];
            }

            postcode[j + 1] = key;
        }
    }

    bool startsWith(const char* cstring, const char* subString) {
        return std::strstr(cstring, subString) == cstring;
    }
    bool load(PostalCode& post)
    {
        bool check = false;
        char code[7];

        // if reading of postalcode and population are successful
        if (read(code) && read(post.population)) {

            // allocate memory to the size of the postalcode + 1
            post.code = new char[strlen(code) + 1];

            // copy the postalcode into the newly allocated memroy
            strcpy(post.code, code);

            check = true;
        }

        return check;
    }

    bool load(const char filename[])
    {
        bool check = false;
        int i = 0;

        openFile(filename); 
            noOfPost = noOfRecords();

            // dynamically allocated the size of the noOfPost to Postalcode pointer
            postcode = new PostalCode[noOfPost];

            //  In a loop load the postalcode records from the file into the dynamic array.
            for (int j = 0; j < noOfPost; j++) {
                i += load(postcode[j]);
            }

            // If the number of the records does not match the number of reads print the message
            if (i != noOfPost)
            {
                std::cout << "Error: incorrect number of records read; the data is possibly corrupted!";
                        }

            closeFile();
      
        //else {
        //    std::cout << "Could not open data file: " << filename << std::endl;
        //}

        return check;
    }

    void display(const PostalCode& code)
    {
        std::cout << code.code << ":  " << code.population << std::endl;
    }

    void display()
    {
        std::cout << "Postal Code: population" << std::endl;
        std::cout << "-------------------------" << std::endl;

        sort();

        for (int i = 0; i < noOfPost; i++) {
            std::cout << i + 1 << "- ";
            display(postcode[i]);
            noOfPopul += postcode[i].population;
        }

        std::cout << "-------------------------" << std::endl;
        std::cout << "Population of Canada: " << noOfPopul << std::endl;
    }

    void deallocateMemory()
    {
        // Firstly, delete the postalcode of each struct which memory was allocated
        for (int i = 0; i < noOfPost; i++) {
            delete[] postcode[i].code;
            postcode[i].code = nullptr;
        }

        // Lastly, delete the Postalcode pointer which memory was allocated
        delete[] postcode;
        postcode = nullptr;
    }
}
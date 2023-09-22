/***********************************************************************
// OOP244 Workshop #2 DIY (part 2):
//
// File  File.cpp
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
#include <cstdio>
#include "File.h"

namespace sdds {
   FILE* fptr;
   bool openFile(const char filename[]) {
      fptr = fopen(filename, "r");
      return fptr != NULL;
   }
   int noOfRecords()
   {
       int noOfRecs = 0;
       char ch;
       while (fscanf(fptr, "%c", &ch) == 1) {
           noOfRecs += (ch == '\n');
       }
       rewind(fptr);
       return noOfRecs;
   }

   void closeFile()
   {
       if (fptr)
           fclose(fptr);
   }

   // Create Functions:
   // Reads the postalcode
   bool read(char* code)
   {
       return fscanf(fptr, "%[^,],", code) == 1;
   }

   // Reads the population
   bool read(int& population)
   {
       return fscanf(fptr, "%d\n", &population) == 1;
   }

}
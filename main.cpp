/*
 * main.cpp
 *
 *  Submission for CS210 Project Three
 *
 *  Date: 2023 APR 16
 *  Author: Dennis James Stelmach
 */

#include <iostream>
#include <string>
#include "FrequencyCounter.h"

using namespace std;

int main()
{
  // Create a FrequencyCounter object
  FrequencyCounter fc;
  // Read input file into the frequency counter
  fc.readInputFile("CS210_Project_Three_Input_File.txt");

  int option = 0;
  // Display a menu of options and allow the user to select one
  while (option != 4)
  {
    cout << "Please select an option:" << endl;
    cout << "1. Search for an item and print its frequency" << endl;
    cout << "2. Print the list of all items and their frequencies" << endl;
    cout << "3. Print a histogram of item frequencies" << endl;
    cout << "4. Exit the program" << endl;

    string line;
    getline(cin, line);
    try
    {
      option = std::stoi(line); // Convert the user input to an integer
    }
    catch (const std::invalid_argument &ia)
    {
      option = -1; // If the user input is not an integer, set option to an invalid value
    }

    switch (option)
    {
    case 1: // Search for an item and print its frequency
    {
      string item;
      cout << "Enter the item you want to search for: ";
      getline(cin, item);                                           // Get the user input for the item to be searched
      int frequency = fc.searchFrequency(item);                     // Get the frequency of the item
      cout << item << " appears " << frequency << " times" << endl; // Print the result
      break;
    }
    case 2: // Print the list of all items and their frequencies
    {
      fc.printFrequencies(); // Call the function to print the frequencies
      break;
    }
    case 3: // Print a histogram of item frequencies
    {
      fc.printHistogram(); // Call the function to print the histogram
      break;
    }
    case 4: // Exit the program
    {
      cout << "Exiting the program...";
      break;
    }
    default: // Handle invalid input
    {
      cout << "Invalid option. Please try again." << endl;
      break;
    }
    }

    cout << endl;
  }

  return 0;
}

/*
 * FrequencyCounter.cpp
 *  Class member definitions for the FrequencyCounter class
 *
 *  Submission for CS210 Project Three
 *
 *  Date: 2023 APR 16
 *  Author: Dennis James Stelmach
 */

#include <algorithm>          // for std::remove
#include <fstream>            // for file I/O
#include <iomanip>            // for std::setw
#include <iostream>           // for console I/O
#include "FrequencyCounter.h" // header file for the FrequencyCounter class

using namespace std;

// Reads input from a file and updates the frequency map accordingly
void FrequencyCounter::readInputFile(string filename)
{
    ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        string item;
        const char LINE_ENDINGS[] = { '\r', '\n' }; // array of line endings to remove
        while (getline(inputFile, item))
        {
            // Remove line endings to prevent key issues
            for (char lineEnding : LINE_ENDINGS)
            {
                item.erase(std::remove(item.begin(), item.end(), lineEnding), item.end());
            }

            frequencyMap[item]++; // increment frequency count for the current item
        }
        inputFile.close();
        writeOutputFile("frequency.dat"); // write frequency map to a file
    }
}

// Returns the frequency of a given item in the frequency map
int FrequencyCounter::searchFrequency(string item)
{
    if (frequencyMap.count(item))
    {
        return frequencyMap[item]; // return frequency count if the item is found in the map
    }
    else
    {
        return 0; // return 0 if the item is not found in the map
    }
}

// Prints out all items and their respective frequencies in the frequency map
void FrequencyCounter::printFrequencies()
{
    for (const auto& item : frequencyMap)
    {
        cout << item.first << " " << item.second << endl;
    }
}

// Prints out a histogram of the item frequencies in the frequency map
void FrequencyCounter::printHistogram()
{
    size_t maxItemLength = 0;
    for (const auto& item : frequencyMap)
    {
        if (item.first.length() > maxItemLength)
        {
            maxItemLength = item.first.length(); // find the length of the longest item in the map
        }
    }
    for (const auto& item : frequencyMap)
    {
        cout << setw(maxItemLength) << right << item.first << " " << left;
        for (int i = 0; i < item.second; i++)
        {
            cout << "*"; // print asterisks to represent the frequency count of the current item
        }
        cout << endl;
    }
}

// Writes the contents of the frequency map to a file
void FrequencyCounter::writeOutputFile(string filename)
{
    ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        for (const auto& item : frequencyMap)
        {
            outputFile << item.first << " " << item.second << endl;
        }
        outputFile.close();
    }
}

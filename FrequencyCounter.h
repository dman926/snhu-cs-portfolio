/*
 * FrequencyCounter.h
 *  Class and class member declarations for FrequencyCounter class
 *
 *  Submission for CS210 Project Three
 *
 *  Date: 2023 APR 16
 *  Author: Dennis James Stelmach
 */

// Avoid redefinition of FrequencyCounter
#ifndef CORNER_GROCER_FREQUENCY_COUNTER_H_
#define CORNER_GROCER_FREQUENCY_COUNTER_H_

#include <map>
#include <string>

using namespace std;

class FrequencyCounter
{
private:
  map<string, int> frequencyMap;

public:
  void readInputFile(string filename);
  int searchFrequency(string item);
  void printFrequencies();
  void printHistogram();
  void writeOutputFile(string filename);
};

#endif // CORNER_GROCER_FREQUENCY_COUNTER_H_

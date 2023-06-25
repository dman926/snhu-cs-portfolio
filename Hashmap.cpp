//============================================================================
// Name        : Hashmap.cpp
// Author      : Dennis James Stelmach
// Version     : 1.0
// Description : Driver file for Project Two to implement a data structure (Hash Table) to load, retrieve, and modify a list of courses and their data.
//               All actions are facilitated through a menu using the terminal and basic user I/O
//============================================================================

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <list>
#include <functional>

/**
 * Convert given string to upper case
 */
std::string toUpperCase(const std::string &str)
{
	std::string result;

	for (char c : str)
	{
		result += toupper(c);
	}

	return result;
}

// BEGIN HASH TABLE DEFINITION

#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename ValueType>
class HashTable
{
private:
	std::vector<std::list<std::pair<std::string, ValueType>>> table;
	int hashFunction(std::string key);

public:
	HashTable();
	HashTable(int tableSize);
	virtual ~HashTable();
	void insert(std::string key, ValueType value);
	const ValueType *search(std::string key);
	bool empty();
	void clear();
	int size();
	std::vector<std::string> keys() const;
	std::vector<ValueType> values() const;
};

#endif // HASHTABLE_H

#ifndef HASHTABLE_TPP
#define HASHTABLE_TPP

template <typename ValueType>
HashTable<ValueType>::HashTable()
{
  table.resize(1);
}

template <typename ValueType>
HashTable<ValueType>::HashTable(int tableSize)
{
  table.resize(tableSize);
}

template <typename ValueType>
void HashTable<ValueType>::clear()
{
  for (auto &bucket : table)
  {
    bucket.clear();
  }
}

template <typename ValueType>
HashTable<ValueType>::~HashTable()
{
  clear();
}

template <typename ValueType>
int HashTable<ValueType>::hashFunction(std::string key)
{
  return std::hash<std::string>{}(key) % table.size();
}

template <typename ValueType>
void HashTable<ValueType>::insert(std::string key, ValueType value)
{
  int index = hashFunction(key);
  table[index].push_back(std::make_pair(key, value));
}

template <typename ValueType>
const ValueType *HashTable<ValueType>::search(std::string key)
{
  int index = hashFunction(key);

  for (const std::pair<std::string, ValueType> &entry : table[index])
  {
    if (entry.first == key)
    {
      return &(entry.second);
    }
  }
  return nullptr;
}

template <typename ValueType>
bool HashTable<ValueType>::empty()
{
  return !size();
}

template <typename ValueType>
int HashTable<ValueType>::size()
{
  int size = 0;
  for (const std::list<std::pair<std::string, ValueType>> &bucket : table)
  {
    size += bucket.size();
  }
  return size;
}

template <typename ValueType>
std::vector<std::string> HashTable<ValueType>::keys() const
{
  std::vector<std::string> keyList;
  for (const std::list<std::pair<std::string, ValueType>> &bucket : table)
  {
    for (const std::pair<std::string, ValueType> &entry : bucket)
    {
      keyList.push_back(entry.first);
    }
  }

  // Sort keys in ascending alphanumeric order
  std::sort(keyList.begin(), keyList.end());

  return keyList;
}

template <typename ValueType>
std::vector<ValueType> HashTable<ValueType>::values() const
{
  std::vector<ValueType> valueList;
  for (const std::list<std::pair<std::string, ValueType>> &bucket : table)
  {
    for (const std::pair<std::string, ValueType> &entry : bucket)
    {
      valueList.push_back(entry.second);
    }
  }
  return valueList;
}

#endif // HASHTABLE_TPP

// END HASH TABLE DEFINITION

using namespace std;

struct Course
{
	string courseNumber;
	string title;
	vector<string> prerequisites;
};

void loadCourses(HashTable<Course> &courses, const string filePath)
{
	ifstream dataFile;
	dataFile.open(filePath);
	if (!dataFile.is_open())
	{
		cerr << "Failed to open data file at: " << filePath << endl;
		return;
	}

	// Temporary holding area until the input file is confirmed to be valid
	HashTable<Course> coursesBuffer;

	// Parse given CSV
	string line;
	while (getline(dataFile, line))
	{
		vector<string> tokens;
		stringstream iss(line);
		string token;
		int loopCnt = 0;
		while (getline(iss, token, ','))
		{
			// Remove leading whitespace
			token.erase(0, token.find_first_not_of(" \t\r\n"));

			// Remove trailing whitespace
			token.erase(token.find_last_not_of(" \t\r\n") + 1);

			if (!token.empty())
			{
				tokens.push_back(token);
			}
			else if (loopCnt == 0 || loopCnt == 1) // If the curent token is empty and it is the course number or title
			{
				cerr << "Invalid input file: Missing " << (loopCnt ? "course number" : "title") << "." << endl;
				return;
			}

			loopCnt++;
		}

		if (tokens.size() < 2)
		{
			cerr << "Invalid input file: " << filePath << ". Not enough tokens." << endl;
			return;
		}

		struct Course readCourse;
		// Convert course number to upper case as it is the also key of the element
		readCourse.courseNumber = toUpperCase(tokens.at(0));
		readCourse.title = tokens.at(1);
		// At most 5 prerequisites
		for (size_t i = 2; i < tokens.size(); i++)
		{
			readCourse.prerequisites.push_back(tokens.at(i));
		}
		coursesBuffer.insert(readCourse.courseNumber, readCourse);
	}
	for (const Course &c : coursesBuffer.values())
	{
		for (const string &prerequisite : c.prerequisites)
		{
			if (!coursesBuffer.search(prerequisite))
			{
				cerr << "Invalid input file: " << filePath << ". Given prerequisite \"" << prerequisite << "\" is not a valid course." << endl;
				return;
			}
		}
	}
	courses.clear();
	courses = coursesBuffer;
}

void showMenu()
{
	cout << "Menu:" << endl;
	cout << "  1. Load Courses" << endl;
	cout << "  2. Print Course List" << endl;
	cout << "  3. Print Course" << endl;
	cout << "  9. Exit" << endl;
	cout << "Enter choice: ";
}

int main()
{
	HashTable<Course> courses;

	// Define a timer variable
	clock_t ticks;

	// Define courseKey variable for searching individual courses
	string heldString;
	const Course *tempCoursePtr = nullptr;

	int choice = 0;
	while (choice != 9)
	{
		showMenu();
		if (!(cin >> choice))
		{
			cin.clear();
			cin.ignore();
			cerr << "Invalid input. Please enter a valid option." << endl;
			continue;
		}
		cin.ignore();

		switch (choice)
		{

		case 1:
			// Load courses into courses HashTable

			courses.clear();
			cout << "Please enter the file path for the file to load courses from." << endl
					 << "(Starting with `/` uses the absolute path, otherwise relative path is used): ";
			getline(cin, heldString);

			// Initialize a timer variable before loading bids
			ticks = clock();

			loadCourses(courses, heldString);

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			cout << courses.size() << " courses read" << endl;
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 2:
			// Display sorted list of courses
			if (!courses.empty())
			{
				cout << "Here is a sample schedule:" << endl;
				for (const string &key : courses.keys())
				{
					cout << key << ", " << courses.search(key)->title << endl;
				}
			}
			else
			{
				cout << "Please load courses to show using Option 1." << endl;
			}

			break;
		case 3:
			// Display details of requested course
			if (!courses.empty())
			{
				cout << "What course do you want to know about? ";
				getline(cin, heldString);
				// Convert courseKey to upper case
				heldString = toUpperCase(heldString);

				ticks = clock();

				tempCoursePtr = courses.search(heldString);

				ticks = clock() - ticks; // current clock ticks minus starting clock ticks

				if (tempCoursePtr != nullptr)
				{
					Course c = *tempCoursePtr;
					cout << c.courseNumber << ", " << c.title << endl;
					cout << "Prerequisites: ";
					if (c.prerequisites.size())
					{
						for (size_t i = 0; i < c.prerequisites.size() - 1; i++)
						{
							cout << c.prerequisites[i] << ", ";
						}
						cout << c.prerequisites.back();
					}
					else
					{
						cout << "None";
					}
					cout << endl;
				}
				else
				{
					cout << "Course Number " << heldString << " not found." << endl;
				}

				cout << "time: " << ticks << " clock ticks" << endl;
				cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			}
			else
			{
				cout << "Please load courses to show using Option 1." << endl;
			}

			break;
		default:
			if (choice != 9)
			{
				cerr << choice << " is not a valid option." << endl;
			}
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
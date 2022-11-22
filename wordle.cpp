// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
//#include <cstring>
using namespace std;


// Add prototypes of helper functions here

/*
 * Helper to generate all possible VALID combinations
 * of a string of length n
 * VALID = contains all fixed and at least 1 of each floating 
 * character
 */
void charCombiner(
    std::string in,
    unsigned int currentIndex,
		std::string floatingCopy,
    const std::set<std::string>& dict,
		std::set<std::string>& answers);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
	// Instantiating container for valid words
	std::set<std::string> validWords;

	// Making copies of the const referenced sets
	// to allow for manipulation and access in the helper
	std::string input = in;
	std::string floatingChars = floating;
	charCombiner(input, 0, floatingChars, dict, validWords);

	// The helper function updates the validWords appropriately
	return validWords;
}

// Define any helper functions here

// charCombiner recursively generates all valid words and checks if they
// exist in the dictionary, thus updating the set with appropriate words
void charCombiner(
    std::string in,
    unsigned int currentIndex,
		std::string floatingCopy,
    const std::set<std::string>& dict,
		std::set<std::string>& answers)
{

	// Counting how many non-fixed letters need to be filled
	unsigned int fillCount = 0;
	char currentCharacter;
	for (unsigned int i = 0; i < in.size(); ++i)
	{
		currentCharacter = in[i];
		if (currentCharacter == '-')
		{
			fillCount++;
		}
	} 

	// Base Case: we reached the full length of the string
	if (currentIndex == in.size())
	{
		// If the word exists in the dictionary, add it to the set
		std::set<std::string>::iterator dictFind = dict.find(in);
		if (dictFind != dict.end())
		{
			answers.insert(in);
		}
		return;
	}



	// Base Case: we hit a fixed letter
	currentCharacter = in[currentIndex];
	if (currentCharacter != '-')
	{
			// Move onto the next index without modifying in
			charCombiner(in, currentIndex + 1, floatingCopy, dict, answers);
			return;
	}

	else
	{

		// If the number of free characters we have to fill is the same as the number
		// of floating characters left to place, try all combinations of them
		if (fillCount == floatingCopy.size())
		{
			for (unsigned int j = 0; j < floatingCopy.size(); ++j)
			{
				// Update in and increment the index
				in[currentIndex] = floatingCopy[j];

				// Passing in an updated floating set with the character we just added to in
				// removed, in essence marking it as placed
				std::string newFloatingCopy = floatingCopy;
				newFloatingCopy.erase(j, 1);

				// Recursive call with updated in and the new copy of the current floating characters
				// left to place
				charCombiner(in, currentIndex + 1, newFloatingCopy, dict, answers); 
			}
		}

		// If we have more spaces than floating characters, fill with a-z
		else
		{
			// A loop that will facilitate int-to-char conversion for all
			// letters in the alphabet 
			for (int i = 0; i < 26; ++i)
			{
				char c = char(i + 97);
				in[currentIndex] = c;

				// If the current letter is a floating character, remove it from the 
				// copied floating string to denote it has been added 
				unsigned int floatingIndex = floatingCopy.find(c);
				if (floatingIndex <= floatingCopy.size())
				{
					std::string newFloatingCopy = floatingCopy;
					newFloatingCopy.erase(floatingIndex, 1);

					// Recursive call with updated in and the new copy of the current floating characters
					// left to place
					charCombiner(in, currentIndex + 1, newFloatingCopy, dict, answers); 
				}

				// If the current letter is not a floating character, simply make a recursive call
				// with an updated index and in string
				else
				{
					charCombiner(in, currentIndex + 1, floatingCopy, dict, answers); 
				}
			}
		}
	}
}
/*
 * hashNode.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Michael Guerrero &  Michael Figura
 */

#include "hashNode.hpp"
#include <string>
#include <time.h>
using namespace std;



hashNode::hashNode(){		//Hashnode constructor with no parameters
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
}

hashNode::hashNode(string s){	//Hashnode constructor with parameter s used for the keyword of the node, also initializes values and gives it a size.
	keyword = s;
	valuesSize = 100;
	currSize = 0;
	values = new string[valuesSize];
}

hashNode::hashNode(string s, string v){		//Hashnode constructor, assign s to keyword and adds the given string v to the values array.
	keyword = s;
	valuesSize = 100;
	currSize = 1;
	values = new string[valuesSize];
	values[0] = v;
}

void hashNode::addValue(string v){		//Adds v to the array of values
	if(currSize < valuesSize){			//Checks if there is room in the array to add another value
		values[currSize] = v;		//Adds it at the index one past the current size
		currSize ++;					//Adds one to the current sized
	}
	else{
		dblArray();						//If there isn't room it doubles the array and copies over the values
	}
}

void hashNode::dblArray(){
	string *newArray = new string[(2*valuesSize)];			//Makes a new dynamically allocated array twice the size of the current
	for(int i=0; i < valuesSize; i++){						//goes through the old array and copies over the values
		newArray[i] = values[i];
	}
	values = newArray;						//Sets the new array to be the values array
	valuesSize = valuesSize * 2;
}

string hashNode::getRandValue(){					//Gets a random value from the array of values
	if(currSize != 0){								//Checks to make sure the array isn't empty
		int randomvalue = rand() % currSize;		//Picks a random value within the size of the array and returns it
		return values[randomvalue];
	}
	else{
		return "";									//If the array is empty it'll return an empty string.
	}
}



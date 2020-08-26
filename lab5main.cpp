/*
 * lab5main.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Michael Guerrero &  Michael Figura
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "makeSeuss.hpp"

using namespace std;

int main(){
	srand(time(NULL));
	makeSeuss("DrSeuss.txt", "Output1.txt", 1, 1);		//Makes a seuss story with h1 and c1 both initialized to 1
	makeSeuss("DrSeuss.txt", "Output2.txt", 1, 0);		//Makes a seuss story with h1 initialized to 1 and c1 initialized 0
	makeSeuss("DrSeuss.txt", "Output3.txt", 0, 1);		//Makes a seuss story with h1 initialized to 0 and c1 initialized to 1
	makeSeuss("DrSeuss.txt", "Output4.txt", 0, 0);		//Makes a seuss story with both h1 and c1 initialized to 0
}

/*
 * hashMap.cpp
 *
 * Created on: Nov 9, 2018
 * Author: Michael Guerrero & Michael Figura
 */

 #include "hashMap.hpp"
 #include <iostream>
 #include <stdlib.h>
 #include <string>
 #include <fstream>
 #include <time.h>
 using namespace std;


hashMap::hashMap(bool hash1, bool coll1){	//constructor that initilizes the hashmap
	first = "";
	numKeys = 0;
	mapSize = 100;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;

	map = new hashNode*[mapSize];		//initializes every element in the map to null
	for(int i = 0; i < mapSize; i++){
		map[i] = NULL;
	}
}

void hashMap::addKeyValue(string k, string v){
	int index = getIndex(k);				//finds the index at the key
	if(map[index] == NULL){					//if the space is null
		map[index] = new hashNode(k, v);	//add the new key and value
		numKeys ++;							//a key has been added, num keys + 1

	}else{									//if the space isn't null
		map[index]->addValue(v);			//adds the new value to the pre existing key
	}
	reHash();					//rehashs if need to.
}

int hashMap::getIndex(string k){
	 reHash();					//rehashes the map to ensure that every index is in the correct position
	 int index = 0;				//index to be returned
	 if(h1){					//determines which hash function will be used
		 index = calcHash(k);	//sets the index
	 }
	 else{
		 index = calcHash2(k);	//sets the index
	 }
	 if(map[index] == NULL || map[index]->keyword == k){	//this means the space being looked at is null or is filled with the same key
		 return index;										//so simply return the index (based off of calcHash functions
	 }
	 else{						//if the above condition is not true we have encountered a collision and must change the index to be returned
	 	 if(c1){				//determines which collision function will be used
			 index = collHash1(index, k);	//sets the index
			 return index;					//returns the index
	 	 }
		 else{
			 index = collHash2(index, k);	//sets the index
			 return index;					//returns the index
		 }
	 }
}

int hashMap::calcHash(string k){
	 int sum = 0;							//sum corresponds to the location of each key
	 for(int i = 0; i < k.length(); i++){	//goes through the word with each individual letter
		 if(k[i] % 2 == 0){			//if the letter's value is even
			 sum += int(k[i]);		//add it to the total value
		 }
		 else{						//if the letter's value is odd
			 sum += int(k[i]) * 7;	//multiply it by 7 and add it to the total value
		 }
	 }
	 return sum % mapSize;			//returns the key's location in the array and mods by mapsize to ensure it's not out of bounds
}

int hashMap::calcHash2(string k){
	 int sum = 0;						//sum corresponds to the location of each key
	 int hashedSum = 0;					//hashed sum is the sum plus the length of the word (for unpredictability and so each word's value is more unique)
	 int hashAdd = 0;					//increments
	 for(int i = 0; i < k.length(); i++){	//goes through the word with each individual letter
		 sum += int(k[i]);				//adds each letter to the total value
		 hashAdd++;						//adds one per letter in the word
	 }
	 hashedSum = sum + hashAdd;			//gets the value to return
	 return hashedSum % mapSize;		//returns the key's location in the array and mods by mapsize to ensure it's not out of bounds
}

void hashMap::getClosestPrime(){
	 int db = mapSize*2;				//double the map size
	 for(int i = 2; i < db; i++){		//for loop incrementing from 2 to the value (tests if it's prime)
		 if ((db % i) == 0){			//if this is never true then the number is prime
			 db++;						//adds one to db, meaning it's previous value was not prime
			 i = 2;						//restarts the count
		 }
	 }
	 mapSize = db;	//sets the map size to the nearest prime rounded up from double it's previous size
}

void hashMap::reHash(){
	 int index = 0;							//variable used to rehash properly
	 int oldSize = mapSize;
	 if(numKeys >= mapSize*.7){				//need to rehash if the number of keys goes over 70% of the map size
		 getClosestPrime();					//adjusts the map size
		 hashNode **tmp = map;				//points to 'old' map so the new map can be changed
		 map = new hashNode*[mapSize];		//reassigns the map to the new map size
		 for(int i = 0; i < mapSize; i++){	//initializes every element in the map to null (must be done upon each initialization of the map)
			 map[i] = NULL;
		 }

		 for(int i = 0; i < oldSize; i++){	//looks at the old map to reassign values
			 if(tmp[i] != NULL){			//if the index of the old map contained data
				 index = getIndex(tmp[i]->keyword);	//retrieve this data
				 map[index] = tmp[i];				//add it to the index in the new map
			 }
		 }
	 }
}

int hashMap::collHash1(int currentindex, string k){
	 collisionct1++;					//adds one to first count (each time the initial collision occurs)
	 int hashVal = currentindex;		//the new value after hashing
	 int count = 0;						//count used for quadratic probing
	 while(map[hashVal] != NULL){		//if the position is already filled, move on
		 if(map[hashVal]->keyword == k){	//if the keyword at that index matches the given keyword it'll break the loop
			 break;
		 }
		 count++;						//adds one to the count (each time probed, must increment)
		 collisionct2++;				//adds one to the second count (for each additional collision)
		 if(hashVal >= mapSize - 1){	//if the values goes out of the map
			 hashVal = 0;				//bring it back to 0
		 }
		 else{
			 hashVal = (currentindex + (count * count)) % mapSize;	//quadratic probing, adds count squared
		 }
	 }
	 return hashVal;
}

int hashMap::collHash2(int currentindex, string k){
	collisionct1++;						//adds one to first count (each time the initial collision occurs)
	int hashVal = currentindex;				//the new value after hashing
	while(map[hashVal] != NULL){		//if the position is already filled, move on
		if(map[hashVal]->keyword == k){		//if the keyword at that index matches the given keyword it'll break the loop
			break;
		}
		collisionct2++;				//adds one to the second count (for each additional collision)
		if(hashVal >= mapSize - 1){	//if the values goes out of the map
			hashVal = 0;			//bring it back to 0
		}
		else{
			hashVal ++;				//linear probing, adds 1 each time
		}
	}
	return hashVal;
}

int hashMap::findKey(string k){
	 if(map[getIndex(k)]->keyword == k){	//if the keyword matches the value found at that index
		 return getIndex(k);				//return that index
	 }
	 else{
		 return -1;							//return -1 otherwise (keyword not equal or null)
	 }
}

void hashMap::printMap(){
	cout << "Original collisions: "<< collisionct1 << endl;			//Prints original collisions
	cout << "Secondary collisions: "<< collisionct2 << endl;		//Prints secondary collisions
	 for(int i = 0; i < mapSize; i++){		//loops through the entire map
		 if(map[i] != NULL){				//if the value at the current space isn't null
			 cout << map[i];				//print out the data in that map location
		 }
	 }
	 cout << endl;
}

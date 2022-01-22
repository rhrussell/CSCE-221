/*Name: Ryan Russell
Username: rhrussell
Section: CSCE 221_511
Email: rhrussell@tamu.edu*/

#pragma once
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename T>
class HashTable {
private:
	int size;
	list<pair<int, T>> *table;   
	
    int hash(const int _key) {
        return _key % size;
    }
public:
    HashTable(const int _size) {
		this->size = _size;
		this->table = new list<pair<int, T>>[size];
    }
	
	~HashTable(){
		delete[] table;
		this->size = 0;
	}
    
    void insert(const int _key, T _value) {
		int hash_value = hash(_key);
		std::pair<int, T> pair(_key, _value);
		table[hash_value].push_back(pair);
    }
	
	int minChainLen(){
		list<pair<int, T>> list;
		int num;
		int min;
		min = table[0].size();
		for(int i = 0; i < this->size; i++)
		{
			list = table[i];
			num = list.size();
			if(num < min)
			{
				min = num;
			}
		}
		return min;
	}
	
	int maxChainLen(){
		list<pair<int, T>> list;
		int num;
		int max;
		max = table[0].size();
		for(int i = 0; i < this->size; i++)
		{
			list = table[i];
			num = list.size();
			if(num > max)
			{
				max = num;
			}
		}
		return max;
	}
	
	double averageChainLen(){		
		list<pair<int, T>> list;
		double num;
		double sum;
		double average;
		for(int i = 0; i < this->size; i++)
		{
			list = table[i];
			num = list.size();
			sum += num;
		}
		average = sum/this->size;
		return average;
	}
    
    T* search(int _key) {
		int index = hash(_key);
		T* value = nullptr;
		for(auto itr = table[index].begin(); itr != table[index].end(); itr++)
		{
			if(_key == itr->first)
			{
				value = &itr->second;
				break;
			}
		}
		return value;
		//return T();
    }  
};
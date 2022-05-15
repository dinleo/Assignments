#include "wordfrequency.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>


using namespace std;

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2022. 5. 1
  *
  */

WordFrequency::WordFrequency()
{
	map = new WordFreqMap;
}

WordFrequency::~WordFrequency()
{
	delete map;
}

void WordFrequency::ReadText(const char* filename)
{
	fstream file(filename);
    stringstream ss;
    string s;
    string sub;

    if(file.is_open()){
        ss << file.rdbuf();
        s = ss.str();
        file.close();
    }

    transform(s.begin(),s.end(),s.begin(), ::tolower);

    for(int i=0;i<s.size();i++){
        if(('a' <= s[i]) && (s[i] <= 'z')){
            sub += s[i];
        } else if(sub != ""){
            IncreaseFrequency(sub);
            sub = "";
        }
    }
}

int WordFrequency::GetFrequency(const std::string word)
{
	if(map->find(word)!=NULL){
        return map->find(word)->val;
    }
	return 0;
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
    int frq = GetFrequency(word);
    map->insert(word,frq + 1);
}
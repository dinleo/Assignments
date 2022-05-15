//#include "wordfrequency.h"
#include <iostream>
#include <functional>
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

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	delete[] ht;
}
	
template <class HashMapElemType>
HashMapElemType*
HashMap<HashMapElemType>::find(const KeyType k) 
{
    int hv = hashfunction(k);
    MapElem<KeyType, ValType>* curr = ht[hv];
    while(curr != NULL){
        if (curr->key == k){
            return curr;
        }
        curr = curr->link;
    }

    return NULL;
}
	
template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
    int hv = hashfunction(k);

    MapElem<KeyType, ValType>* mpel = new MapElem<string, int>;
    mpel->key = k;
    mpel->val = v;
    mpel->link = NULL;

    if(ht[hv]==NULL){ // 새로운 해쉬값 (k-v pair 추가)
        ht[hv] = mpel;
        mapsize += 1;
    } else{ // 중복 해쉬값 존재
        MapElem<string, int>* curr = ht[hv];
        MapElem<string, int>* prev;
        while(curr != NULL){
            if (curr->key == k){ // 중복 키 존재 (v 변경)
                curr->val=v;
                return;
            }
            prev = curr;
            curr = curr->link;
        }
        // 중복 해쉬값 & 새로운 키 (k-v pair 추가)
        prev->link = mpel;
        mapsize += 1;
    }
}
		
template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
    int hv = hashfunction(k);
    MapElem<KeyType, ValType>*  curr = ht[hv];
    MapElem<KeyType, ValType>*  prev = NULL;
    while(curr!=NULL){
        if (curr->key==k){ // 키 발견
            if(prev==NULL){ // 이전키 없음(첫 노드)
                ht[hv] = curr->link;
            } else{ // 이전키 있음(중간/마지막 노드)
                prev->link = curr->link;
            }
            delete curr;
            mapsize -= 1;
            return true;
        }
        prev = curr;
        curr = curr->link;
    }
    // 키 발견 못 함
	return false;
}
	
template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	int hash_val;
    int num = 0;
    for(int i=0; i<k.length(); i++){
        num += k[i];
    }

    hash_val = num%divisor;

	return hash_val;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
    if (isEmpty()){
        cout<< "Text is empty" << endl;
        return;
    }

    MapElem<KeyType, ValType>* curr;
    KeyType keys[mapsize];
    ValType vals[mapsize] = {0};

	for(int i=0; i<capacity; i++){ // 기존 map 탐색
        curr = ht[i];
        while(curr!=NULL){ // Elem 발견
            KeyType key = curr->key;
            ValType val = curr->val;


            int j = 0;
            while(val <= vals[j]){
                j++;
            }
            for(int k=mapsize-1; j<k; k--){
                if(vals[k-1]==0){
                    continue;
                }
                keys[k] = keys[k-1];
                vals[k] = vals[k-1];
            }
            keys[j] = key;
            vals[j] = val;

            curr = curr->link;
        }
    }

    for(int i=0; i<mapsize; i++){
        if(vals[i]==0){
            break;
        }
        cout << keys[i] << ":" << vals[i] << endl;
    }
}
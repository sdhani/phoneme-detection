/*
Author: Shania Dhani
Course: CSCI-135
Instructor: Prof. Zamansky
Assignment: Project 02
This program uses the CMU Pronunciation Dictionary to find
similarities among the pronunciations of a given word and the
words in the dictionary. These similarities include but are not
limited to phoneme manipluation and comparison for AddPhoneme, 
Remove Phoneme, and ReplacePhoneme word.
*/

#include <iostream>
#include <fstream>
using namespace std;
//Takes a string and splits it on space, returning the
//before and after values through call by reference
void splitOnSpace(string s, string & before, string & after){
  // reset strings
  before = ""; 
  after = "";
  // accumulate before space
  int i = 0; 
  // skip the space
  while (i < s.size() && not isspace(s[i])){ 
    before += s[i]; 
    i++; 
  }
  i++;
  //accumulate after space
  while (i < s.size()){ 
    after += s[i]; 
    i++; 
  }
}

//Takes in a word w and returns word w in all caps
string toCapital(string w){
  for(int i = 0; i < w.size(); i++){
    if((w[i] >= 'a') && (w[i] <= 'z')){
      w[i] = (char)((int)w[i] -32);
    }
  }
  return w;
}

//Takes in a word w and returns its pronunciation if 
//it is in the dictionary
string pronounce(string w){
  ifstream file("cmudict.0.7a.txt"); //open dictionary
  string search, word, pronunciation; //dictonary search declarations
  
  //while reading dictionary, split the word from the pronunciation 
  while(getline(file, search)){
    splitOnSpace(search, word, pronunciation);
    //if the word is the same as the user word w, 
    //return pronunciation
    if(word == w){
      return pronunciation;
    }
  }
  file.close();
  return "Not found";//else return "NotFound"
}

//Takes in a word's pronunciation, and returns the
//total amount of phonemes in it
int countPhoneme(string pronunciation){
  int ctr = 0;
  for(int i = 0; i < pronunciation.length(); i++){
    if(pronunciation[i]== ' '){
      ctr++;
    }
  }
  return ctr;
}

//Takes in a string and a character, and returns true
//if the char is in the string
bool charInString(string w, char symbol){
  for(int i = 0; i < w.length(); i++){
    if(w[i] == symbol){
      return true;
    }    
  }
  return false;
}

//Takes in a pronunciation and a phoneme and returns true 
//if that phoneme is in the pronunciation
bool foundPhoneme(string & wPronounce, string phoneme){
  //builds the phoneme in wPronounce to compare to the given phoneme
  string wPhoneme = ""; 
  //for the length of the pronunciation, build each phoneme in
  //pronunciation, and compare it to the given phoneme
  for(int i = 0; i < wPronounce.length(); i++){
    if(wPronounce[i] == ' '){
      //if phoneme is in this pronounciation, make wPronounce
      //equal to the remaining phonemes that were not checked
      //and return true. This preserves phoneme placement and order
      if(wPhoneme == phoneme){
        wPronounce = wPronounce.substr(i, wPronounce.length()-i);
        return true;
      }  
      wPhoneme = ""; //reset wPhoneme to build the next one
    }else{
      wPhoneme += wPronounce[i];//build the next Phoneme
    }   
  }
  //checks the last phoneme built, that is not included in loop above
  if(wPhoneme == phoneme){
    wPronounce = ""; //there are no remaining phonemes 
    return true; //returns true if phoneme is in wPronounce
  }
  return false;// returns false if the phoneme is not in wPronounce
}

//Takes in two pronounciations: one from the word w, and the other
//from the dictionary search(after), and returns the amount of phonemes 
//that they both have in common
int comparePhoneme(string wPronounce, string afterPronounce){
  //counts the amount of phonemes found in both pronunciations
  string phoneme = "";
  int phonemeFound = 0;  
  //for length of wPronounce, if a phoneme in wPronounce is in
  //afterPronounce, count it.
  for(int i = 1; i < wPronounce.length(); i++){
    if(wPronounce[i] == ' ' && foundPhoneme(afterPronounce, phoneme)){
      phonemeFound++;
      phoneme = ""; //reset phoneme to build the next
    }else if(wPronounce[i] == ' '){
      phoneme = "";//reset phoneme to build the next
    
    }else if(i == wPronounce.length()-1){//accounts for last phoneme
      phoneme += wPronounce[i];
      if(foundPhoneme(afterPronounce, phoneme)){
        phonemeFound++;
      }
    }else{
      //builds the phoneme in wPronounce for comparison
      phoneme += wPronounce[i];
    }
  }
  return phonemeFound;
}

//Takes in two pronounciations: one from the word w, and the other
//from the dictionary search(after), and returns the amount of phonemes
//they have not only in common, but in order
int replace(string afterPronounce, string wPronounce){
  int phonemeCtr = 0; //keeps track of the phoneme 'index' in wPronounce
  int wTotalPhoneme = countPhoneme(wPronounce);//total amount of phonemes in wPronounce
  int ctr = 0; //counts the amount of phonemes that are both found in afterPronun and 
               //wPronounce AND follows the phoneme placement order as it does in wPronounce
  string tempAfter = afterPronounce; //copies afterPronounce so that it can rewrite 
                                     //tempAfter's memory and not afterPronounce's
  string phoneme = "";
      
  for(int i = 1; i < wPronounce.length(); i++){
    if(wPronounce[i] == ' '){
      phonemeCtr++; //marks phoneme 'index' in wPronounce
      //if phoneme is in tempAfter AND the amount of phonemes
      //remaining in tempafter is the same as the amount in wPronounce
      //where order is preserved, then add one to counter. 
      if(foundPhoneme(tempAfter, phoneme) && 
        countPhoneme(tempAfter) == wTotalPhoneme-phonemeCtr){
        ctr++; 
      }
      phoneme = "";//resets phoneme
    }else{
      phoneme += wPronounce[i];//builds phoneme
    }
  }  
  //added one to Phoneme Ctr bcs the above loop doesnt check the last phoneme nor
  //count it bcs there is no space at the end of the word.
  if(foundPhoneme(tempAfter, phoneme)&& 
    countPhoneme(tempAfter) == wTotalPhoneme-(phonemeCtr+1)){
    ctr++;   
  }
  return ctr;
}

void analyzePhoneme(string w){
  ifstream file("cmudict.0.7a.txt");
  string search, before, after,  wPronounce = pronounce(w);
  //copies after so that it can rewrite the duplicates memory and not the original's
  string tempafter;    
  int wCtr = countPhoneme(wPronounce);//stores amount of phonemes in w
  int replaceCtr;//will store the replace comparison for phonemes
    
  //intializes the return strings
  string identical = "", addPhoneme = "", removePhoneme = "", replacePhoneme = "";
  //runs through the entire dictionary
  while(getline(file, search)){
    splitOnSpace(search, before, after);
    tempafter = after;
    //if the Pronunciation is identical to w's but the word itself is different
    //add to identical string
    if(wPronounce == after && before != w){
      identical += before + " ";
    }
    //if the amount of similar Phonemes in w and the dictionary word is
    //equal to the the amount of phonemes in w, and the dictionary word has 
    //one more phoneme total than w, add dictionary word to addPhoneme string
    if(comparePhoneme(wPronounce, tempafter) == wCtr && countPhoneme(after) == (wCtr+1)){
      if(!charInString(before, ')')){//ignores multiple pronunciations
        addPhoneme += before + " ";
      }
    }
    //if the amount of similar Phonemes in w and the dictionary word is
    //one less than the amount of phonemes in w, and the dictionary word has 
    //one less total phonemes than w, add dictionary word to removePhoneme string
    if(comparePhoneme(wPronounce,tempafter) == wCtr-1 && countPhoneme(after) == wCtr-1){
      if(!charInString(before, ')')){//ignores multiple pronunciation
        removePhoneme += before + " ";
      }
    }
    //if the amount of similar Phonemes in w and the dictionary word is one less 
    //than the amount of phonemes in w, and the dictionary word has the same 
    //amount of phonemes than w, add dictionary word to replacePhoneme string
    if(comparePhoneme(wPronounce, tempafter) == wCtr-1 && countPhoneme(after) == wCtr){
      tempafter = after;//resets after for string manipulation
      //counts phoneme similarity where order is preserved
      replaceCtr = replace(tempafter, wPronounce);
      //only one phoneme should be replaced, so replaceCtr should have a similarity
      //of the total phonemes in w-1
      if(replaceCtr == countPhoneme(wPronounce)-1){
        if(!charInString(before, ')')){//ignores multiple pronunciations
          replacePhoneme += before + " ";
        }
      }
    }
  }
  cout << "Identical: "<< identical << endl;
  cout << "Add Phoneme: " << addPhoneme << endl;
  cout << "Remove Phoneme: " << removePhoneme << endl;
  cout << "Replace Phoneme: " << replacePhoneme << endl;//replacePhoneme << endl;
  file.close();
}

int main(){
  string w;
  cin >> w; 
  w = toCapital(w);
  //Runs Pronounce, Identical, AddPhoneme, RemovePhoneme, and ReplacePhoneme
  cout << "Pronounce: " << pronounce(w) << endl;
  analyzePhoneme(w);
  return 0;
}
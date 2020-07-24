# Phoneme Class Project
> A C++ Class Project.

   This program uses the CMU Pronunciation Dictionary to find similarities 
among the pronunciations of a given word and the words in the dictionary. 

### Capabilities

These comparisons extend for words whose pronunciations differ from the input 
word by: 
   - [x] one additional phoneme *[Add Phoneme]* 
   - [x] one less phoneme *[Remove Phoneme]*
   - [x] pronunciations with the same amount of phonemes as the input word, with only one differing phoneme from the original word *[Replace Phoneme]*. 
   - [x] pronunciation of the original word other words that 
   - [x] pronunciation of words with identical pronunciation to the input word. 

### Instructions: 

1. Download the cmudict.0.7a.txt and the pronounce.cpp application.
2. Build the pronounce program using the following command in the terminal:

    `g++ pronounce.cpp`
    
    `./a.out`
    
3. Open up your terminal and type any word into your terminal or shell. and click `ENTER` to see 
how its pronunciation compares to other words available in the CMU dictionary.

---
```
##### Example Output

Input the word *donut*

      donut  
      Pronounce:  D OW1 N AH2 T  
      Identical: DOUGHNUT   
      Add Phoneme: DONUTS DONUTS' DOUGHNUTS   
      Remove Phoneme: DON'T   
      Replace Phoneme: DONAT DONATE   

``` 

> Date: March 2018 - May 2018

 

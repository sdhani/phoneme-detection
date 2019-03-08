## Phoneme Class Project

*A C++ Class Project.*

   This program uses the CMU Pronunciation Dictionary to find similarities 
among the pronunciations of a given word and the words in the dictionary. 
These comparisons extend for words whose pronunciations differ from the input 
word by one additional phoneme *[Add Phoneme]*, one less phoneme *[Remove Phoneme]*, 
or pronunciations with the same amount of phonemes as the input word, except with
it contains one differing phoneme from the original word *[Replace Phoneme]*. 
It also shows the pronunciation of the original word, as well as other words that 
have an identical pronunciation to the input word. 

### Instructions: 

1. Download the cmudict.0.7a.txt and the pronounce.cpp application.
2. Build the pronounce program using the following command in the terminal:

    `g++ pronounce.cpp`
    
    `./a.out`
    
3. **Now you may type any word into your terminal or shell and click enter to see 
how its pronunciation compares to other words available in the CMU dictionary.**

====================================================================================

**Example Output**

Input the word *donut*

      donut  
      Pronounce:  D OW1 N AH2 T  
      Identical: DOUGHNUT   
      Add Phoneme: DONUTS DONUTS' DOUGHNUTS   
      Remove Phoneme: DON'T   
      Replace Phoneme: DONAT DONATE   


###### Date: March - May 2018

 

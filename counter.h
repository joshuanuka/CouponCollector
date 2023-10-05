#pragma once
#include <iostream>
#include <vector>    // if you wish to use this
using namespace std;


class Counter {
    private:
    int size;
    vector<int> *nums;

    public:
    Counter(int n):size(n){
      nums= new vector<int>[n];        //Creates an array of vectors of size n
    }
    void collect(int j){
      nums[j].push_back(1);            //Add a '1' to a vaector to signify a collected coupon
    }
    int get_count(int j) const{
      return nums[j].size();           //returns size of vector at index n
    }
    int get_total_count() const{
      int count=0;
      for (int k=0;k<size;k++){       //loops through all vectors in the array
        count+=nums[k].size();        //gets total count at each iteration
      }
      return count;
    }
    int most_common_type() const{
      int max=0;
      int max_coupon=0;
      for (int k=0;k<size;k++){
        if(nums[k].size()>max){      //checks condition for max count
          max=nums[k].size();       //updates the max coupon count
          max_coupon=k ;            //keeps track of most common coupon so far
        }
      }
      return max_coupon;
    }
    bool done() const{
      bool found=true;            
      for (int k=0;k<size;k++){
        if (nums[k].size()==0){      //if a vector is empty the loop breaks
          found=false;               // and the fxn returns false
          break;
        } 
      }
      return found ;
    }
    void reset(){
      for (int k=0;k<size;k++){   
        nums[k].clear();            //empties all the vectors created
      }
    }

};  // end of Counter class
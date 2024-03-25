#include<algorithm>
#include<iostream>
#include<vector>
#include<cassert>

template<typename T> 
int recursive_binary_search(std::vector<T> elements, T target, int low, int high){
    if (low > high){
        return -1;
    }
    int mid = (high+low) / 2;

    if (elements[mid] == target){
        return mid;
    }
    else if (elements[mid] > target){
        return recursive_binary_search(elements, target, low, mid-1);
    }
    else{
        return recursive_binary_search(elements, target, mid+1, high);
    }
}

template<typename T> 
int iterative_binary_search(std::vector<T> elements, T target){
    int low = 0 ;
    int high = elements.size();
    while (low <= high){
        int mid = (high+low)/2;
        if (elements[mid] == target){
            return mid;
        }
        else if (elements[mid] > target){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }

    }
    return -1;
}

int main(int argc, char const *argv[])
{
    std::vector<int>v = {-1,0,3,5,9,12,9};
    int target = 12;
    int gt = std::binary_search(v.begin(),v.end(),target);
    assert(recursive_binary_search(v,target,0,v.size()-1) == gt );
    assert(iterative_binary_search(v,target) == gt);
    return 0;
}

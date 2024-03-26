#include <cassert>
#include "dynamic_array.h"

int main(int argc, char const *argv[])
{
    // test array creation
    auto test_array = DynamicArray<int>(5);
    assert(test_array.get_capacity() == 5);
    assert(test_array.get_size() == 0);

    //test push
    for(int i = 1 ; i<= 5; ++i){
        test_array.push(1);
    }
    assert(test_array.get_size() == 5);

    //test insertion
    test_array.insert(1,3);
    assert(test_array.get(1) == 3);

    //test prepend
    test_array.prepend(2);
    assert(test_array.get(0) == 2);


    //test find
    assert(test_array.find(1) == 1);
    assert(test_array.find(6) == -1);

    //test deletion
    test_array.remove_element(1);
    assert(test_array.get_size() == 2);

    return 0;
}

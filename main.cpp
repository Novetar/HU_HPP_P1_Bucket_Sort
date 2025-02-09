#include <iostream>
#include <vector>


// int int_test() {
//     int test = 1;
//     return test;
// }


void print_vector(const std::vector<int>& input) {
    std::cout << "{ ";
    for (auto i: input) {
        std::cout << i << " ";
    }
    std::cout << "}" << std::endl;
}


void print_vector_vector(const std::vector<std::vector<int>>& input) {
    for (auto i: input) {
        print_vector(i);
    }
}


std::vector<int> bucket_sort(std::vector<int>& vector_to_sort) {

    std::vector<std::vector<int>> bucket_array(10);  // Creates a two dimensional array with the 10 buckets

    int vector_size = vector_to_sort.size();

    for (int i = 0; i < 1; i++) {
        // Distribution pass
        for (int number : vector_to_sort) {
            std::string number_as_string = std::to_string(number);  // int to string
            int integer = number_as_string[i] - '0';  // Converts char to int by subtracting ascii codes. Example 51 (3) - 48 (0) = 3
            bucket_array[integer].push_back(number);  // Adds the number to the corresponding bucket.
        }

        // Debugging prints
        std::cout << std::endl;
        std::cout << "Distribution pass: " << i << std::endl;
        print_vector_vector(bucket_array);

        // Gathering pass
        vector_to_sort.clear();  // Removes all elements from the vector.
        for (std::vector<int> bucket: bucket_array) {
            for (int number : bucket) {
                vector_to_sort.push_back(number);
            }
        }
    }
    return vector_to_sort;
}


int main() {
    std::vector<int> vector_to_sort = {4, 5, 3, 2, 1};

    std::cout << "Array Pre Sorting" << std::endl;
    print_vector(vector_to_sort);
    bucket_sort(vector_to_sort);
    std::cout << std::endl;
    std::cout << "Array Post Sorting" << std::endl;
    print_vector(vector_to_sort);

    // // test negative ints
    // int test = -123;
    // std::string test_as_string = std::to_string(test);
    // std::cout << test_as_string << std::endl;

    // system("pause");  // Halts the program (so the terminal doesn't close instantly)
    return 0;
}




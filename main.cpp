#include <iostream>
#include <vector>
#include <cmath>


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

// Sort given vector by using bucket sort
std::vector<int> bucket_sort(std::vector<int>& vector_to_sort) {

    std::vector<std::vector<int>> pos_bucket_array(10);  // Creates a two dimensional array with 10 buckets
    std::vector<std::vector<int>> neg_bucket_array(10);

    // Find the biggest number and get its size
    int max_number = -999999999;
    int max_number_size;
    for (int number : vector_to_sort) {
        if (number > max_number) {
            max_number = number;
        }
    max_number_size = std::to_string(max_number).size();
    }

    for (int i = 0; i < max_number_size; i++) {

        // Distribution pass
        // Clears buckets
        for (std::vector<int>& bucket : pos_bucket_array) {
            bucket.clear();
        }
        for (int number : vector_to_sort) {
            int factor = std::pow(10, i+1);
            int second_factor = std::pow(10, i);
            int focus = (number % factor - number % second_factor) / second_factor;  // (343 modulo 100 - 343 modulo 10) / 10 = 4
            pos_bucket_array[focus].push_back(number);  // Adds the number to the corresponding bucket.
        }

        // Debugging prints
        std::cout << std::endl;
        std::cout << "Distribution pass on index: " << i << std::endl;
        print_vector_vector(pos_bucket_array);

        // Gathering pass
        // Clears vector_to_sort
        vector_to_sort.clear();
        for (std::vector<int> bucket: pos_bucket_array) {
            for (int number : bucket) {
                vector_to_sort.push_back(number);
            }
        }
    }
    return vector_to_sort;
}


int main() {
    std::vector<int> vector_to_sort = {4356, 5364, 531, 322, 411, 788};

    std::cout << "Array Pre Sorting" << std::endl;
    print_vector(vector_to_sort);
    bucket_sort(vector_to_sort);
    std::cout << std::endl;
    std::cout << "Array Post Sorting" << std::endl;
    print_vector(vector_to_sort);

    return 0;
}




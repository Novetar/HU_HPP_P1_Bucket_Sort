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

    std::vector<std::vector<int>> pos_buckets_vector(10);  // Creates a two dimensional array with 10 buckets for positive numbers
    std::vector<std::vector<int>> neg_buckets_vector(10);  // Creates a two dimensional array with 10 buckets for negative numbers

    // Find the length of the longest number.
    int max_number_size = 0;
    for (int number : vector_to_sort) {
        int number_size = std::to_string(number).size();
        if (number_size > max_number_size) {
            max_number_size = number_size;
        }
    }

    for (int i = 0; i < max_number_size; i++) {

        // Distribution pass
        // Clears buckets
        for (std::vector<int>& bucket : pos_buckets_vector) {
            bucket.clear();
        }
        for (int number : vector_to_sort) {
            int factor = std::pow(10, i+1);
            int second_factor = std::pow(10, i);
            int focus = (number % factor - number % second_factor) / second_factor;  // (343 modulo 100 - 343 modulo 10) / 10 = 4
            pos_buckets_vector[focus].push_back(number);  // Adds the number to the corresponding bucket.
        }

        // Debugging prints
        std::cout << std::endl;
        std::cout << "Distribution pass on index: " << i << std::endl;
        print_vector_vector(pos_buckets_vector);

        // Gathering pass
        // Clears vector_to_sort
        vector_to_sort.clear();
        for (std::vector<int> bucket: pos_buckets_vector) {
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

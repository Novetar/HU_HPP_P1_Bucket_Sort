#include <iostream>
#include <vector>
#include <cmath>


void print_vector(const std::vector<int> &input) {
    std::cout << "{ ";
    for (auto i: input) {
        std::cout << i << " ";
    }
    std::cout << "}" << std::endl;
}


void print_vector_vector(const std::vector<std::vector<int>> &input) {
    for (auto i: input) {
        print_vector(i);
    }
}

// Sort given vector by using bucket sort
std::vector<int> bucket_sort(std::vector<int> &vector_to_sort) {

    std::vector<int> pos_to_sort;
    std::vector<int> neg_to_sort;

    std::vector<std::vector<int>> pos_buckets(10);  // Creates a two dimensional array with 10 buckets for positive numbers
    std::vector<std::vector<int>> neg_buckets(10);  // Creates a two dimensional array with 10 buckets for negative numbers

    // Find the length of the longest number.
    // TODO: Maybe add a check if the number is negative because negative number is longer because of -
    int max_number_size = 0;
    for (const int &number : vector_to_sort) {
        int number_size = std::to_string(number).size();
        if (number_size > max_number_size) {
            max_number_size = number_size;
        }
    }

    // Sort the numbers into positive and negative
    for (const int &number : vector_to_sort) {
        if (number < 0) {
            neg_to_sort.push_back(number);
        } else {
            pos_to_sort.push_back(number);
        }
    }

    // Sort the vectors
    for (int i = 0; i < max_number_size; i++) {

        // Distribution pass
        // Clears buckets
        for (std::vector<int> &bucket : pos_buckets) {
            bucket.clear();
        }
        for (std::vector<int> &bucket : neg_buckets) {
            bucket.clear();
        }
        // Positive numbers
        for (const int &number : pos_to_sort) {
            int factor = std::pow(10, i+1);
            int second_factor = std::pow(10, i);
            int focus = (number % factor - number % second_factor) / second_factor;  // (343 modulo 100 - 343 modulo 10) / 10 = 4
            pos_buckets[focus].push_back(number);  // Adds the number to the corresponding bucket.
        }
        // Negative numbers
        for (const int &number : neg_to_sort) {
            int factor = std::pow(10, i+1);
            int second_factor = std::pow(10, i);
            int focus = (number % factor - number % second_factor) / second_factor;  // (343 modulo 100 - 343 modulo 10) / 10 = 4
            neg_buckets[focus].push_back(number);  // Adds the number to the corresponding bucket.
        }

        // Debugging prints
        std::cout << std::endl;
        std::cout << "Distribution pass on index: " << i << std::endl;
        print_vector_vector(pos_buckets);
        print_vector_vector(neg_buckets);

        // Gathering pass
        pos_to_sort.clear();
        neg_to_sort.clear();

        // Positive numbers
        for (std::vector<int> bucket: pos_buckets) {
            for (int number : bucket) {
                pos_to_sort.push_back(number);
            }
        }
        // Negative numbers
        for (std::vector<int> bucket: neg_buckets) {
            for (int number : bucket) {
                neg_to_sort.push_back(number);
            }
        }
    }
    vector_to_sort.clear();
    vector_to_sort.insert(vector_to_sort.end(), neg_to_sort.begin(), neg_to_sort.end());
    vector_to_sort.insert(vector_to_sort.end(), pos_to_sort.begin(), pos_to_sort.end());
    return vector_to_sort;
}


int main() {
    std::vector<int> vector_to_sort = {4356, 5364, 531, 322, 411, 788, -2};

    std::cout << "Array Pre Sorting" << std::endl;
    print_vector(vector_to_sort);
    bucket_sort(vector_to_sort);
    std::cout << std::endl;
    std::cout << "Array Post Sorting" << std::endl;
    print_vector(vector_to_sort);

    return 0;
}

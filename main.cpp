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

int find_longest_number(const std::vector<int> &vector) {
    // Find the longest number in the vector
    // Example: 5432 => 4
    int max_number_size = 0;
    for (const int &number : vector) {
        int number_size = std::to_string(number).size();
        if (number_size > max_number_size) {
            max_number_size = number_size;
        }
    }
    return max_number_size;
}


void pos_bucket_sort(std::vector<int> &pos_vector_to_sort) {

    std::vector<std::vector<int>> pos_buckets(10);  // Creates a two dimensional array with 10 buckets

    int max_number_size = find_longest_number(pos_vector_to_sort);

    // Sort the vectors
    for (int i = 0; i < max_number_size; i++) {

        // Distribution pass
        // Clears buckets
        for (std::vector<int> &bucket : pos_buckets) {
            bucket.clear();
        }
        // Sort numbers into buckets
        for (const int &number : pos_vector_to_sort) {
            int factor = std::pow(10, i+1);
            int second_factor = std::pow(10, i);
            int focus = (number % factor - number % second_factor) / second_factor;  // (343 modulo 100 - 343 modulo 10) / 10 = 4
            pos_buckets[focus].push_back(number);  // Adds the number to the corresponding bucket.
        }

        // Gathering pass
        pos_vector_to_sort.clear();
        // Convert numbers from buckets back into the vector
        for (std::vector<int> bucket: pos_buckets) {
            for (int number : bucket) {
                pos_vector_to_sort.push_back(number);
            }
        }
    }
}


void neg_bucket_sort(std::vector<int> &neg_vector_to_sort) {

    std::vector<std::vector<int>> neg_buckets(10);  // Creates a two dimensional array with 10 buckets


    // Make numbers positive
    for (int &number : neg_vector_to_sort) {
        number = number * -1;
    }

    int max_number_size = find_longest_number(neg_vector_to_sort);

    // Sort the vectors
    for (int i = 0; i < max_number_size; i++) {

        // Distribution pass
        // Clears buckets
        for (std::vector<int> &bucket : neg_buckets) {
            bucket.clear();
        }

        // Sort numbers into buckets
        // TODO: change logic here to (9 - number)
        for (const int &number : neg_vector_to_sort) {
            int factor = std::pow(10, i+1);
            int second_factor = std::pow(10, i);
            int focus = (number % factor - number % second_factor) / second_factor;  // (343 modulo 100 - 343 modulo 10) / 10 = 4
            neg_buckets[focus].push_back(number);  // Adds the number to the corresponding bucket.
        }

        // Gathering pass
        neg_vector_to_sort.clear();
        // Convert numbers from buckets back into the vector
        for (std::vector<int> bucket: neg_buckets) {
            for (int number : bucket) {
                neg_vector_to_sort.push_back(number);
            }
        }
    }
}

// Sort given vector by using bucket sort
std::vector<int> bucket_sort(std::vector<int> &vector_to_sort) {

    std::vector<int> pos_to_sort;
    std::vector<int> neg_to_sort;

    // Sort the numbers into positive and negative
    for (const int &number : vector_to_sort) {
        if (number < 0) {
            neg_to_sort.push_back(number);
        } else {
            pos_to_sort.push_back(number);
        }
    }

    pos_bucket_sort(pos_to_sort);
    neg_bucket_sort(neg_to_sort);


        // // Debugging prints
        // std::cout << std::endl;
        // std::cout << "Distribution pass on index: " << i << std::endl;
        // print_vector_vector(pos_buckets);
        // print_vector_vector(neg_buckets);


    vector_to_sort.clear();
    vector_to_sort.insert(vector_to_sort.end(), neg_to_sort.begin(), neg_to_sort.end());
    vector_to_sort.insert(vector_to_sort.end(), pos_to_sort.begin(), pos_to_sort.end());
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

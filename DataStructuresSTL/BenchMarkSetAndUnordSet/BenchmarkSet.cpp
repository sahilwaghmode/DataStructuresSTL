//
//  BenchmarkSet.cpp
//  DataStructuresSTL
//
//  Created by Sahil Waghmode on 16/07/24.
//

#include "BenchmarkSet.hpp"


#include <iostream>
#include <set>
#include <unordered_set>
#include <chrono>
namespace BenchMarkSet
{

void BenchMarkOrderedSet()
{
    std::set<int> my_set;
    const int num_elements = 1000000; // Number of elements to insert
    
    // Insert elements into the sets
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        my_set.insert(i);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto set_insertion_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    
    std::cout << "Set insertion time: " << set_insertion_time << " ms\n";
    
    // Look up an element in the sets
    start_time = std::chrono::high_resolution_clock::now();
    my_set.find(500000);
    my_set.find(500001);
    my_set.find(500002);
    my_set.find(500003);
    my_set.find(500004);
    my_set.find(500005);
    end_time = std::chrono::high_resolution_clock::now();
    
    // Measure lookup time
    auto set_lookup_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "Set lookup time: " << set_lookup_time << " ns\n";
}

void BenchMarkOrderedSetWithString()
{
    std::set<std::string> my_set;
    const int num_elements = 1000000; // Number of elements to insert
    
    // Insert elements into the sets
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        my_set.insert(std::to_string(i));
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto set_insertion_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    
    std::cout << "Set of string insertion time: " << set_insertion_time << " ms\n";
    
    // Look up an element in the sets
    start_time = std::chrono::high_resolution_clock::now();
    my_set.find("500000");
    end_time = std::chrono::high_resolution_clock::now();
    
    // Measure lookup time
    auto set_lookup_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "Set of string lookup time: " << set_lookup_time << " ns\n";
}

void BenchMarkUnorderedSet()
{
    const int num_elements = 1000000; // Number of elements to insert
    
    // Create a set and an unordered_set
    std::unordered_set<int> my_unordered_set;
    
    // Insert elements into the sets
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        my_unordered_set.insert(i);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto set_insertion_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    
    std::cout << "Unordered Set insertion time: " << set_insertion_time << " ms\n";
    
    start_time = std::chrono::high_resolution_clock::now();
    my_unordered_set.find(500000);
    my_unordered_set.find(500001);
    my_unordered_set.find(500002);
    my_unordered_set.find(500003);
    my_unordered_set.find(500004);
    my_unordered_set.find(500005);
    end_time = std::chrono::high_resolution_clock::now();
    
    // Measure lookup time
    auto set_lookup_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "Unordered Set lookup time: " << set_lookup_time << " ns\n";
}

void BenchMarkUnorderedSetWithString()
{
    const int num_elements = 1000000; // Number of elements to insert
    
    // Create a set and an unordered_set
    std::unordered_set<std::string> my_unordered_set;
    
    // Insert elements into the sets
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        my_unordered_set.insert(std::to_string(i));
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto set_insertion_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    
    std::cout << "Unordered Set of string insertion time: " << set_insertion_time << " ms\n";
    
    start_time = std::chrono::high_resolution_clock::now();
    my_unordered_set.find("500000");
    end_time = std::chrono::high_resolution_clock::now();
    
    // Measure lookup time
    auto set_lookup_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "Unordered Set of string lookup time: " << set_lookup_time << " ns\n";
}

void Run()
{
    BenchMarkOrderedSet();
    BenchMarkUnorderedSet();
    //BenchMarkOrderedSetWithString();
    //BenchMarkUnorderedSetWithString();
}

}

//
//  Algorithms.cpp
//  DataStructuresSTL
//
//  Created by Sahil Waghmode on 10/10/24.
//

#include "Algorithms.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <complex>
#include <cassert>

namespace algorithm
{
void all_of()
{
    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
       std::cout << "All numbers are even\n";

    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<>(),
                                                    std::placeholders::_1, 2)))
       std::cout << "None of them are odd\n";

    struct DivisibleBy
    {
       const int d;
       DivisibleBy(int n) : d(n) {}
       bool operator()(int n) const { return n % d == 0; }
    };

    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7)))
       std::cout << "At least one number is divisible by 7\n";
}

void find()
{
    const auto v = {1, 2, 3, 4};
     
    for (const int n : {3, 5})
        (std::find(v.begin(), v.end(), n) == std::end(v))
            ? std::cout << "v does not contain " << n << '\n'
            : std::cout << "v contains " << n << '\n';

    auto is_even = [](int i) { return i % 2 == 0; };

    for (const auto& w : {std::array{3, 1, 4}, {1, 3, 5}})
        if (auto it = std::find_if(begin(w), end(w), is_even); it != std::end(w))
            std::cout << "w contains an even number " << *it << '\n';
        else
            std::cout << "w does not contain even numbers\n";

    std::vector<std::complex<double>> nums{{4, 2}};
    #ifdef __cpp_lib_algorithm_default_value_type
        // T gets deduced making list-initialization possible
        const auto it = std::find(nums.begin(), nums.end(), {4, 2});
    #else
        const auto it = std::find(nums.begin(), nums.end(), std::complex<double>{4, 2});
    #endif
    assert(it == nums.begin());
}

}

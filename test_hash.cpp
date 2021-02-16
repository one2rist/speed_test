#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <unordered_map>

constexpr size_t KEY_SIZE=5;
constexpr size_t MAP_SIZE=100000;
constexpr size_t TEST_LOOP=100;

namespace cmmn {

using namespace std;

template<typename IntType, size_t Max, size_t Min>
IntType randomInt() {
    static uniform_int_distribution<IntType> dist(Min, Max);
    static mt19937 gen{random_device()()};
    return dist(gen);
}


string gen_random_string(const int len) {
    string tmp_s;
    tmp_s.reserve(len);
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[cmmn::randomInt<size_t, 0, KEY_SIZE>() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

}

int main()
{
    // set of keys to find in hash table
    std::set<std::string> test_keys;
    for (size_t i=0; i<MAP_SIZE; ++i) {
        test_keys.emplace(cmmn::gen_random_string(KEY_SIZE));
    }

    // create hash table
    std::unordered_map<std::string, int> hash;
    for (int i=0; i<MAP_SIZE; ++i) {
        hash[cmmn::gen_random_string(KEY_SIZE)] = 0;
    }

    std::cout << "Test set size: " << test_keys.size() << "(" << MAP_SIZE << ")" << std::endl;
    std::cout << "Hash map size: " << hash.size() << "(" << MAP_SIZE << ")" << std::endl;

    // check all keys from test set
    clock_t t1 = clock();
    size_t found_count(0);
    for (size_t i=0; i<TEST_LOOP; ++i) {
        for (const auto & key : test_keys) {
            if (hash.find(key) != hash.end())
                ++found_count;
        }
    }

    clock_t t2 = clock();

    std::cout << "Loops    : " << TEST_LOOP << std::endl;
    std::cout << "Found    : " << found_count / TEST_LOOP << std::endl;
    std::cout << "Time     : " << (double)(t2-t1)/(double)CLOCKS_PER_SEC << std::endl;

    return 0;
}

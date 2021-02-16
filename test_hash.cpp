#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <unordered_map>
#include <set>
#include <unistd.h>
#include <random>

constexpr size_t KEY_SIZE=5;
constexpr size_t MAP_SIZE=100000;
constexpr size_t TEST_LOOP=100;

namespace cmmn {

using namespace std;

template<typename IntType>
class RandomInt {
    public:
        RandomInt(IntType fromIncl, IntType toIncl)
            : gen(rd())
            , dist(fromIncl, toIncl)
        {
        }
        IntType operator()() {return dist(gen);}
    private:
        random_device rd;
        mt19937 gen;
        uniform_int_distribution<IntType> dist;
};

}

std::string gen_random_string(const int len) {
    std::string tmp_s;
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    tmp_s.reserve(len);
    cmmn::RandomInt<size_t> gen(0,sizeof(alphanum));
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[gen() % (sizeof(alphanum) - 1)];
    return tmp_s;
}


int main()
{
    // set of keys to find in hash table
    std::set<std::string> test_keys;
    for (size_t i=0; i<MAP_SIZE; ++i) {
        test_keys.emplace(gen_random_string(KEY_SIZE));
    }

    // create hash table
    std::unordered_map<std::string, int> hash;
    for (int i=0; i<MAP_SIZE; ++i) {
        auto s = gen_random_string(KEY_SIZE);
        //std::cout << s << std::endl;
        hash[s] = 0;
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

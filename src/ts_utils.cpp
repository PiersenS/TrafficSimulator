/* C++ includes */
#include <random>
/* Simulator includes */
#include "ts_utils.h"

int ts::random(int min, int max) {
    using namespace std;

    random_device rand_dev;
    uniform_int_distribution<int> uid(min, max);

    return uid(rand_dev);
}
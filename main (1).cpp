#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "counter.h"
using namespace std;
using namespace std::chrono;

// rename this main (and change name of original main) if you'd like to do more controlled testing.
int main_test() {
    Counter prizes{20};   // new counter for universe of 20 coupons
    prizes.collect(17);
    prizes.collect(5);
    prizes.collect(5);
    prizes.collect(18);
    bool hey= prizes.done();
    cout<< hey << endl;
    cout << prizes.get_total_count() << endl;  // should print 4, as we've collected 4 coupons
    cout << prizes.get_count(17) << endl;      // should print 1, as we have 1 of coupon #17
    cout << prizes.get_count(18) << endl;      // should print 0, as we have 0 of coupon #18
    cout << prizes.most_common_type() << endl; // should print 5, as coupon #5 is the most common thus far
    prizes.reset();
    prizes.collect(2);
    prizes.collect(17);
    cout << prizes.get_count(17) << endl;      // should print 0, as we have not collected any #17 since being reset
    cout << prizes.most_common_type() << endl; // might print 0, as coupon #0 is tied for most common. could print something else, as all coupons are tied
}

int main_original() {
    srand(time(0));
    cout << fixed << setprecision(3);

    int n, trials;
    cout << "How many coupons? ";
    cin >> n;
    cout << "How many trials? ";
    cin >> trials;

    double avg_coupons = 0;
    double avg_most_common = 0;
    int max_coupons = 0;
    int max_most_common = 0;
    double total_time = 0;

    bool warning{false};

    Counter counter(n);
    for (int i = 0; i < trials; ++i) {
        auto start = chrono::high_resolution_clock::now();
        int coupons_our_count{0};
        while (!counter.done()) {
            int random_coupon = rand() % n;
            counter.collect(random_coupon);
            coupons_our_count++;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        total_time += elapsed.count();

        int total_coupons = counter.get_total_count();
        if (total_coupons != coupons_our_count) warning = true;
        int most_common = counter.get_count(counter.most_common_type());

        avg_coupons += total_coupons;
        avg_most_common += most_common;

        if (total_coupons > max_coupons) {
            max_coupons = total_coupons;
        }

        if (most_common > max_most_common) {
            max_most_common = most_common;
        }

        counter.reset();
    }

    avg_coupons /= trials;
    avg_most_common /= trials;
    total_time /= trials;

    cout << "The average number of coupons collected per trial was " << avg_coupons << endl;
    cout << "The average count for the most common coupon per trial was " << avg_most_common << endl;
    cout << "The average running time per trial was " << total_time << " milliseconds" << endl;
    cout << "Of all trials, the maximum number of coupons collected was " << max_coupons << endl;
    cout << "Of all trials, the maximum number of any one coupon collected was " << max_most_common << endl;

    if (warning) {
        cout << "WARNING: your get_total_count() did not agree with our accounting." << endl;
    }

    return 0;
}

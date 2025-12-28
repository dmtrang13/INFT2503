#include <iostream>
#include <thread>
#include <vector>
using namespace std;

template <class Pred>
struct PF {
    Pred pred; unsigned threads;
};

template <class Pred>
PF<Pred> ParallellFilter(Pred p, unsigned threads = 12) {
    return {move(p), threads};
}

// pipeline operator, returner per-thread buckets
template <class T, class Pred>
vector<vector<T>> operator|(const vector<T>& v, const PF<Pred>& pf) {
    unsigned N = pf.threads ? pf.threads : 1;
    vector<vector<T>> buckets(N);
    vector<thread> workers;
    workers.reserve(N);

    for (unsigned t = 0; t < N; t++) {
        workers.emplace_back([&, t] {
            auto& out = buckets[t];
            for (size_t i = t; i < v.size(); i += N) {
                const T& e = v[i];
                if (pf.pred(e)) out.push_back(e);
            }
        });
    }
    for (auto& th : workers) th.join();
    return buckets;
}

// utskrift
template <class T> 
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "{ ";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) os << ", ";
        os << v[i];
    };
    return os << " }";
}

template <class T> 
ostream& operator<<(ostream& os, const vector<vector<T>>& vv) {
    os << "{ ";
    for (size_t i = 0; i < vv.size(); i++) {
        if (i) os << ", ";
        os << vv[i];
    };
    return os << " }";
}

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << (vec | ParallellFilter([](int e) { return e % 2 == 0; })) << endl;
    cout << (vec | ParallellFilter([](int e) { return e % 2 == 1; })) << endl;
}
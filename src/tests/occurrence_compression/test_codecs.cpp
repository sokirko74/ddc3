// The codecs of the occurrences (ConcordAlgorithm.h): VByte ("archive") and Stream VByte ("svbyte") must return
// the sorted lists they encode: distances of 1-4 bytes, lengths with all the remainders of a group of 4.
#include "ConcordLib/ConcordAlgorithm.h"
#include <cstdio>
#include <random>
#include <vector>

int main() {
    std::mt19937 rng(42);
    int failures = 0;
    for (int test = 0; test < 2000; test++) {
        size_t n = test < 40 ? test : rng() % 3000 + 1;
        int maxbytes = test % 4 + 1;                     // the largest distance: 1..4 bytes
        std::vector<uint32_t> in;
        uint64_t pos = test % 3 == 0 ? 0 : rng() % 1000;  // a list may start at the position 0
        for (size_t i = 0; i < n && pos < 0xFFFFFFFFull; i++) {
            in.push_back((uint32_t)pos);
            uint32_t range = maxbytes == 4 ? (1u << 26) : (1u << (8 * maxbytes)) - 1;
            pos += 1 + rng() % range;
        }
        std::vector<uint32_t> enc, out(4 * in.size() + 8);
        uint32_t count = 0;
        ConvertToStreamVByte(in, enc);
        DeconvertFromStreamVByte(enc.data(), enc.data() + enc.size(), out.data(), count);
        if (count != in.size() || !std::equal(in.begin(), in.end(), out.begin())) {
            printf("Stream VByte: test %d (n=%zu) failed\n", test, in.size());
            failures++;
        }
        if (!in.empty()) {
            ConvertToVariableInteger(in, enc);
            DeconvertFromVariableInteger(enc.data(), enc.data() + enc.size(), out.data(), count);
            if (count != in.size() || !std::equal(in.begin(), in.end(), out.begin())) {
                printf("VByte: test %d (n=%zu) failed\n", test, in.size());
                failures++;
            }
        }
    }
    printf(failures ? "FAILED %d\n" : "codecs ok\n", failures);
    return failures ? 1 : 0;
}

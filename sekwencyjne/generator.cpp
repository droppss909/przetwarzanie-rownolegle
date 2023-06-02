#include <cstdint>

class MersenneTwister {
    private:
        static const int N = 624;
        static const int M = 397;
        static const uint32_t MATRIX_A = 0x9908b0dfUL;
        static const uint32_t UPPER_MASK = 0x80000000UL;
        static const uint32_t LOWER_MASK = 0x7fffffffUL;

        uint32_t mt[N];
        int index;

    public:
        MersenneTwister(uint32_t seed) {
            mt[0] = seed;
            for (int i = 1; i < N; i++) {
                mt[i] = 1812433253UL * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;
            }
            index = N;
        }

        void generateNumbers() {
            for (int i = 0; i < N - M; i++) {
                uint32_t x = (mt[i] & UPPER_MASK) | (mt[i + 1] & LOWER_MASK);
                mt[i] = mt[i + M] ^ (x >> 1) ^ ((x & 1) * MATRIX_A);
            }

            for (int i = N - M; i < N - 1; i++) {
                uint32_t x = (mt[i] & UPPER_MASK) | (mt[i + 1] & LOWER_MASK);
                mt[i] = mt[i + (M - N)] ^ (x >> 1) ^ ((x & 1) * MATRIX_A);
            }

            uint32_t x = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
            mt[N - 1] = mt[M - 1] ^ (x >> 1) ^ ((x & 1) * MATRIX_A);
        }

        uint32_t extractNumber() {
            if (index >= N) {
                generateNumbers();
                index = 0;
            }

            uint32_t y = mt[index];
            y ^= (y >> 11);
            y ^= ((y << 7) & 0x9d2c5680UL);
            y ^= ((y << 15) & 0xefc60000UL);
            y ^= (y >> 18);

            index++;
            return y;
        }
};

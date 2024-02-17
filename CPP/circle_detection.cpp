#include <iostream>
#include <algorithm>
#include <tuple>

// https://en.wikipedia.org/wiki/Cycle_detection
template<typename func_t, typename step_t>
std::tuple<bool, size_t, size_t> tortoise_hare_run(const func_t& run,
                                            step_t origin, size_t maxcircle) {
    size_t circlepoint{0};
    size_t circumference{0};
    step_t tortoise{origin};
    step_t hare{origin};

    // Try to figure out the circumference if there are any circles
    size_t harestop = 1; // the next place for the hare to stop
    while (true) {
        // Hare takes a step, checks whether it's within a circle and
        // exactly one circumference away from tortoise
        hare = run(hare);
        circumference += 1;
        if (tortoise == hare) {
            break;
        }

        // No circle detected yet, keeps the hare running towards the next stop
        if (circumference < harestop) {
            continue;
        }

        // Now the hare has reached it's current stop. Aligns the tortoise with
        // the hare, extends the next stop and try all over again.
        if (harestop >= maxcircle) {
            return std::make_tuple(false, 0, 0);
        }
        tortoise = hare;
        circumference = 0;
        harestop = std::min(harestop<<1, maxcircle);
    }

    // Figures out the point where the circle starts.
    for (tortoise = origin; tortoise != hare; ++circlepoint) {
        tortoise = run(tortoise);
        hare = run(hare);
    }
    return std::make_tuple(true, circlepoint, circumference);
}

int main(int argc, char* argv[]) {
    // size_t N{3}, S{1}, P{1}, Q{1}; // 3
    size_t N{100000000}, S{569099406}, P{1607140150}, Q{823906344}; // 31
    // size_t N{100000000}, S{1506922183}, P{1236189611}, Q{306853238}; // 100000000
    // size_t N{10000000}, S{658061970}, P{695098531}, Q{1430548937}; // 10000000
    // size_t N{100000000}, S{831602480}, P{704408287}, Q{1134515747};

    auto detect = [&P, &Q](size_t step){return (step*P+Q)&0x7FFFFFFF;};
    auto result = tortoise_hare_run(detect, S, N);
    if (std::get<0>(result) == false) {
        std::cout << "No circle was detected. N: " << N << std::endl;
    } else {
        const size_t& circlepoint = std::get<1>(result);
        const size_t& circumference = std::get<2>(result);
        std::cout << "Circle was detected. Starting point: " << circlepoint;
        std::cout << ", circumference: " << circumference << ", N = ";
        std::cout << std::min(N, circlepoint+circumference) << std::endl;
    }
    return 0;
}

#pragma once

#include <benchmark/benchmark.h>


struct DataGenerator
{
    template<class T>
    static std::string make_data(const benchmark::State& state);
};

#include <autodiff.hpp>
namespace aad
{
    thread_local Tape<double> globalTape;
    template<>
    thread_local Tape<double>* ascalar::tape = &globalTape;
}

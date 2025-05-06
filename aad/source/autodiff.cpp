#include <autodiff.hpp>
#include <Tape.hpp>
#include <scalar.hpp>
#include <addutils.hpp>

namespace aad{
    Tape<double> globalTape;
    template<>
    thread_local Tape<double> *Scalar<double>::tape = &globalTape;
    using adouble = Scalar<double>;
}

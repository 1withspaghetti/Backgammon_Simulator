#include "simulation.cpp"
//#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

Results _simulate(Board board) {
    return simulate(&board, 0);
}

double _chanceWin(Results first, Results second) {
    return first.chanceWinAgainst(&second);
}

EMSCRIPTEN_BINDINGS(wasm_main) {
    emscripten::function("simulate", &_simulate);
    emscripten::function("chanceWin", &_chanceWin);

    class_<Board>("Board")
        .constructor<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>()
        ;
    
    class_<Results>("Results")
        .function("probPerTurn", &Results::probPerTurn)
        .function("sum", &Results::sum)
        ;

    value_object<ResultsProbability>("ResultsProbability")
        .field("average", &ResultsProbability::average)
        .field("perTurn", &ResultsProbability::perTurn) // Need to register the array type
        ;

    // Register std::array<double, 24> because ResultsProbability::perTurn is interpreted as such
    value_array<std::array<double, 24>>("array_double_24")
        .element(emscripten::index<0>())
        .element(emscripten::index<2>())
        .element(emscripten::index<1>())
        .element(emscripten::index<3>())
        .element(emscripten::index<4>())
        .element(emscripten::index<5>())
        .element(emscripten::index<6>())
        .element(emscripten::index<7>())
        .element(emscripten::index<8>())
        .element(emscripten::index<9>())
        .element(emscripten::index<10>())
        .element(emscripten::index<11>())
        .element(emscripten::index<12>())
        .element(emscripten::index<13>())
        .element(emscripten::index<14>())
        .element(emscripten::index<15>())
        .element(emscripten::index<16>())
        .element(emscripten::index<17>())
        .element(emscripten::index<18>())
        .element(emscripten::index<19>())
        .element(emscripten::index<20>())
        .element(emscripten::index<21>())
        .element(emscripten::index<22>())
        .element(emscripten::index<23>())
        ;
}

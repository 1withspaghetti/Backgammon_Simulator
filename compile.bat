./emsdk/emsdk activate latest
emcc wasm-main.cpp -o function.html -sEXPORTED_FUNCTIONS=_int_sqrt -sEXPORTED_RUNTIME_METHODS=ccall,cwrap

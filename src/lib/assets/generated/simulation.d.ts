// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
interface WasmModule {
}

export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  // @ts-ignore - If targeting lower than ESNext, this symbol might not exist.
  [Symbol.dispose](): void;
  clone(): this;
}
export interface Board extends ClassHandle {
}

export interface Results extends ClassHandle {
  probPerTurn(): ResultsProbability;
}

export type array_double_24 = [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ];

export type ResultsProbability = {
  average: number,
  perTurn: array_double_24
};

interface EmbindModule {
  Board: {
    new(_0: number, _1: number, _2: number, _3: number, _4: number, _5: number): Board;
  };
  Results: {};
  simulate(_0: Board): Results;
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;

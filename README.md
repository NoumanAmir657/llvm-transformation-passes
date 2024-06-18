# Transformation Passes for LLVM-IR

## Passes
    1. Add Constant
    2. Add Metadata
    3. Add to Sub instruction
    4. Mul to Shift instruction
    5. Simple Profiler

## Build
```
LLVM_INSTALL_DIR=<path_to_llvm_build>

cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -G "Ninja" -B build/ .

cd build

cmake --build .
```

## Run
```
opt -load-pass-plugin build/lib/libAddConst.so -passes=<pass_name> -S examples/foo.ll
```

## Tests
```
opt -load-pass-plugin build/lib/libAddConst.so -passes=<pass_name> -S examples/foo.ll -o output/bar.ll

FileCheck tests/<checks_file> -input-file=output/bar.ll
```

## Name of passes
```
1.  add-const
2.  add-metadata
3.  add-to-sub
4.  mul-to-shift
5.  add-call   
```
<b>Note</b>: Printer pass can be run by setting `passes` as     `print<pass_name>`.
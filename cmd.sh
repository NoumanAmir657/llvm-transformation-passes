LLVM_INSTALL_DIR=/home/lpt-10xe/riscv-llvm/_build
cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -G "Ninja" -B build/ .
cd build
cmake --build .
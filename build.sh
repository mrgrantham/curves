if [ ! -d "build" ]; then
  echo "build folder missing"
  mkdir build
fi
cd build
cmake ..
# cmake \
# -DCMAKE_PREFIX_PATH="/usr/local/opt/llvm" \
# -DCMAKE_CXX_COMPILER="/usr/local/opt/llvm/bin/clang++" \
# -DCMAKE_C_COMPILER="/usr/local/opt/llvm/bin/clang" ..

cmake --build .
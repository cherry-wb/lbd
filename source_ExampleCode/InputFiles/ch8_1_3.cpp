// clang -c ch8_1_3.cpp -emit-llvm -o ch8_1_3.bc
<<<<<<< HEAD
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch8_1_3.bc -o ch8_1_3.cpu0.s
=======
// /Users/Jonathan/llvm/test/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch8_1_3.bc -o ch8_1_3.cpu0.s
>>>>>>> 835f5d4b63205622010953bfd1928b4eb0ee820f

extern int sum_i(int x, int y);

int main()
{
  int b = 1;
  int c = 2;
  int a = sum_i(b, c);
  
  return a;
}

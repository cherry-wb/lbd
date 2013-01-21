// clang -c ch4_4.cpp -emit-llvm -o ch4_4.bc
<<<<<<< HEAD
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch4_4.bc -o ch4_4.cpu0.s
=======
// /Users/Jonathan/llvm/test/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch4_4.bc -o ch4_4.cpu0.s
>>>>>>> 835f5d4b63205622010953bfd1928b4eb0ee820f

int main()
{
  int a = 1;
  int b = 2;
  int k = 0;
  unsigned int a1 = -5, f1 = 0;
  
  f1 = a1 / b;
  k = (a >> 2);

  return k;
}

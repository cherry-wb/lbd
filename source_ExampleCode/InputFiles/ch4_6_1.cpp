// clang -c ch4_6_1.cpp -emit-llvm -o ch4_6_1.bc
<<<<<<< HEAD
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch4_6_1.bc -o ch4_6_1.cpu0.s
=======
// /Users/Jonathan/llvm/test/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch4_6_1.bc -o ch4_6_1.cpu0.s
>>>>>>> 835f5d4b63205622010953bfd1928b4eb0ee820f

int main()
{
  int b = 11;
  int a = 12;

  b = (b+1)%a;
  
  return b;
}

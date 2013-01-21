// clang -c ch8_1_4.cpp -emit-llvm -o ch8_1_4.bc
<<<<<<< HEAD
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch8_1_4.bc -o ch8_1_4.cpu0.s
=======
// /Users/Jonathan/llvm/test/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch8_1_4.bc -o ch8_1_4.cpu0.s
>>>>>>> 835f5d4b63205622010953bfd1928b4eb0ee820f

int multiply(int x, int y)
{
  return (x*y);
}

int add(int x, int y)
{
  return (x+y);
}

int madd(int x, int y, int z)
{
  return add(z, multiply(x, y));
}

int main()
{
  int cc = 5;
  int a = madd(1, 2, cc);
  
  return a;
}

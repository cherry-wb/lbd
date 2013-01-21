// clang -c ch8_1_2.cpp -emit-llvm -o ch8_1_2.bc
<<<<<<< HEAD
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -view-isel-dags -view-sched-dags -relocation-model=pic -filetype=asm ch8_1_2.bc -o ch8_1_2.cpu0.s
=======
// /Users/Jonathan/llvm/test/cmake_debug_build/bin/Debug/llc -march=cpu0 -view-isel-dags -view-sched-dags -relocation-model=pic -filetype=asm ch8_1_2.bc -o ch8_1_2.cpu0.s
>>>>>>> 835f5d4b63205622010953bfd1928b4eb0ee820f

int sum_i(int x, int y, int* c)
{
  int* p = c;
  int sum = x + y;
  
  return sum; 
}

int main()
{
  int cc = 5;
  int a = sum_i(1, 2, &cc);
  
  return a;
}

// clang -c ch7_1_4.cpp -emit-llvm -o ch7_1_4.bc
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -view-isel-dags -view-sched-dags -relocation-model=pic -filetype=asm ch7_1_4.bc -o ch7_1_4.cpu0.s

int main()
{
  int a[3]={0, 1, 2};
    
  return 0;
}

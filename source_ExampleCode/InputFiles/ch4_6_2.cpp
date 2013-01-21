// clang -c ch4_6_2.cpp -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include/ -emit-llvm -o ch4_6_2.bc
<<<<<<< HEAD
// /Users/Jonathan/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch4_6_2.bc -o ch4_6_2.cpu0.s
=======
// /Users/Jonathan/llvm/test/cmake_debug_build/bin/Debug/llc -march=cpu0 -relocation-model=pic -filetype=asm ch4_6_2.bc -o ch4_6_2.cpu0.s
>>>>>>> 835f5d4b63205622010953bfd1928b4eb0ee820f

#include <stdlib.h>

int main()
{
  int b = 11;
//  unsigned int b = 11;
  int c = rand();
  
  b = (b+1)%c;
  
  return b;
}

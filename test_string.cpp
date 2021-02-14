#include <stdio.h>
#include <time.h>
#include <string>


std::wstring g_s;
unsigned g_cnt = 0;

int main()
{
  clock_t t1 = clock();

  unsigned r_seed = 1;

  // 1. strings test
  for ( unsigned n = 0; n < 3000000; n++ )
      {
        g_s += 'a';
        g_s += L"sdfjkdhkJHKJHKKJHKJHKJHKJ";
        g_s += 'A';
      }

  for ( size_t n = 0; n < g_s.size(); n++ )
      {
        if ( g_s[n] == 'A' )
           {
             g_cnt++;
           }
      }

  clock_t t2 = clock();

  printf("debug info: %d,%d\n",(unsigned)g_s.size(),g_cnt);  // this is needed for optimized compilers to avoid code elimination
  printf("Elapsed time: %.3f sec\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);

  return 0;
}

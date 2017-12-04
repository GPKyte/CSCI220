// Gavin Kyte
// Sun Dec  3 18:00:30 2017

#include <iostream>
#include <iomanip>
using namespace std;

uint32_t numberOfSetBits(uint32_t i)
{
     // Java: use >>> instead of >>
     // C or C++: use uint32_t
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

unsigned oat_hash(int *key, int len)
{
    unsigned char *p = (unsigned char*)(key);
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}

int main(){
  int arr[100];
  for(int i = 0; i<100; i++) arr[i]=0;
  for(int num = 0; num < 100; num++) {
    int hash = oat_hash(&num, sizeof(num))%100;
    cout<<hash;
    if(!arr[hash]) cout<<endl;
    else cout<<" replaced"<<endl;
    arr[hash] = 1;
  }
  return 0;
}

//#include "hasher.h"
#include <hasher.h>

//#define STAND_ALONE

#ifndef STAND_ALONE

static MHASH td;
static unsigned char hash[32]; /* enough size for MD5 */

/* init mhash module */
int hasher_init(void)
{
   td = mhash_init(MHASH_MD5);
   if (td == MHASH_FAILED) 
     return -1;
}

void hasher_calculate(unsigned char byte)
{
   unsigned char buffer = byte;
   mhash(td, &buffer, 1);
}

/* deinit mhash module and fill the result buffer */
void hasher_term(void)
{
    mhash_deinit(td, hash);
}

/* get the hash */
unsigned char *hasher_hashget(unsigned char *s)
{

  memcpy(s, hash, mhash_get_block_size(MHASH_MD5));
  return s;

}

/*int main(void)
{
   unsigned char c=3, mhash[32];

   hasher_init();
   hasher_calculate(c);
   hasher_term();
   hasher_hashget(mhash);
}*/


#else

int main(void)
{
   int i;
   MHASH td;
   unsigned char buffer;
   unsigned char hash[32]; /* enough size for MD5 */

   td = mhash_init(MHASH_MD5);

   if (td == MHASH_FAILED) exit(1);

   while (fread(&buffer, 1, 1, stdin) == 1) 
      mhash(td, &buffer, 1);

   mhash_deinit(td, hash);

   for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++)
      printf("%.2x", hash[i]);
   printf("\nHash is %d bytes long\n", i);

   exit(0);
}
#endif

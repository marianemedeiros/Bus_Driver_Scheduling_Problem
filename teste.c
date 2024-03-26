#include <stdio.h>
#include <stdlib.h>
char* return_buffer(int len)
{
      char* buf;
      buf = (char*) malloc(len * sizeof(char));
      if (buf == NULL) exit(1);
      for (int i = 0; i < len; i++)
            buf[i] = rand() % 26;
      return buf;
}
int main(int argc, char* argv[])
{
      printf("Type a number:\n");
      int length;
      scanf("%d", length);
      char* buffer;
      buffer = return_buffer(length);
      int i;
      for (i = 0; i < length; i++)
            printf("Value \"%c\" at \"%d\"\n", buffer[i], i);
      free(buffer);
      return 0;
}
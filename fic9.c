#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *comenzi[15] = {"pushq", "movq", "movl", "cmpl", "jge", "jmp", "subl",
  "popq", "ret"};
int stat[15];
int command_Index = 0;

int main()
{
  FILE *f;
  f=fopen("test.s", "r");
  if(!f)
  {
    perror("Error reading input file");
    exit(1);
  }

  char buff[15];
  int i;
  while((fgets(buff, 50, f)) != NULL)
  {

    for(i = 0; i < 9; i++){
      if(strstr(buff, comenzi[i]) != NULL){
        stat[i]++;
      }

  }
}

  for(i=0;i<9;i++){
    printf("%s: %d\n", comenzi[i], stat[i]);

  }

  fclose(f);
  return 0;
}

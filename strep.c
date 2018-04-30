/** strep program
 *  @author <put name here>
 *  INCOMPLETE: MUST BE COMPLETED BY STUDENT
 **/

// some included built-in library code, which may or may not be useful
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>

#define TRUE  1
#define FALSE 0

int string_length(char * str);

int main(int argc, char *argv[]){}

// find the length of a null terminated string
int string_length(char *str){
  int length = 0;
  while(str[length] != '\0'){
    length++;
  }
  return length;
}

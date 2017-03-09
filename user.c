#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

struct runner_t{
   //stored in hundredths of seconds to avoid floats
  char name[40], country[40];
  struct list_head runners;
};
void addRunner(int intime, int inrecord, char *inname, char *incountry);
void clearRunners(void);
void printRunners(void);

struct runner_t head;
int file_pointer, counter = 0;

int main(int argc, char *argv[])
{	
  INIT_LIST_HEAD(&(head.runners));
  file_pointer = open("assign6", O_RDWR); 
  addRunner(13142, 11500,"Jonathan","America");
  addRunner(135726, 12551,"Jimmy the Snail","America");
  addRunner(19241, 91500,"\"Robert\'; DROP TABLE Students;--\"","XKCD");
  addRunner(17360, 911521,"Hussein","America");
  addRunner(18192, 9500,"Hiroshi","Japan");
  printRunners();
  clearRunners();
}




void addRunner(int intime, int inrecord, char *inname, char *incountry){
  struct runner_t *newrunner = malloc(sizeof(struct runner_t));
  write(file_pointer, &intime, 4); //writes random value
  strcpy(newrunner->name, inname);
  strcpy(newrunner->country, incountry);
  INIT_LIST_HEAD(&(newrunner->runners));
  list_add_tail(&(newrunner->runners), &head.runners);
  counter++;
}

void printRunners(){
  struct runner_t *temp;
  int num = 0, x[20]; //array for values, supports up to 20 at this time
  read(file_pointer, &x[0], 4*counter); 
  list_for_each_entry(temp, &head.runners, runners){
    printf("runner number %d is %s from %s with a record time of %d:%d:%d\n", num+1, temp->name, temp->country, x[num]/60000,(x[num]%60000)/1000, (x[num]%1000));
    num++;
  }

}
void clearRunners(void){
  int clr = 0;
  write(file_pointer, &clr, 4); //writes random value

}

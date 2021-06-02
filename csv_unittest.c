#include <stdio.h>
#include "csv.h"


void test_new_record(){
  printf("Test: Create and free a record\n");
  struct record* r = empty_record();
  free_record(r);
}


void test_parse_one_line(){
  printf("Test: Parse one line into a record\n");
  char line[] = "00005962-ed09-46aa-aa4b-9035a7ed6e3a,39.3889274,-87.701537,2021-03-12 08:21:06\n";
  char delimiters[] = ",\n";
  struct record* r = empty_record();
  parse_fields(r, line, delimiters);
  printf("Printing record\n");
  print_record(r);
  printf("Freeing record\n");
  free_record(r);
}


void test_parse_small_csv(){
  printf("Test: Parse a small csv file\n");
  char* file = "/home/ryan/CProjects/CSV/device_data.csv";
  char* delimiters = ",\n";
  printf("Reading table\n");
  struct table* t = read_csv(file, delimiters);
  printf("Printing table\n");
  print_table(t);
  printf("Freeing table\n");
  free_table(t);
}


int main(){
  test_new_record();
  test_parse_one_line();
  test_parse_small_csv();
  return 0;
}

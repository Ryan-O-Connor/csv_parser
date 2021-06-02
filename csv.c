#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"


static const int MAXBUFFER = 10000;


struct record* empty_record(){
  struct record* r = malloc(sizeof(struct record));
  char** fields = malloc(sizeof(char*));
  r->fields = fields;
  r->num_fields = 0;
  r->array_size = 1;
  return r;
}


void parse_fields(struct record* r, char* line, char* delimiters){
  char* field;
  field = strtok(line, delimiters);
  while (field != NULL){
    add_field(r, strdup(field));
    field = strtok(NULL, delimiters);
  }
}


void add_field(struct record* r, char* field){
  if (r->num_fields == r->array_size){
    int new_size = 2*r->array_size;
    r->fields = realloc(r->fields, new_size*sizeof(char*));
    r->array_size = new_size;
  }
  r->fields[r->num_fields++] = field;
}


void print_record(struct record* r){
  int i;
  char end_character;
  for (i=0; i<r->num_fields; i++){
    end_character = (i==r->num_fields-1) ? '\n' : ',';
    printf("%s%c", r->fields[i], end_character);
  }
}


void free_record(struct record* r){
  int i;
  for (i=0; i<r->num_fields; i++){
    free(r->fields[i]);
  }
  free(r->fields);
  free(r);
}


struct table* empty_table(){
  struct table* t = malloc(sizeof(struct table));
  struct record** records = malloc(sizeof(struct record*));
  t->records = records;
  t->num_records = 0;
  t->array_size = 1;
  return t;
}


struct table* read_csv(char* filename, char* delimiters){
  FILE* fptr = fopen(filename, "r");
  struct table* t = empty_table();
  char buffer[MAXBUFFER];
  
  while (fgets(buffer, MAXBUFFER, fptr) != NULL){
    struct record* r = empty_record();
    parse_fields(r, buffer, delimiters);
    add_record(t, r);
  }

  fclose(fptr);
  return t;
}


void add_record(struct table* t, struct record* r){
  if (t->num_records == t->array_size){
    int new_size = 2*t->array_size;
    t->records = realloc(t->records, new_size*sizeof(struct record*));
    t->array_size = new_size;
  }
  t->records[t->num_records++] = r;
}


void print_table(struct table* t){
  int i;
  for (i=0; i<t->num_records; i++){
    print_record(t->records[i]);
  }
}


void free_table(struct table* t){
  int i;
  for (i=0; i<t->num_records; i++){
    free_record(t->records[i]);
  }
  free(t->records);
  free(t);
}



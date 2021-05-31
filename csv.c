#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int MAXBUFFER = 1000;
static int MAXFIELDS = 100;
static char delimiters[] = ",";


struct record{
  char** fields;
  int num_fields;
};


struct record_table{
  struct record** records;
  int num_records;
  int array_size;
};


struct record* parse_fields(char* buffer);
struct record* empty_record();
struct record_table* empty_record_table();
void add_record(struct record_table* table, struct record* r);
void resize_table(struct record_table* table, int new_size);
void free_table(struct record_table* table);
void print_record_table(struct record_table* table);
void print_record(struct record* r);


int main(){
  char buffer[MAXBUFFER];

  char* file = "/home/ryan/CProjects/CSV/device_data.csv";
  FILE* fptr = fopen(file, "r");

  struct record_table* table = empty_record_table();
  int i = 1;
  while(fgets(buffer, MAXBUFFER, fptr) != NULL){
    struct record* r = parse_fields(buffer);
    add_record(table, r);
    //print_record(r);
    //free(r);
  }
  //print_record(table->records[5]);
  print_record_table(table);  
  printf("OK.\n");

  //Free all pointers that were malloc'd
  fclose(fptr);
  free_table(table);
  
  return 0;
}


struct record* parse_fields(char* buffer){
  struct record* r = empty_record();
  char* field = strtok(buffer, ",\n");
  int i = 0;
  while (field != NULL){
    r->fields[i++] = field;
    field = strtok(NULL, ",\n");
  }
  if (i == 0){
    printf("Error: No fields read from buffer: %s\n", buffer);
  }
  r->num_fields = i;
  return r;
}


struct record* empty_record(){
  struct record* r = (struct record*) malloc(sizeof(struct record));
  char** fields = (char**) malloc(MAXFIELDS*sizeof(char*));
  r->fields = fields;
  r->num_fields = 0;
  return r;
}


struct record_table* empty_record_table(){
  struct record_table* table = (struct record_table*) malloc(sizeof(struct record_table));
  struct record** records = (struct record**) malloc(sizeof(struct record*));
  table->records = records;
  table->num_records = 0;
  table->array_size = 1;
  return table;
}


void add_record(struct record_table* table, struct record* r){
  if (table->array_size == table->num_records){
    resize_table(table, 2*table->array_size);
  }
  table->records[table->num_records++] = r;
  //print_record(table->records[table->num_records-1]);
}


void resize_table(struct record_table* table, int new_size){
  table->records = (struct record**) realloc(table->records, new_size*sizeof(struct record*));
  table->array_size = new_size;
}


void print_record_table(struct record_table* table){
  int i;
  for (i=0; i<table->num_records; i++){
    print_record(table->records[i]);
  }
}

void print_record(struct record* r){
  int i;
  for (i=0; i<r->num_fields; i++){
    printf(" %s ", r->fields[i]);
  }
  printf("\n");
}

void free_table(struct record_table* table){

}

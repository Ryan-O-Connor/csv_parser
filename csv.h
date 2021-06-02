struct record{
  char** fields;
  int num_fields;
  int array_size;
};


struct table{
  struct record** records;
  int num_records;
  int array_size;
};


struct record* empty_record();
void parse_fields(struct record* r, char* line, char* delimiters);
void add_field(struct record* r, char* field);
void resize_fields(struct record* r, int new_size);
void print_record(struct record* r);
void free_record(struct record* r);

struct table* empty_table();
struct table* read_csv(char* filename, char* delimiters);
void add_record(struct table* t, struct record* r);
void print_table(struct table* t);
void free_table(struct table* t);

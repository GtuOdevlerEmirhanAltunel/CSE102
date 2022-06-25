#ifndef util
#define util
#define DATABASE_KEY 346892156


typedef unsigned char bool;
typedef unsigned char length;
typedef struct
{
    char tip;
    short boyut;
    /**
     * First byte:
     *  0 -> char
     *  1 -> numeric
     *  2 -> floating
     *  3 -> date
     *  4 -> bool
     */
} table_type;

typedef union 
{
    table_type a;
    char yazma[4];
} table_types;

typedef struct
{
    length column_number;
    table_types * type;
    char ** field;
    bool * isNull;
    bool * isKey;
} table;

typedef struct tables
{
    struct tables * next; /* tables * next give error so i added struct to the beginning */
    char * name; /* table name */ /* i moved it to here to access easily */
    table * t;
} tables ;

typedef struct
{
    tables * tables_linked_list_head;
    length table_count;
    char * database_name;
} database;

typedef struct
{
    char ** command;
    int n_command;
} commands;

/** Main Functions */
database * open_database (char * database_name);
void show_table (database * d);
void desc_table (database * d, tables * t);
void insert_table (database * d, char * database_name);
void remove_table (database * d, char * name);
void insert_key (database * d, table * t, char key_value);

/** Side Funtions */
database * read_database(FILE * fp, char * database_name);
database * create_database(char * database_name);
void save_database(database * d, char * database_name);
commands command();


#endif
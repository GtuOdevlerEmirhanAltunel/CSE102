#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


char table_typessss[5][10] = {
    "CHAR",
    "NUMERIC",
    "FLOAT",
    "DATE",
    "BOOLEAN"
};

/**
 * @brief
 *  If there is database, it open it.
 *  Else it creates new one.
 * 
 * @param database_name Name of the file.
 * @return database* Database structure.
 */
database * open_database(char * database_name)
{
    FILE * fp = fopen(database_name, "rb");
    if(fp)
    {
        return read_database(fp, database_name);
    }
    else
    {
        printf("New database created.\n");
        return create_database(database_name);
    }
}

/** Side Functions */

/**
 * @brief 
 *  It convert file to database structure.
 * 
 * @param fp Database file.
 * @return database* Database structure.
 */
database * read_database(FILE * fp, char * database_name)
{
    database * database_object = (database *) calloc(1, sizeof(database_object));
    int i, j;
    tables * iter, * temp;
    length table_name;
    table * dum;
    int database_check;

    fread(&database_check, sizeof(int), 1, fp);
    if(database_check != DATABASE_KEY)
    {
        printf("There is a file named same but it isn't database file.");
        if(
            (database_name[0] >= 'a' && database_name[0] < 'z') || 
            (database_name[0] >= 'A' || database_name[0] < 'Z') ||
            (database_name[0] >= '0' || database_name[0] < '9'))
        {
            database_name[0]++;
        }
        else
        {
            database_name[0]--;
        }
        printf("New database created this name -> %s", database_name);
        database_object = create_database(database_name);
    }
    else
    {
        fread(&table_name, sizeof(length), 1, fp);
        database_object->database_name = (char *) calloc(table_name + 1, sizeof(char));
        fread(database_object->database_name, sizeof(char), table_name, fp);
        database_object->database_name[table_name] = 0;
        fread(&database_object->table_count, sizeof(length), 1, fp);

        if(database_object->table_count == 0)
        {
            database_object->tables_linked_list_head = 0;
        }
        else
        {
            iter = (tables *) calloc(1, sizeof(tables));
            fread(&table_name, sizeof(length), 1, fp);
            iter->name = (char *) calloc(table_name + 1, sizeof(char));
            fread(iter->name, sizeof(char), table_name, fp);

            iter->next = 0;
            database_object->tables_linked_list_head = iter;

            for(i = 1; i < database_object->table_count; i++)
            {
                temp = (tables *) calloc(1, sizeof(tables));
                fread(&table_name, sizeof(length), 1, fp);
                temp->name = (char *) calloc(table_name + 1, sizeof(char));
                fread(temp->name, sizeof(char), table_name, fp);
                temp->name[table_name] = 0;
                temp->next = 0;
                temp->t = 0;
                iter->next = temp;
                iter = temp;
            }
            
            iter = database_object->tables_linked_list_head;

            for(i = 0; i < database_object->table_count; i++)
            {
                dum = (table *) calloc(1, sizeof(table));
                fread(&dum->column_number, sizeof(length), 1, fp); /** Column Number */

                dum->field = (char **) calloc(dum->column_number, sizeof(char *));
                dum->type = (table_types *) calloc(dum->column_number, sizeof(table_types));
                dum->isNull = (bool *) calloc(dum->column_number, sizeof(bool));
                dum->isKey = (bool *) calloc(dum->column_number, sizeof(bool));
                for (j = 0; j < dum->column_number; j++)
                {
                    fread(&table_name, sizeof(length), 1, fp);
                    dum->field[j] = (char *) calloc(table_name, sizeof(char));
                    fread(dum->field[j], sizeof(char), table_name, fp);
                    fread(dum->type[j].yazma, sizeof(table_types), 1, fp);
                    fread(&dum->isNull[j], sizeof(bool), 1, fp);
                    fread(&dum->isKey[j], sizeof(bool), 1, fp);
                }
                iter->t = dum;
                iter = iter->next;
            }

        }
    }
    fclose(fp);
    return database_object;
}

/** */
database * create_database(char * database_name)
{
    database * database_object = (database *) calloc(1, sizeof(database));
    char buffer[256];
    printf("Name of new database : ");
    scanf("%s",buffer);
    buffer[255] = 0;
    database_object->table_count = 0;
    database_object->tables_linked_list_head = 0;
    database_object->database_name = (char *) calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(database_object->database_name, buffer);
    save_database(database_object, database_name);
    FILE * fp = fopen(database_name, "rb");
    return read_database(fp, database_name);
}

/** */
void save_database(database * d, char * database_name)
{
    FILE * fp = fopen(database_name, "wb");
    int check = DATABASE_KEY;
    int i, j;
    tables * iter = d->tables_linked_list_head;
    length name_len;
    fwrite(&check, sizeof(int), 1, fp);
    name_len = strlen(d->database_name);
    fwrite(&name_len, sizeof(length), 1, fp);
    fwrite(d->database_name, sizeof(char), name_len, fp);
    fwrite(&d->table_count, sizeof(length), 1, fp);
    for (i = 0; i < d->table_count; i++)
    {
        name_len = strlen(iter->name);
        fwrite(&name_len, sizeof(length), 1, fp);
        fwrite(iter->name, sizeof(char), name_len, fp);
        iter = iter->next;
    }

    iter = d->tables_linked_list_head;

    for(i = 0; i < d->table_count; i++)
    {
        fwrite(&iter->t->column_number, sizeof(length), 1, fp); /** Column Number */

        for (j = 0; j < iter->t->column_number; j++)
        {
            name_len = strlen(iter->t->field[j]);
            fwrite(&name_len, sizeof(length), 1, fp);

            fwrite(iter->t->field[j], sizeof(char), name_len, fp);
            fwrite(iter->t->type[j].yazma, sizeof(table_types), 1, fp);
            fwrite(&iter->t->isNull[j], sizeof(bool), 1, fp);
            fwrite(&iter->t->isKey[j], sizeof(bool), 1, fp);
        }
        iter = iter->next;
    }
    fclose(fp);
}

void show_table (database * d)
{
    int i;
    tables * iter = d->tables_linked_list_head;
    printf("Tables of -> \e[33m%s\e[0m\n", d->database_name);
    for (i = 0; i < d->table_count; i++)
    {
        printf("%3d. %s\n", i+1, iter->name);
        iter = iter->next;
    }
}

void desc_table (database * d, tables * t)
{
    int i;
    printf("\e[33m%s\e[0m -> \e[33m%s\e[0m\n", d->database_name, t->name);
    printf("+------------+--------------------------+----+----+\n");
    printf("|FIELD       |TYPE                      |NULL| KEY|\n");
    printf("+------------+--------------------------+----+----+\n");
    for (i = 0; i < t->t->column_number; i++)
    {
        printf("|%-12s|%2d-%-23s|%4s|%4s|\n",
            t->t->field[i],
            t->t->type[i].a.boyut,
            table_typessss[t->t->type[i].a.tip],
            (t->t->isNull[i]) ? "YES" : "NO",
            (t->t->isKey[i]) ? "YES" : "NO");
    }
    printf("+------------+--------------------------+----+----+\n");
}

void insert_table (database * d, char * database_name)
{
    int i;
    tables * dum = (tables *) calloc(1, sizeof(tables));
    dum->name = (char *) calloc(30, sizeof(char));
    dum->t = (table *) calloc(1, sizeof(table));
    tables * iter;
    int jk;

    printf("Creating new table\n");
    printf("Table name : ");
    scanf("%s", dum->name);
    printf("Column number : ");
    scanf("%d",&jk);
    dum->t->column_number = jk;
    dum->t->field = (char **) calloc(dum->t->column_number, sizeof(char *));
    dum->t->type = (table_types *) calloc(dum->t->column_number, sizeof(char));
    dum->t->isNull = (bool *) calloc(dum->t->column_number, sizeof(char));
    dum->t->isKey = (bool *) calloc(dum->t->column_number, sizeof(char));

    for (i = 0; i < dum->t->column_number; i++)
    {
        dum->t->field[i] = (char *) calloc(30, sizeof(char));
        printf("Column name : ");
        scanf("%s",dum->t->field[i]);
        printf("Column type : (0 -> char, 1 -> numeric, 2 -> floating, 3 -> date, 4 -> bool)\n");
        scanf("%d",&jk);
        dum->t->type[i].a.tip = jk;
        printf("Data size : ");
        scanf("%d",&jk);
        dum->t->type[i].a.boyut = jk;
        printf("Null : (1/0)\n");
        scanf("%d", &jk);
        dum->t->isNull[i] = jk;
        printf("Key : (1/0)\n");
        scanf("%d", &jk);
        dum->t->isKey[i] = jk;
    }
    
    d->table_count++;
    if (d->table_count == 1)
    {
        d->tables_linked_list_head = dum;
    }
    else
    {
        iter = d->tables_linked_list_head;
        for (i = 0; i < d->table_count - 2; i++)
        {
            iter = iter->next;
        }
        iter->next = dum;
    }
    save_database(d, database_name);
}


commands command()
{
    printf(">");
    fflush(stdin);
    commands cmp;
    cmp.command = (char **) calloc(10, sizeof(char *));
    cmp.n_command = 0;
    char * word = (char *) calloc(30, sizeof(char));
    char temp, i = 0;
    do
    {
        temp = getchar();
        
        if (temp == ' ' || temp == 0 || temp == '\n')
        {
            i = 0;
            cmp.command[cmp.n_command] = word;
            word = (char *) calloc(30, sizeof(char));
            cmp.n_command++;
            continue;
        }

        if (++i >= 30)
        {
            i = 0;
        }

        word[i - 1] = temp;
        word[i] = 0;

    } while (temp != '\n' && cmp.n_command < 10);

    return cmp;
}
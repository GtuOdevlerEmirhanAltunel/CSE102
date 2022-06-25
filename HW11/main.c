#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(int argc, char const *argv[])
{
    commands cmp;
    database ** d = (database **) calloc(10, sizeof(database *));
    char ** database_names = (char **) calloc(10, sizeof(char *));
    int active_database = -1;
    int d_c = 0;
    int main = 1;
    int dummy, i;
    tables * iter;

    while (main)
    {
        if (active_database != -1)
        {
            printf("[\e[31m%s\e[0m]",d[active_database]->database_name);
        }
        cmp = command();
        if(!strcmp(cmp.command[0], "OPEN"))
        {
            if (cmp.n_command == 1)
            {
                printf("Open what?\n");
            }
            else
            {
                database_names[d_c] = (char *) calloc(30, sizeof(char));
                strcpy(database_names[d_c], cmp.command[1]);
                d[d_c++] = open_database(cmp.command[1]);
                active_database = d_c - 1;
            }
        }
        else if(!strcmp(cmp.command[0], "SHOW"))
        {
            if (active_database == -1)
            {
                printf("There is no opened database.\n");
            }
            else
            {
                show_table(d[active_database]);
            }
        }
        else if(!strcmp(cmp.command[0], "DESC"))
        {
            if (active_database == -1)
            {
                printf("There is no opened database.\n");
            }
            else
            {
                if(!d[active_database]->table_count)
                {
                    printf("There is no table of this database.\n");
                }
                else
                {
                    show_table(d[active_database]);
                    printf("Select table : \n");
                    scanf("%d",&dummy);
                    fflush(stdin);
                    iter = d[active_database]->tables_linked_list_head;
                    for (i = 1; i < dummy; i++)
                    {
                        iter = iter->next;
                    }
                    desc_table(d[active_database], iter);
                }
            }
        }
        else if(!strcmp(cmp.command[0], "SHW"))
        {
            if (d_c)
            {
                printf("Databases : \n");
                for (i = 0; i < d_c; i++)
                {
                    printf("%d. %s\n",i + 1, d[i]->database_name);
                }
            }
            else
            {
                printf("There is no opened database.\n");
            }
        }
        else if(!strcmp(cmp.command[0], "INSR"))
        {
            if (active_database == -1)
            {
                printf("There is no opened database.\n");
            }
            else
            {
                insert_table(d[active_database], database_names[active_database]);
            }
        }
        else if(!strcmp(cmp.command[0], "HELP"))
        {
            printf("1. OPEN -> open database\
                  \n2. SHOW -> show tables of active database\
                  \n3. DESC -> describe one of the tables of active database\
                  \n4. SHW  -> show all opened databases\
                  \n5. HELP\
                  \n6. EXIT\n");
        }
        else if(!strcmp(cmp.command[0], "EXIT"))
        {
            main = 0;
        }
        else
        {
            printf("Unknown command write \e[32mHELP\e[0m\n");
        }
    }

    return 0;
}
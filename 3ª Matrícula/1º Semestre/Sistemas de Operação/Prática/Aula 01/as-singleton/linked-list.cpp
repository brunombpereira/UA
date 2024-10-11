#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

/*******************************************************/

/**
 * \brief The data to be stored in the list
 */
struct Student
{
    uint32_t nmec;        ///< Student number
    char *name;     ///< Student name
};

/**
 * \brief The linked-list support data structure:
 */
struct SllNode 
{
    Student reg;          ///< Student data
    struct SllNode *next;    ///< Pointer to next node
};

/*******************************************************/

static SllNode *list = NULL;

/*******************************************************/

void sllDestroy()
{
    while (list != NULL)
    {
        SllNode *temp = list->next;
        free(list->reg.name);
        free(list);
        list = temp;
    }

    list = NULL;
}

/*******************************************************/

void sllPrint(FILE *fout)
{
    if (list == NULL)
    {
        fprintf(fout, "List is empty.\n");
    }

    fprintf(fout, "%-6s | %-99s\n", "NMec", "Nome");
    
    for (SllNode *p = list; p != NULL; p = p->next)
    {
        fprintf(fout, "%6d | %s", p->reg.nmec, p->reg.name);
    }
}

/*******************************************************/

void sllInsert(uint32_t nmec, const char *name)
{
    assert(name != NULL && name[0] != '\0');
    assert(!sllExists(nmec));

    if (list == NULL || list->reg.nmec > nmec)
    {
        SllNode *temp = list;

        if (list != NULL && list->reg.nmec > nmec)
        {
            temp = list;
        }
        

        list = new SllNode();
        list->reg.nmec = nmec;
        list->reg.name = strdup(name);
        list->next = temp;
        return;        
    }    

    SllNode *p = list;

    while (p != NULL)
    {
        if (p->next == NULL)
        {
            p->next = new SllNode();
            p->next->reg.name = strdup(name);
            p->next->reg.nmec = nmec;
            return;
        }
        
        if (p->next->reg.nmec > nmec)
        {
            SllNode *temp = p->next;
            p->next = new SllNode();
            p->next->reg.name = strdup(name);
            p->next->reg.nmec = nmec;
            p->next->next = temp;
            return;
        }
        p = p->next;
    }
}

/*******************************************************/

bool sllExists(uint32_t nmec)
{
    SllNode *p = list;
    while (p != NULL)
    {
        if (p->reg.nmec == nmec)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

/*******************************************************/

void sllRemove(uint32_t nmec)
{
    assert(sllExists(nmec));

    SllNode *p = list;
    SllNode *prev = NULL;

    if (list->reg.nmec == nmec)
    {
        SllNode *temp = list->next;
        free(list->reg.name);
        free(list);
        list = temp;
    }
    

    while (p != NULL)
    {
        if (p->reg.nmec == nmec)
        {
            prev->next = p->next;
            free(p->reg.name);
            free(p);
            break;
        }
        prev = p;
        p = p->next;
    }
}

/*******************************************************/

const char *sllGetName(uint32_t nmec)
{
    assert(sllExists(nmec));

    SllNode *p = list;

    while (list != NULL)
    {
        if (list->reg.nmec == nmec)
        {
            return list->reg.name;
        }
        
        p = p->next;
    }

    return NULL;
}

/*******************************************************/

bool sllLoad(FILE *fin)
{
    assert(fin != NULL);

    ssize_t read;
    size_t len = 0;
    char* line = NULL;
    int lc = 1;

    while ((read = getline(&line, &len, fin)) != -1)
    {
        char name[100];
        int32_t nmec;

        if (sscanf(line, "%d;%99[^;]", &nmec, name) == 2)
        {
            sllInsert(nmec, name);
        } else
        {
            printf("Error reading file, line = %d", lc);
            return false;
        }
        
        lc++;
    }
    
    free(line);

    return true;
}

/*******************************************************/


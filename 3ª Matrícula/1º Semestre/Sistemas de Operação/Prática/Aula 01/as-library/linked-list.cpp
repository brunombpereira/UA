#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

/*******************************************************/

SllNode* sllDestroy(SllNode* list)
{
    SllNode* p = list;

    while (p != NULL)
    {
        SllNode* next = p->next;
        free(p->reg.name);
        free(p);
        p = next;
    }
    
    return NULL;
}

/*******************************************************/

void sllPrint(SllNode *list, FILE *fout)
{
    if (list == NULL)
    {
        fprintf(fout, "List is empty.");
    }

    fprintf(fout, "%-6s | %-99s\n", "NMec", "Nome");

    for (SllNode* p = list; p != NULL; p = p->next)
    {
        fprintf(fout, "%6d | %s", p->reg.nmec, p->reg.name);
    }
}

/*******************************************************/

SllNode* sllInsert(SllNode* list, uint32_t nmec, const char *name)
{
    assert(name != NULL && name[0] != '\0');
    assert(!sllExists(list, nmec));

    SllNode* sllNode = (SllNode*)malloc(sizeof(SllNode));

    if (sllNode == NULL)
    {
        printf("No memory available to allocate a new student.\n");
        exit(1);
    }

    char* studentName = strdup(name);

    sllNode->reg.name = studentName;
    sllNode->reg.nmec = nmec;
    sllNode->next = NULL;

    if (list == NULL || list->reg.nmec > nmec)
    {
        sllNode->next = list;
        return sllNode;
    }

    SllNode* p = list;

    while (p->next != NULL && p->next->reg.nmec < nmec)
    {
        p = p->next;
    }
    
    sllNode->next = p->next;
    p->next = sllNode;

    return list;
}

/*******************************************************/

bool sllExists(SllNode* list, uint32_t nmec)
{
    SllNode* p = list;

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

SllNode* sllRemove(SllNode* list, uint32_t nmec)
{
    assert(list != NULL);
    assert(sllExists(list, nmec));

    SllNode* p = list;
    SllNode* prev = NULL;

    if (list->reg.nmec == nmec)
    {
        SllNode* next = list->next;
        free(list->reg.name);
        free(list);
        return next;
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

    return list;
}

/*******************************************************/

const char *sllGetName(SllNode* list, uint32_t nmec)
{
    assert(list != NULL);
    assert(sllExists(list, nmec));

    SllNode* p = list;

    while (p != NULL)
    {
        if (p->reg.nmec == nmec)
        {
            return p->reg.name;
        }
        p = p->next;
    }
    
    return NULL;
}

/*******************************************************/

SllNode* sllLoad(SllNode *list, FILE *fin, bool *ok)
{
    assert(fin != NULL);

    if (ok != NULL) {
       *ok = false; // load failure
    }

    ssize_t read;
    size_t len = 0;
    char* line = NULL;
    int lc = 1;

    while ((read = getline(&line,&len,fin)) != -1)
    {
        char name[100];
        int32_t nmec;

        if (sscanf(line, "%d;%99[^;]", &nmec, name) == 2)
        {
            list = sllInsert(list, nmec, name);
        } else
        {
            printf("Error reading file, line = %d\n", lc);
        }
        
        lc++;
    }

    free(line);

    if (ok != NULL)
    {
        *ok = true;
    }

    return list;
}

/*******************************************************/


#ifndef DUMP_INCLUDED
#define DUMP_INCLUDED

#include <stdio.h>
#include "../hashtable/hashtable.h"
void DtStart (FILE* dotfile);
void DtSetTitle(FILE* dotfile, struct Hashtable *HashT);
void DtSetBuf (FILE *dotfile, struct Hashtable* HashT);
void DtSetNodes (FILE* dotfile, struct node *i, struct Hashtable *HashT);
void DtSetDependence (FILE* dotfile, struct Hashtable *HashT);
void DtEnd (FILE* dotfile);

#endif
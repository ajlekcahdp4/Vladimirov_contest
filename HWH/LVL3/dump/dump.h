#include <stdio.h>
#include "../hashtable/hashtable.h"
void DtStart (FILE* dotfile);
void DtSetTitle(FILE* dotfile, struct Hashtable *HashT);
void DtSetNode (FILE* dotfile, struct node *i);
void DtSetDependence (FILE* dotfile, struct Hashtable *HashT);
void DtEnd (FILE* dotfile);
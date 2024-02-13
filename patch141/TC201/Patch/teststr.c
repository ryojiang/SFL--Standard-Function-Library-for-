/*  ----------------------------------------------------------------<Prolog>-
    Name:       teststr.c
    Title:      Test program for string functions
    Package:    Standard Function Library (SFL)

    Written:    96/04/24  Pieter Hintjens <ph@imatix.com>
    Revised:    96/10/26

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"

int main (int argc, char *argv [])
{
    char
        dest [128],
        *table [10] = { "One", "Two", "Three", "Four", "Five",
                       "Six", "Seven", "Eight", "Nine", NULL },
        **new_table;
    DESCR
        *descr;
    int
        string;

    puts ("Testing xstrcat():");
    xstrcpy (dest, "This ", "Is ", "A ", "String", NULL);
    puts (dest);
    xstrcat (dest, "1", "2", "3", NULL);
    puts (dest);
/*Line 36,37,40 function name were typo. Correct it by Jau-Bing Lin 2023/11/9*/
    puts ("Testing strt2descr():");	  /* modify str2descr() --> strt2descr() */
    descr     = strt2descr (table);	  /* modify str2descr() --> strt2descr() */
    printf ("Descriptor size=%d\n", descr-> size);

    new_table = descr2strt (descr);   /* modify descr2str() --> descr2strt() */
    printf ("Contents of table: ");
    for (string = 0; new_table [string]; string++)
        printf ("[%s] ", new_table [string]);
    puts ("");

    return (EXIT_SUCCESS);
}

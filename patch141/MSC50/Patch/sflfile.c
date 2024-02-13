/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflfile.c
    Title:      File-access functions
    Package:    Standard Function Library (SFL)

    Written:    92/10/28  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/14  Pieter Hintjens <ph@imatix.com>

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal header file            */
#include "sflstr.h"                     /*  String handling functions        */
#include "sflmem.h"                     /*  Memory allocation functions      */
#include "sflnode.h"                    /*  Linked-list functions            */
#include "sfldir.h"                     /*  Directory access functions       */
#include "sflfile.h"                    /*  Prototypes for functions         */


/*  Ensure our buffers will be big enough for dir + name + delimiters        */
#if ((LINE_MAX - FILE_NAME_MAX) < (FILE_DIR_MAX + 10))
#   error "Cannot compile; FILE_NAME_MAX is too large."
#endif

static char
#if (PATHFOLD == TRUE)
    path_name [PATH_MAX + 1],           /*  Copy of path symbol              */
#endif
    work_name [LINE_MAX + 1],           /*  Name plus ext                    */
    full_name [LINE_MAX + 1];           /*  Dir plus name plus ext           */

Bool file_crlf = FALSE;                 /*  Initial default                  */


/*  Function prototypes                                                      */

static char  *build_next_path (char *dest, char *path, char *name);
static dbyte  file_mode       (char *filename);


/*  ---------------------------------------------------------------------[<]-
    Function: file_open

    Synopsis: Opens the specified file for input or output.  If you use
    the file_read / file_write functions you must open the file using this
    function.  This set of functions lets you read files without concern
    for the line format (CRLF or LF).  Mode should be one of 'r' 'w' 'a'.

    Returns a FILE pointer if the file is opened correctly; else NULL.
    Sets the global variable file_crlf to FALSE on all systems except MS-DOS
    (and Windows by inheritence) where it is set to TRUE by default.
    ---------------------------------------------------------------------[>]-*/

FILE *
file_open (char *filename, char mode)
{
    ASSERT (filename != NULL);

#   if (defined (__MSDOS__))
    file_crlf = TRUE;
#   else
    file_crlf = FALSE;
#   endif
    return (fopen (filename, (mode == 'r'? FOPEN_READ_BINARY:
                              mode == 'w'? FOPEN_WRITE_BINARY:
                              /* else */   FOPEN_APPEND_BINARY)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_locate

    Synopsis: Combines the functions of file_where() and file_open when you
    want to read a file.  Searches for a file on a specified path, opens the
    file if found, and returns a FILE * for the open file.  Returns NULL if
    the file was not found or could not be opened for reading.
    ---------------------------------------------------------------------[>]-*/

FILE *
file_locate (char *path, char *name, char *ext)
{
    char
        *filename;

    filename = file_where ('r', path, name, ext);
    if (filename)
        return (file_open (filename, 'r'));
    else
        return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_close

    Synopsis: Closes an open file stream.  Returns FALSE if okay, TRUE if
    there were errors.  Equivalent to fclose, and supplied because it looks
    nice when you use file_open() and file_close() together.
    ---------------------------------------------------------------------[>]-*/

Bool
file_close (FILE *stream)
{
    ASSERT (stream != NULL);
    return (fclose (stream));
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_read

    Synopsis: Reads a line of text delimited by newline from the stream.
    The string must be LINE_MAX + 1 long.  Places a null byte in place of
    the newline character.  Expands tab characters to every 8th column.
    Returns TRUE when there is more input waiting; FALSE when the last line
    of the file has been read.

    Sets the global variable file_crlf to TRUE if CR was found in the file.
    This variable is by default FALSE.  It is also used by file_write.
    ---------------------------------------------------------------------[>]-*/

Bool
file_read (FILE *stream, char *string)
{
    int
        ch,                             /*  Character read from file         */
        cnbr;                           /*  Index into returned string       */

    ASSERT (stream);

    cnbr = 0;                           /*  Start at the beginning...        */
    memset (string, ' ', LINE_MAX);     /*    and prepare entire line        */
    for (;;)
    {
        ch = fgetc (stream);            /*  Get next character from file     */
        if (ch == '\t')                 /*  Jump if tab                      */
            cnbr = ((cnbr >> 3) << 3) + 8;
        else
        if (ch == '\r')                 /*  Found carriage-return            */
            file_crlf = TRUE;           /*    Set flag and ignore CR         */
        else
        if ((ch == '\n')                /*  Have end of line                 */
        ||  (ch == EOF)                 /*    or end of file                 */
        ||  (ch == 26))                 /*    or MS-DOS Ctrl-Z               */
        {
            string [cnbr] = '\0';       /*  Terminate string                 */
            return (ch == '\n' || cnbr);    /*  and return TRUE/FALSE        */
        }
        else
        if (cnbr < LINE_MAX)
            string [cnbr++] = (char) ch;    /*  Else add char to string      */

        if (cnbr >= LINE_MAX)           /*  Return in any case if line is    */
        {                               /*    too long - the line will be    */
            string [LINE_MAX] = '\0';   /*    cut into pieces                */
            return (TRUE);
        }
    }
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_write

    Synopsis: Writes a line of text to the specified output stream.  If the
    variable file_crlf is TRUE, adds a carriage-return to the line being
    written to the output stream.  This variable is supplied so that you can
    either ignore crlf issues (do nothing), or handle them explicitly (play
    with file_crlf).  Returns the string written, or NULL if no data could
    be written to the file.
    ---------------------------------------------------------------------[>]-*/

char *
file_write (FILE *stream, char *string)
{
    fputs (string, stream);
    if (file_crlf)
        fputc ('\r', stream);

    if (fputc ('\n', stream) == EOF)
        return (NULL);
    else
        return (string);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_copy

    Synopsis: Copies a file called src to one called dest.  The dest file
    may not already exist.  If mode is 'b', copies a binary file; if mode is
    't', copies a text file.  This distinction only applies to MS-DOS and
    Windows; on other platforms the two modes are equivalent.  Returns 0
    if no problems occurred, -1 if an error occurred, 1 if the destination
    file already exists.
    ---------------------------------------------------------------------[>]-*/

int
file_copy (char *dest, char *src, char mode)
{
    FILE *inf, *outf;
    char *buffer,
         openmode [3]; /* Modified for MSC 5.0 by Jau-Bing Lin on 2023-11-23 */
    size_t chars_read;                  /*  Amount read from stream          */
    int  feedback = 0;

    if (file_exists (dest))
        return (1);                     /*  Cancel: dest already exists      */

#   if (defined (__MSDOS__))
    openmode [1] = mode;
#   else
    openmode [1] = 0;
#   endif
    openmode [0] = 'r';
    if ((inf = fopen (src, openmode)) == NULL)
        return (-1);                    /*  Input file not found             */

    if ((buffer = mem_alloc (SHRT_MAX)) == NULL)
        feedback = -1;                  /*  Insufficient memory for buffer   */
    else
      {
        openmode [0] = 'w';
        outf = fopen (dest, openmode);
        while ((chars_read = fread (buffer, 1, SHRT_MAX, inf)) != 0)
            if (fwrite (buffer, 1, chars_read, outf) != chars_read)
              {
                feedback = -1;
                break;
              }
        fclose (outf);
        mem_free (buffer);
      }
    fclose (inf);
    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_exists

    Synopsis: Returns TRUE if the file exists, or FALSE if it does not.
    ---------------------------------------------------------------------[>]-*/

Bool
file_exists (char *filename)
{
    return (file_mode (filename) > 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_where

    Synopsis: Scans a user-specified path symbol for a specific file, and
    returns the fully-specified filename.  Also adds an extension if this
    is required.

    The mode argument can be one of: r, w, a, or s for read, write, append,
    or static.  The function tries to locate existing files somewhere on the
    path.  New files are always created in the current directory.  Static
    files are created in the first directory on the path.

    The path argument is only used when more is r, a, or s.  If the path is
    NULL or empty, it is ignored.  Otherwise, the path is translated as an
    environment variable, and cut into a list of directory names.  The path
    is cut up as follows:
    <TABLE>
        MS-DOS    directory names separated by ';'. ;; means current.
        OS/2      directory names separated by ';'. ;; means current.
        Unix      directory names separated by ':'. :: means current.
        VMS       directory names separated by ','. " ", means current.
        Other     single directory name.
    </TABLE>

    When the mode is 'r' or 'a', searches the current directory before
    considering the path value.  When the path cannot be translated, and is
    not null or empty, it is used as a literal value.

    The name argument is the filename with or without extension.  It will
    be prefixed by the path and suffixed by the extension, if required.

    The ext argument is a default or mandatory extension.  If ext starts
    with a dot, it is mandatory and always used.  Otherwise it is used only
    if the name does not already have an extension.  If ext is NULL or empty,
    it is ignored.

    The total length of a name including path, name, extension, and any
    delimiters is FILE_NAME_MAX.  Names are truncated if too long.  The
    maximum size of one directory component is FILE_DIR_MAX chars.

    All parameters are case-sensitive; the precise effect of this depends on
    the system.  On MS-DOS, filenames are always folded to uppercase, but the
    path must be supplied in uppercase correctly.  On UNIX, all parameters are
    case sensitive.  On VMS, path and filenames are folded into uppercase.

    Returns a pointer to a static character array containing the filename; if
    mode is 'r' and the file does not exist, returns NULL.  If the mode is
    'w', 'a', or 's', always returns a valid filename.
    ---------------------------------------------------------------------[>]-*/

char *
file_where (char mode, char *path, char *name, char *ext)
{
    char
        *pathptr;                       /*  End of directory in Path         */

    if (ext != NULL && *ext)            /*  Append extension if not null     */
      {                                 /*    to get name + ext into         */
        if (ext [0] == '.')             /*    work_name.                     */
            fixed_extension (work_name, name, ext);
        else
            default_extension (work_name, name, ext);
      }
    else
        strcpy (work_name, name);
#       if (NAMEFOLD == TRUE)
        strupc (work_name);             /*  Fold to uppercase if needed      */
#       endif

    if (path != NULL && *path)          /*  Get value of path, or NULL       */
      {
        pathptr = getenv (path);        /*  Translate path symbol            */
        if (pathptr == NULL)
            pathptr = path;             /*  If not found, use literally      */
#       if (PATHFOLD == TRUE)           /*  Fold to uppercase if necessary   */
        if (pathptr)
          {
            ASSERT (strlen (pathptr) < PATH_MAX);
            strcpy (path_name, pathptr);
            pathptr = path_name;
            strupc (path_name);         /*  Fold path value if required      */
          }
#       endif
      }
    else
        pathptr = NULL;

    /*  Take care of 'w' and 's' options first                               */
    if (mode == 'w')                    /*  Create output file locally       */
        return (work_name);

    if (mode == 's')                    /*  Get specific directory name      */
      {
        build_next_path (full_name, pathptr, work_name);
        return (full_name);
      }

    if (file_exists (work_name))        /*  Find file in current directory?  */
        return (work_name);             /*  Then return name + ext           */

#   if (defined (__VMS__))
    /*  VMS lets you open a file like this 'path:name'                       */
    if (pathptr)
        sprintf (full_name, "%s:%s", path, work_name);
    else
        strcpy (full_name, work_name);

    if ((mode == 'a')                   /*  Create file locally or find it   */
    ||  (file_exists (full_name)))      /*    using path symbol value        */
        return (full_name);
    else
        return (NULL);                  /*  Not found for reading            */
#   else

    if (!pathptr)                       /*  Now we need a path               */
        return (NULL);                  /*   - if none defined, give up      */

    for (;;)                            /*  Try each path component          */
      {
        pathptr = build_next_path (full_name, pathptr, work_name);
        if (file_exists (full_name))
            return (full_name);         /*  Until we find one,               */

        if (*pathptr == '\0')           /*    or we come to the end of       */
          {                             /*    the path                       */
            if (mode == 'r')
                return (NULL);          /*  Input file was not found...      */
            else
                return (full_name);
          }
      }
#   endif
}

/*  -------------------------------------------------------------------------
 *  build_next_path -- internal
 *
 */

static char *
build_next_path (char *dest, char *path, char *name)
{
    int
        length;                         /*  length of directory name         */

    length = strcspn (path, PATHSEP);
    strncpy (dest, path, length);
    path += length;                     /*  Bump past path delimiter         */
    if (*path)                          /*    unless we are at the end       */
        path++;                         /*    of the path                    */

    if ((length)
    && (dest [length - 1] != PATHEND))
        dest [length++] = PATHEND;      /*  Add path-to-filename delimiter   */

    dest [length] = '\0';
    strcat (dest, name);
    return (path);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_cycle

    Synopsis: Cycles the file: if the file already exists, renames the
    existing file.  This function tries to rename the file using the date
    of creation of the file; if this fails because an existing file had the
    same name, generates a guaranteed unique file name.  Returns TRUE if
    the cycle operation succeeded, or FALSE if it failed (e.g. due to a
    protection problem.)
    ---------------------------------------------------------------------[>]-*/

Bool
file_cycle (char *filename)
{
    time_t
        file_time_t;
    struct tm
        *file_time;
    char
        *point,
        *insert_at;                     /*  Where we start messing name      */
    int
        unique_nbr;                     /*  To generate a unique name        */

    if (!file_exists (filename))
        return (TRUE);                  /*  Not found - nothing more to do   */

    if ((file_time_t = get_file_time (filename)) == 0)
        return (FALSE);                 /*  Could not get file date & time   */

    file_time = localtime (&file_time_t);
    strcpy (full_name, filename);

    point = strrchr (full_name, '.');
    if (point)
      {
        strcpy (work_name, point);      /*  Save extension, if any           */
        *point = '\0';                  /*    and truncate original name     */
      }
    else
        strclr (work_name);

    /*  We leave up to 2 original letters of the filename, then stick-in     */
    /*  the 6-digit timestamp.                                               */
    if ((insert_at = strrchr (full_name, PATHEND)) == NULL)
        insert_at = full_name;
    else
        insert_at++;

    if (*insert_at)                     /*  Bump insert_at twice, to leave   */
        insert_at++;                    /*    up to 2 letters before we      */
    if (*insert_at)                     /*    stick-in the date stamp        */
        insert_at++;

    sprintf (insert_at, "%02d%02d%02d", file_time-> tm_year,
                                        file_time-> tm_mon + 1,
                                        file_time-> tm_mday);
    strcat (insert_at, work_name);
    if (file_exists (full_name))
      {
        point = strrchr (full_name, '.') + 1;
        for (unique_nbr = 0; unique_nbr < 1000; unique_nbr++)
          {
            sprintf (point, "%03d", unique_nbr);
            if (!file_exists (full_name))
                break;
          }
      }
    if (file_exists (full_name))
        return (FALSE);                 /*  We give up!                      */

    if (rename (filename, full_name))
        return (FALSE);                 /*  No permission                    */
    else
        return (TRUE);                  /*  Okay, it worked                  */
}


/*  ---------------------------------------------------------------------[<]-
    Function: safe_to_extend

    Synopsis: Handles system-specific case of extending a file that may not
    be in a valid state for such an operation. Returns TRUE if the extend
    can go ahead; returns FALSE if the extend cannot be permitted.

    Under MS-DOS and Windows, if the last byte in the file is Ctrl-Z (26)
    the file is truncated by 1 position to remove this character.
    ---------------------------------------------------------------------[>]-*/

Bool
safe_to_extend (char *filename)
{
#if (defined (__MSDOS__))
    int  handle;                        /*  Opened file handle               */
    char endoffile;                     /*  Last character in file           */

    handle = open (filename, O_RDWR + O_BINARY, S_IREAD | S_IWRITE);
    if (handle)                         /*  If not found, ignore             */
      {
        lseek (handle, -1, SEEK_END);
        read  (handle, &endoffile, 1);
        if (endoffile == 26)
            chsize (handle, filelength (handle) - 1);

        close (handle);
      }
#endif
    return (TRUE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: default_extension

    Synopsis: Copies src to dest and adds ext if necessary.  Returns 0 if
    the name was okay, -1 if it was invalid.  Dest must be large enough for
    a fully-formatted filename -- define it as char [FILE_NAME_MAX + 1].
    Ext can start with or without a point. If ext is null or empty, does
    nothing.
    ---------------------------------------------------------------------[>]-*/

int
default_extension (char *dest, char *src, char *ext)
{
    int len, i;
    char *ptr;

    if (dest != src)                    /*  Copy src to dest if not same     */
        strcpy (dest, src);

    if (ext != NULL && *ext != 0)
      {
        len = strlen (dest);
        for (i = len - 1, ptr = dest + i; i >= 0; i--, ptr--)
            if (*ptr == '\\' || *ptr == '/' || *ptr == '.')
                break;

        if (i < 0 || *ptr != '.')
          {
            if (*ext != '.')
              {
                dest [len++] = '.';
                dest [len] = '\0';
              }
            strcat (dest + len, ext);
          }
      }
    return (0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: fixed_extension

    Synopsis: Copies src to dest and enforces ext extension.  Returns 0 if
    the name was okay, -1 if it was invalid.  Dest must be large enough for
    a fully-formatted filename -- define it as char [FILE_NAME_MAX + 1].
    Ext can start with or without a point. If ext is null or empty, does
    nothing.
    ---------------------------------------------------------------------[>]-*/

int
fixed_extension (char *dest, char *src, char *ext)
{
    if (dest != src)                    /*  Copy src to dest if not same     */
        strcpy (dest, src);

    strip_extension (dest);
    return (default_extension (dest, dest, ext));
}


/*  ---------------------------------------------------------------------[<]-
    Function: strip_extension

    Synopsis: Removes dot and extension from the name, if any was present.
    If the name contained multiple extensions, removes the last one only.
    Returns name.
    ---------------------------------------------------------------------[>]-*/

char *
strip_extension (char *name)
{
    char *dot, *slash;

    dot = strrchr (name, '.');          /*  Find dot in name, if any         */
    slash = strrchr (name, '\\');       /*  Find last slash (DOS or Unix)    */
    if (slash == NULL)
        slash = strrchr (name, '/');
    if (dot > slash)
        *dot = 0;                       /*  If we had a dot, truncate name   */

    return (name);
}


/*  ---------------------------------------------------------------------[<]-
    Function: strip_file_path

    Synopsis: Removes the leading path from the filename, if any path was
    present.  Returns name.  The path can be specified using the local
    operating system syntax.
    ---------------------------------------------------------------------[>]-*/

char
*strip_file_path (char *name)
{
    char *path_end;

    ASSERT (name != NULL);
    path_end = strrchr (name, PATHEND); /*  Find end of path, if any         */
    if (path_end != NULL)
        memmove (name, path_end + 1, strlen (path_end));
    return (name);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_is_readable

    Synopsis: Returns TRUE if the current process can read the specified
    file or directory.
    ---------------------------------------------------------------------[>]-*/

Bool
file_is_readable (char *file_name)
{
    return ((file_mode (file_name) & S_IREAD) != 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_is_writeable

    Synopsis: Returns TRUE if the current process can write the specified
    or directory.
    ---------------------------------------------------------------------[>]-*/

Bool
file_is_writeable (char *file_name)
{
    return ((file_mode (file_name) & S_IWRITE) != 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_is_executable

    Synopsis: Returns TRUE if the current process can execute the specified
    file, or change to the specified directory.  Directories are considered
    as 'executable' to keep things compatible with UNIX's world view.  If
    you need to distinguish executable files from directories, test first
    with file_is_directory(), then with this function.  Under MS-DOS and
    Windows, appends ".com", ".exe", and ".bat", in that order.
    ---------------------------------------------------------------------[>]-*/

Bool
file_is_executable (char *file_name)
{
    if (file_mode (file_name) & S_IFDIR)
        return (TRUE);                  /*  Always true for directories      */

#if defined (__MSDOS__)
    if (file_where ('r', "PATH", file_name, ".com")
    ||  file_where ('r', "PATH", file_name, ".exe")
    ||  file_where ('r', "PATH", file_name, ".bat"))
        return (TRUE);                  /*  Executable file found            */
    else
        return (FALSE);
#else
    return ((file_mode (file_name) & S_IEXEC) != 0);
#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: file_is_directory

    Synopsis: Returns TRUE if the specified file is a directory.
    ---------------------------------------------------------------------[>]-*/

Bool
file_is_directory (char *file_name)
{
    return ((file_mode (file_name) & S_IFDIR) != 0);
}


/*  -------------------------------------------------------------------------
 *  file_mode -- internal
 *
 *  Returns the file mode for the specified file or directory name; returns
 *  0 if the specified file does not exist.
 */

static dbyte
file_mode (char *file_name)
{
    static struct stat
        stat_buf;

    ASSERT (file_name != NULL);
    if (stat (file_name, &stat_buf) == 0)
        return ((dbyte) stat_buf.st_mode);
    else
        return (0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_file_size

    Synopsis: Returns the size, in bytes, of the specified file or
    directory.  The size of a directory is not a portable concept.
    ---------------------------------------------------------------------[>]-*/

long
get_file_size (char *file_name)
{
    struct stat
        stat_buf;

    ASSERT (file_name != NULL);
    if (stat (file_name, &stat_buf) == 0)
        return ((long) stat_buf.st_size);
    else
        return (0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_file_time

    Synopsis: Returns the modification time of the specified file or
    directory.  The returned time is suitable for feeding to localtime().
    ---------------------------------------------------------------------[>]-*/

time_t
get_file_time (char *file_name)
{
    struct stat
        stat_buf;

    ASSERT (file_name != NULL);
    if (stat (file_name, &stat_buf) == 0)
        return (stat_buf.st_mtime);
    else
        return (0);
}

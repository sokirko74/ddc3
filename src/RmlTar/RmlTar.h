/*
**  Copyright 1998-2003 University of Illinois Board of Trustees
**  Copyright 1998-2003 Mark D. Roth
**  All rights reserved.
**
**  libtar.h - header file for libtar library
**
**  Mark D. Roth <roth@uiuc.edu>
**  Campus Information Technologies and Educational Services
**  University of Illinois at Urbana-Champaign
*/

#ifndef LIBTAR_H
#define LIBTAR_H

struct TAR;
/* open a new tarfile handle */
int tar_open(TAR **t, const char *pathname);
/* close tarfile handle */
int tar_close(TAR *t);
/* get next file, it returns false, if Result contains a file, otherwise there is no more files in the tar archive  */
bool tar_get_next_file(TAR *t, string& FileName, vector<char>& Result, bool& bError);


#endif /* ! LIBTAR_H */


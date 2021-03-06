/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR (c) 1990 - 2016                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/*********************************************************************
 * parse_args.c: parse command line args, open files as required
 *
 * RAP, NCAR, Boulder CO
 *
 * December 1990
 *
 * Mike Dixon
 *
 *********************************************************************/

#include "mdv2ascii.h"

void parse_args(int argc, char **argv)

{
  
  int error_flag = 0;
  int i;
  int malloc_debug_level;
  char usage[BUFSIZ];
  char *end_pt;
  
  /*
   * set usage string
   */
  
  sprintf(usage, "%s%s%s%s",
	  "Usage: ", Glob->prog_name, " [options as below] file-name\n",
	  "options:\n"
	  "       [ --, -h, -help, -man ] produce this list.\n"
          "       [ -field ?] field number\n"
	  "       [ -bad ?] Set value to use for bad/missing data\n"
	  "       [ -comp ?] compute composite (overrides -plane)\n"
	  "       [ -format ?] output format (def ' %7.2f')\n"
	  "       [ -mdebug level] malloc debug level (def 0)\n"
	  "       [ -min ?] constrain min output value\n"
	  "       [ -max ?] constrain max output value\n"
	  "       [ -ncols ?] number of cols in printout (def 10)\n"
	  "       [ -plane ?] plane num (def 0)\n"
	  "       [ -start ?] start row (TOP or BOT, def BOT)\n"
          "       [ -vol ?] print out entire volume (overrides -plane and -comp)\n"
	  "\n");
  
  if (argc < 2) {
    fprintf(stderr, "%s", usage);
    exit(1);
  }
  
  /*
   * set defaults
   */
  
  Glob->plane_num = 0;
  Glob->field_num = 0;
  Glob->ncolumns = 10;
  Glob->format = " %7.2f";
  Glob->min_output_val = -1.0e99;
  Glob->max_output_val = 1.0e99;
  Glob->start_row = BOT;
  Glob->composite = FALSE;
  Glob->vol = FALSE;
  Glob->bad = -999.0;
  Glob->badSet = 0;

  malloc_debug_level = 0;

  /*
   * set file name
   */
  
  Glob->file_name = argv[argc - 1];
  
  /*
   * look for command options
   */
  
  for (i =  1; i < argc; i++) {
    
    if (!strcmp(argv[i], "--") ||
	!strcmp(argv[i], "-h") ||
	!strcmp(argv[i], "-help") ||
	!strcmp(argv[i], "-man")) {
      
      fprintf(stderr, "%s", usage);
      exit(0);
      
    } else if (!strcmp(argv[i], "-field")) {
      
      if (i < argc - 1)
	Glob->field_num = strtol(argv[i+1], &end_pt, 10);
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-format")) {
      
      if (i < argc - 1)
	Glob->format = argv[i+1];
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-mdebug")) {
      
      if (i < argc - 1)
	malloc_debug_level = strtol(argv[i+1], &end_pt, 10);
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-min")) {
      
      if (i < argc - 1)
	Glob->min_output_val = strtod(argv[i+1], &end_pt);
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-max")) {
      
      if (i < argc - 1)
	Glob->max_output_val = strtod(argv[i+1], &end_pt);
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-ncols")) {
      
      if (i < argc - 1)
	Glob->ncolumns = strtol(argv[i+1], &end_pt, 10);
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-plane")) {
      
      if (i < argc - 1)
	Glob->plane_num = strtol(argv[i+1], &end_pt, 10);
      else
	error_flag = TRUE;
      
    } else if (!strcmp(argv[i], "-bad")) {
      if (i < argc - 1){
	Glob->bad = atof(argv[i+1]);
	Glob->badSet = 1;
      } else {
	error_flag = TRUE;
      }

    } else if (!strcmp(argv[i], "-comp")) {
      
      Glob->composite = TRUE;
      
    } else if (!strcmp(argv[i], "-vol")) {
      
      Glob->vol = TRUE;
      
    } else if (!strcmp(argv[i], "-start")) {
      
      if (i < argc - 1) {
	if (!strcmp(argv[i+1], "TOP")) {
	  Glob->start_row = TOP;
	} else if (!strcmp(argv[i+1], "BOT")) {
	  Glob->start_row = BOT;
	} else {
	  error_flag = TRUE;
	}
      } else {
	error_flag = TRUE;
      }
      
    }
    
  }
  
  /*
   * set the malloc debug level
   */
  
  umalloc_debug ((int) malloc_debug_level);
  
  /*
   * print message if warning or error flag set
   */
  
  if(error_flag) {
    fprintf(stderr, "%s", usage);
  }
  
  if (error_flag)
    exit(-1);
  
}



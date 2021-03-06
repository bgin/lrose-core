// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

// SCCS info
//   %W% %D% %T%
//   %F% %E% %U%
//
// RCS info
//   $Author: dixon $
//   $Locker:  $
//   $Date: 2016/03/06 23:31:57 $
//   $Id: spdb2bdry.cc,v 1.5 2016/03/06 23:31:57 dixon Exp $
//   $Revision: 1.5 $
//   $State: Exp $
//

/**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**/
/*********************************************************************
 * spdb2bdry.cc: Program to convert SPDB files to ASCII boundary format.
 *
 * RAP, NCAR, Boulder CO
 *
 * February 1999
 *
 * Jaimi Yee
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <toolsa/os_config.h>
#include <dataport/port_types.h>
#include <rapformats/bdry.h>
#include <symprod/spdb_client.h>
#include <symprod/spdb_products.h>
#include <tdrp/tdrp.h>
#include <toolsa/str.h>
#include <toolsa/umisc.h>
#include <toolsa/utim.h>
#include <toolsa/file_io.h>

#include "spdb2bdry_tdrp.h"

#define INTERVAL_TIME 5
#define MAX_TYPE_LEN 40

// Prototypes for static functions

static int parse_args(int argc, char **argv,
		      int *check_params_p,
		      char **params_file_path_p,
		      tdrp_override_t *override);

static void tidy_and_exit(int sig);


// Global variables

spdb2bdry_tdrp_struct Params;
FILE *OutputFp;


/*********************************************************************
 * main()
 */

int main(int argc, char **argv)
{
  // basic declarations

  char *prog_name;
  path_parts_t progname_parts;
  char *params_path_name;
  
  int check_params;
  tdrp_override_t override;
  TDRPtable *table;

  spdb_handle_t handle;
  time_t first_time, end_time;
  time_t start_time, last_time;

  int  nchunks;
  spdb_chunk_ref_t *headers;
  char *chunk_buffer;

  BDRY_spdb_product_t *bdry_spdb_product;
  BDRY_spdb_product_t *prev_spdb_product;
  SIO_shape_data_t *bdry_shape;

  int i,j;
  bool duplicate;

  // initialize output file pointer
  OutputFp = NULL;
  
  // set program name

  uparse_path(argv[0], &progname_parts);
  prog_name = STRdup(progname_parts.base);

  // display ucopyright message

  ucopyright(prog_name);

  // parse the command line arguments

  if (parse_args(argc, argv, &check_params,
		 &params_path_name, &override) != 0)
    exit(-1);

  // load up parameters

  table = spdb2bdry_tdrp_init(&Params);
  
  if (params_path_name)
  {
    if (TDRP_read(params_path_name,
		  table, &Params,
		  override.list) == FALSE)
    {
      fprintf(stderr, "ERROR - %s: Cannot read params file '%s'\n",
	      prog_name, params_path_name);
      exit(-1);
    }
  }
  else
  {
    TDRP_set_defaults(table, &Params);
  }
  
  TDRP_free_override(&override);
  
  if (check_params)
  {
    TDRP_check_is_set(table, &Params);
    TDRP_print_params(table, &Params, prog_name, TRUE);
    exit(-1);
  }

  //
  // Initialize spdb handle
  //
  if( SPDB_init( &handle, SPDB_BDRY_LABEL, SPDB_BDRY_ID, 
                 Params.input_path ) ) {
     fprintf( stderr, "%s: ERROR: could not create spdb handle",
              prog_name );
     tidy_and_exit( -1 );
  }

  //
  // Get start and end times for data base
  //
  first_time = UTIMstring_US_to_time( Params.start_time );
  last_time = UTIMstring_US_to_time( Params.end_time );

  //
  // Open output file
  //
  if( (OutputFp = 
       ta_fopen_uncompress( Params.output_file_path, "a" )) == NULL ) {
     fprintf( stderr, "%s: ERROR: could not open output file %s",
	      prog_name, Params.output_file_path );
     tidy_and_exit( -1 );
  }
  
  // Process boundary files

  start_time = first_time;
  while( start_time < last_time )
  {
     end_time = start_time + INTERVAL_TIME;
     if( end_time > last_time )
	end_time = last_time;
     
     if( SPDB_fetch_interval( &handle, 0, start_time, end_time,
                              &nchunks, &headers, (void **) &chunk_buffer ) ) {
	fprintf( stderr, "%s: ERROR: could not read data base",
                 prog_name );
	tidy_and_exit( -1 );
     }

     for( i = 0; i < nchunks; i++ ) {
	
        bdry_spdb_product = (BDRY_spdb_product_t *)
	   (chunk_buffer + headers[i].offset );
	
        BDRY_spdb_product_from_BE( bdry_spdb_product );
 
        duplicate = false;
        if( Params.rm_duplicates ) {
	   
	    for( j = 0; j < i; j++ ) {
	       prev_spdb_product = (BDRY_spdb_product_t *)
		  (chunk_buffer + headers[j].offset);

	       if( (bdry_spdb_product->data_time != 
		    prev_spdb_product->data_time) )
		  continue;

	       if( !STRequal( bdry_spdb_product->desc, 
			      prev_spdb_product->desc ) )
		  continue;

	       if( (bdry_spdb_product->polylines[0].num_pts !=
		    prev_spdb_product->polylines[0].num_pts ) )
		  continue;

	       if( (bdry_spdb_product->polylines[0].points[0].lat !=
		    prev_spdb_product->polylines[0].points[0].lat ) ||
		   (bdry_spdb_product->polylines[0].points[0].lon !=
		    prev_spdb_product->polylines[0].points[0].lon ) )
		  continue;

	       duplicate = true;
	       break;
	    }
	}

        if( duplicate )
	   continue;
	
        if( (bdry_shape = 
             BDRY_spdb_product_to_SIO_shape( bdry_spdb_product )) == NULL ) {
	   fprintf( stderr, "%s: ERROR: could not convert product",
                    prog_name );
	   tidy_and_exit( -1 );
	}
	
        SIO_write_data( OutputFp, bdry_shape, 1 );
     }

     start_time = end_time + 1;
     
  }
    
  tidy_and_exit(0);
}


/*******************************************************************
 * parse_args() - Parse the command line arguments.
 *
 * Returns 0 if successful and command line is proper, returns -1
 * if the program should exit.
 */

static int parse_args(int argc, char **argv,
		      int *check_params_p,
		      char **params_file_path_p,
		      tdrp_override_t *override)
{
  int error_flag = 0;
  int warning_flag = 0;
  int i;

  char usage[BUFSIZ];
  char tmp_str[BUFSIZ];
  
  // load up usage string

  sprintf(usage, "%s%s%s",
	  "Usage:\n\n", argv[0], " [options] as below:\n\n"
	  "       [ --, -help, -man] produce this list.\n"
	  "       [ -check_params] check parameter usage\n"
	  "       [ -debug ] debugging on\n"
	  "       [ -params name] parameters file name (required)\n"
	  "       [ -print_params] print parameter usage\n"
	  "\n");

  // initialize

  *check_params_p = FALSE;
  TDRP_init_override(override);
  *params_file_path_p = (char *)NULL;
  
  // search for command options
  
  for (i =  1; i < argc; i++)
  {
    if (STRequal_exact(argv[i], "--") ||
	STRequal_exact(argv[i], "-help") ||
	STRequal_exact(argv[i], "-man"))
    {
      printf("%s", usage);
      return(-1);
    }
    else if (STRequal_exact(argv[i], "-check_params") ||
	     STRequal_exact(argv[i], "-print_params"))
    {
      *check_params_p = TRUE;
    }
    else if (STRequal_exact(argv[i], "-debug"))
    {
      sprintf(tmp_str, "debug = true;");
      TDRP_add_override(override, tmp_str);
    }
    else if (i < argc - 1)
    {
      if (STRequal_exact(argv[i], "-params"))
      {
	*params_file_path_p = argv[i+1];

	i++;
      }
    } /* if (i < argc - 1) */
    
  } /* i */

  // print usage if there was an error

  if (error_flag || warning_flag)
  {
    fprintf(stderr, "%s\n", usage);
    fprintf(stderr, "Check the parameters file '%s'.\n\n",
	    *params_file_path_p);
  }

  if (error_flag)
    return(-1);

  return(0);
}

/************************************************************************
 * tidy_and_exit()
 */

static void tidy_and_exit(int sig)
{
   // free memory associated with SPDB calls

   SPDB_free_get();

   // close output file

   if( OutputFp != NULL )
      fclose( OutputFp );

  // exit with code sig

  exit(sig);
}

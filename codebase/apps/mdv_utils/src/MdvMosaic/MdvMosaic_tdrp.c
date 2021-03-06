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
/*******************************************
 * MdvMosaic_tdrp.c
 *
 * TDRP C code file 'MdvMosaic' module.
 *
 * Code for program MdvMosaic
 *
 * This file has been automatically
 * generated by TDRP, do not modify.
 *
 *******************************************/

#include "MdvMosaic_tdrp.h"
#include <string.h>

/*
 * file scope variables
 */

static TDRPtable Table[19];
static MdvMosaic_tdrp_struct *Params;
static char *Module = "MdvMosaic";

/*************************************************************
 * MdvMosaic_tdrp_load_from_args()
 *
 * Loads up TDRP using the command line args.
 *
 * Check TDRP_usage() for command line actions associated with
 * this function.
 *
 *   argc, argv: command line args
 *
 *   MdvMosaic_tdrp_struct *params: loads up this struct
 * 
 *   char **override_list: A null-terminated list of overrides
 *     to the parameter file.
 *     An override string has exactly the format of an entry
 *     in the parameter file itself.
 *
 *   char **params_path_p: if non-NULL, this is set to point to
 *                         the path of the params file used.
 *
 *  Returns 0 on success, -1 on failure.
 */

int MdvMosaic_tdrp_load_from_args(int argc, char **argv,
                         MdvMosaic_tdrp_struct *params,
                         char **override_list,
                         char **params_path_p)
{
  Params = params;
  MdvMosaic_tdrp_init(Params);
  if (tdrpLoadFromArgs(argc, argv,
                       Table, Params,
                       override_list, params_path_p)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * MdvMosaic_tdrp_load()
 *
 * Loads up TDRP for a given module.
 *
 * This version of load gives the programmer the option to load
 * up more than one module for a single application. It is a
 * lower-level routine than MdvMosaic_tdrp_load_from_args,
 * and hence more flexible, but the programmer must do more work.
 *
 *   char *param_file_path: the parameter file to be read in.
 *
 *   MdvMosaic_tdrp_struct *params: loads up this struct
 *
 *   char **override_list: A null-terminated list of overrides
 *     to the parameter file.
 *     An override string has exactly the format of an entry
 *     in the parameter file itself.
 *
 *  expand_env: flag to control environment variable
 *                expansion during tokenization.
 *              If TRUE, environment expansion is set on.
 *              If FALSE, environment expansion is set off.
 *
 *  Returns 0 on success, -1 on failure.
 */

int MdvMosaic_tdrp_load(char *param_file_path,
               MdvMosaic_tdrp_struct *params,
               char **override_list,
               int expand_env, int debug)
{
  Params = params;
  MdvMosaic_tdrp_init(Params);
  if (tdrpLoad(param_file_path, Table,
               params, override_list,
               expand_env, debug)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * MdvMosaic_tdrp_load_defaults()
 *
 * Loads up defaults for a given module.
 *
 * See MdvMosaic_tdrp_load() for more details.
 *
 *  Returns 0 on success, -1 on failure.
 */

int MdvMosaic_tdrp_load_defaults(MdvMosaic_tdrp_struct *params,
                        int expand_env)
{
  Params = params;
  MdvMosaic_tdrp_init(Params);
  if (tdrpLoad(NULL, Table,
               params, NULL,
               expand_env, FALSE)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * MdvMosaic_tdrp_sync()
 *
 * Syncs the user struct data back into the parameter table,
 * in preparation for printing.
 */

void MdvMosaic_tdrp_sync(void)
{
  tdrpUser2Table(Table, Params);
}

/*************************************************************
 * MdvMosaic_tdrp_print()
 * 
 * Print params file
 *
 * The modes supported are:
 *
 *   PRINT_SHORT:   main comments only, no help or descriptions
 *                  structs and arrays on a single line
 *   PRINT_NORM:    short + descriptions and help
 *   PRINT_LONG:    norm  + arrays and structs expanded
 *   PRINT_VERBOSE: long  + private params included
 */

void MdvMosaic_tdrp_print(FILE *out, tdrp_print_mode_t mode)
{
  tdrpPrint(out, Table, Module, mode);
}

/*************************************************************
 * MdvMosaic_tdrp_check_all_set()
 *
 * Return TRUE if all set, FALSE if not.
 *
 * If out is non-NULL, prints out warning messages for those
 * parameters which are not set.
 */

int MdvMosaic_tdrp_check_all_set(FILE *out)
{
  return (tdrpCheckAllSet(out, Table, Params));
}

/*************************************************************
 * MdvMosaic_tdrp_check_is_set()
 *
 * Return TRUE if parameter is set, FALSE if not.
 *
 */

int MdvMosaic_tdrp_check_is_set(char *param_name)
{
  return (tdrpCheckIsSet(param_name, Table, Params));
}

/*************************************************************
 * MdvMosaic_tdrp_free_all()
 *
 * Frees up all TDRP dynamic memory.
 */

void MdvMosaic_tdrp_free_all(void)
{
  tdrpFreeAll(Table, Params);
}

/*************************************************************
 * MdvMosaic_tdrp_array_realloc()
 *
 * Realloc 1D array.
 *
 * If size is increased, the values from the last array entry is
 * copied into the new space.
 *
 * Returns 0 on success, -1 on error.
 */

int MdvMosaic_tdrp_array_realloc(char *param_name, int new_array_n)
{
  if (tdrpArrayRealloc(Table, Params, param_name, new_array_n)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * MdvMosaic_tdrp_array2D_realloc()
 *
 * Realloc 2D array.
 *
 * If size is increased, the values from the last array entry is
 * copied into the new space.
 *
 * Returns 0 on success, -1 on error.
 */

int MdvMosaic_tdrp_array2D_realloc(char *param_name,
                          int new_array_n1,
                          int new_array_n2)
{
  if (tdrpArray2DRealloc(Table, Params, param_name,
			 new_array_n1, new_array_n2)) {
    return (-1);
  } else {
    return (0);
  }
}

/*************************************************************
 * MdvMosaic_tdrp_table()
 *
 * Returns pointer to static Table for this module.
 */

TDRPtable *MdvMosaic_tdrp_table(void)
{
  return (Table);
}

/*************************************************************
 * MdvMosaic_tdrp_init()
 *
 * Module table initialization function.
 *
 *
 * Returns pointer to static Table for this module.
 */

TDRPtable *MdvMosaic_tdrp_init(MdvMosaic_tdrp_struct *params)

{

  TDRPtable *tt = Table;

  MdvMosaic_tdrp_struct pp; /* for computing byte_offsets */

  /* zero out struct, and store size */

  memset(params, 0, sizeof(MdvMosaic_tdrp_struct));
  params->struct_size = sizeof(MdvMosaic_tdrp_struct);

  /* Parameter 'debug' */
  /* ctype is 'MdvMosaic_debug' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("debug");
  tt->descr = tdrpStrDup("Debug option");
  tt->help = tdrpStrDup("If set, debug messages will be printed with the appropriate level of detail.");
  tt->val_offset = (char *) &(pp.debug) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("debug");
  tt->enum_def.nfields = 4;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
    tt->enum_def.fields[0].val = DEBUG_OFF;
    tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_WARNINGS");
    tt->enum_def.fields[1].val = DEBUG_WARNINGS;
    tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_NORM");
    tt->enum_def.fields[2].val = DEBUG_NORM;
    tt->enum_def.fields[3].name = tdrpStrDup("DEBUG_VERBOSE");
    tt->enum_def.fields[3].val = DEBUG_VERBOSE;
  tt->single_val.e = DEBUG_OFF;
  tt++;
  
  /* Parameter 'malloc_debug_level' */
  /* ctype is 'long' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = LONG_TYPE;
  tt->param_name = tdrpStrDup("malloc_debug_level");
  tt->descr = tdrpStrDup("Malloc debug level");
  tt->help = tdrpStrDup("0 - none, 1 - corruption checking, 2 - records all malloc blocks and checks, 3 - printout of all mallocs etc.");
  tt->val_offset = (char *) &(pp.malloc_debug_level) - (char *) &pp;
  tt->has_min = TRUE;
  tt->has_max = TRUE;
  tt->min_val.l = 0;
  tt->max_val.l = 3;
  tt->single_val.l = 0;
  tt++;
  
  /* Parameter 'instance' */
  /* ctype is 'char*' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRING_TYPE;
  tt->param_name = tdrpStrDup("instance");
  tt->descr = tdrpStrDup("Process instance");
  tt->help = tdrpStrDup("Used for registration with procmap.");
  tt->val_offset = (char *) &(pp.instance) - (char *) &pp;
  tt->single_val.s = tdrpStrDup("Test");
  tt++;
  
  /* Parameter 'mode' */
  /* ctype is 'MdvMosaic_mode' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("mode");
  tt->descr = tdrpStrDup("Operation mode");
  tt->help = tdrpStrDup("Program may be run in two modes, archive and realtime. In realtime mode, the analysis is performed for each volume scan as it becomes available. In archive mode, the file list is obtained from the command line.");
  tt->val_offset = (char *) &(pp.mode) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("mode");
  tt->enum_def.nfields = 2;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("ARCHIVE");
    tt->enum_def.fields[0].val = ARCHIVE;
    tt->enum_def.fields[1].name = tdrpStrDup("REALTIME");
    tt->enum_def.fields[1].val = REALTIME;
  tt->single_val.e = ARCHIVE;
  tt++;
  
  /* Parameter 'trigger' */
  /* ctype is 'MdvMosaic_trigger' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("trigger");
  tt->descr = tdrpStrDup("Trigger mechanism.");
  tt->help = tdrpStrDup("TIME_TRIGGER: the program is triggered at constant time intervals - see time_trigger_interval. FILE_TRIGGER: the program watches the first input_dir and triggers based on data in that directory.");
  tt->val_offset = (char *) &(pp.trigger) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("trigger");
  tt->enum_def.nfields = 2;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("TIME_TRIGGER");
    tt->enum_def.fields[0].val = TIME_TRIGGER;
    tt->enum_def.fields[1].name = tdrpStrDup("FILE_TRIGGER");
    tt->enum_def.fields[1].val = FILE_TRIGGER;
  tt->single_val.e = TIME_TRIGGER;
  tt++;
  
  /* Parameter 'time_trigger_interval' */
  /* ctype is 'long' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = LONG_TYPE;
  tt->param_name = tdrpStrDup("time_trigger_interval");
  tt->descr = tdrpStrDup("Interval for TIME_TRIGGER - secs.");
  tt->help = tdrpStrDup("For TIME_TRIGGER, this is the interval between trigger events. In REALTIME mode, a time trigger always occurs on the hour, and at constant intervals thereafter. In ARCHIVE mode the trigger starts at start_time and at constant intervals thereafter.");
  tt->val_offset = (char *) &(pp.time_trigger_interval) - (char *) &pp;
  tt->has_min = TRUE;
  tt->min_val.l = 0;
  tt->single_val.l = 300;
  tt++;
  
  /* Parameter 'trigger_time_margin' */
  /* ctype is 'long' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = LONG_TYPE;
  tt->param_name = tdrpStrDup("trigger_time_margin");
  tt->descr = tdrpStrDup("Max time diff for searching for files relative to the trigger time - secs.");
  tt->help = tdrpStrDup("When matching files up with the trigger time, the difference between the trigger time and file time must be less than this margin. This value is also used as the max age of the latest data info file when in REALTIME mode with FILE_TRIGGER.");
  tt->val_offset = (char *) &(pp.trigger_time_margin) - (char *) &pp;
  tt->has_min = TRUE;
  tt->min_val.l = 0;
  tt->single_val.l = 600;
  tt++;
  
  /* Parameter 'input_dirs' */
  /* ctype is 'char*' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRING_TYPE;
  tt->param_name = tdrpStrDup("input_dirs");
  tt->descr = tdrpStrDup("Array of input directories.");
  tt->help = tdrpStrDup("If available, data from these directories will be merged.");
  tt->val_offset = (char *) &(pp.input_dirs.val) - (char *) &pp;
  tt->len_offset = (char *) &(pp.input_dirs.len) - (char *) &pp;
  tt->array_offset = (char *) &(pp._input_dirs) - (char *) &pp;
  tt->array_n_offset = (char *) &(pp.input_dirs_n) - (char *) &pp;
  tt->is_array = TRUE;
  tt->array_len_fixed = FALSE;
  tt->array_elem_size = sizeof(char*);
  tt->array_n = 1;
  tt->array_vals = (tdrpVal_t *)
      tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
    tt->array_vals[0].s = tdrpStrDup(".");
  tt++;
  
  /* Parameter 'output_dir' */
  /* ctype is 'char*' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRING_TYPE;
  tt->param_name = tdrpStrDup("output_dir");
  tt->descr = tdrpStrDup("Output directory.");
  tt->help = tdrpStrDup("The merged files are placed in this directory.");
  tt->val_offset = (char *) &(pp.output_dir) - (char *) &pp;
  tt->single_val.s = tdrpStrDup(".");
  tt++;
  
  /* Parameter 'output_projection' */
  /* ctype is 'MdvMosaic_output_projection' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = ENUM_TYPE;
  tt->param_name = tdrpStrDup("output_projection");
  tt->descr = tdrpStrDup("Projection of output grid.");
  tt->help = tdrpStrDup("FLAT - (x,y) Cartesian data in km from a given origin. LATLON - lat/lon grid with constant grid spacing.");
  tt->val_offset = (char *) &(pp.output_projection) - (char *) &pp;
  tt->enum_def.name = tdrpStrDup("output_projection");
  tt->enum_def.nfields = 2;
  tt->enum_def.fields = (enum_field_t *)
      tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
    tt->enum_def.fields[0].name = tdrpStrDup("OUTPUT_PROJ_FLAT");
    tt->enum_def.fields[0].val = OUTPUT_PROJ_FLAT;
    tt->enum_def.fields[1].name = tdrpStrDup("OUTPUT_PROJ_LATLON");
    tt->enum_def.fields[1].val = OUTPUT_PROJ_LATLON;
  tt->single_val.e = OUTPUT_PROJ_LATLON;
  tt++;
  
  /* Parameter 'output_origin' */
  /* ctype is 'MdvMosaic_output_origin' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRUCT_TYPE;
  tt->param_name = tdrpStrDup("output_origin");
  tt->descr = tdrpStrDup("Origin of output grid.");
  tt->help = tdrpStrDup("Used with both OUTPUT_PROJ_LATLON and OUTPUT_PROJ_FLAT.");
  tt->val_offset = (char *) &(pp.output_origin) - (char *) &pp;
  tt->struct_def.name = tdrpStrDup("output_origin");
  tt->struct_def.nfields = 2;
  tt->struct_def.fields = (struct_field_t *)
      tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
    tt->struct_def.fields[0].ftype = tdrpStrDup("double");
    tt->struct_def.fields[0].fname = tdrpStrDup("lat");
    tt->struct_def.fields[0].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[0].rel_offset = 
      (char *) &(pp.output_origin.lat) - (char *) &(pp.output_origin);
    tt->struct_def.fields[1].ftype = tdrpStrDup("double");
    tt->struct_def.fields[1].fname = tdrpStrDup("lon");
    tt->struct_def.fields[1].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[1].rel_offset = 
      (char *) &(pp.output_origin.lon) - (char *) &(pp.output_origin);
  tt->n_struct_vals = 2;
  tt->struct_vals = (tdrpVal_t *)
      tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
    tt->struct_vals[0].d = 40;
    tt->struct_vals[1].d = -104;
  tt++;
  
  /* Parameter 'output_grid' */
  /* ctype is 'MdvMosaic_grid' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRUCT_TYPE;
  tt->param_name = tdrpStrDup("output_grid");
  tt->descr = tdrpStrDup("Output grid parameters.");
  tt->help = tdrpStrDup("The grid params for the output grid.");
  tt->val_offset = (char *) &(pp.output_grid) - (char *) &pp;
  tt->struct_def.name = tdrpStrDup("grid");
  tt->struct_def.nfields = 9;
  tt->struct_def.fields = (struct_field_t *)
      tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
    tt->struct_def.fields[0].ftype = tdrpStrDup("long");
    tt->struct_def.fields[0].fname = tdrpStrDup("nx");
    tt->struct_def.fields[0].ptype = LONG_TYPE;
    tt->struct_def.fields[0].rel_offset = 
      (char *) &(pp.output_grid.nx) - (char *) &(pp.output_grid);
    tt->struct_def.fields[1].ftype = tdrpStrDup("long");
    tt->struct_def.fields[1].fname = tdrpStrDup("ny");
    tt->struct_def.fields[1].ptype = LONG_TYPE;
    tt->struct_def.fields[1].rel_offset = 
      (char *) &(pp.output_grid.ny) - (char *) &(pp.output_grid);
    tt->struct_def.fields[2].ftype = tdrpStrDup("long");
    tt->struct_def.fields[2].fname = tdrpStrDup("nz");
    tt->struct_def.fields[2].ptype = LONG_TYPE;
    tt->struct_def.fields[2].rel_offset = 
      (char *) &(pp.output_grid.nz) - (char *) &(pp.output_grid);
    tt->struct_def.fields[3].ftype = tdrpStrDup("double");
    tt->struct_def.fields[3].fname = tdrpStrDup("minx");
    tt->struct_def.fields[3].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[3].rel_offset = 
      (char *) &(pp.output_grid.minx) - (char *) &(pp.output_grid);
    tt->struct_def.fields[4].ftype = tdrpStrDup("double");
    tt->struct_def.fields[4].fname = tdrpStrDup("miny");
    tt->struct_def.fields[4].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[4].rel_offset = 
      (char *) &(pp.output_grid.miny) - (char *) &(pp.output_grid);
    tt->struct_def.fields[5].ftype = tdrpStrDup("double");
    tt->struct_def.fields[5].fname = tdrpStrDup("minz");
    tt->struct_def.fields[5].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[5].rel_offset = 
      (char *) &(pp.output_grid.minz) - (char *) &(pp.output_grid);
    tt->struct_def.fields[6].ftype = tdrpStrDup("double");
    tt->struct_def.fields[6].fname = tdrpStrDup("dx");
    tt->struct_def.fields[6].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[6].rel_offset = 
      (char *) &(pp.output_grid.dx) - (char *) &(pp.output_grid);
    tt->struct_def.fields[7].ftype = tdrpStrDup("double");
    tt->struct_def.fields[7].fname = tdrpStrDup("dy");
    tt->struct_def.fields[7].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[7].rel_offset = 
      (char *) &(pp.output_grid.dy) - (char *) &(pp.output_grid);
    tt->struct_def.fields[8].ftype = tdrpStrDup("double");
    tt->struct_def.fields[8].fname = tdrpStrDup("dz");
    tt->struct_def.fields[8].ptype = DOUBLE_TYPE;
    tt->struct_def.fields[8].rel_offset = 
      (char *) &(pp.output_grid.dz) - (char *) &(pp.output_grid);
  tt->n_struct_vals = 9;
  tt->struct_vals = (tdrpVal_t *)
      tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
    tt->struct_vals[0].l = 1830;
    tt->struct_vals[1].l = 918;
    tt->struct_vals[2].l = 1;
    tt->struct_vals[3].d = -129.981;
    tt->struct_vals[4].d = 20.018;
    tt->struct_vals[5].d = 0.5;
    tt->struct_vals[6].d = 0.038239;
    tt->struct_vals[7].d = 0.0359331;
    tt->struct_vals[8].d = 1;
  tt++;
  
  /* Parameter 'field_list' */
  /* ctype is 'long' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = LONG_TYPE;
  tt->param_name = tdrpStrDup("field_list");
  tt->descr = tdrpStrDup("List of field numbers to be processed from input files.");
  tt->help = tdrpStrDup("These fields will be read from the input files and merged into the output files.");
  tt->val_offset = (char *) &(pp.field_list.val) - (char *) &pp;
  tt->len_offset = (char *) &(pp.field_list.len) - (char *) &pp;
  tt->array_offset = (char *) &(pp._field_list) - (char *) &pp;
  tt->array_n_offset = (char *) &(pp.field_list_n) - (char *) &pp;
  tt->is_array = TRUE;
  tt->array_len_fixed = FALSE;
  tt->array_elem_size = sizeof(long);
  tt->array_n = 1;
  tt->array_vals = (tdrpVal_t *)
      tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
    tt->array_vals[0].l = 0;
  tt++;
  
  /* Parameter 'data_set_name' */
  /* ctype is 'char*' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRING_TYPE;
  tt->param_name = tdrpStrDup("data_set_name");
  tt->descr = tdrpStrDup("Data set name.");
  tt->help = tdrpStrDup("This is placed in the MDV master header for documentation purposes.");
  tt->val_offset = (char *) &(pp.data_set_name) - (char *) &pp;
  tt->single_val.s = tdrpStrDup("Unknown");
  tt++;
  
  /* Parameter 'data_set_source' */
  /* ctype is 'char*' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = STRING_TYPE;
  tt->param_name = tdrpStrDup("data_set_source");
  tt->descr = tdrpStrDup("Data set source details.");
  tt->help = tdrpStrDup("This is placed in the MDV master header for documentation purposes.");
  tt->val_offset = (char *) &(pp.data_set_source) - (char *) &pp;
  tt->single_val.s = tdrpStrDup("Merged data created by MdvMosaic.");
  tt++;
  
  /* Parameter 'data_scale' */
  /* ctype is 'double' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = DOUBLE_TYPE;
  tt->param_name = tdrpStrDup("data_scale");
  tt->descr = tdrpStrDup("scale value used for converting between byte values and data values");
  tt->help = tdrpStrDup("The byte value is calculated from the byte value using the following formula: byte = (value - data_bias) / data_scale. Only used if compute_scale_and_bias is TRUE");
  tt->val_offset = (char *) &(pp.data_scale) - (char *) &pp;
  tt->single_val.d = 0.3;
  tt++;
  
  /* Parameter 'data_bias' */
  /* ctype is 'double' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = DOUBLE_TYPE;
  tt->param_name = tdrpStrDup("data_bias");
  tt->descr = tdrpStrDup("bias value used for converting between byte values and data values");
  tt->help = tdrpStrDup("The byte value is calculated from the byte value using the following formula: byte = (value - data_bias) / data_scale. ");
  tt->val_offset = (char *) &(pp.data_bias) - (char *) &pp;
  tt->single_val.d = 0;
  tt++;
  
  /* Parameter 'compute_scale_and_bias' */
  /* ctype is 'tdrp_bool_t' */
  
  memset(tt, 0, sizeof(TDRPtable));
  tt->ptype = BOOL_TYPE;
  tt->param_name = tdrpStrDup("compute_scale_and_bias");
  tt->descr = tdrpStrDup("Option to automatically compute the data scale and bias.");
  tt->help = tdrpStrDup("If set to TRUE, the data scale and bias will automatically be computed from the input data, otherwise the data_scale and data_bias parameter values will be used.");
  tt->val_offset = (char *) &(pp.compute_scale_and_bias) - (char *) &pp;
  tt->single_val.b = pFALSE;
  tt++;
  
  /* trailing entry has param_name set to NULL */
  
  tt->param_name = NULL;
  
  return (Table);

}

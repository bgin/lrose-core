// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research(UCAR)
// ** National Center for Atmospheric Research(NCAR)
// ** Boulder, Colorado, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program TitanSelect
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
using namespace std;

#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params/--params path ] specify params file path\n"
        << "   [ -check_params/--check_params] check which params are not set\n"
        << "   [ -print_params/--print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("Program TitanSelect");
    tt->comment_text = tdrpStrDup("TitanSelect selects specified Titan track data from the database and prints it to stdout. It watches the Rview shmem segments for user activity and reacts when a new track is specified.");
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DEBUGGING AND PROCESS CONTROL");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is '_debug_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed appropriately");
    tt->val_offset = (char *) &debug - &_start_;
    tt->enum_def.name = tdrpStrDup("debug_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
      tt->enum_def.fields[0].val = DEBUG_OFF;
      tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_NORM");
      tt->enum_def.fields[1].val = DEBUG_NORM;
      tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_VERBOSE");
      tt->enum_def.fields[2].val = DEBUG_VERBOSE;
    tt->single_val.e = DEBUG_OFF;
    tt++;
    
    // Parameter 'instance'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("instance");
    tt->descr = tdrpStrDup("Process instance");
    tt->help = tdrpStrDup("Used for registration with procmap.");
    tt->val_offset = (char *) &instance - &_start_;
    tt->single_val.s = tdrpStrDup("Test");
    tt++;
    
    // Parameter 'log_read_errors'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("log_read_errors");
    tt->descr = tdrpStrDup("Option to log titan read errors to log directory.");
    tt->help = tdrpStrDup("If true, TITAN read errors will be logged to the directory specified by errors_log_dir. The reason for dealing with errors in this way is that stdout from this program is displayed as the main product. It is difficult to separate stderr from stdout and pipe stderr to a logging filter. Therefore we log the titan errors directly.");
    tt->val_offset = (char *) &log_read_errors - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'errors_log_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("errors_log_dir");
    tt->descr = tdrpStrDup("Errors log directory.");
    tt->help = tdrpStrDup("See log_titan_errors.");
    tt->val_offset = (char *) &errors_log_dir - &_start_;
    tt->single_val.s = tdrpStrDup("/tmp");
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("USER INTERFACE");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'sleep_msecs'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("sleep_msecs");
    tt->descr = tdrpStrDup("sleep milli-seconds");
    tt->help = tdrpStrDup("Number of milli-seconds to sleep between checks for mouse clicks.");
    tt->val_offset = (char *) &sleep_msecs - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 20;
    tt->single_val.i = 250;
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("SHARED MEMORY WITH DISPLAY");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'rview_shmem_key'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("rview_shmem_key");
    tt->descr = tdrpStrDup("Rview shared memory key");
    tt->help = tdrpStrDup("Id for the shared memory status segment used for communicating with the display. Must match that used by Rview and TimeHist. There are actually 2 shared mem segments used, one with this key and one with this key + 1.");
    tt->val_offset = (char *) &rview_shmem_key - &_start_;
    tt->single_val.i = 46100;
    tt++;
    
    // Parameter 'Comment 4'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 4");
    tt->comment_hdr = tdrpStrDup("DATA INPUT");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'input_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("input_url");
    tt->descr = tdrpStrDup("URL for reading TITAN data.");
    tt->help = tdrpStrDup("See DIDSS documentation for URL specs.");
    tt->val_offset = (char *) &input_url - &_start_;
    tt->single_val.s = tdrpStrDup("titanp:://localhost::titan/storms");
    tt++;
    
    // Parameter 'Comment 5'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 5");
    tt->comment_hdr = tdrpStrDup("DISPLAY OPTIONS");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'property_list'
    // ctype is '_property_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("property_list");
    tt->descr = tdrpStrDup("Array of properties to printed.");
    tt->help = tdrpStrDup("The properties will be printed in the order they exist in this list.");
    tt->array_offset = (char *) &_property_list - &_start_;
    tt->array_n_offset = (char *) &property_list_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(property_t);
    tt->array_n = 15;
    tt->enum_def.name = tdrpStrDup("property_t");
    tt->enum_def.nfields = 22;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("CENTROID_POSITION");
      tt->enum_def.fields[0].val = CENTROID_POSITION;
      tt->enum_def.fields[1].name = tdrpStrDup("TOP");
      tt->enum_def.fields[1].val = TOP;
      tt->enum_def.fields[2].name = tdrpStrDup("BASE");
      tt->enum_def.fields[2].val = BASE;
      tt->enum_def.fields[3].name = tdrpStrDup("VOLUME");
      tt->enum_def.fields[3].val = VOLUME;
      tt->enum_def.fields[4].name = tdrpStrDup("AREA_MEAN");
      tt->enum_def.fields[4].val = AREA_MEAN;
      tt->enum_def.fields[5].name = tdrpStrDup("PRECIP_FLUX");
      tt->enum_def.fields[5].val = PRECIP_FLUX;
      tt->enum_def.fields[6].name = tdrpStrDup("MASS");
      tt->enum_def.fields[6].val = MASS;
      tt->enum_def.fields[7].name = tdrpStrDup("TILT_ANGLE");
      tt->enum_def.fields[7].val = TILT_ANGLE;
      tt->enum_def.fields[8].name = tdrpStrDup("TILT_DIRN");
      tt->enum_def.fields[8].val = TILT_DIRN;
      tt->enum_def.fields[9].name = tdrpStrDup("DBZ_MAX");
      tt->enum_def.fields[9].val = DBZ_MAX;
      tt->enum_def.fields[10].name = tdrpStrDup("DBZ_MEAN");
      tt->enum_def.fields[10].val = DBZ_MEAN;
      tt->enum_def.fields[11].name = tdrpStrDup("DBZ_MAX_GRADIENT");
      tt->enum_def.fields[11].val = DBZ_MAX_GRADIENT;
      tt->enum_def.fields[12].name = tdrpStrDup("DBZ_MEAN_GRADIENT");
      tt->enum_def.fields[12].val = DBZ_MEAN_GRADIENT;
      tt->enum_def.fields[13].name = tdrpStrDup("HT_OF_DBZ_MAX");
      tt->enum_def.fields[13].val = HT_OF_DBZ_MAX;
      tt->enum_def.fields[14].name = tdrpStrDup("PROJ_AREA");
      tt->enum_def.fields[14].val = PROJ_AREA;
      tt->enum_def.fields[15].name = tdrpStrDup("HAIL_PRESENT");
      tt->enum_def.fields[15].val = HAIL_PRESENT;
      tt->enum_def.fields[16].name = tdrpStrDup("VIL_FROM_MAXZ");
      tt->enum_def.fields[16].val = VIL_FROM_MAXZ;
      tt->enum_def.fields[17].name = tdrpStrDup("LTG_COUNT");
      tt->enum_def.fields[17].val = LTG_COUNT;
      tt->enum_def.fields[18].name = tdrpStrDup("FOKRCATEGORY");
      tt->enum_def.fields[18].val = FOKRCATEGORY;
      tt->enum_def.fields[19].name = tdrpStrDup("POH");
      tt->enum_def.fields[19].val = POH;
      tt->enum_def.fields[20].name = tdrpStrDup("HAILMASSALOFT");
      tt->enum_def.fields[20].val = HAILMASSALOFT;
      tt->enum_def.fields[21].name = tdrpStrDup("VIHM");
      tt->enum_def.fields[21].val = VIHM;
    tt->array_vals = (tdrpVal_t *)
        tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
      tt->array_vals[0].e = TOP;
      tt->array_vals[1].e = VOLUME;
      tt->array_vals[2].e = AREA_MEAN;
      tt->array_vals[3].e = PROJ_AREA;
      tt->array_vals[4].e = PRECIP_FLUX;
      tt->array_vals[5].e = MASS;
      tt->array_vals[6].e = TILT_ANGLE;
      tt->array_vals[7].e = DBZ_MAX;
      tt->array_vals[8].e = DBZ_MAX_GRADIENT;
      tt->array_vals[9].e = HT_OF_DBZ_MAX;
      tt->array_vals[10].e = VIL_FROM_MAXZ;
      tt->array_vals[11].e = FOKRCATEGORY;
      tt->array_vals[12].e = POH;
      tt->array_vals[13].e = HAILMASSALOFT;
      tt->array_vals[14].e = VIHM;
    tt++;
    
    // Parameter 'nlines_scroll_before_printing'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("nlines_scroll_before_printing");
    tt->descr = tdrpStrDup("Number of lines to scroll off the top before starting to print.");
    tt->help = tdrpStrDup("This is sometimes useful to clear the output window of previous output.");
    tt->val_offset = (char *) &nlines_scroll_before_printing - &_start_;
    tt->single_val.i = 1;
    tt++;
    
    // Parameter 'length_delimiter_line'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("length_delimiter_line");
    tt->descr = tdrpStrDup("Length of line delimiting prints.");
    tt->help = tdrpStrDup("A line of dashes will be printed above each series of items printed. This is the number of dashes used. Set to 0 if you do not want a delimiter.");
    tt->val_offset = (char *) &length_delimiter_line - &_start_;
    tt->single_val.i = 34;
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }

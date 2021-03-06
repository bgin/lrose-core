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
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program lmaGridder
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
        << "   [ -check_params] check which params are not set\n"
        << "   [ -print_params [mode]] print parameters\n"
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
    tt->comment_hdr = tdrpStrDup("lmaGridder is a simple program to ingest ltg data from\nthe U of New Mexico Ltg Mapping Array. The altitude information\nis discarded. Files are ASCII with (roughly) the following format :\n\nNew Mexico Tech's Lightning Mapping System -- Ananlyzed Data\nData start time: 08/21/02 05:45:00\nNumber of seconds analyzed:  600\nLocation: New Mexico 2002\nAnalysis program: analysis_v6 -n1\nAnalysis started : Fri Jun 27 13:17:57 2003\nAnalysis finished: Fri Jun 27 13:19:05 2003\nNumber of active stations: 8\nActive stations: A B C D E F G I\nData: time (UT sec of day), lat, lon, alt(m), reduced chi^2, # of stations contributed\nData format: 15.9f 10.6f 10.6f 7.1f 5.2f 2d\nNumber of events:        25939\n*** data ***\n 20707.488263089  -7.778016 -48.345406 25514939.5  1.13  6\n 20707.527138089  33.909109 -107.008366  5261.2  0.00  6\n 20707.536238566  33.915601 -107.005872  5404.0  1.46  6\n 20707.537721091  33.915629 -107.005798  5467.0  1.65  6\n 20707.544873473  33.859059 -106.852575  8290.4  1.15  6\n 20707.550234035  33.913167 -107.013857  7726.4  1.79  6\n 20707.553575905  33.901588 -106.985319  6727.9  1.82  7\n\n\nThe output is a 2D and 3D gridded field of counts of LMA\nactivity.\nNiles Oien January 2003.\n\nNOTE : I just added a new format, so if your data looks something\nlike this :\n\n04/25/05 19:47:04.063769   32.6116  -97.8602     7374\n04/25/05 19:48:35.404669   32.4400  -98.0730     7614\n04/25/05 19:48:35.448107   32.4350  -98.0804     7484\n04/25/05 19:48:35.449442   32.4375  -98.0767     7550\n04/25/05 19:48:35.495172   32.4307  -98.0543     6930\n04/25/05 19:49:01.900245   32.7168  -97.9040     8919\n04/25/05 19:49:01.933207   32.7185  -97.8996     8758\n04/25/05 19:49:01.936794   32.7164  -97.8962     8438\n04/25/05 19:49:02.018703   32.7026  -97.8878     8245\n04/25/05 19:49:29.987431   32.7164  -97.8927     8765\n04/25/05 19:49:30.000040   32.7161  -97.8837     8576\n04/25/05 19:49:30.090099   32.7172  -97.8950     8667\n04/25/05 19:50:12.657643   32.6337  -97.8279     6382\n\nThen use the FORMAT_TWO option rather than FORMAT_ONE\n\nA Third format is now available:\n\nData: time (UT sec of day), lat, lon, alt(m), reduced chi^2, P(dBW), mask\nData format: 15.9f 10.6f 11.6f 7.1f 5.2f 5.1f 4x\nNumber of events: 219\n*** data ***\n10813.894135780  33.526691  -87.155466  5143.8  0.51  10.4 01d6\n10814.010797168  33.576237  -87.134562  8106.6  0.09  15.0 2156\n10814.171478723  33.637351  -87.109934  9051.5  2.17  13.1 11d6\n10814.301532186  33.552997  -87.141906  9619.2  1.36  25.4 05cc\n\nUse the FORMAT_THREE option for this data type\n\n");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'output_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("output_url");
    tt->descr = tdrpStrDup("Output MDV url, of form mdvp:://host.domain:[port]:dir/dir ");
    tt->help = tdrpStrDup("Data are written here.");
    tt->val_offset = (char *) &output_url - &_start_;
    tt->single_val.s = tdrpStrDup("mdvp:://localhost::./mdv/LMAltgGrid");
    tt++;
    
    // Parameter 'InDir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("InDir");
    tt->descr = tdrpStrDup("Input directory.");
    tt->help = tdrpStrDup("Directory path for input data files.");
    tt->val_offset = (char *) &InDir - &_start_;
    tt->single_val.s = tdrpStrDup("./");
    tt++;
    
    // Parameter 'fileExtension'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("fileExtension");
    tt->descr = tdrpStrDup("Input file extension.");
    tt->help = tdrpStrDup("If string is NULL, all extensions are valid.");
    tt->val_offset = (char *) &fileExtension - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'max_realtime_valid_age'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("max_realtime_valid_age");
    tt->descr = tdrpStrDup("Max age of input data");
    tt->help = tdrpStrDup("For realtime only - max age of input data for it to be valid");
    tt->val_offset = (char *) &max_realtime_valid_age - &_start_;
    tt->single_val.i = 7200;
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DEBUGGING AND PROCESS CONTROL");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed appropriately");
    tt->val_offset = (char *) &debug - &_start_;
    tt->single_val.b = pFALSE;
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
    
    // Parameter 'mode'
    // ctype is '_op_mode'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("mode");
    tt->descr = tdrpStrDup("Operation mode");
    tt->help = tdrpStrDup("In realtime mode, the conversion is performed for each input file as it becomes available. In archive mode, the file list is obtained from the command line. In TIME_INTERVAL mode, a list of files is gathered between start and end times.");
    tt->val_offset = (char *) &mode - &_start_;
    tt->enum_def.name = tdrpStrDup("op_mode");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("ARCHIVE");
      tt->enum_def.fields[0].val = ARCHIVE;
      tt->enum_def.fields[1].name = tdrpStrDup("REALTIME");
      tt->enum_def.fields[1].val = REALTIME;
      tt->enum_def.fields[2].name = tdrpStrDup("TIME_INTERVAL");
      tt->enum_def.fields[2].val = TIME_INTERVAL;
    tt->single_val.e = REALTIME;
    tt++;
    
    // Parameter 'Expiry'
    // ctype is 'long'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = LONG_TYPE;
    tt->param_name = tdrpStrDup("Expiry");
    tt->descr = tdrpStrDup("How long the data are valid, seconds.");
    tt->help = tdrpStrDup("Depends on input frequency.");
    tt->val_offset = (char *) &Expiry - &_start_;
    tt->single_val.l = 600;
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("Options to select a subregion to ingest (the whole thing may\nbe a pretty big database). The limits on altitude mat allow you to\neffectively select cloud-to-cloud ltg.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'minLat'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("minLat");
    tt->descr = tdrpStrDup("Minimum latitude to accept, decimal degrees.");
    tt->help = tdrpStrDup("Set to define the ingest region.");
    tt->val_offset = (char *) &minLat - &_start_;
    tt->single_val.d = -90;
    tt++;
    
    // Parameter 'maxLat'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("maxLat");
    tt->descr = tdrpStrDup("Maximum latitude to accept, decimal degrees.");
    tt->help = tdrpStrDup("Set to define the ingest region.");
    tt->val_offset = (char *) &maxLat - &_start_;
    tt->single_val.d = 90;
    tt++;
    
    // Parameter 'minLon'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("minLon");
    tt->descr = tdrpStrDup("Minimum longitude to accept, decimal degrees.");
    tt->help = tdrpStrDup("Set to define the ingest region.");
    tt->val_offset = (char *) &minLon - &_start_;
    tt->single_val.d = -180;
    tt++;
    
    // Parameter 'maxLon'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("maxLon");
    tt->descr = tdrpStrDup("Maximum longitude to accept, decimal degrees.");
    tt->help = tdrpStrDup("Set to define the ingest region.");
    tt->val_offset = (char *) &maxLon - &_start_;
    tt->single_val.d = 180;
    tt++;
    
    // Parameter 'minAlt'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("minAlt");
    tt->descr = tdrpStrDup("Minimum altitude to accept, m.");
    tt->help = tdrpStrDup("Set to define the ingest region.");
    tt->val_offset = (char *) &minAlt - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'maxAlt'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("maxAlt");
    tt->descr = tdrpStrDup("Maximum altitude to accept, m.");
    tt->help = tdrpStrDup("Set to define the ingest region. May also be used for\nquality control - occasionally data with clearly erroneously high\naltitudes come in.");
    tt->val_offset = (char *) &maxAlt - &_start_;
    tt->single_val.d = 20000;
    tt++;
    
    // Parameter 'applyClosenessCriteria'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("applyClosenessCriteria");
    tt->descr = tdrpStrDup("Set to TRUE to only accept strikes close to the\nlocation defined by the centralPoint parameter.");
    tt->help = tdrpStrDup("Cuts down on the number of ingested strikes, which\ncould otherwise be so large as to be unmanagable.");
    tt->val_offset = (char *) &applyClosenessCriteria - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'centralPoint'
    // ctype is '_centralPoint_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("centralPoint");
    tt->descr = tdrpStrDup("Defines the location and maximum distance to test for if\nwe are applying a closeness criteria test.");
    tt->help = tdrpStrDup("Relevant only if applyClosenessCriteria is TRUE.");
    tt->val_offset = (char *) &centralPoint - &_start_;
    tt->struct_def.name = tdrpStrDup("centralPoint_t");
    tt->struct_def.nfields = 3;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("double");
      tt->struct_def.fields[0].fname = tdrpStrDup("lat");
      tt->struct_def.fields[0].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &centralPoint.lat - (char *) &centralPoint;
      tt->struct_def.fields[1].ftype = tdrpStrDup("double");
      tt->struct_def.fields[1].fname = tdrpStrDup("lon");
      tt->struct_def.fields[1].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &centralPoint.lon - (char *) &centralPoint;
      tt->struct_def.fields[2].ftype = tdrpStrDup("double");
      tt->struct_def.fields[2].fname = tdrpStrDup("maxRangeKm");
      tt->struct_def.fields[2].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &centralPoint.maxRangeKm - (char *) &centralPoint;
    tt->n_struct_vals = 3;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].d = 39.3669;
      tt->struct_vals[1].d = -101.7;
      tt->struct_vals[2].d = 300;
    tt++;
    
    // Parameter 'maxChiSqrd'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("maxChiSqrd");
    tt->descr = tdrpStrDup("Maximum value for chi-square measure to accept an entry.");
    tt->help = tdrpStrDup("Each entry has such a measure associated with it.");
    tt->val_offset = (char *) &maxChiSqrd - &_start_;
    tt->single_val.d = 10;
    tt++;
    
    // Parameter 'minNumStations'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("minNumStations");
    tt->descr = tdrpStrDup("Minimum number of stations reporting to accept an entry.");
    tt->help = tdrpStrDup("Each entry has such a measure associated with it.");
    tt->val_offset = (char *) &minNumStations - &_start_;
    tt->single_val.i = 6;
    tt++;
    
    // Parameter 'minPower'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("minPower");
    tt->descr = tdrpStrDup("Minimum power.");
    tt->help = tdrpStrDup("Only used with FORMAT_THREE.");
    tt->val_offset = (char *) &minPower - &_start_;
    tt->single_val.d = 5;
    tt++;
    
    // Parameter 'outputInterval'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("outputInterval");
    tt->descr = tdrpStrDup("Data interval, seconds.");
    tt->help = tdrpStrDup("MDV files are produced every outputInterval.");
    tt->val_offset = (char *) &outputInterval - &_start_;
    tt->single_val.i = 120;
    tt++;
    
    // Parameter 'lookbackInterval'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("lookbackInterval");
    tt->descr = tdrpStrDup("Look back interval, seconds.");
    tt->help = tdrpStrDup("MDV files are produced every outputInterval, but they\nlook back by this interval (seconds) which should be\nequal to or (more likely) greater than dataInterval.");
    tt->val_offset = (char *) &lookbackInterval - &_start_;
    tt->single_val.i = 300;
    tt++;
    
    // Parameter 'timestamp'
    // ctype is '_timestamp_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("timestamp");
    tt->descr = tdrpStrDup("How to timestamp the data.");
    tt->help = tdrpStrDup("Controls if data are timestamped wit the start,\nmiddle or end of the time interval.");
    tt->val_offset = (char *) &timestamp - &_start_;
    tt->enum_def.name = tdrpStrDup("timestamp_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("TIMESTAMP_START");
      tt->enum_def.fields[0].val = TIMESTAMP_START;
      tt->enum_def.fields[1].name = tdrpStrDup("TIMESTAMP_MIDDLE");
      tt->enum_def.fields[1].val = TIMESTAMP_MIDDLE;
      tt->enum_def.fields[2].name = tdrpStrDup("TIMESTAMP_END");
      tt->enum_def.fields[2].val = TIMESTAMP_END;
    tt->single_val.e = TIMESTAMP_END;
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("OUTPUT GRID DEFINITION");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'output_projection'
    // ctype is '_output_projection_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("output_projection");
    tt->descr = tdrpStrDup("Projection of output grid.");
    tt->help = tdrpStrDup("FLAT - (x,y) Cartesian data in km from a given origin.\nLATLON - lat/lon grid with constant grid spacing.\n");
    tt->val_offset = (char *) &output_projection - &_start_;
    tt->enum_def.name = tdrpStrDup("output_projection_t");
    tt->enum_def.nfields = 2;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("OUTPUT_PROJ_FLAT");
      tt->enum_def.fields[0].val = OUTPUT_PROJ_FLAT;
      tt->enum_def.fields[1].name = tdrpStrDup("OUTPUT_PROJ_LATLON");
      tt->enum_def.fields[1].val = OUTPUT_PROJ_LATLON;
    tt->single_val.e = OUTPUT_PROJ_FLAT;
    tt++;
    
    // Parameter 'output_origin'
    // ctype is '_output_origin_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("output_origin");
    tt->descr = tdrpStrDup("Origin of output grid.");
    tt->help = tdrpStrDup("Used with OUTPUT_PROJ_FLAT and OUTPUT_PROJ_LAMBERT.");
    tt->val_offset = (char *) &output_origin - &_start_;
    tt->struct_def.name = tdrpStrDup("output_origin_t");
    tt->struct_def.nfields = 2;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("double");
      tt->struct_def.fields[0].fname = tdrpStrDup("lat");
      tt->struct_def.fields[0].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &output_origin.lat - (char *) &output_origin;
      tt->struct_def.fields[1].ftype = tdrpStrDup("double");
      tt->struct_def.fields[1].fname = tdrpStrDup("lon");
      tt->struct_def.fields[1].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &output_origin.lon - (char *) &output_origin;
    tt->n_struct_vals = 2;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].d = 40;
      tt->struct_vals[1].d = -104;
    tt++;
    
    // Parameter 'output_grid'
    // ctype is '_grid_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("output_grid");
    tt->descr = tdrpStrDup("Output grid parameters.");
    tt->help = tdrpStrDup("The grid params for the output grid.");
    tt->val_offset = (char *) &output_grid - &_start_;
    tt->struct_def.name = tdrpStrDup("grid_t");
    tt->struct_def.nfields = 9;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("long");
      tt->struct_def.fields[0].fname = tdrpStrDup("nx");
      tt->struct_def.fields[0].ptype = LONG_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &output_grid.nx - (char *) &output_grid;
      tt->struct_def.fields[1].ftype = tdrpStrDup("long");
      tt->struct_def.fields[1].fname = tdrpStrDup("ny");
      tt->struct_def.fields[1].ptype = LONG_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &output_grid.ny - (char *) &output_grid;
      tt->struct_def.fields[2].ftype = tdrpStrDup("long");
      tt->struct_def.fields[2].fname = tdrpStrDup("nz");
      tt->struct_def.fields[2].ptype = LONG_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &output_grid.nz - (char *) &output_grid;
      tt->struct_def.fields[3].ftype = tdrpStrDup("double");
      tt->struct_def.fields[3].fname = tdrpStrDup("minx");
      tt->struct_def.fields[3].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[3].rel_offset = 
        (char *) &output_grid.minx - (char *) &output_grid;
      tt->struct_def.fields[4].ftype = tdrpStrDup("double");
      tt->struct_def.fields[4].fname = tdrpStrDup("miny");
      tt->struct_def.fields[4].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[4].rel_offset = 
        (char *) &output_grid.miny - (char *) &output_grid;
      tt->struct_def.fields[5].ftype = tdrpStrDup("double");
      tt->struct_def.fields[5].fname = tdrpStrDup("minz");
      tt->struct_def.fields[5].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[5].rel_offset = 
        (char *) &output_grid.minz - (char *) &output_grid;
      tt->struct_def.fields[6].ftype = tdrpStrDup("double");
      tt->struct_def.fields[6].fname = tdrpStrDup("dx");
      tt->struct_def.fields[6].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[6].rel_offset = 
        (char *) &output_grid.dx - (char *) &output_grid;
      tt->struct_def.fields[7].ftype = tdrpStrDup("double");
      tt->struct_def.fields[7].fname = tdrpStrDup("dy");
      tt->struct_def.fields[7].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[7].rel_offset = 
        (char *) &output_grid.dy - (char *) &output_grid;
      tt->struct_def.fields[8].ftype = tdrpStrDup("double");
      tt->struct_def.fields[8].fname = tdrpStrDup("dz");
      tt->struct_def.fields[8].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[8].rel_offset = 
        (char *) &output_grid.dz - (char *) &output_grid;
    tt->n_struct_vals = 9;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].l = 400;
      tt->struct_vals[1].l = 400;
      tt->struct_vals[2].l = 15;
      tt->struct_vals[3].d = -199.5;
      tt->struct_vals[4].d = -199.5;
      tt->struct_vals[5].d = 0.5;
      tt->struct_vals[6].d = 1;
      tt->struct_vals[7].d = 1;
      tt->struct_vals[8].d = 1;
    tt++;
    
    // Parameter 'takeZeroAsBadValue'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("takeZeroAsBadValue");
    tt->descr = tdrpStrDup("Option to take 0 as the bad value in MDV.");
    tt->help = tdrpStrDup("Generally useful for display purposes.");
    tt->val_offset = (char *) &takeZeroAsBadValue - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'format'
    // ctype is '_in_format'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("format");
    tt->descr = tdrpStrDup("Input data file format.");
    tt->help = tdrpStrDup("See comments at top of param file.");
    tt->val_offset = (char *) &format - &_start_;
    tt->enum_def.name = tdrpStrDup("in_format");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("FORMAT_ONE");
      tt->enum_def.fields[0].val = FORMAT_ONE;
      tt->enum_def.fields[1].name = tdrpStrDup("FORMAT_TWO");
      tt->enum_def.fields[1].val = FORMAT_TWO;
      tt->enum_def.fields[2].name = tdrpStrDup("FORMAT_THREE");
      tt->enum_def.fields[2].val = FORMAT_THREE;
    tt->single_val.e = FORMAT_ONE;
    tt++;
    
    // Parameter 'ldata_available'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("ldata_available");
    tt->descr = tdrpStrDup("Flag to indicate availability of latest data info files");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &ldata_available - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }

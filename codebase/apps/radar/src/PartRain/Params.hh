// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research(UCAR)
// ** National Center for Atmospheric Research(NCAR)
// ** Boulder, Colorado, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////
// Params.hh
//
// TDRP header file for 'Params' class.
//
// Code for program PartRain
//
// This header file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.hh
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @class Params
 *
 * @author automatically generated
 *
 */

#ifndef Params_hh
#define Params_hh

using namespace std;

#include <tdrp/tdrp.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>

// Class definition

class Params {

public:

  // enum typedefs

  typedef enum {
    DEBUG_OFF = 0,
    DEBUG_NORM = 1,
    DEBUG_VERBOSE = 2,
    DEBUG_EXTRA = 3
  } debug_t;

  typedef enum {
    FIR_LEN_125 = 0,
    FIR_LEN_30 = 1,
    FIR_LEN_20 = 2,
    FIR_LEN_10 = 3
  } fir_filter_len_t;

  typedef enum {
    SNR = 0,
    DBZ = 1,
    VEL = 2,
    WIDTH = 3,
    ZDR = 4,
    LDR = 5,
    PHIDP = 6,
    RHOHV = 7,
    KDP = 8,
    DBZ_FOR_KDP = 9,
    ZDR_FOR_KDP = 10,
    RHOHV_FOR_KDP = 11,
    SNR_FOR_KDP = 12,
    PHIDP_FOR_KDP = 13,
    PHIDP_FILT_FOR_KDP = 14,
    SDPHIDP_FOR_KDP = 15,
    SDZDR_FOR_KDP = 16,
    PRECIP_RATE_ZH = 17,
    PRECIP_RATE_ZH_SNOW = 18,
    PRECIP_RATE_Z_ZDR = 19,
    PRECIP_RATE_KDP = 20,
    PRECIP_RATE_KDP_ZDR = 21,
    PRECIP_RATE_HYBRID = 22,
    PRECIP_RATE_PID = 23,
    PRECIP_RATE_HIDRO = 24,
    PRECIP_RATE_BRINGI = 25,
    DBZ_FOR_RATE = 26,
    ZDR_FOR_RATE = 27,
    KDP_FOR_RATE = 28,
    PARTICLE_ID = 29,
    PID_INTEREST = 30,
    PARTICLE_ID2 = 31,
    PID_INTEREST2 = 32,
    PID_CONFIDENCE = 33,
    DBZ_FOR_PID = 34,
    ZDR_FOR_PID = 35,
    LDR_FOR_PID = 36,
    PHIDP_FOR_PID = 37,
    RHOHV_FOR_PID = 38,
    KDP_FOR_PID = 39,
    SDZDR_FOR_PID = 40,
    SDPHIDP_FOR_PID = 41,
    TEMP_FOR_PID = 42
  } output_field_id_t;

  // struct typedefs

  typedef struct {
    double min_val;
    double max_val;
  } data_range_t;

  typedef struct {
    output_field_id_t id;
    char* name;
    char* units;
    double scale;
    double bias;
  } output_field_t;

  ///////////////////////////
  // Member functions
  //

  ////////////////////////////////////////////
  // Default constructor
  //

  Params ();

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params (const Params&);

  ////////////////////////////////////////////
  // Destructor
  //

  ~Params ();

  ////////////////////////////////////////////
  // Assignment
  //

  void operator=(const Params&);

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

  int loadFromArgs(int argc, char **argv,
                   char **override_list,
                   char **params_path_p,
                   bool defer_exit = false);

  bool exitDeferred() { return (_exitDeferred); }

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

  int loadApplyArgs(const char *params_path,
                    int argc, char **argv,
                    char **override_list,
                    bool defer_exit = false);

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  static bool isArgValid(const char *arg);

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

  int load(const char *param_file_path,
           char **override_list,
           int expand_env, int debug);

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

  int loadFromBuf(const char *param_source_str,
                  char **override_list,
                  const char *inbuf, int inlen,
                  int start_line_num,
                  int expand_env, int debug);

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int loadDefaults(int expand_env);

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void sync() const;

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

  void print(FILE *out, tdrp_print_mode_t mode = PRINT_NORM);

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int checkAllSet(FILE *out);

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int checkIsSet(const char *param_name);

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

  int arrayRealloc(const char *param_name,
                   int new_array_n);

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

  int array2DRealloc(const char *param_name,
                     int new_array_n1,
                     int new_array_n2);

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void freeAll(void);

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  static void usage(ostream &out);

  ///////////////////////////
  // Data Members
  //

  char _start_; // start of data region
                // needed for zeroing out data
                // and computing offsets

  debug_t debug;

  char* instance;

  char* input_fmq_url;

  tdrp_bool_t seek_to_start_of_input;

  tdrp_bool_t override_wavelength;

  double wavelength_cm;

  char* dsr_name_SNR;

  tdrp_bool_t SNR_available;

  double noise_dbz_at_100km;

  char* dsr_name_DBZ;

  char* dsr_name_VEL;

  char* dsr_name_WIDTH;

  char* dsr_name_ZDR;

  char* dsr_name_PHIDP;

  char* dsr_name_RHOHV;

  tdrp_bool_t KDP_available;

  char* dsr_name_KDP;

  char* dsr_name_LDR;

  tdrp_bool_t replace_missing_LDR;

  double LDR_replacement_value;

  tdrp_bool_t apply_median_filter_to_DBZ;

  int DBZ_median_filter_len;

  tdrp_bool_t apply_median_filter_to_ZDR;

  int ZDR_median_filter_len;

  tdrp_bool_t apply_median_filter_to_LDR;

  int LDR_median_filter_len;

  tdrp_bool_t apply_median_filter_to_RHOHV;

  int RHOHV_median_filter_len;

  int ngates_for_sdev;

  tdrp_bool_t apply_median_filter_to_PHIDP;

  int PHIDP_median_filter_len;

  fir_filter_len_t KDP_fir_filter_len;

  double KDP_phidp_difference_threshold;

  double KDP_phidp_sdev_threshold;

  double KDP_zdr_sdev_threshold;

  double KDP_rhohv_threshold;

  tdrp_bool_t apply_median_filter_to_PID;

  int PID_median_filter_len;

  double min_DBZ_for_KDP_rates;

  double min_valid_rate;

  double PRECIP_snr_threshold;

  double zh_aa;

  double zh_bb;

  double zh_aa_snow;

  double zh_bb_snow;

  double zzdr_aa;

  double zzdr_bb;

  double zzdr_cc;

  double kdp_aa;

  double kdp_bb;

  double kdpzdr_aa;

  double kdpzdr_bb;

  double kdpzdr_cc;

  double hybrid_dbz_threshold;

  double hybrid_kdp_threshold;

  double hybrid_zdr_threshold;

  double hidro_dbz_threshold;

  double hidro_kdp_threshold;

  double hidro_zdr_threshold;

  double bringi_dbz_threshold;

  double bringi_kdp_threshold;

  double bringi_zdr_threshold;

  char* pid_thresholds_file_path;

  double PID_snr_threshold;

  double PID_snr_upper_threshold;

  double PID_min_valid_interest;

  tdrp_bool_t override_standard_pseudo_earth_radius;

  double pseudo_earth_radius_ratio;

  tdrp_bool_t use_soundings_from_spdb;

  char* sounding_spdb_url;

  int sounding_search_time_margin_secs;

  data_range_t sounding_required_pressure_range_hpa;

  data_range_t sounding_required_height_range_m;

  tdrp_bool_t sounding_check_pressure_monotonically_decreasing;

  char* output_fmq_url;

  int output_fmq_size;

  int output_fmq_nslots;

  tdrp_bool_t output_fmq_compress;

  tdrp_bool_t write_blocking;

  output_field_t *_output_fields;
  int output_fields_n;

  tdrp_bool_t output_particle_interest_fields;

  int data_mapper_report_interval;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[107];

  const char *_className;

  bool _exitDeferred;

};

#endif


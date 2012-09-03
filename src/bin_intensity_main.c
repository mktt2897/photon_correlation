#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>

#include "files.h"
#include "modes.h"
#include "error.h"
#include "strings.h"
#include "bin_intensity_t2.h"
#include "bin_intensity_t3.h"
#include "histogram_gn.h"
#include "options.h"

int main(int argc, char *argv[]) {
	int result = 0;

	options_t options;

	FILE *in_stream = NULL;
	FILE *out_stream = NULL;

	program_options_t program_options = {
		13,
"This program calculates the intensities in each bin of a correlation, as \n"
"required for exact normalization of the correlation. The input is either t2\n"
"or t3 data, and the output roughly follows that of the histogram:\n"
"     t1-t0 lower, t1-t0 upper, channel 0 counts, channel 1 counts\n"
"\n"
"For the best results, pass the same arguments for time and pulse bin\n"
"definitions as for histogram.\n",
		{OPT_HELP, OPT_VERBOSE, OPT_VERSION,
			OPT_FILE_IN, OPT_FILE_OUT,
			OPT_MODE, OPT_CHANNELS, OPT_ORDER, 
			OPT_QUEUE_SIZE,
			OPT_TIME, OPT_PULSE,
			OPT_TIME_SCALE, OPT_PULSE_SCALE}};

	result = parse_options(argc, argv, &options, &program_options);

	result += open_streams(&in_stream, options.in_filename,
			&out_stream, options.out_filename);

	if ( ! result ) {
		result = bin_intensity_dispatch(in_stream, out_stream, &options);
	}

	free_options(&options);
	free_streams(in_stream, out_stream);
	
	return(parse_result(result));
}

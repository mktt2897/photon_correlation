#include "correlate.h"
#include "error.h"
#include "files.h"
#include "modes.h"

int correlate_dispatch(FILE *in_stream, FILE *out_stream, options_t *options) {
	int result;

	debug("Checking the mode.\n");
	if ( options->mode == MODE_T2 ) {
		debug("Mode t2.\n");
		if ( options->start_stop ) {
			result = correlate_t2_start_stop(in_stream, out_stream,
					options);
		} else {
			result = correlate_t2(in_stream, out_stream, options);
		}
	} else if ( options->mode == MODE_T3 ) {
		debug("Mode t3.\n");
		result = correlate_t3(in_stream, out_stream, options);
	}  else {
		result = -1;
	}

	return(result);
}

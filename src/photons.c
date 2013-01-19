#include "photons.h"
#include "photon.h"
#include "t2.h"
#include "t2_void.h"
#include "t3.h"
#include "t3_void.h"
#include "modes.h"
#include "error.h"

int photons_dispatch(FILE *stream_in, FILE *stream_out, options_t *options) {
	if ( options->mode == MODE_T2 ) {
		if ( options->use_void ) {
			return(t2v_echo(stream_in, stream_out, 
					options->binary_in, options->binary_out));
		} else {
			return(t2_echo(stream_in, stream_out, 
					options->binary_in, options->binary_out));
		} 
	} else if ( options->mode == MODE_T3 ) {
		if ( options->use_void ) {
			return(t3v_echo(stream_in, stream_out,
					options->binary_in, options->binary_out));
		} else {
			return(t3_echo(stream_in, stream_out,
					options->binary_in, options->binary_out));
		} 
	} else { 
		error("Unsupported echo mode: %d\n", options->mode);
		return(PC_ERROR_MODE);
	}
}
 
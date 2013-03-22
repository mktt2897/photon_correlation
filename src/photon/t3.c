#include "t3.h"
#include "../error.h"

/* 
 * Functions to implement t3 photon read/write.
 */
int t3_fscanf(FILE *stream_in, t3_t *t3) {
	int n_read = fscanf(stream_in,
			"%u,%lld,%lld\n",
			&(t3->channel),
			&(t3->pulse),
			&(t3->time));

	if ( n_read == 3 ) {
		return(PC_SUCCESS);
	} else {
		if ( feof(stream_in) ) { 
			return(EOF);
		} else {
			return(PC_ERROR_IO);
		}
	} 
}

int t3v_fscanf(FILE *stream_in, void *t3) {
	return(t3_fscanf(stream_in, t3));
}

int t3_fprintf(FILE *stream_out, t3_t const *t3) {
	fprintf(stream_out,
			"%u,%lld,%lld\n",
			t3->channel,
			t3->pulse,
			t3->time);

	return( ! ferror(stream_out) ? PC_SUCCESS : PC_ERROR_IO );
}

int t3v_fprintf(FILE *stream_in, void const *t3) {
	return(t3_fprintf(stream_in, t3));
}

int t3v_compare(void const *a, void const *b) {
	/* Comparator to be used with standard sorting algorithms (qsort) to sort
	 * t3 photons. 
     */
	/* The comparison must be done explicitly to avoid issues associated with
	 * casting int64_t to int. If we just return the difference, any value
	 * greater than max_int would cause problems.
	 */
	/* The comparator needed for sorting a list of t3 photons. Follows the 
     * standard of qsort (-1 sorted, 0 equal, 1 unsorted)
	 */
	int64_t difference;

	if ( ((t3_t *)a)->pulse == ((t3_t *)b)->pulse ) {
		difference = ((t3_t *)a)->time - ((t3_t *)b)->time;
	} else {
		difference = ((t3_t *)a)->pulse - ((t3_t *)b)->pulse;
	}

	return( difference > 0 );
}

int t3_echo(FILE *stream_in, FILE *stream_out) {
	t3_t t3;
	t3_next_t next = t3_fscanf;
	t3_print_t print = t3_fprintf;

	while ( next(stream_in, &t3) == PC_SUCCESS ) {
		print(stream_out, &t3);
	}

	return(PC_SUCCESS);
}

long long t3v_window_dimension(void const *t3) {
	return(((t3_t *)t3)->pulse);
}

long long t3v_channel_dimension(void const *t3) {
	return(((t3_t *)t3)->channel);
}
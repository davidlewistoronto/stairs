#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <stdlib.h>

bool verbose = true;

int calc_orders (int nlevels, int *width, int n_placed, int total_pieces, int *order)
{   int ilev;
	int total;
	int i;
	int max_at_level;
	int t_width;

	if (n_placed == total_pieces) {
		total = 1;
		if (verbose) {
			for (i = 0; i < total_pieces; i++) {
				printf (" %d", order [i]);
			}
			printf ("\n");
		}

	} else {
		total = 0;
		for (ilev = 0; ilev < nlevels; ilev++) {
			if (width [ilev] < nlevels - ilev && (ilev == 0 || width [ilev] < width [ilev - 1])) {
				width [ilev]++;
				order [n_placed] = ilev;
				total += calc_orders (nlevels, width, n_placed + 1, total_pieces, order);
				width [ilev]--;

			}
		}
	}
    return total;
}

int _tmain(int argc, _TCHAR* argv[]) 
{   int nlevels;
	int *width;
	int *order;
	int total_pieces;
	int norders;
    int i;

	if (argv [1] [0] == '-')
	{	verbose = false;
		argv++;
	}
	sscanf (argv [1], "%d", & nlevels);
	width = (int *) malloc (nlevels * sizeof (int));
	total_pieces = (nlevels * (nlevels + 1)) / 2;
    order = (int *) malloc (total_pieces * sizeof (int));
	for (i = 0; i < nlevels; i++) {
		width [i] = 0;
	}
	norders = calc_orders (nlevels, width, 0, total_pieces, order);
    printf ("%d\n", norders);

	return 0;
}

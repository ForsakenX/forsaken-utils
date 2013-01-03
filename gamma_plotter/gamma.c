#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char uchar_t;

uchar_t table[256];

void build_table( double gamma )
{
	double k;
	int i;

	k = 255.0/pow(255.0, 1.0/gamma);
	
	for (i = 0; i <= 255; i++)
	{
		table[i] = (uchar_t)(k*(pow((double)i, 1.0/gamma)));
		if( i && !table[i] )
			table[i] = 1;
	}
}

void dump_table( void )
{
	int i = 0;
	for ( i = 0; i <= 255; i++ )
		printf("%d\n",table[i]);
}

int main (int argc, char** argv)
{
	//double factor = ((double) atoi(argv[1])) / 100.0f;
	//build_table( factor );
	build_table( (double) atoi(argv[1]) );
	dump_table();
}


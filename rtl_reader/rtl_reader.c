#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32;
typedef unsigned short uint16;

int parse( char * file );
int parse_light( FILE * fp );

#define get( V, S ) \
	if ( fread( &(V), sizeof( V ), 1, fp ) != 1 ) \
	{\
		printf("Error reading " #V " from file\n");\
		return 1;\
	}\
	else\
	{\
		printf(S"\n",V);\
	}

#define gett( S, T ) \
        if ( fread( &(s), sizeof( uint16 ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S": '%s',\n",T[s]);\
        }

#define getf( S ) \
        if ( fread( &(f), sizeof( float ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S": %f,\n",f);\
        }

#define gets( S ) \
        if ( fread( &(s), sizeof( uint16 ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S": %d,\n",s);\
        }

#define tputs( S ) \
	tab(tabs);\
	printf(S"\n");


int main (int argc, char** argv) 
{
	return parse( argv[1] );
}

void tab( int count )
{
	int x;
	for( x = 0; x < count; x++ )
		printf("\t");
}

int parse( char * file )
{
	FILE 	* fp;

	int	j;
	char	MagicNumber[4];
	uint32	VersionNumber;
	uint16 	number_of_lights;

	fp = fopen( file, "rb" );
	if(!fp)
	{
		printf("failed to open file!\n");
		return 1;
	}

	puts("--[[");
	printf("parsed file: %s\n", file);
	get( MagicNumber, " magic number = %.4s" );
	get( VersionNumber, " version number = %d" );
	get( number_of_lights, " there are %d lights in the file" );
	puts("--]]");

	for ( j = 0; j < number_of_lights; j++ )
	{
		puts("");
		printf("--[[ light %d ]]\n", j );
		puts("{");
		parse_light( fp );
		puts("}");
	}

	return 0;
}

typedef enum
{
	LIGHT_FIXED,
	LIGHT_PULSING,
	LIGHT_FLICKERING,
	LIGHT_SPOT,
} LIGHTTYPE;

typedef enum
{
	GENTYPE_Initialised,	// Initialised immediatly
	GENTYPE_Time,		// Initialised after time
	GENTYPE_Trigger,	// Initialised by trigger
} GENTYPE;

char * light_types[] =
{
	"fixed",
	"pulsing",
	"flickering",
	"spot"
};

char * generation_types[] =
{
	"initialized",
	"timed",
	"triggered"
};

char * pulse_types[] =
{
	"blink",
	"ramp",
	"halfwave",
	"wave",
};

int parse_light( FILE * fp )
{
	uint16	s, light_type;
	float	f;
	int	tabs = 1;

	gett("type", light_types);
	light_type = s;

	gets("group");
	getf("x");
	getf("y");
	getf("z");
	getf("range");
	getf("r");
	getf("g");
	getf("b");

	tputs("generation: {");
	tabs++;
	gett("type", generation_types);
	getf("delay");
	tabs--;
	tputs("}");

	tab(tabs);
	printf("%s: {\n", light_types[light_type] );
	tabs++;

	switch ( light_type )
	{
	case LIGHT_FIXED:
		
			gett("on_type", pulse_types);
			gett("off_type", pulse_types);
			gets("on_time");
			gets("off_time");
	
		break;
	case LIGHT_PULSING:
		
			gett("type", pulse_types);
			getf("on_time");
			getf("stay_on_time");
			getf("off_time");
			getf("stay_off_time");
		
		break;
	case_LIGHT_FLICKERING:
		
			getf("stay_on_chance");
			getf("stay_off_chance");
			getf("stay_on_time");
			getf("stay_off_time");
		
		break;
	case_LIGHT_SPOT:
		
			tputs("dir: {");
			tabs++;
			getf("x");
			getf("y");
			getf("z");
			tabs--;
			tputs("}");

			tputs("up: {");
			tabs++;
			getf("x");
			getf("y");
			getf("z");
			tabs--;
			tputs("}");

			getf("cone");
			getf("rotation_period");
		
		break;
	}

	tabs--;
	tputs("}");

	return;
}

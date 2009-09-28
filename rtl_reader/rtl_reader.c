#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32;
typedef unsigned short uint16;

int parse( char * file );
int parse_light( FILE * fp );
void tab( int count );

int tabs = 0;

#define GET( V, S ) \
	if ( fread( &(V), sizeof( V ), 1, fp ) != 1 ) \
	{\
		printf("Error reading " #V " from file\n");\
		return 1;\
	}\
	else\
	{\
		printf(S"\n",V);\
	}

#define GETT( S, T ) \
        if ( fread( &(s), sizeof( uint16 ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S" = '%s',\n",T[s]);\
        }

#define GETF( S ) \
        if ( fread( &(f), sizeof( float ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S" = %g,\n",f);\
        }

#define GETS( S ) \
        if ( fread( &(s), sizeof( uint16 ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S" = %d,\n",s);\
        }

#define GETB( S ) \
        if ( fread( &(b), sizeof( uint32 ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " S " from file\n");\
                return 1;\
        }\
        else\
        {\
		tab(tabs);\
                printf(S" = %d,\n",b);\
        }

#define OPEN( S ) \
	tab(tabs);\
	if(S) puts(#S" = {");\
	else  puts("{");\
	tabs++;

#define CLOSE() \
	tabs--;\
	tab(tabs);\
	puts("},");

#define TPUTS( S ) \
	tab(tabs);\
	printf(S"\n");

int main (int argc, char** argv) 
{
	if(argc < 2)
	{
		puts("Error: You must pass a file to parse as the first argument!");
		exit(1);
	}
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
	int	j, number_of_lights;
	char	MagicNumber[4];
	uint16  s;
	uint32 	b;

	fp = fopen( file, "rb" );
	if(!fp)
	{
		printf("failed to OPEN file!\n");
		return 1;
	}

	puts("");
	puts("--[[ lua table format ]]");
	puts("");

	printf("file = '%s',\n", file);
	printf("description = 'real time lights',\n");

	GET( MagicNumber, "magic_number = '%.4s'," );
	GETB("version_number");
	GETS("total_lights");
	number_of_lights = s;

	for ( j = 0; j < number_of_lights; j++ )
	{
		printf("\n--[[ light %d ]]\n", j );
		OPEN(NULL);
		parse_light( fp );
		CLOSE();
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

	GETT("type", light_types);
	light_type = s;

	GETS("group");
	GETF("x");
	GETF("y");
	GETF("z");
	GETF("range");
	GETF("r");
	GETF("g");
	GETF("b");

	OPEN("generation");
	GETT("type", generation_types);
	GETF("delay");
	CLOSE();

	OPEN(light_types[light_type]);

	switch ( light_type )
	{
	case LIGHT_FIXED:
		
			GETT("on_type", pulse_types);
			GETT("off_type", pulse_types);
			GETS("on_time");
			GETS("off_time");
	
		break;
	case LIGHT_PULSING:
		
			GETT("type", pulse_types);
			GETF("on_time");
			GETF("stay_on_time");
			GETF("off_time");
			GETF("stay_off_time");
		
		break;
	case LIGHT_FLICKERING:
		
			GETF("stay_on_chance");
			GETF("stay_off_chance");
			GETF("stay_on_time");
			GETF("stay_off_time");
		
		break;
	case LIGHT_SPOT:
	
			OPEN("dir");	
			GETF("x");
			GETF("y");
			GETF("z");
			CLOSE();

			OPEN("up");
			GETF("x");
			GETF("y");
			GETF("z");
			CLOSE();

			GETF("cone");
			GETF("rotation_period");
		
		break;
	}

	CLOSE();

	return;
}

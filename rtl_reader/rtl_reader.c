#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32;
typedef unsigned short uint16;

int parse( FILE * fp );
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

#define gett( V, S, T ) \
        if ( fread( &(V), sizeof( V ), 1, fp ) != 1 ) \
        {\
                printf("Error reading " #V " from file\n");\
                return 1;\
        }\
        else\
        {\
                printf(S"\n",T[V]);\
        }

int main (int argc, char** argv) 
{
	FILE * fp;
	printf("parsing file: %s\n", argv[1]);
	fp = fopen( argv[1], "rb" );
	if(!fp)
	{
		printf("failed to open file!\n");
		return 1;
	}
	return parse( fp );
}

int parse( FILE * fp )
{
	int	j;
	char	MagicNumber[4];
	uint32	VersionNumber;
	uint16 	number_of_lights;

	get( MagicNumber, "magic number = %.4s" );
	get( VersionNumber, "version number = %d" );
	get( number_of_lights, "there are %d lights in the file" );

	for ( j = 0; j < number_of_lights; j++ )
	{
		printf( "\nparsing light %d\n", j );
		parse_light( fp );
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
	uint16	light_type, type, group, generation_type;
	float	x,y,z, range, r,g,b, delay, time, now_time;

	gett( light_type, "type: %s", light_types );
	get( group, "group %d" );
	get( x, "x %f" );
	get( y, "y %f" );
	get( z, "z %f" );
	get( range, "range %f" );
	get( r, "r %f" );
	get( g, "g %f" );
	get( b, "b %f" );
	gett( generation_type, "generation type %s", generation_types );
	get( delay, "generation delay %f" );

	switch ( light_type )
	{
	case LIGHT_FIXED:
		{
			float time;
			gett( type, "fixed on type %s", pulse_types );
			gett( type, "fixed off type %s", pulse_types );
			get( time, "fixed on time" );
			get( time, "fixed off time" );
		}
		break;
	case LIGHT_PULSING:
		{
			float on_time, stay_on_time, off_time, stay_off_time;
			gett( type, "pulsing type %s", pulse_types );
			get( on_time, "pulsing on time %f" ); 
			get( stay_on_time, "pulsing stay on time %f" ); 
			get( off_time, "pulsing off time %f" ); 
			get( stay_off_time, "pulsing stay off time %f" ); 
		}
		break;
	case LIGHT_FLICKERING:
		{
			float stay_on_chance, stay_off_chance, stay_on_time, stay_off_time;
			get( stay_on_chance, "flickering stay_on_chance %f" );
			get( stay_off_chance, "flickering stay_off_chance %f" );
			get( stay_on_time, "flickering stay_on_time %f" );
			get( stay_off_time, "flickering stay_off_time %f" );
		}
		break;
	case LIGHT_SPOT:
		{
			float x,y,z, cone, rotation_period;
			get( x, "spot dir.x %f" );
			get( y, "spot dir.y %f" );
			get( z, "spot dir.z %f" );
			get( x, "spot up.x %f" );
			get( y, "spot up.y %f" );
			get( z, "spot up.z %f" );
			get( cone, "spot cone %f" );
			get( rotation_period, "spot rotation period %f");
		}
		break;
	}

	return;
}

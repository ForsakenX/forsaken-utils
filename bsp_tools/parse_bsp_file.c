#include <stdlib.h>
#include <stdio.h>

#define BSP_VERSION_NUMBER      (1)
#define MAGIC_NUMBER    0x584A5250 //1481265744

// Represents a vector
typedef struct VECTOR {
    float x;
    float y;
    float z;
}VECTOR;

// This represents a single bsp node in binary .BSP file.
// You can use this to cast the binary data in a .BSP file.
typedef struct BSP_RAWNODE
{
        VECTOR  Normal;
        float   Offset;
        int     Front;
        int     Back;
        int     Colour;
}BSP_RAWNODE;

// parse the bsp file

int parse_bsp ( char * filename )
{
  FILE * fp;
  u_int32_t MagicNumber, VersionNumber;
  int16_t	NumGroups, NumNodes = 0;
  int GroupCount, NodeCount = 0;

  // open the file

  fp = fopen( filename, "rb" );
  if( fp == NULL )
	{
    printf("Could not open file!\n");
    return 1;
  }

  // get the magic number

  fread( &MagicNumber, sizeof( u_int32_t ), 1, fp );
  printf("magic number\t = %d\n",MagicNumber);
  if( MagicNumber != MAGIC_NUMBER )
	{
    printf("Notice: Magic number not correctly set...\n");
  }

  // get the bsp version number

  fread( &VersionNumber, sizeof( u_int32_t ), 1, fp );
  printf("pic version\t = %d\n",VersionNumber);
  if( VersionNumber != BSP_VERSION_NUMBER )
	{
    printf("Notice: Pic Version Number not correctly set...\n");
  }
  
  // get number of groups

  fread( &NumGroups, sizeof( int16_t ), 1, fp );
  printf("Number of Groups\t = %i\n",NumGroups);

  // for each group

  for( GroupCount = 0; GroupCount < NumGroups; GroupCount++ )
	{
    fread( &NumNodes, sizeof( int16_t ), 1, fp );

    printf("group: %i, nodes: %i\n",
			GroupCount, NumNodes);

    // for each node
    
    for( NodeCount = 0; NodeCount < NumNodes; NodeCount++ )
		{
      BSP_RAWNODE Node;
      VECTOR vector;

      fread( &Node, sizeof( BSP_RAWNODE ), 1, fp );
      vector = (VECTOR) Node.Normal;

      printf(
				"Node: %i, "
				"x: %f, y: %f, z: %f, "
				"offset: %f, front: %i, back: %i, "
				"color: %i"
				"\n",
				NodeCount,
				vector.x, vector.y, vector.z,
        Node.Offset, Node.Front, Node.Back,
				Node.Colour
			);

    }

	}
  fclose( fp );
  return 0;
}

int main( int argc , char *argv[] )
{
  if ( argc < 2 )
	{
    printf("Usage: ./%s <filename>\n",argv[0]);
    return 1;
  }
  parse_bsp( argv[1] );
  return 0;
}



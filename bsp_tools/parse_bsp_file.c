
#include <stdio.h>

#define BSP_VERSION_NUMBER      (1)
#define MAGIC_NUMBER    0x584A5250 //1481265744

typedef	unsigned char		uint8;			/* Unsigned 8 Bit Integer  */
typedef	char				int8;			/* Signed 8 Bit Integer    */
typedef	unsigned short int	uint16;			/* Unsigned 16 Bit Integer */
typedef	short int			int16;			/* Signed 16 bit Integer   */
typedef	unsigned long		uint32;			/* Unsigned 32 Bit Integer */
typedef	long				int32;			/* Signed 32 Bit Integer   */

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

int parse_bsp ( char * filename ) {

  FILE * fp;
  uint32 MagicNumber, VersionNumber;
  int16	NumGroups, NumNodes = 0;
  int GroupCount, NodeCount = 0;

  // open the file

  fp = fopen( filename, "rb" );
  if( fp == NULL ) {
    printf("Could not open file!\n");
    return 1;
  }

  // get the magic number

  fread( &MagicNumber, sizeof( uint32 ), 1, fp );
  printf("magic number\t = %i\n",MagicNumber);
  if( MagicNumber != MAGIC_NUMBER ) {
    printf("Notice: Magic number not correctly set...\n");
  }

  // get the bsp version number

  fread( &VersionNumber, sizeof( uint32 ), 1, fp );
  printf("pic version\t = %i\n",VersionNumber);
  if( VersionNumber != BSP_VERSION_NUMBER ){
    printf("Notice: Pic Version Number not correctly set...\n");
  }
  
  // get number of groups

  fread( &NumGroups, sizeof( int16 ), 1, fp );
  printf("Number of Groups\t = %i\n",NumGroups);

  // for each group

  for( GroupCount = 0; GroupCount < NumGroups; GroupCount++ ) {
    printf("\n\n");

    printf("Group:\t %i\n",GroupCount);

    fread( &NumNodes, sizeof( int16 ), 1, fp );
    printf("Nodes:\t %i\n",NumNodes);

    // for each node
    
    for( NodeCount = 0; NodeCount < NumNodes; NodeCount++ ){
      BSP_RAWNODE Node;
      VECTOR vector;

      printf("\n");
      printf("Node:\t %i\n",NodeCount);

      fread( &Node, sizeof( BSP_RAWNODE ), 1, fp );

      vector = (VECTOR) Node.Normal;

      printf("x (%f), y (%f), z (%f)\n", vector.x, vector.y, vector.z);

      printf("Offset (%f), Front (%i), Back (%i), Colour (%i)\n",
             Node.Offset,  Node.Front,  Node.Back,  Node.Colour);
    }

	}
  fclose( fp );
  return 0;
}

int main( int argc , char *argv[] ){
  if ( argc < 2 ) {
    printf("Usage: ./%s <filename>\n",argv[0]);
    return 1;
  }
  parse_bsp( argv[1] );
  return 0;
}



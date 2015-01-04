/****************************************************************************
 * audio.c
 * MPATE-GE 2618
 * Problem Set 4
 * 
 * Processes the beginning of an AIFF file.  
 * Reads in the the FORM id at the beginning of the file and then
 * reads the chunk size that follows it.  The chunk size is equal the
 * size of the entire AIFF file not including the 4-byte FORM id 
 * and the 4-byte chunk size value.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "audio.h"

int main(int argc, char * argv[])
{

  const char *infile = "mysteryAudio";
  unsigned char chunkId[4];
  uint32_t chunkSize, convertedChunkSize;
  int counter = 1;
  
  // try to open input file 
  FILE *inptr = fopen(infile, "rb");
  if (inptr == NULL) {
    printf("Could not open %s.\n", infile);
    return 1;
  }

  //Open output files
  const char *outfile1 = "f1.aiff";
  const char *outfile2 = "f2.aiff";
  const char *outfile3 = "f3.aiff";
  const char *outfile4 = "f4.aiff";
  const char *outfile5 = "f5.aiff";

  //Overwrite files or try to write to the output files
  FILE *outptr1 = fopen(outfile1, "wb");
  if (outptr1 == NULL) {
    printf("Could not open %s.\n",outfile1);
    fclose (inptr);
    return 1;

  }

  FILE *outptr2 = fopen(outfile2, "wb");
  if (outptr2 == NULL) {
    printf("Could not open %s.\n",outfile2);
    fclose (inptr);
    return 1;

  }

  FILE *outptr3 = fopen(outfile3, "wb");
  if (outptr3 == NULL) {
    printf("Could not open %s.\n",outfile3);
    fclose (inptr);
    return 1;

  }

  FILE *outptr4 = fopen(outfile4, "wb");
  if (outptr4 == NULL) {
    printf("Could not open %s.\n",outfile4);
    fclose (inptr);
    return 1;

  }

   FILE *outptr5 = fopen(outfile5, "wb");
  if (outptr5 == NULL) {
    printf("Could not open %s.\n",outfile5);
    fclose (inptr);
    return 1;

  }

  printf ("Working.......\n"); 
  while (!feof(inptr)){

  // Read in the first 4 characters -- they should be 'FORM'
  fread(chunkId, sizeof(unsigned char), 4, inptr);
  //Check to see if the characters are the Form
  if ( chunkId[0] == 'F' && chunkId[1] == 'O' && chunkId[2] == 'R' && chunkId[3] == 'M' ){ 
    //if it is get the chunk Size and convert it from Big Endian
    chunkSize = getChunkSize(inptr); 
    convertedChunkSize = convertFromBigEndian(chunkSize);
    
    //set up 5 cases for writing to 5 different files with a counter
    //Write the ChunkID to new file
    //Write the size of the chunk to new file
    //Write the rest of the data into the new file
    switch (counter){
    case 1:
        fwrite( chunkId, sizeof(unsigned char), 4, outptr1 );
        fwrite (&convertedChunkSize, sizeof(uint32_t), 1, outptr1);
        writeBytes (inptr, outptr1, convertedChunkSize);
        break;

    case 2:
        fwrite( chunkId, sizeof(unsigned char), 4, outptr2 );
        fwrite (&convertedChunkSize, sizeof(uint32_t), 1, outptr2);
        writeBytes (inptr, outptr2, convertedChunkSize);
        break;

    case 3:
        fwrite( chunkId, sizeof(unsigned char), 4, outptr3 );
        fwrite (&convertedChunkSize, sizeof(uint32_t), 1, outptr3);
        writeBytes (inptr, outptr3, convertedChunkSize);
        break;


    case 4:
        fwrite( chunkId, sizeof(unsigned char), 4, outptr4 );
        fwrite (&convertedChunkSize, sizeof(uint32_t), 1, outptr4);
        writeBytes (inptr, outptr4, convertedChunkSize);
        break;

    case 5:
        fwrite( chunkId, sizeof(unsigned char), 4, outptr5 );
        fwrite (&convertedChunkSize, sizeof(uint32_t), 1, outptr5);
        writeBytes (inptr, outptr5, convertedChunkSize); 
        break;

        } 
    //increment up so that each file is created
    counter ++; 
  }
  //if the counter has not hit 6 then continue to seek through the file
  if (counter != 6){
       fseek(inptr, -3, SEEK_CUR );
  }

}

  printf ("Extracted!"); 
  //Close files
  fclose(inptr);
  fclose(outptr1);
  fclose(outptr2);
  fclose(outptr3);
  fclose(outptr4);
  fclose(outptr5);

  return 0;
}

// Read in a 4-byte integer from the file
uint32_t getChunkSize(FILE *fp)
{

  uint32_t chunkSize;
  fread(&chunkSize, sizeof(uint32_t), 1, fp);
  return chunkSize;
}

// Convert from a big endian to little endian format if necessary
// Note: you don't have understand this function (yet)
uint32_t convertFromBigEndian(uint32_t val)
{
  const int ONE = 1;
  uint32_t littleEndianVal = val;

  if ((*(char*)&ONE) != 0) { // means architecture is little endian
    littleEndianVal = (littleEndianVal >> 24) | (littleEndianVal >> 8 & 0x0000FF00) 
      | (littleEndianVal << 8  &  0x00FF0000) | (littleEndianVal << 24);
    //printf("Your machine is little endian.\n");
    return littleEndianVal;
  } else { // if architecture is big endian, just return the val as is.
    printf("Your machine is big endian.\n");
    return val;
  }
}

void writeBytes( FILE *fp, FILE *outp, uint32_t bytes_left ) {
    uint32_t bytes_to_read;
    const int bsize = 512;
    char buffer[bsize];

    while ( bytes_left > 0 ) {
        bytes_to_read = ( bytes_left < bsize ) ? bytes_left : bsize;
        fread( buffer, sizeof( char ), bytes_to_read, fp );
        fwrite( buffer, sizeof( char ), bytes_to_read, outp );
        bytes_left -= bytes_to_read;
    }
}


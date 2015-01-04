/****************************************************************************
 * audio.h
 * MPATE-GE 2618
 * Problem Set 4
 ***************************************************************************/
#include <stdint.h>

uint32_t convertFromBigEndian(uint32_t val);
uint32_t getChunkSize(FILE *fp);


void writeBytes( FILE *fp, FILE *outp, uint32_t bytes_left );




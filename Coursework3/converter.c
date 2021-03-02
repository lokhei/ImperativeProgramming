#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "displayfull.h"

typedef unsigned char byte;

void assert(int line, bool b); //prototype for assert


// Header (P5 space) and test file is a PGM file
int header(FILE *pgm, byte ch){
	ch = fgetc(pgm); //P
	assert(__LINE__, ch == 'P');
	ch = fgetc(pgm); //five
	assert(__LINE__, ch == '5');
	ch = fgetc(pgm); //space
	assert(__LINE__, ch == ' ');
	return ch;
}

//new filename
char *skfilename(char *args, int length){
	char *newname = malloc(256);
	strncpy(newname, args, length);
	newname[length- 1] = '\0';
	newname[length - 2] = 'k';	
	newname[length - 3] = 's';	
	return newname;

}



//function to get width and height
int val(FILE *pgm, byte ch){
	int result = 0;
	ch = fgetc(pgm);
	while (!feof(pgm) && (ch != 9 && ch !=10 && ch != 13 && ch != 32)){
		result = (result * 10) + ((int)ch - 48);
		ch = fgetc(pgm);
	}
	return result;
}



int pgm_convert(byte ch, byte prev, byte *image, int pgm_index, int sk_index, int width){
	int x = pgm_index % width;
	int index = 0;
	if (prev != ch){ //RGBA
		image[sk_index ++] = 0xc0 | (ch >> 6); // rr
		image[sk_index ++] = 0xc0 | (ch & 0x3F); //  rrrrrrr
		image[sk_index ++] = 0xc0 | ((ch & 0xFC) >> 2); // gggggg
		image[sk_index ++] = 0xc0 | ((ch & 0x3) << 4) | ((ch & 0xf0) >> 4); // gg bbbb
		image[sk_index ++] = 0xc0 | ((ch & 0xf) << 2) | 0x3; //bbbb 11
		image[sk_index ++] = 0xc0 | 0x3f; // 11 1111
		image[sk_index ++] = 0x83; // colour
		index += 7;
	}
	image[sk_index ++] = 0x1; // s -> x += 1
	image[sk_index ++] = 0x40; // s -> x += 1


	
	index += 2;

	if (width - 1 == x){ //line ends
		image[sk_index ++] = 0x80; //set tool equal to none
		image[sk_index ++] = 0x1; //s -> x += 1
		image[sk_index ++] = 0x81; //line
		image[sk_index ++] = 0x41; // s -> y += 1
		image[sk_index ++] = 0xc0; // data
		image[sk_index ++] = 0x84; // targetx
		index += 6;

	}
	
	

	
	return index;

}
	
int main(int n, char *args[n]) {
   
    if (n != 2) { // return usage hint if not exactly one argument
        printf("wrong input\n");
        exit(1);
    }

    FILE *pgm = fopen(args[1], "rb"); // open argument file
	
	if (pgm == NULL) { //if file empty, cannot convert
		fprintf(stderr, "Cannot convert image\n");
		exit(1);
	}

	int length = strlen(args[1]);
	char *name = skfilename(args[1], length);
	


	FILE *out = fopen(name, "wb"); //open out file
	
	byte ch = 0;
	header(pgm, ch); //P5 space

	//get width, height, maxval
	int width = val(pgm, ch);
	int height = val(pgm, ch);
	int maxVal = 0;

	ch = fgetc(pgm);
	while (!feof(pgm) && (ch != 9 && ch !=10 && ch != 13 && ch != 32)){
		maxVal = (maxVal * 10) + ((int)ch - 48); //get maxval
		ch = fgetc(pgm);
	}

	int pgm_index = 0, sk_index = 0;
	byte prev = ch; // space
	ch = fgetc(pgm); //start of pixels
	byte image[width*height*15];
	
	while (!feof(pgm) && maxVal <= 255){
	
		sk_index += pgm_convert(ch, prev, image, pgm_index, sk_index, width);
		prev = ch;
		ch = fgetc(pgm);
		pgm_index ++;
	}

	
	fwrite(image, 1, sk_index, out);


	
	//close files
	fclose(pgm);
	fclose(out);
	printf("File %s has been written.", name);
	free(name);
	void testname();

    return 0;
}




//function for assertion
void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}

//test new filename is correct
void testname(){
	char * bands = skfilename("bands.pgm", 9);
	assert(__LINE__, strncmp(bands,"bands.sk", 9));
	char * fractal = skfilename("fractal.pgm", 12);
	assert(__LINE__, strncmp(fractal,"fractal.sk", 12));
	free(bands);
	free(fractal);
}



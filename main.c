#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);

/*
Para cada ponto (x,y) da imagem:
    Obtem a cor do pixel (r,g,b)
    // calcula o equivalente cinza da cor
    i = (0.3 * r + 0.59 * g + 0.11 * b)
    // armazena o cinza no pixel
    EscreveCor(x,y,i,i,i) # x,y,r,g,b
*/

// Img converter(Img imagem[]) {
//     //int size = &imagem->width * &imagem->height;
//     Img result;
//
//     return result;
// }

// Carrega uma imagem para a struct Img
// largura e altura vai definir quebras de linha da imagem
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    printf("Primeiros 100 pixels da imagem:\n");
    for(int i=0; i<100; i++) {
        printf("[%3d %3d %3d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    printf("\n");
    Img clone = converter(pic);
    for(int i=0; i<100;i++) {
        printf("[%3d %3d %3d] ", clone.img[i].r, clone.img[i].g, clone.img[i].b);
    }

    free(pic.img);
}

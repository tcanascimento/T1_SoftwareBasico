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

//ler parâmetro de redução, que deverá representar o tamanho dos blocos -> 50% representa reduzir o vator à metade do seu tamanho original. Ex: vetor de 12 posições; 50% = 6 blocos de 2 pixels cada
int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);
    int vetor_size = pic.width * pic.height; //inserir fator de correção
    printf("Tamanho do vetor: %d\n", vetor_size);


    int vetor_clone = [vetor_size];
    for(int i = 0; i < vetor_size; i++){
      float k = ((0.3 * pic.img[i].r) + (0.59 * pic.img[i].g) + (0.11 * pic.img[i].b)); //gera tom de cinza
      vetor_clone[i] = int(k);
    }

    //mapear conjunto de caracteres com valores de tons de cinza - @ mais próximo de 255, e '.' mais próximo de 0.

    // para gerar saída em html, cada linha vai ter o tamanho do width da imagem de entrada (dimensionada para o bloco);

    // printf("Primeiros 100 pixels da imagem:\n");
    // for(int i=0; i<100; i++) {
    //     printf("[%3d %3d %3d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    // }

    // printf("tons de cinza: \n");
    // for(int i=0; i<100; i++) {
    //   float j = ((0.3 * pic.img[i].r) + (0.59 * pic.img[i].g) + (0.11 * pic.img[i].b));
    //   printf("tom: %3f\n", j);
    // }
    printf("\n");
    free(pic.img);
}

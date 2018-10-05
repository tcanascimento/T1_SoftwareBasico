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
//usar média
//ler parâmetro de redução, que deverá representar o tamanho dos blocos -> 50% representa reduzir o vator à metade do seu tamanho original. Ex: vetor de 12 posições; 50% = 6 blocos de 2 pixels cada
int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    printf("Argumento 2 e 3: %s %s\n", argv[2], argv[3]);
    int height = pic.height;
    int width = pic.width;
    int length = height * width;
    float clone_vetor[length];

    for(int i = 0; i < length; i++){
        float k = ((0.3 * pic.img[i].r) + (0.59 * pic.img[i].g) + (0.11 * pic.img[i].b));
        clone_vetor[i] = k;
      }
    }

    char vetor_char[length];

    //mapear conjunto de caracteres com valores de tons de cinza - @ mais próximo de 255, e '.' mais próximo de 0.
    // fazer por média de tom
    for(int i = 0; i < length; i++){
        if(clone_vetor[i] <= 90) {
          vetor_char[i] = '#';
        } else if(clone_vetor[i] > 90 && clone_vetor[i] < 190) {
          vetor_char[i] = '~';
        } else {
          vetor_char[i] = '.';
        }
    }



    FILE *file = fopen("imagem.html", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    //int height = pic.width;
    //char vetor_char[length];

    // imprimir estrutura do body
    fprintf(file, "<html><head></head>\n");
    fprintf(file, "<body style="background: black;" leftmargin=0 topmargin=0>\n");
    fprintf(file, "<style>\n");
    fprintf(file, "pre  {\n");
    fprintf(file, "         color: white;\n");
    fprintf(file, "         font-family: Courier;\n");
    fprintf(file, "         font-size: 8px;}\n");
    fprintf(file, "</style>\n");
    fprintf(file, "<pre>\n");
    //laço para imprimir imagem
    for(int i = 0; i < length; i++) {
      int temp = 0;
      while(temp < width){
        fprintf(file, "%s", vetor_char[i]);
        temp +=1;
      }
      fprintf(file, "<pre>\n");
    }
    fprintf(file, "</pre>\n");
    fprintf(file, "</body>\n");
    fprintf(file, "</html>\n");

    fclose(file);


    // para gerar saída em html, cada linha vai ter o tamanho do width da imagem de entrada (dimensionada para o bloco);


    printf("\n");
    free(pic.img);
}

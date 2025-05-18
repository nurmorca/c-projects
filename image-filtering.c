// this is a program that applies gaussian and laplacian filters to images. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int **getImage(char path[], int *w, int *h, int *max, int *format) {
    FILE *ptr;
    int i, j;
    char readchars[256], type[3];

    ptr = fopen(path, "rb");
    if (ptr == NULL) {
        printf("\ncouldn't open file.\n");
        exit(1);
    }

    // read metadata.
    fscanf(ptr, "%2s", type);
    *format = (strcmp(type, "P2") == 0) ? 2 : 5;
    fscanf(ptr, "%s", readchars);
    if (strcmp(readchars, "#") == 0) {
        fscanf(ptr, "%*[^\n]");
    }
    fscanf(ptr, "%s", readchars);
    *w = atoi(readchars);
    fscanf(ptr, "%s", readchars);
    *h = atoi(readchars);
    fscanf(ptr, "%s", readchars);
    *max = atoi(readchars);

    int **pgm = (int **) malloc((*h) * sizeof(int *));
    int *data = (int *) malloc((*h) * (*w) * sizeof(int));
    for (i = 0; i < *h; i++) {
        pgm[i] = data + i * (*w);
    }

    if (*format == 2) {
        for (i = 0; i < *h; i++) {
            for (j = 0; j < *w; j++) {
                fscanf(ptr, "%d", &pgm[i][j]);
            }
        }
    } else {
        fgetc(ptr);
        unsigned char *buffer = (unsigned char *) malloc((*h) * (*w));
        fread(buffer, sizeof(unsigned char), (*h) * (*w), ptr);
        for (i = 0; i < *h; i++) {
            for (j = 0; j < *w; j++) {
                pgm[i][j] = buffer[i * (*w) + j];
            }
        }
        free(buffer);
    }

    fclose(ptr);
    return pgm;
}

void createFilter(double **filter, int dimension, float deviation) {
    double sum = 0.0;
    int halfSize = dimension / 2;
    double sigma2 = 2 * deviation * deviation;
    int i, j;

    for (i = -halfSize; i <= halfSize; i++) {
        for (j = -halfSize; j <= halfSize; j++) {
            filter[i + halfSize][j + halfSize] = exp(-(i * i + j * j) / sigma2) / (M_PI * sigma2);
            sum += filter[i + halfSize][j + halfSize];
        }
    }

    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            filter[i][j] /= sum;
        }
    }

}

void applyGaussianFilter(int **image, int **output, int w, int h, double **filter, int filterDim) {
    int halfSize = filterDim / 2;
    int i, j, idx, idy;
    int imgX, imgY;
    double sum;

    for (i = halfSize; i < h - halfSize; i++) {
        for (j = halfSize; j < w - halfSize; j++) {
            sum = 0.0;

            for (idx = 0; idx < filterDim; idx++) {
                for (idy = 0; idy < filterDim; idy++) {
                    imgX = j + idy - halfSize;
                    imgY = i + idx - halfSize;
                    sum += image[imgY][imgX] * filter[idx][idy];
                }
            }
            output[i][j] = (int) sum;
        }
    }
}

void applyLaplacianFilter(int **image, int **output, int w, int h, int kernel[3][3]) {
    int halfSize = 1, i, j, idx, idy, sum;

    for (i = halfSize; i < h - halfSize; i++) {
        for (j = halfSize; j < w - halfSize; j++) {
            sum = 0;

            for (idx = 0; idx < 3; idx++) {
                for (idy = 0; idy < 3; idy++) {
                    sum += image[i + idx - halfSize][j + idy - halfSize] * kernel[idx][idy];
                }
            }

            output[i][j] = sum;
        }
    }
}

void
saveImage(char *originalName, int **image, int w, int h, int max, int format, int filterDim, float stdDev, char *type) {
    char filename[256];
    int i, j;
    sprintf(filename, "%s_filtered_%dx%d_%.1f_%s.pgm", originalName, filterDim, filterDim, stdDev, type);

    FILE *file = fopen(filename, format == 2 ? "w" : "wb");
    if (file == NULL) {
        printf("couldn't save image.\n");
        return;
    }

    fprintf(file, "P%d\n%d %d\n%d\n", format, w, h, max);

    if (format == 2) {
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) {
                fprintf(file, "%d ", image[i][j]);
            }
            fprintf(file, "\n");
        }
    } else {
        unsigned char *buffer = (unsigned char *) malloc(w * h);
        for (i = 0; i < h; i++)
            for (j = 0; j < w; j++)
                buffer[i * w + j] = (unsigned char) image[i][j];

        fwrite(buffer, sizeof(unsigned char), w * h, file);
        free(buffer);
    }

    fclose(file);
}

int main() {
    int w, h, max, format, i, filterDim;
    float stdDev;
    int path, dev, dim;
    int filterDims[3] = {3, 5, 7};
    float standardDevs[3] = {1, 2, 4};
    int laplacian1[3][3] = {{0, 1,  0},
                            {1, -4, 1},
                            {0, 1,  0}};
    int laplacian2[3][3] = {{1, 1,  1},
                            {1, -8, 1},
                            {1, 1,  1}};
    char paths[3][60] = {"C:\\Users\\nur\\CLionProject\\imageprocessing\\fruit.pgm",
                         "C:\\Users\\nur\\CLionProject\\imageprocessing\\coins.ascii.pgm",
                         "C:\\Users\\nur\\CLionProject\\imageprocessing\\saturn.ascii.pgm"};

    for (path = 0; path < 3; path++) {
        printf("%d ", path);
        int **pgm = getImage(paths[path], &w, &h, &max, &format);

        int **resultImage = (int **) malloc(h * sizeof(int *));
        for (i = 0; i < h; i++) {
            resultImage[i] = (int *) malloc(w * sizeof(int));
        }

        for (dim = 0; dim < 3; dim++) {
            for (dev = 0; dev < 3; dev++) {
                filterDim = filterDims[dim];
                stdDev = standardDevs[dev];

                double **filter = (double **) malloc(filterDim * sizeof(double *));
                for (i = 0; i < filterDim; i++) {
                    filter[i] = (double *) malloc(filterDim * sizeof(double));
                }
                createFilter(filter, filterDim, stdDev);


                applyLaplacianFilter(pgm, resultImage, w, h, laplacian1);
                saveImage(paths[path], resultImage, w, h, max, format, 0, 0, "laplacian1");
                applyLaplacianFilter(pgm, resultImage, w, h, laplacian2);
                saveImage(paths[path], resultImage, w, h, max, format, 0, 0, "laplacian2");
                applyGaussianFilter(pgm, resultImage, w, h, filter, filterDim);
                saveImage(paths[path], resultImage, w, h, max, format, filterDim, stdDev, "gaussian");
                applyLaplacianFilter(pgm, resultImage, w, h, laplacian1);
                saveImage(paths[path], resultImage, w, h, max, format, filterDim, stdDev, "laplacian1");
                applyLaplacianFilter(pgm, resultImage, w, h, laplacian2);
                saveImage(paths[path], resultImage, w, h, max, format, filterDim, stdDev, "laplacian2");

                for (i = 0; i < filterDim; i++) {
                    free(filter[i]);
                }
                free(filter);
            }
        }

        free(pgm[0]);
        free(pgm);
        for (i = 0; i < h; i++) {
            free(resultImage[i]);
        }
        free(resultImage);
    }
    return 0;
}

#include <stdlib.h>
#include <stdio.h>

#define FIXED_BITS_WIDTH 4
#define R_FP_FACTOR ((int)(0.2126f * (1 << FIXED_BITS_WIDTH)))
#define G_FP_FACTOR ((int)(0.7152f * (1 << FIXED_BITS_WIDTH)))
#define B_FP_FACTOR ((int)(0.0722f * (1 << FIXED_BITS_WIDTH)))

int main(void) {
    FILE* bitmap, * bitmap_out;
    int type, w, h, d;

    printf("RGB Color Test\n");
    bitmap = fopen("ada.pbm", "rb");
    bitmap_out = fopen("out.pbm", "wb");

    if (bitmap) {
        if (bitmap_out) {
            int ret;
            ret = fscanf(bitmap, "P%d%d%d%d\n\r", &type, &w, &h, &d);
            printf("type = %d, width = %d, height = %d, palette size = %d, returned %d\n", type, w, h, d, ret);

            fprintf(bitmap_out, "P%d %d %d %d ", type, w, h, d);

            // read original bitmap
            // and convert it
            {
                int pixel_index;
                unsigned char r, g, b;
                int l;
                for (pixel_index = 0; pixel_index < w * h; pixel_index++) {
                    fread(&r, sizeof(unsigned char), 1, bitmap);
                    fread(&g, sizeof(unsigned char), 1, bitmap);
                    fread(&b, sizeof(unsigned char), 1, bitmap);

                    l = (unsigned char)((r * R_FP_FACTOR + g * G_FP_FACTOR + b * B_FP_FACTOR) >> FIXED_BITS_WIDTH);

                    // Do your conversion process here
                    fwrite(&l, sizeof(unsigned char), 1, bitmap_out);
                    fwrite(&l, sizeof(unsigned char), 1, bitmap_out);
                    fwrite(&l, sizeof(unsigned char), 1, bitmap_out);
                }
            }
            fclose(bitmap_out);
        }
        fclose(bitmap);
    }

    return 0;
}
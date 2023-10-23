#include <stdlib.h>
#include <stdio.h>

int main(void){
    FILE *bitmap, *bitmap_out;
    int type,w,h,d;

    printf("RGB Color Test\n");
    bitmap = fopen("ada.pbm", "rb");
    bitmap_out = fopen("out.pbm", "wb");

    if (bitmap){
        if (bitmap_out){
            int ret;
            ret = fscanf(bitmap, "P%d%d%d%d\n\r", &type, &w, &h, &d);
            printf("type = %d, width = %d, height = %d, palette size = %d, returned %d\n", type, w, h, d, ret);

            fprintf(bitmap_out, "P%d %d %d %d ", type, w, h, d);

            // read original bitmap
            // and convert it
            {
                int pixel_index;
                unsigned char r, g, b, l;
                for(pixel_index = 0; pixel_index < w * h; pixel_index++){
                    fread(&r, sizeof(unsigned char), 1, bitmap);
                    fread(&g, sizeof(unsigned char), 1, bitmap);
                    fread(&b, sizeof(unsigned char), 1, bitmap);

                    l = 255 - ((r + g + b) / 3);

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
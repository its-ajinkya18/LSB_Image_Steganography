#include <stdio.h>
#include <string.h>
#include "types.h"
#include "encode.h"

/* Function Definitions */
 
/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    // printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    // printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);
    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    if(argv[2] != NULL)
    {
        encInfo->src_image_fname = argv[2];
        char *src_ext = strstr(argv[2], ".bmp");
        if(src_ext != NULL && (strcmp(src_ext, ".bmp") == 0)) 
        {
            if (argv[3] != NULL)
            {
                char *secret_ext = strrchr(argv[3], '.');
                if (secret_ext != NULL && (strcmp(secret_ext, ".txt") == 0 || strcmp(secret_ext, ".csv") == 0 || strcmp(secret_ext, ".c") == 0   || strcmp(secret_ext, ".py") == 0))
                {
                    encInfo->secret_fname = argv[3];
                    strcpy(encInfo->extn_secret_file, secret_ext);  // copy only extension
                }
                else
                {
                    printf("Error: Unsupported or missing secret file extension.\n");
                    return e_failure;
                }
            }
            else
            {
                printf("Error: Secret file not provided.\n");
                return e_failure;
            }
            if(argv[4] != NULL)
            {
                char * dest_ext = strstr(argv[4], ".bmp");
                if(dest_ext != NULL && strcmp(dest_ext, ".bmp") == 0)
                {
                    encInfo->stego_image_fname = argv[4];
                }
                else
                {
                    printf("Error : Wrong Destination file\n");
                    return e_failure;
                }
            }
            else
            {
                encInfo->stego_image_fname = "stego.bmp";
            }
        }
        else
        {
            printf("Error : .bmp file not found\n");
            return e_failure;
        }
    }
    else
    {
        return e_failure;
    }
    return e_success;
}

Status do_encoding(EncodeInfo *encInfo)
{
    printf("Do Encoding\n");

    char mg_str[100];
    printf("Enter the Magic string: ");
    scanf(" %[^\n]",mg_str);
    encInfo->magic_str = mg_str;

    if(open_files(encInfo) == e_failure)
    {
        printf("Error! Files not opened\n");
        return e_failure;
    }
    else
    {
        printf("File opened Succesfully\n");
    }
    if (check_capacity(encInfo) == e_failure)
    {
        printf("Error: check capacity\n");
        return e_failure;
    }
    else
    {
        printf("check capacity done successfully\n");
    }
    if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
    {
        printf("Encoding of header file is done\n");
    }
    else
    {
        printf("Error! Encoding of header file is failed\n");
        return e_failure;
    }
    if(encode_magic_string_size(strlen(encInfo->magic_str), encInfo) == e_success)
    {
        printf("Encoding magic string size is done\n");
    }
    else
    {
        printf("Error! Encoding magic string size is failed\n");
        return e_failure;
    }
    if(encode_magic_string(encInfo->magic_str, encInfo) == e_success)
    {
        printf("Encoding magic string is done\n");
    }
    else
    {
        printf("Error! Encoding magic string is failed\n");
        return e_failure;
    }
    if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file), encInfo) == e_success)
    {
        printf("Encoding Secret file extention size is done\n");
    }
    else
    {
        printf("Error! Encoding Secret file extention size is failed\n");
        return e_failure;
    }
    if(encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_success)
    {
        printf("Encoding Secret file extention is done\n");
    }
    else
    {
        printf("Error! Encoding Secret file extention is failed\n");
        return e_failure;
    }
    if(encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_success)
    {
        printf("Encoding Secret file size is done\n");
    }
    else
    {
        printf("Error! Encoding Secret file size is failed\n");
        return e_failure;
    }
    if(encode_secret_file_data(encInfo) == e_success)
    {
        printf("Encoding Secret file data is done\n");
    }
    else
    {
        printf("Error! Encoding Secret file data is failed\n");
        return e_failure;
    }
    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
    {
        printf("Succesfully copy remaining image data\n");
    }
    else
    {
        printf("Error! Copy remaining image data is failed\n");
        return e_failure;
    }
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);
    uint enc_things_size = (strlen(encInfo->magic_str) + strlen(encInfo->extn_secret_file) + encInfo->size_secret_file + 12);
    if((encInfo->image_capacity) >= (enc_things_size * 8) + 54)
    {
        return e_success;
    }
    else
    {
        printf("Source file is not capable for Encoding\n");
        return e_failure;
    }
}

uint get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);
    return ftell(fptr);
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    rewind(fptr_src_image);
    char header[54];
    fread(header, sizeof(char[54]), 1, fptr_src_image);
    fwrite(header, sizeof(char[54]), 1, fptr_dest_image);
    return e_success;
}
Status encode_magic_string_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer, sizeof(char[32]), 1, encInfo->fptr_src_image);
    encode_integer(file_size, buffer);
    fwrite(buffer, sizeof(char[32]), 1, encInfo->fptr_stego_image);
    return e_success;
}
Status encode_magic_string(char *magic_string, EncodeInfo *encInfo)
{
    encode_data_to_image(magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_extn_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer, sizeof(char[32]), 1, encInfo->fptr_src_image);
    encode_integer(file_size, buffer);
    fwrite(buffer, sizeof(char[32]), 1, encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo)
{
    encode_data_to_image(file_extn, strlen(file_extn), encInfo->fptr_src_image, encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer, sizeof(char [32]), 1, encInfo->fptr_src_image);
    encode_integer(file_size, buffer);
    fwrite(buffer, sizeof(char [32]), 1, encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    rewind(encInfo->fptr_secret);
    char buffer[encInfo->size_secret_file + 1];
    fread(buffer, sizeof(char[encInfo->size_secret_file]), 1, encInfo->fptr_secret);
    buffer[encInfo->size_secret_file] = '\0';
    encode_data_to_image(buffer, encInfo->size_secret_file, encInfo->fptr_src_image, encInfo->fptr_stego_image);
    return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;
    while(fread(&ch, 1, 1, fptr_src) > 0)
    {
        fwrite(&ch, 1, 1, fptr_dest);
    }
    return e_success;
}
Status encode_integer(int size, char *image_buffer)
{
    for(int i=0; i<32; i++)
    {
        uint get_bit = (uint)(size & (1 << i)) >> (i);
        uint clear_bit = image_buffer[i] & (~1);
        image_buffer[i] = get_bit | clear_bit;
    }
    return e_success;
}
Status encode_character(char data, char *image_buffer)
{
    for(int i=0; i<8; i++)
    {
        uint get_bit = (uint)(data & (1 << i)) >> (i);
        uint clear_bit = image_buffer[i] & (~1);
        image_buffer[i] = get_bit | clear_bit;
    }
    return e_success;
}
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[8];
    for(int i=0; i<size; i++)
    {
        fread(buffer, sizeof(char[8]), 1, fptr_src_image);
        encode_character(data[i], buffer);
        fwrite(buffer, sizeof(char[8]), 1, fptr_stego_image);
    }
    return e_success;
}
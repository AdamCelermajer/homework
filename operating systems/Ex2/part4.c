// adam celermajer 332638592
#include "copytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void print_usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s [-l] [-p] <source_directory> <destination_directory>\n", prog_name);
    fprintf(stderr, "  -l: Copy symbolic links as links\n");
    fprintf(stderr, "  -p: Copy file permissions\n");
}

int create_destination_directory(const char *dest_dir, int copy_permissions)
{
    struct stat st = {0};

    if (stat(dest_dir, &st) == -1)
    {
        if (mkdir(dest_dir, copy_permissions ? 0777 : 0755) != 0)
        {
            fprintf(stderr, "Error creating directory %s: %s\n", dest_dir, strerror(errno));
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int copy_symlinks = 0;
    int copy_permissions = 0;
    int opt = 1;

    // Handle the flags manually
    for (; opt < argc && argv[opt][0] == '-'; opt++)
    {
        if (strcmp(argv[opt], "-l") == 0)
        {
            copy_symlinks = 1;
        }
        else if (strcmp(argv[opt], "-p") == 0)
        {
            copy_permissions = 1;
        }
        else
        {
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    // Check if there are exactly two remaining arguments (source and destination directories)
    if (opt + 2 != argc)
    {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *src_dir = argv[opt];
    const char *dest_dir = argv[opt + 1];

    // Create the destination directory
    if (create_destination_directory(dest_dir, copy_permissions) != 0)
    {
        return EXIT_FAILURE;
    }

    // Copy the directory
    copy_directory(src_dir, dest_dir, copy_symlinks, copy_permissions);

    return 0;
}

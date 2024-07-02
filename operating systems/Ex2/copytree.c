// adam celermajer 332638592
#include "copytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void copy_symlink(const char *src, const char *dest, int copy_permissions)
{
    char link_target[1024];
    ssize_t len = readlink(src, link_target, sizeof(link_target) - 1);
    if (len == -1)
    {
        perror("readlink failed");
        return;
    }

    link_target[len] = '\0';
    // Now you can use the resolved absolute path
    copy_file(link_target, dest, 0, copy_permissions);
}
void copy_file(const char *src, const char *dest, int copy_symlinks, int copy_permissions)
{
    struct stat statbuf;
    printf("copying file %s to %s\n", src, dest);
    if (lstat(src, &statbuf) == -1)
    {
        perror("lstat failed");
        return;
    }

    if (S_ISLNK(statbuf.st_mode))
    {
        // printf("im a link \n");
        if (copy_symlinks)
        {
            // Copy symbolic link itself
            char link_target[1024];
            ssize_t len = readlink(src, link_target, sizeof(link_target) - 1);
            if (len == -1)
            {
                perror("readlink failed");
                return;
            }
            link_target[len] = '\0';

            if (symlink(link_target, dest) == -1)
            {
                perror("symlink failed");
                return;
            }
        }
        else
        {
            copy_symlink(src, dest, copy_permissions);
        }
    }
    else
    {
        int source_fd = open(src, O_RDONLY);
        if (source_fd == -1)
        {
            perror("open source file failed");
            return;
        }

        int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dest_fd == -1)
        {
            perror("open destination file failed");
            close(source_fd);
            return;
        }
        // now gotta write the content
        char buffer[8192];
        ssize_t bytes_read, bytes_written;
        while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0)
        {
            bytes_written = write(dest_fd, buffer, bytes_read);
            if (bytes_written != bytes_read)
            {
                perror("write failed");
                close(source_fd);
                close(dest_fd);
                return;
            }
        }
        close(source_fd);
        close(dest_fd);
        // Copy file permissions if required
        if (copy_permissions)
        {
            if (chmod(dest, statbuf.st_mode) == -1)
            {
                perror("chmod failed");
            }
        }
    }
}
void copy_directory(const char *src, const char *dest, int copy_symlinks, int copy_permissions)
{
    DIR *dsrc = opendir(src);
    struct dirent *psrc;
    struct stat statbuf;
    while ((psrc = readdir(dsrc)) != NULL)
    {
        // Skip "." and ".." entries
        if (strcmp(psrc->d_name, ".") == 0 || strcmp(psrc->d_name, "..") == 0)
        {
            continue;
        }

        char filepathSrc[1024];
        char filepathDest[1024];
        snprintf(filepathSrc, sizeof(filepathSrc), "%s/%s", src, psrc->d_name);
        snprintf(filepathDest, sizeof(filepathDest), "%s/%s", dest, psrc->d_name);

        if (psrc->d_type == 4)
        {
            // printf("bitch is a folder gotta recurse\n");
            // printf("path: %s type: %d\n", filepathSrc, psrc->d_type);
            // todo copy directory
            if (copy_permissions == 1)
            {
                if (stat(filepathSrc, &statbuf) == 0)
                {
                    mkdir(filepathDest, statbuf.st_mode);
                }
                else
                {
                    perror("stat failed");
                }
            }
            else
            {
                mkdir(filepathDest, 0777);
            }

            copy_directory(filepathSrc, filepathDest, copy_symlinks, copy_permissions);
        }
        else
        {
            copy_file(filepathSrc, filepathDest, copy_symlinks, copy_permissions);
        }
    }
}

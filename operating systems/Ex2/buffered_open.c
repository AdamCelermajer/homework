// adam celermajer 332638592
#include "buffered_open.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
int preappend_write(buffered_file_t *bf)
{
    // Read the existing content
    off_t original_pos = lseek(bf->fd, 0, SEEK_END);
    if (original_pos == -1)
    {
        perror("Failed to seek to end of file");
        return -1; // lseek failed
    }

    // Allocate buffer to hold existing content
    char *existing_content = (char *)malloc(original_pos);
    if (!existing_content)
    {
        perror("Failed to allocate buffer for existing content");
        return -1; // Allocation failed
    }

    // Read existing content
    if (lseek(bf->fd, 0, SEEK_SET) == -1)
    {
        free(existing_content);
        perror("Failed to seek to beginning of file");
        return -1; // lseek failed
    }

    ssize_t bytes_read = read(bf->fd, existing_content, original_pos);
    if (bytes_read < 0)
    {
        free(existing_content);
        perror("Failed to read existing content");
        return -1; // Read failed
    }

    // Move to the beginning and write the new content
    if (lseek(bf->fd, 0, SEEK_SET) == -1)
    {
        free(existing_content);
        perror("Failed to seek to beginning of file");
        return -1; // lseek failed
    }

    ssize_t bytes_written = write(bf->fd, bf->write_buffer, bf->write_buffer_pos);
    if (bytes_written < 0)
    {
        free(existing_content);
        perror("Failed to write new content");
        return -1; // Write failed
    }

    // Write back the existing content
    bytes_written = write(bf->fd, existing_content, bytes_read);
    if (bytes_written < 0)
    {
        free(existing_content);
        perror("Failed to write existing content");
        return -1; // Write failed
    }

    free(existing_content);
    return 0;
}

int buffered_flush(buffered_file_t *bf)
{
    if (bf->write_buffer_pos > 0)
    {
        if (bf->preappend)
        {
            if (preappend_write(bf) < 0)
            {
                return -1; // preappend_write failed
            }
        }
        else
        {
            ssize_t bytes_written = write(bf->fd, bf->write_buffer, bf->write_buffer_pos);
            if (bytes_written < 0)
            {
                perror("Failed to flush write buffer");
                return -1; // Write failed
            }
        }
        bf->write_buffer_pos = 0; // Reset buffer position after flushing
    }
    return 0;
}

// ****************************done****************************
ssize_t buffered_write(buffered_file_t *bf, const void *buf, size_t count)
{
    int firstIt = 1;
    size_t i = 0;
    while (count > 0)
    {
        // Check if there is enough space in the write buffer
        if (bf->write_buffer_pos + count <= bf->write_buffer_size)
        {

            for (int j = 0; j < count; j++)
            {
                bf->write_buffer[bf->write_buffer_pos++] = ((const char *)buf)[j + i];
            }
            i += count;
            buffered_flush(bf);

            return i; // All data has been written to the buffer
        }
        if (firstIt)
        {
            // Flush the buffer
            if (buffered_flush(bf) < 0)
            {
                printf("Failed to flush\n");
                return -1; // Flush failed
            }
            firstIt = 0;
        }
        // If not enough space, fill the buffer and flush it

        size_t space_left = bf->write_buffer_size - bf->write_buffer_pos;
        for (int j = 0; j < space_left; j++)
        {
            bf->write_buffer[bf->write_buffer_pos++] = ((const char *)buf)[j];
        }

        i += space_left;

        count -= space_left;
        // Flush the buffer
        if (buffered_flush(bf) < 0)
        {
            printf("Failed to flush\n");
            return -1; // Flush failed
        }
    }

    return i; // Return the number of bytes written
}

ssize_t buffered_read(buffered_file_t *bf, void *buf, size_t count)
{
    // Flush write buffer before reading
    if (buffered_flush(bf) < 0)
    {
        printf("buffered_flush error\n");
        return -1; // Flush failed
    }

    size_t i = 0;
    while (count - i > 0)
    {
        if (bf->read_buffer_pos < bf->read_buffer_size)
        {
            ((char *)buf)[i] = bf->read_buffer[bf->read_buffer_pos++];
            i++;
            continue;
        }

        if (bf->read_buffer_pos == bf->read_buffer_size)
        {
            ssize_t bytes_read = read(bf->fd, bf->read_buffer, BUFFER_SIZE);
            if (bytes_read < 0)
            {
                printf("error read\n");
                perror("Failed to read from file");
                return -1; // Read failed
            }

            bf->read_buffer_pos = 0;
            bf->read_buffer_size = bytes_read;

            // If no more data is available from the file, break out of the loop
            if (bytes_read == 0)
            {
                break;
            }
        }
    }
    return i; // Return the number of bytes read
}

int buffered_close(buffered_file_t *bf)
{ // Check if bf is NULL
    if (!bf)
    {
        return -1; // Invalid buffered_file_t pointer
    }

    // Flush the write buffer if there's any data
    if (bf->write_buffer_pos > 0)
    {
        if (buffered_flush(bf) < 0)
        {
            return -1; // Flush failed
        }
    }
    int fd = bf->fd;
    free(bf->read_buffer);
    free(bf->write_buffer);
    free(bf);
    // Close the file descriptor
    if (close(fd) < 0)
    {
        perror("Failed to close file descriptor");
        return -1; // Close failed
    }
    return 0;
}
buffered_file_t *dinit()
{
    buffered_file_t *bf = (buffered_file_t *)malloc(sizeof(buffered_file_t));
    if (!bf)
    {
        return NULL; // Allocation failed
    }

    bf->fd = -1; // Invalid file descriptor to start
    bf->read_buffer = (char *)malloc(BUFFER_SIZE);
    bf->write_buffer = (char *)malloc(BUFFER_SIZE);
    if (!bf->read_buffer || !bf->write_buffer)
    {
        free(bf->read_buffer);
        free(bf->write_buffer);
        free(bf);
        return NULL; // Allocation failed
    }

    bf->read_buffer_size = BUFFER_SIZE;
    bf->write_buffer_size = BUFFER_SIZE;
    bf->read_buffer_pos = BUFFER_SIZE;
    bf->write_buffer_pos = 0;
    bf->flags = 0;     // No flags set initially
    bf->preappend = 0; // O_PREAPPEND flag not set initially

    return bf;
}
buffered_file_t *buffered_open(const char *pathname, int flags, ...)
{
    buffered_file_t *nfd = dinit();
    if (!nfd)
    {
        return NULL; // Allocation failed
    }
    nfd->flags = flags;
    nfd->preappend = flags & O_PREAPPEND ? 1 : 0;
    int nflags = flags ^ O_PREAPPEND;

    va_list args;
    va_start(args, flags);

    int mode = 0;
    if (flags & O_CREAT)
    {
        mode = va_arg(args, int);
        nfd->fd = open(pathname, nflags, mode);
    }
    else
    {
        nfd->fd = open(pathname, nflags);
    }

    va_end(args);

    if (nfd->fd == -1)
    {
        free(nfd->read_buffer);
        free(nfd->write_buffer);
        free(nfd);
        return NULL; // Open failed
    }
    if (nfd->preappend)
    {
        if (lseek(nfd->fd, 0, SEEK_SET) == -1)
        {
            close(nfd->fd);
            free(nfd->read_buffer);
            free(nfd->write_buffer);
            free(nfd);
            return NULL; // lseek failed
        }
    }
    return nfd;
}
// ************************************************************

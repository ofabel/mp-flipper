#include <stdio.h>

#include <furi.h>
#include <storage/storage.h>

#include <py/reader.h>

#include "state.h"

typedef struct {
    size_t pointer;
    char* content;
    size_t size;
} FileReaderContext;

FileReaderContext* file_reader_context_alloc(File* file) {
    FileReaderContext* context = malloc(sizeof(FileReaderContext));

    context->pointer = 0;
    context->size = storage_file_size(file);
    context->content = malloc(context->size * sizeof(char));

    storage_file_read(file, context->content, context->size);

    return context;
}

void file_reader_context_free(FileReaderContext* context) {
    free(context->content);
    free(context);
}

mp_uint_t file_reader_read(void* data) {
    FileReaderContext* context = data;

    if(context->size == 0 || context->pointer >= context->size) {
        return MP_READER_EOF;
    }

    return context->content[context->pointer++];
}

void file_reader_close(void* data) {
    file_reader_context_free(data);
}

void mp_reader_new_file(mp_reader_t* reader, qstr filename) {
    FuriString* file_path = furi_string_alloc();
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    furi_string_printf(file_path, "%s/%s", root_module_path, qstr_str(filename));

    if(!storage_file_open(file, furi_string_get_cstr(file_path), FSAM_READ, FSOM_OPEN_EXISTING)) {
        furi_crash("unable to open file");
    }

    reader->data = file_reader_context_alloc(file);
    reader->readbyte = file_reader_read;
    reader->close = file_reader_close;

    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
    furi_string_free(file_path);
}

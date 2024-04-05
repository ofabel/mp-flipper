#include "py/reader.h"

#include "mp_flipper_file_reader.h"

void mp_reader_new_file(mp_reader_t* reader, qstr filename) {
    reader->data = mp_flipper_file_reader_context_alloc(qstr_str(filename));
    reader->readbyte = mp_flipper_file_reader_read;
    reader->close = mp_flipper_file_reader_close;
}

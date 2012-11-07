/*
    libkpass, a library for reading and writing KeePass format files
    Copyright (C) 2009 Brian De Wolf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// A modified version of test2 to be a generic sample for testing keyfile
// databases

#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "kpass.h"

int main(int argc, char* argv[]) {
	uint8_t *file = NULL;
	uint8_t *keyfile = NULL;
	int length, keyfile_length;
	char *filename, *pass, *keyfilename;
	int fd, keyfile_fd;
	struct stat sb;
	unsigned char pw_hash[32];
	kpass_db *db;
	kpass_retval retval;
	uint8_t *outdb;
	int outdb_len;

	if(argc <= 1) exit(1);

	filename = argv[1];
	keyfilename = argv[2];

	db = malloc(sizeof(kpass_db));

// open database file
	fd = open(filename, O_RDONLY);
	if(fd == -1) {
		printf("open failed: %m\n");
		exit(1);
	}

	if(fstat(fd, &sb) == -1) {
		printf("fstat failed: %m\n");
		exit(1);
	}

	length = sb.st_size;

	file = mmap(NULL, length, PROT_READ, MAP_SHARED, fd, 0);
	if(file == MAP_FAILED) {
		printf("mmap failed: %m\n");
		exit(1);
	}

// open keyfile file
	keyfile_fd = open(keyfilename, O_RDONLY);
	if(fd == -1) {
		printf("open failed: %m\n");
		exit(1);
	}

	if(fstat(keyfile_fd, &sb) == -1) {
		printf("fstat failed: %m\n");
		exit(1);
	}

	keyfile_length = sb.st_size;

	keyfile = mmap(NULL, length, PROT_READ, MAP_SHARED, keyfile_fd, 0);
	if(keyfile == MAP_FAILED) {
		printf("mmap failed: %m\n");
		exit(1);
	}

// do the kpass stuff
	retval = kpass_init_db(db, file, length);
	printf("init: %s\n", kpass_strerror(retval));
	if(retval) exit(retval);

	kpass_hash_pw_keyfile(pass = getpass("password:"), keyfile,
				keyfile_length, pw_hash);
	printf("hash: %s\n", kpass_strerror(retval));
	
	retval = kpass_decrypt_db(db, pw_hash);
	printf("decrypt: %s\n", kpass_strerror(retval));
	if(retval) exit(retval);

	outdb_len = kpass_db_encrypted_len(db);
	outdb = malloc(outdb_len);

	retval = kpass_encrypt_db(db, pw_hash, outdb);
	printf("encrypt: %s\n", kpass_strerror(retval));
	if(retval) exit(retval);

	retval = memcmp(file, outdb, outdb_len);
	printf("comparison: %d\n", retval);

	munmap(file, length);
	munmap(keyfile, keyfile_length);

	kpass_free_db(db);

	free(db);
	free(outdb);

	return retval;
}


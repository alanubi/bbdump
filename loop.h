/*
 * Output buffers.
 */
extern char line_bytes[];
extern char line_ascii[];

/*
 * Main read-write loop.
 * Return 1 on reading error, 0 otherwise.
 */
int loop(int coloring_mode, int verbosity_level,
	unsigned bytes_per_group, unsigned groups_per_line);

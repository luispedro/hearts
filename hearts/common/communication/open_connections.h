namespace connection_errors {
		enum type { no_address = 1, interrupted = 2, unix_error = 3 };
}

int open_client_connection(int argc, char* argv[]);
int open_client_connection(const char*);
int open_client_connection(const char*,short);

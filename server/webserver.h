typedef const char* (*push_callback)(const char*, int, int*);

int serverMain(int argc, char **argv, push_callback handlerFunc);

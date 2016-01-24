typedef const char* (*push_callback)(int, const char*, const char*, int, int*);
typedef const char* (*get_callback)(const char*, const char*, int, int*);

int serverMain(int argc, char **argv, push_callback handlerFunc, get_callback getHandler);

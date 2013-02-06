#! /bin/bash

echo "This intend to make C++ constness semantic"
sed -i 's/char \*/const char \*/g' include/xen/api/*.h
sed -i 's/char \*/const char \*/g' src/*.c
sed -i 's/const char \*\*/char \*\*/g' include/xen/api/*.h
sed -i 's/const char \*\*/char \*\*/g' src/*.c
# DIRTY FIX
sed -i 's/const const char/const char/g' include/xen/api/*.h src/*.c
sed -i -e 's/^    const char \*/    char \*/g' include/xen/api/*.h 
echo "patch back 'const char * xen_strdup_(const char *in)' to "
echo "'char * xen_strdup_(const char *in)' by hand"
echo "'const char *session_id;' in include/xen/api/xen_common.h also"

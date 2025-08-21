find . -type f -name "*.c" -exec sh -c 'mv "$1" "${1%.c}.bak"' _ {} \;

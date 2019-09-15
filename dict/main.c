#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <stdio.h>

int main() {
    // _setmode(_fileno(stdout), _O_U16TEXT); 
    FILE *fp = fopen("out.txt", "w");
    wchar_t *str = L"à";

    fputws(str, stdout);
    fputws(str, fp);
    
    fclose(fp);
}
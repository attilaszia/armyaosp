void DrawString(char* str, unsigned int len, unsigned int x, unsigned int y);
void FormatString(char* formatstr, unsigned int len, char* dest, ...);

void hello(void) {
    DrawString("Hello!", 6, 150, 150);
    unsigned int i;
    char string[5];

    for( i = 1; i < 20; i++) {
     FormatString("%d!!", 5, string, i);
     DrawString(string, 5, 150+i*20, 150+i*20);          
    }
}

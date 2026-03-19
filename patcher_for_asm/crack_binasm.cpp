#include "A_Main.h"

int main()
{
    int click_or_click = okno_sfml("do you want hack Sanek?");  

    if(click_or_click == JUST_YES)
    {
        unsigned char what_ptintit[] = {0xB9, 0x00, 0x00}; // 0x39 // mv cx, 0
        // unsigned char what_ptintit[] = {0x1}; // 0x88 // flag = 1 work

        int error_ = change_bin_asm("CRACKME.COM", 0x39, what_ptintit); // mov cx, 8 => mov cx, 0 => success
        AsserT(error_, -1);
    }

    return 0;
}


int change_bin_asm(const char* name_file, int where_wr, unsigned char* what_wr)
{
    AsserT(where_wr < 0, 1);

    FILE* fp = fopen(name_file, "r+b");
    AsserT(fp == NULL, 1);


    fseek(fp, where_wr, SEEK_SET);
    fwrite(what_wr, 1, 3, fp);


    fclose (fp);

    return 0;
}

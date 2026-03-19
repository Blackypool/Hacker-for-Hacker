#ifndef FRAME_FOR_PATCHER_H
#define FRAME_FOR_PATCHER_H


#define OX_OX 800
#define OY_OY 500

#define JUST_YES 1
#define JUST_NOO 2


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
//                                        //________file_names_________//
//clang++ -std=c++17 -stdlib=libc++ -o app crack_binasm.cpp sf_ml_ka.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -rpath /opt/homebrew/lib

int change_bin_asm(const char* name_file, int where_wr, unsigned char* what_wr);
int okno_sfml(const char* question);


enum pose
{
    POSE_yes_OX = 150,
    POSE_yes_minus_OY = 330,

    POSE_noo_OX = 450,
    POSE_noo_minus_OY = 330,

    //координаты левого верхнего угла прямоугольника
    SIZE_but_OX = 200,  
    SIZE_but_OY = 50,
};


#define ART(paint) \
            window.draw(paint)


#define AsserT(what_need, retern)  \
            if(what_need){  \
                fprintf(stderr, "\nerror in line, %s:%d\n", __FILE__, __LINE__);  \
                return retern;  \
            }


#endif
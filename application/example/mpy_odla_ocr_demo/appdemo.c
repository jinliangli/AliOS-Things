/*
 * Copyright (C) 2015-2020 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdlib.h>
#include <aos/kernel.h>
#include "aos/init.h"
#include "board.h"
#include <k_api.h>
#include "haascv_main.h"
int application_start(int argc, char *argv[])
{
    int count = 0;
    int arg_num =  2 ;
    char* argvs[] = {"micropython","/data/odla_demo.py"} ;

    printf(" micropython:uai_odla_demo start\r\n");
    mpy_init();
    mpy_run(arg_num,argvs);
    printf(" micropython:uai_odla_demo end\r\n");
}


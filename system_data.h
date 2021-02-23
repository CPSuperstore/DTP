//
// Created by Christopher on 2021-02-22.
//

#ifndef DTP_SYSTEM_DATA_H
#define DTP_SYSTEM_DATA_H

#endif //DTP_SYSTEM_DATA_H

#include <stdio.h>


int get_device_id(){
    int num;
    FILE *fptr;

    if ((fptr = fopen("D:\\Programming\\C\\DTP\\identity.txt","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    fscanf(fptr,"%d", &num);
    fclose(fptr);

    return num;

}
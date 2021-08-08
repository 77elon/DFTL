#include "init.h"

int main()
{
    struct ssd_info *ssd;
    ssd = (struct ssd_info*)malloc(sizeof(struct ssd_info));

    init_ssd(ssd);


    printf("hello\n");

    int test1;

    test1 = ssd->channel[1].way[1].die[1].plane[1].block[1].OOB;

    printf("%d", test1);

    return 0;
}


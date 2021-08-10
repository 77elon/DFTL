#include "init.h"
#include "ssd.h"

int main()
{
    struct ssd_info* ssd;
    ssd = (struct ssd_info*)malloc(sizeof(struct ssd_info));
    
    init_ssd(ssd);
    
    
    printf("hello\n");
    
    SSD_write(ssd, 0, 0, 0, 0, 0, 0, "테슼");
    SSD_write(ssd, 0, 0, 0, 0, 0, 0, "테슼");
    SSD_write(ssd, 0, 0, 0, 0, 0, 0, "테슼");
    SSD_write(ssd, 0, 0, 0, 0, 0, 0, "테슼");
    
    SSD_read(ssd, 0, 0, 0, 0, 0, 0);
    printf("%d\n", ssd-> parameter ->write_count);
    
    return 0;
}


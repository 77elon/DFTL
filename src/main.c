#include "init.h"
#include "ssd.h"
#include "print.h"

int main()
{
    struct ssd_info* ssd;
    ssd = (struct ssd_info*)malloc(sizeof(struct ssd_info));
    
    init_ssd(ssd, 'p');
    
    
    printf("hello\n");
    
    FTL_write(ssd, 0, "Test1");
    SSD_write(ssd, 0, 0, 0, 0, 2, 0, "Test2");
    //SSD_write(ssd, 0, 0, 0, 0, 0, 0, "테슼");
    //SSD_write(ssd, 0, 0, 0, 0, 0, 0, "테슼");
    
    //SSD_read(ssd, 0, 0, 0, 0, 0, 0);
    printf("%d\n", ssd->parameter->write_count);
    
    printf("%d\n", ssd->dram->pmap[4].lbn);
    
    //print_mappingTable(ssd->dram->pmap, ssd->parameter, 'p');		// mapping table을 .txt 파일에 출력
    
    //Erase Test
    
    SSD_erase(ssd, 0, 0, 0, 0, 0);
    SSD_read(ssd, 0, 0, 0, 0, 0, 0);
    SSD_read(ssd, 0, 0, 0, 0, 1, 0);
    SSD_read(ssd, 0, 0, 0, 0, 2, 0);
    
    
    printf("%d \n", ssd->dram->pmap[1].lpn);
    printf("%d \n", ssd->dram->pmap[1].ppn);
    
    return 0;
}


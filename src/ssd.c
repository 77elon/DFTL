#include "init.h"
#include "ssd.h"

void FTL_read(struct ssd_info *ssd, unsigned int lpn)
{
    struct mapping_table *mp = ssd->dram->pmap;
    if(mp[lpn].state == 1) //is Valid, not inValid or empty..
    {
        unsigned int ppn = mp[lpn].ppn;
        
        struct calc_loc ret = get_location(ssd, ppn, 0);
        unsigned int ch, way, die, plane, block, page;
        
        ch = ret . ch;
        way = ret . way;
        die = ret . die;
        plane = ret . plane;
        block = ret . block;
        page = ret . page;
        
        SSD_read(ssd, ch, way, die, plane, block, page);
    }
    
}

void FTL_write(struct ssd_info *ssd, unsigned int lpn, char* input)
{
    struct mapping_table *mp = ssd->dram->pmap;
    
    /*only Debugging*/
    //mapping_update(mp, 0, 0);
    int iter_count = 0;
    if(mp[lpn].ppn != -1)
    {
        iter_count = mp[lpn].ppn;
    }

    while(mp[lpn].ppn != -1)
    {
        ++mp[lpn].ppn;
    }
    mapping_update(mp, lpn, iter_count);
    //mp[lpn].ppn = iter_count;
    
    unsigned int ppn = mp[lpn].ppn;
    struct calc_loc ret = get_location(ssd, ppn, 0);
    unsigned int ch, way, die, plane, block, page;
    
    ch = ret . ch;
    way = ret . way;
    die = ret . die;
    plane = ret . plane;
    block = ret . block;
    page = ret . page;
    
    
    SSD_write(ssd, ch, way, die, plane, block, page, input);
    
}

void FTL_erase(struct ssd_info *ssd, unsigned int lpn)
{
    struct mapping_table *mp = ssd->dram->pmap;
    unsigned int ppn = mp[lpn].ppn;
    
    struct calc_loc ret = get_location(ssd, ppn, '\1');
    unsigned int ch, way, die, plane, block;
    
    ch = ret . ch;
    way = ret . way;
    die = ret . die;
    plane = ret . plane;
    block = ret . block;
    
    SSD_erase(ssd, ch, way, die, plane, block);
    
}


/* plain operations */
void SSD_read(struct ssd_info* ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block, unsigned int I_page)
{
    if (ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page[I_page].data != NULL) {
        ssd->parameter->read_count++;
        printf("%s\n", ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page[I_page].data);
    }
    else
        printf("page is Empty\n");
    
}

void SSD_write(struct ssd_info* ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block, unsigned int I_page, char* input)
{
    if (ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page[I_page].data == NULL) {
        //ssd -> channel [I_ch].way[I_chip]. die [I_die] .plane[I_plane] .block [I_block] .page[I_page].spare -> lpn = lpn;
        ssd->parameter->write_count++;
        
        //lpn has written data
        //strcpy(ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page[I_page].data, input);
        ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page[I_page].data = input;
        //mapping_update(ssd->dram->pmap, 1, 2);
        
    }
    else
        printf("is full\n");
}

void SSD_erase(struct ssd_info* ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block)
{
    /*if Block Object isDeleted*/
    //unsigned int b_erase_count = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].erase_count;
    //unsigned int b_lbn = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].lbn;
    //unsigned int b_pbn = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . pbn;
    //int b_OOB = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . OOB;
    
    free(ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page);
    for (int i = 0; i < PAGE_NUM; i++)
    {
        struct page_info* erase_page;
        erase_page = ssd->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page;
        init_page(erase_page);
    }
    
    /*backed data restore*/
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].erase_count = b_erase_count;
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].lbn = b_lbn;
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . pbn = b_pbn;
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . OOB = b_OOB;
    
    ssd->parameter->erase_count++;
}

#include "init.h"

/* plain operations */
void SSD_read (struct ssd_info * ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block, unsigned int I_page)
{
    printf("%s", ssd ->channel[I_ch].way[I_chip].die[I_die].plane[I_plane].block[I_block].page[I_page].data);
}

void SSD_write (struct ssd_info * ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block, unsigned int I_page, char * input)
{
    
    //ssd -> channel [I_ch].way[I_chip]. die [I_die] .plane[I_plane] .block [I_block] .page[I_page].spare -> lpn = lpn;
    ssd -> channel [I_ch] .way[I_chip] .die [I_die] . plane[I_plane] . block [I_block] . page[I_page] . spare -> write_count++;
    
    //lpn has written data
    strcpy(ssd -> channel [I_ch] .way[I_chip] .die [I_die] . plane[I_plane] .block [I_block] . page[I_page].data, input);
}

void SSD_erase (struct ssd_info * ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block)
{
    free(ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block]. page);
    
    
    struct page_info * Empty_page = NULL;
    struct spare_page_info * Empty_sp = NULL;
    
    Empty_page = init_page(Empty_page);
    Empty_sp = init_spare_page(Empty_sp);
    
    ssd -> channel [I_ch].way[I_chip].die [I_die] . plane[I_plane]. block [I_block] .erase_count++;
}


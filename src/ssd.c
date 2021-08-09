#include "init.h"
#include "ssd.h"

void block_info_restore(struct ssd_info * ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block)
{


}

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
    unsigned int b_erase_count = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].erase_count;
    unsigned int b_lbn = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].lbn;
    unsigned int b_pbn = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . pbn;
    int b_OOB = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . OOB;

    free(ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . page);
    for (int i = 0; i < PAGE_NUM; i++)
    {
        struct page_info* erase_page;
        erase_page = ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block[I_block] . page;
        init_page(erase_page);
    }

    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].erase_count = b_erase_count;
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block].lbn = b_lbn;
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . pbn = b_pbn;
    //ssd -> channel [I_ch].way[I_chip]. die [I_die].plane[I_plane].block [I_block] . OOB = b_OOB;

    ssd -> channel [I_ch].way[I_chip].die [I_die] . plane[I_plane]. block [I_block] .erase_count++;
}


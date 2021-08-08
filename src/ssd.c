#include "init.h"

void SSD_read (struct ssd_info * ssd, unsigned int channel, unsigned int chip, unsigned int die, unsigned int plane, unsigned int block, unsigned int page);
void SSD_write (struct ssd_info * ssd, unsigned int channel, unsigned int chip, unsigned int die, unsigned int plane, unsigned int block, unsigned int page, unsigned int input);
void SSD_erase (struct ssd_info * ssd, unsigned int channel, unsigned int chip, unsigned int die, unsigned int plane, unsigned int block);


/* plain operations */
void SSD_read (struct ssd_info * ssd, unsigned int channel, unsigned int chip, unsigned int die, unsigned int plane, unsigned int block, unsigned int page)
{
    printf("%s", ssd -> channel[channel] -> way [chip] -> die [die] -> plane [plane] -> block [block] -> page[page]->state);
}

void SSD_write (struct ssd_info * ssd, unsigned int channel, unsigned int chip, unsigned int die, unsigned int plane, unsigned int block, unsigned int page, unsigned int lpn)
{

    ssd -> channel [channel] ->way[chip] -> die [die] -> plane[plane] ->block [block] -> page[page]->spare -> lpn = lpn;
    ssd -> channel [channel] ->way[chip] -> die [die] -> plane[plane] ->block [block] -> page[page]->spare -> write_count++;

    //lpn has written data
    char temp = (char)lpn; //type casting
    strcpy(ssd -> channel [channel] ->way[chip] -> die [die] -> plane[plane] ->block [block] -> page[page]->data, &temp);
}

void SSD_erase (struct ssd_info * ssd, unsigned int channel, unsigned int chip, unsigned int die, unsigned int plane, unsigned int block)
{
    memset(ssd -> channel [channel] ->way[chip] -> die [die] -> plane[plane] ->block [block] -> page, '/0', PAGE_NUM);
    struct page_info * Empty_page = NULL;
    struct spare_page_info * Empty_sp = NULL;
    
    Empty_page = init_page(Empty_page);
    Empty_sp = init_spare_page(Empty_sp);
    
    ssd -> channel [channel] ->way[chip] -> die [die] -> plane[plane] ->block [block] ->erase_count++;
    
}


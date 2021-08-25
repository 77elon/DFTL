#include "init.h"
#include "dram.h"

void mapping_update(struct mapping_table* mp, int logical, int physical)
{
    mp[logical].lpn = logical;
    mp[logical].ppn = physical;
    mp[logical / PAGE_NUM].lbn = logical / PAGE_NUM;
    mp[logical / PAGE_NUM].pbn = physical / PAGE_NUM;
}


struct calc_loc get_location(struct ssd_info *ssd, unsigned int ppn, char status) //status == 0 (page read), 1 (block erase)
{
    //per page_block,,,
    unsigned int page_per_block = PAGE_NUM;
    unsigned int page_per_plane = page_per_block * BLOCK_NUM;
    unsigned int page_per_die = page_per_plane * PLANE_NUM;
    unsigned int page_per_chip = page_per_die * DIE_NUM;
    unsigned int page_per_channel = page_per_chip * WAY_NUM;
    
    //... number, result
    //unsigned int ch, way, die, plane, block, page;
    struct calc_loc ret_object;
    
    //step 1. calc ch
    ret_object.ch = ppn / page_per_channel; //0 - (PAGE_NUM-1) pages...
    
    //step 2. calc chip
    ret_object.way = (ppn % page_per_channel) / page_per_chip; //
    
    //step 3. calc die
    ret_object.die = (ppn % page_per_channel % page_per_chip) / page_per_die;
    
    //step 4. calc plane
    ret_object.plane = (ppn % page_per_channel % page_per_chip % page_per_die) / page_per_plane;
    
    //step 5. calc block
    ret_object.block = (ppn % page_per_channel % page_per_chip % page_per_die % page_per_plane) / page_per_block; //(PAGE_NUM)
    if(status == '\0') //plain location
    {
        //step 6. calc page
        ret_object.page = ppn % page_per_channel % page_per_chip % page_per_die % page_per_plane % page_per_block;
    }
    else if(status == '\1') //erase operation, no page return
    {
        ret_object.page = -1;
    }
    else
    {
        
    }
    printf("%d, %d, %d, %d, %d, %d, %d", ppn, ret_object.ch, ret_object.way, ret_object.die, ret_object.plane, ret_object.block, ret_object.page);
    //return Object or nums
    return ret_object; // -->
}

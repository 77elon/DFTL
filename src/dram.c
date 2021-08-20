
#include "init.h"

void mapping_update(struct mapping_table* mp, int logical, int physical)
{
    mp[logical].lpn = logical;
    mp[logical].ppn = physical;
    mp[logical / PAGE_NUM].lbn = logical / PAGE_NUM;
    mp[logical / PAGE_NUM].pbn = physical / PAGE_NUM;
}

void get_location(struct ssd_info *ssd, char status, unsigned int ppn)
{
    //... number
    unsigned int ch, way, die, plane, block, page;
    
    //dynamic allocation
    if(status == '\0')
    {
        
    }
    //static allocation
    else
    {
        
    }
}

#include "init.h"

struct spare_page_info* init_spare_page(struct spare_page_info* spare) {
    spare = (struct spare_page_info*)malloc(sizeof(struct spare_page_info));
    
    // 논의 필요
    if (spare != NULL)
    {
        spare->lpn = -1;
        return spare;
    }
    else {
        // Error on Xcode
        return NULL;
    }
}

struct page_info* init_page(struct page_info* page) {
    struct spare_page_info* p_spare;
    
    page->data = malloc(SECTOR_SIZE * PAGE_SIZE * 2);
    page->data = NULL;
    page->state = -1;
    page->test = 123;
    
    p_spare = (page->spare);
    init_spare_page(p_spare);
    
    return page;
}

struct block_info* init_block(struct block_info* block, struct parameter_value* p) {
    struct page_info* p_page;
    
    block->erase_count = 0;
    block->OOB = PAGE_NUM - 1;        // 항상 마지막 페이지
    
    // 수정필요
    block->lbn = 0;
    block->pbn = 0;
    
    block->page = (struct page_info*)malloc(PAGE_NUM * sizeof(struct page_info));
    
    if (block->page != NULL)
    {
        for (int i = 0; i < PAGE_NUM; i++)
        {
            p_page = &(block->page[i]);
            init_page(p_page);              // 블록 페이지 수 만큼 초기화
        }
        
        return block;
    }
    else
    {
        return NULL;
    }
}

struct plane_info* init_plane(struct plane_info* plane, struct parameter_value* p) {
    struct block_info* p_block;
    
    
    plane->block = (struct block_info*)malloc(BLOCK_NUM * sizeof(struct block_info));
    
    if (plane->block != NULL)
    {
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            p_block = &(plane->block[i]);
            init_block(p_block, p);                  // 플래인 블록 수 만큼 초기화
        }
        
        return plane;
    }
    else
    {
        return NULL;
    }
    
}

struct die_info* init_die(struct die_info* die, struct parameter_value* p) {
    struct plane_info* p_plane;
    
    die->isBusy = IDLE;
    
    die->plane = (struct plane_info*)malloc(PLANE_NUM * sizeof(struct plane_info));
    
    if (die->plane != NULL)
    {
        for (int i = 0; i < PLANE_NUM; i++)
        {
            p_plane = &(die->plane[i]);
            init_plane(p_plane, p);                  // 다이 플래인 수 만큼 초기화
        }
        
        return die;
    }
    else
    {
        return NULL;
    }
    
}

struct way_info* init_way(struct way_info* way, struct parameter_value* p) {
    struct die_info* p_die;
    
    way->isBusy = IDLE;
    
    way->die = (struct die_info*)malloc(DIE_NUM * sizeof(struct die_info));
    
    if (way->die != NULL)
    {
        for (int i = 0; i < DIE_NUM; i++)
        {
            p_die = &(way->die[i]);
            init_die(p_die, p);                  // 칩 다이 수만큼 초기화
        }
        return way;
    }
    else
    {
        return NULL;
    }
    
}

struct channel_info* init_channel(struct channel_info* channel, struct parameter_value* p) {
    struct way_info* p_way;
    
    channel->isBusy = IDLE;
    
    channel->way = (struct way_info*)malloc(WAY_NUM * sizeof(struct way_info));
    if (channel->way != NULL)
    {
        for (int i = 0; i < WAY_NUM; i++)
        {
            p_way = &(channel->way[i]);
            init_way(p_way, p);                  // 채널 칩 수 만큼 초기화
        }
        
        return channel;
    }
    else
    {
        return NULL;
    }
    
}

struct ssd_info* init_ssd(struct ssd_info* ssd, char choice) {
    struct channel_info* p_channel;
    struct parameter_value* p;
    struct dram_info* p_dram;
    
    p = init_parameter(ssd->parameter);
    ssd->parameter = p;
    
    ssd->dram = (struct dram_info*)malloc(sizeof(struct dram_info));							// dram 공간 할당
    ssd->channel = (struct channel_info*)malloc(CHANNEL_NUM * sizeof(struct channel_info));		// channel 공간 할당
    
    p_dram = ssd->dram;
    select_table(p_dram, choice);					// mapping table 선택
    
    if (ssd->channel != NULL)
    {
        for (int i = 0; i < CHANNEL_NUM; i++)
        {
            p_channel = &(ssd->channel[i]);
            init_channel(p_channel, p);                  // 채널 수 만큼 초기화
        }
        
        return ssd;
    }
    else
    {
        return NULL;
    }
    
}

//struct dram_info* mapping_table(struct dram_info* dram) {
//	struct mapping_table* p_pmap;
//	struct mapping_table* p_bmap;
//	struct mapping_table* p_cache;
//
//	dram->pmap = (struct mapping_table*)malloc(MP_SIZE * 256 * 1024 * sizeof(struct mapping_table));
//	dram->bmap = (struct mapping_table*)malloc(MP_SIZE * 256 * 1024 * sizeof(struct mapping_table));
//	dram->cache = (struct mapping_table*)malloc(CACHE_SIZE * 256 * 1024 * sizeof(struct mapping_table));
//
//	for (int i = 0; i < MP_SIZE * 256 * 1024; i++)
//	{
//		p_pmap = &(dram->pmap[i]);
//		init_mapping_table(p_pmap);                  // 채널 수 만큼 초기화
//	}
//
//	for (int i = 0; i < MP_SIZE * 256 * 1024; i++)
//	{
//		p_bmap = &(dram->bmap[i]);
//		init_mapping_table(p_bmap);                  // 채널 수 만큼 초기화
//	}
//
//	for (int i = 0; i < CACHE_SIZE * 256 * 1024; i++)
//	{
//		p_cache = &(dram->cache[i]);
//		init_mapping_table(p_cache);                  // 채널 수 만큼 초기화
//	}
//	
//	return dram;
//}

void select_table(struct dram_info* dram, char choice) {
    switch (choice) {
        case 'p':
            init_page_mapping(dram);			// page mapping
            break;
            
        case 'b':
            init_block_mapping(dram);			// block mapping
            break;
            
        case 'c':
            init_cache_mapping(dram);			// DFTL mapping table
            break;
    }
}

struct dram_info* init_page_mapping(struct dram_info* dram) {
    struct mapping_table* p_pmap;
    
    dram->pmap = (struct mapping_table*)malloc(MP_SIZE * 256 * 1024 * sizeof(struct mapping_table));
    
    if (dram->pmap != NULL)
    {
        for (int i = 0; i < MP_SIZE * 256 * 1024; i++)
        {
            p_pmap = &(dram->pmap[i]);
            init_mapping_table(p_pmap);                  // 채널 수 만큼 초기화
        }
    }
    
    for (int i = 0; i < MP_SIZE * 256 * 1024; i++)
    {
        dram->pmap[i].lbn = i;
        dram->pmap[i].lpn = i;
    }
    
    return dram;
}

struct dram_info* init_block_mapping(struct dram_info* dram) {
    struct mapping_table* p_bmap;
    
    dram->bmap = (struct mapping_table*)malloc(MP_SIZE * 256 * 1024 * sizeof(struct mapping_table));
    
    if (dram->bmap != NULL)
    {
        for (int i = 0; i < MP_SIZE * 256 * 1024; i++)
        {
            p_bmap = &(dram->bmap[i]);
            init_mapping_table(p_bmap);
        }
    }
    
    for (int i = 0; i < MP_SIZE * 256 * 1024; i++)
    {
        dram->pmap[i].lbn = i;
        dram->pmap[i].lpn = i;
    }
    
    return dram;
}

struct dram_info* init_cache_mapping(struct dram_info* dram) {
    struct mapping_table* p_cache;
    
    dram->cache = (struct mapping_table*)malloc(CACHE_SIZE * 256 * 1024 * sizeof(struct mapping_table));
    
    if (dram->cache != NULL)
    {
        for (int i = 0; i < CACHE_SIZE * 256 * 1024; i++)
        {
            p_cache = &(dram->cache[i]);
            init_mapping_table(p_cache);
        }
    }
    
    for (int i = 0; i < CACHE_SIZE * 256 * 1024; i++)
    {
        dram->pmap[i].lbn = i;
        dram->pmap[i].lpn = i;
    }
    
    return dram;
}

struct mapping_table* init_mapping_table(struct mapping_table* mp) {
    //if Dynamic allocation
    mp->lpn = -1;
    mp->ppn = -1;
    
    mp->lbn = -1;
    mp->pbn = -1;
    
    mp->state = -1;
    
    return mp;
}

struct ac_time_characteristics* init_time(struct ac_time_characteristics* time) {
    time = (struct ac_time_characteristics*)malloc(sizeof(struct ac_time_characteristics));
    // 초기 값 넣으면 댑니다.
    if (time != NULL)
    {
        time->tPROG = 0;     //program time
        time->tDBSY = 0;     //bummy busy time for two-plane program
        time->tBERS = 0;     //block erase time
        time->tPROGO = 0;    //one shot program time
        time->tERSL = 0;       //the trans time of suspend / resume operation
        time->tCLS = 0;      //CLE setup time
        time->tCLH = 0;      //CLE hold time
        time->tCS = 0;       //CE setup time
        time->tCH = 0;       //CE hold time
        time->tWP = 0;       //WE pulse width
        time->tALS = 0;      //ALE setup time
        time->tALH = 0;      //ALE hold time
        time->tDS = 0;       //data setup time
        time->tDH = 0;       //data hold time
        time->tWC = 0;       //write cycle time
        time->tWH = 0;       //WE high hold time
        time->tADL = 0;      //address to data loading time
        time->tR = 0;        //data transfer from cell to register
        time->tAR = 0;       //ALE to RE delay
        time->tCLR = 0;      //CLE to RE delay
        time->tRR = 0;       //ready to RE low
        time->tRP = 0;       //RE pulse width
        time->tWB = 0;       //WE high to busy
        time->tRC = 0;       //read cycle time
        time->tREA = 0;      //RE access time
        time->tCEA = 0;      //CE access time
        time->tRHZ = 0;      //RE high to output hi-z
        time->tCHZ = 0;      //CE high to output hi-z
        time->tRHOH = 0;     //RE high to output hold
        time->tRLOH = 0;     //RE low to output hold
        time->tCOH = 0;      //CE high to output hold
        time->tREH = 0;      //RE high to output time
        time->tIR = 0;       //output hi-z to RE low
        time->tRHW = 0;      //RE high to WE low
        time->tWHR = 0;      //WE high to RE low
        time->tRST = 0;      //device resetting time
        
        return time;
    }
    else
    {
        return NULL;
    }
    
};

struct parameter_value* init_parameter(struct parameter_value* parameter) {
    parameter = (struct parameter_value*)malloc(sizeof(struct parameter_value));
    
    if (parameter != NULL)
    {
        // parameter->channel_num = 5;
        // parameter->way_channel = 5;
        // parameter->die_way = 5;
        // parameter->plane_die = 2;
        // parameter->block_plane = 60;
        // parameter->page_block = 32;
        
        parameter->data_block_num = -1;
        parameter->translation_block_num = -1;
        parameter->page_num = PAGE_NUM * BLOCK_NUM * PLANE_NUM * DIE_NUM * WAY_NUM * CHANNEL_NUM;		// 전체 페이지 수
        
        parameter->write_count = 0;
        parameter->read_count = 0;
        parameter->erase_count = 0;
        
        return parameter;
    }
    else
    {
        return NULL;
    }
    
}

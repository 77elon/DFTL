#include "init.h"


struct spare_page_info* init_spare_page(struct spare_page_info* spare) {
	spare = (struct spare_page_info*)malloc(sizeof(struct spare_page_info));
	spare->write_count = 0;

	// 논의 필요
	spare->lpn = 0;

	return spare;
}

struct page_info* init_page(struct page_info* page) {
	struct spare_page_info* p_spare;
	page->data = malloc(SECTOR_SIZE * PAGE_SIZE * 2);
	
	page->state = "null";
	page->test = 123;

    p_spare = (page->spare);
	init_spare_page(p_spare);

	return page;
}

struct block_info* init_block(struct block_info* block) {
	struct page_info* p_page;

	block->erase_count = 0;
	block->OOB = PAGE_NUM - 1;        // 항상 마지막 페이지

	// 수정필요
	block->lbn = 0;
	block->pbn = 0;

	block->page = (struct page_info*)malloc(PAGE_NUM * sizeof(struct page_info));

	for (int i = 0; i < PAGE_NUM; i++)
	{
		p_page = &(block->page[i]);
		init_page(p_page);              // 블록 페이지 수 만큼 초기화
	}

	return block;
}

struct plane_info* init_plane(struct plane_info* plane) {
	struct block_info* p_block;


	plane->block = (struct block_info*)malloc(BLOCK_NUM * sizeof(struct block_info));
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		p_block = &(plane->block[i]);
		init_block(p_block);                  // 플래인 블록 수 만큼 초기화
	}

	return plane;
}

struct die_info* init_die(struct die_info* die) {
	struct plane_info* p_plane;

	die->isBusy = "idle";

	die->plane = (struct plane_info*)malloc(PLANE_NUM * sizeof(struct plane_info));
	for (int i = 0; i < PLANE_NUM; i++)
	{
		p_plane = &(die->plane[i]);
		init_plane(p_plane);                  // 다이 플래인 수 만큼 초기화
	}

	return die;
}

struct way_info* init_way(struct way_info* way) {
	struct die_info* p_die;

	way->isBusy = "idle";

	way->die = (struct die_info*)malloc(DIE_NUM * sizeof(struct die_info));
	for (int i = 0; i < DIE_NUM; i++)
	{
		p_die = &(way->die[i]);
		init_die(p_die);                  // 칩 다이 수만큼 초기화
	}

	return way;
}

struct channel_info* init_channel(struct channel_info* channel) {
	struct way_info* p_way;

	channel->isBusy = "idle";

	channel->way = (struct way_info*)malloc(WAY_NUM * sizeof(struct way_info));
	for (int i = 0; i < WAY_NUM; i++)
	{
		p_way = &(channel->way[i]);
		init_way(p_way);                  // 채널 칩 수 만큼 초기화
	}

	return channel;
}


struct ssd_info* init_ssd(struct ssd_info* ssd) {
	struct channel_info* p_channel;

	ssd->channel = (struct channel_info*)malloc(CHANNEL_NUM * sizeof(struct channel_info));
	for (int i = 0; i < CHANNEL_NUM; i++)
	{
		p_channel = &(ssd->channel[i]);
		init_channel(p_channel);                  // 채널 수 만큼 초기화
	}

	return ssd;
}

struct ac_time_characteristics* init_time(struct ac_time_characteristics* time) {
	// 초기 값 넣으면 댑니다.

	int tPROG = 0;     //program time
	int tDBSY = 0;     //bummy busy time for two-plane program
	int tBERS = 0;     //block erase time
	int tPROGO = 0;    //one shot program time
	int tERSL = 0;       //the trans time of suspend / resume operation
	int tCLS = 0;      //CLE setup time
	int tCLH = 0;      //CLE hold time
	int tCS = 0;       //CE setup time
	int tCH = 0;       //CE hold time
	int tWP = 0;       //WE pulse width
	int tALS = 0;      //ALE setup time
	int tALH = 0;      //ALE hold time
	int tDS = 0;       //data setup time
	int tDH = 0;       //data hold time
	int tWC = 0;       //write cycle time
	int tWH = 0;       //WE high hold time
	int tADL = 0;      //address to data loading time
	int tR = 0;        //data transfer from cell to register
	int tAR = 0;       //ALE to RE delay
	int tCLR = 0;      //CLE to RE delay
	int tRR = 0;       //ready to RE low
	int tRP = 0;       //RE pulse width
	int tWB = 0;       //WE high to busy
	int tRC = 0;       //read cycle time
	int tREA = 0;      //RE access time
	int tCEA = 0;      //CE access time
	int tRHZ = 0;      //RE high to output hi-z
	int tCHZ = 0;      //CE high to output hi-z
	int tRHOH = 0;     //RE high to output hold
	int tRLOH = 0;     //RE low to output hold
	int tCOH = 0;      //CE high to output hold
	int tREH = 0;      //RE high to output time
	int tIR = 0;       //output hi-z to RE low
	int tRHW = 0;      //RE high to WE low
	int tWHR = 0;      //WE high to RE low
	int tRST = 0;      //device resetting time

	return time;
};

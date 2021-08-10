#include "init.h"

struct spare_page_info* init_spare_page(struct spare_page_info* spare) {
	spare = (struct spare_page_info*)malloc(sizeof(struct spare_page_info));

	// 논의 필요
	spare->lpn = -1;

	return spare;
}

struct page_info* init_page(struct page_info* page) {
	struct spare_page_info* p_spare;

	page->data = malloc(SECTOR_SIZE * PAGE_SIZE * 2);	
	page->data = NULL;
	page->state = -1;
	page->test = 123;

	p_spare = &(page->spare);
	init_spare_page(p_spare);

	return page;
}

struct block_info* init_block(struct block_info* block, struct parameter_value* p) {
	struct page_info* p_page;

	block->erase_count = 0;
	block->OOB = p->page_block - 1;        // 항상 마지막 페이지

	// 수정필요
	block->lbn = 0;
	block->pbn = 0;

	block->page = (struct page_info*)malloc(PAGE_NUM * sizeof(struct page_info));

	for (int i = 0; i < PAGE_NUM; i++)
	{
		p_page = &(block->page[i]);
		init_page(p_page, p);              // 블록 페이지 수 만큼 초기화
	}

	return block;
}

struct plane_info* init_plane(struct plane_info* plane, struct parameter_value* p) {
	struct block_info* p_block;


	plane->block = (struct block_info*)malloc(BLOCK_NUM * sizeof(struct block_info));
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		p_block = &(plane->block[i]);
		init_block(p_block, p);                  // 플래인 블록 수 만큼 초기화
	}

	return plane;
}

struct die_info* init_die(struct die_info* die, struct parameter_value* p) {
	struct plane_info* p_plane;

	die->isBusy = IDLE;

	die->plane = (struct plane_info*)malloc(PLANE_NUM * sizeof(struct plane_info));
	for (int i = 0; i < PLANE_NUM; i++)
	{
		p_plane = &(die->plane[i]);
		init_plane(p_plane, p);                  // 다이 플래인 수 만큼 초기화
	}

	return die;
}

struct way_info* init_way(struct way_info* way, struct parameter_value* p) {
	struct die_info* p_die;

	way->isBusy = IDLE;

	way->die = (struct die_info*)malloc(p->DIE_NUM * sizeof(struct die_info));
	for (int i = 0; i < p->DIE_NUM; i++)
	{
		p_die = &(way->die[i]);
		init_die(p_die, p);                  // 칩 다이 수만큼 초기화
	}

	return way;
}

struct channel_info* init_channel(struct channel_info* channel, struct parameter_value* p) {
	struct way_info* p_way;

	channel->isBusy = IDLE;

	channel->way = (struct way_info*)malloc(WAY_NUM * sizeof(struct way_info));
	for (int i = 0; i < p->WAY_NUM; i++)
	{
		p_way = &(channel->way[i]);
		init_way(p_way, p);                  // 채널 칩 수 만큼 초기화
	}

	return channel;
}

struct ssd_info* init_ssd(struct ssd_info* ssd) {
	struct channel_info* p_channel;
	struct parameter_value* p;

	p = init_parameter(ssd->parameter);
	ssd->parameter = p;

	ssd->channel = (struct channel_info*)malloc(CHANNEL_NUM * sizeof(struct channel_info));

	for (int i = 0; i < CHANNEL_NUM; i++)
	{
		p_channel = &(ssd->channel[i]);
		init_channel(p_channel, p);                  // 채널 수 만큼 초기화
	}

	return ssd;
}

//struct dram_info* page_mapping(struct dram_info* dram) {
//	struct mapping_table* pmap;
//
//	dram->pmap = (struct mapping_table*)malloc(CHANNEL_NUM * sizeof(struct mapping_table));
//	
//	return dram;
//}

struct ac_time_characteristics* init_time(struct ac_time_characteristics* time) {
	time = (struct ac_time_characteristics*)malloc(sizeof(struct ac_time_characteristics));
	// 초기 값 넣으면 댑니다.

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
};

struct parameter_value* init_parameter(struct parameter_value *parameter){
	parameter = (struct parameter_value*)malloc(sizeof(struct parameter_value));

	// parameter->channel_num = 5;
	// parameter->way_channel = 5;
	// parameter->die_way = 5;
	// parameter->plane_die = 2;
	// parameter->block_plane = 60;			
	// parameter->page_block = 32;

	parameter->data_block_num = -1;
	parameter->translation_block_num = -1;
	parameter->page_num = parameter->page_block * parameter->block_plane * 
		parameter->plane_die * parameter->die_way * parameter->way_channel * parameter->channel_num;		// 전체 페이지 수

	parameter->write_count = 0;
	parameter->read_count = 0;
	parameter->erase_count = 0;
	
	return parameter;
}

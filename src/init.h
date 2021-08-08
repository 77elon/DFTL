#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

#define CHANNEL_NUM 5
#define WAY_NUM 5
#define DIE_NUM 4
#define PLANE_NUM 4

#define BLOCK_NUM 10
#define DATA_BLOCK_NUM 10

// DFTL
#define TRANSLATION_BLOCK_NUM 2

#define PAGE_NUM 32

#define SECTOR_SIZE 512
#define PAGE_SIZE 4

struct ssd_info {

	struct channel_info* channel;
};

struct channel_info {
	char* isBusy;

	struct way_info* way;

};

struct way_info {
	char* isBusy;

	struct die_info* die;
};

struct die_info {
	char* isBusy;

	struct plane_info* plane;
};

struct plane_info {

	// struct block_info *data_block;
	// struct block_info *translation_block;
	struct block_info* block;
};

struct block_info {
	unsigned int erase_count;
	unsigned int lbn;
	unsigned int pbn;
	int OOB;


	// struct page_info *data_page;
	// struct page_info *translation_page;
	struct page_info* page;
};

struct page_info {
	char* state;
	char* data;
	int test;

	struct spare_page_info* spare;
};

struct spare_page_info
{
	unsigned int lpn;
	unsigned int write_count;

};

struct ac_time_characteristics {
	int tPROG;     //program time
	int tDBSY;     //bummy busy time for two-plane program
	int tBERS;     //block erase time
	int tPROGO;    //one shot program time
	int tERSL;       //the trans time of suspend / resume operation
	int tCLS;      //CLE setup time
	int tCLH;      //CLE hold time
	int tCS;       //CE setup time
	int tCH;       //CE hold time
	int tWP;       //WE pulse width
	int tALS;      //ALE setup time
	int tALH;      //ALE hold time
	int tDS;       //data setup time
	int tDH;       //data hold time
	int tWC;       //write cycle time
	int tWH;       //WE high hold time
	int tADL;      //address to data loading time
	int tR;        //data transfer from cell to register
	int tAR;       //ALE to RE delay
	int tCLR;      //CLE to RE delay
	int tRR;       //ready to RE low
	int tRP;       //RE pulse width
	int tWB;       //WE high to busy
	int tRC;       //read cycle time
	int tREA;      //RE access time
	int tCEA;      //CE access time
	int tRHZ;      //RE high to output hi-z
	int tCHZ;      //CE high to output hi-z
	int tRHOH;     //RE high to output hold
	int tRLOH;     //RE low to output hold
	int tCOH;      //CE high to output hold
	int tREH;      //RE high to output time
	int tIR;       //output hi-z to RE low
	int tRHW;      //RE high to WE low
	int tWHR;      //WE high to RE low
	int tRST;      //device resetting time
};



struct ssd_info* init_ssd(struct ssd_info* ssd);
struct channel_info* init_channel(struct channel_info* channel);
struct way_info* init_way(struct way_info* way);
struct die_info* init_die(struct die_info* die);
struct plane_info* init_plane(struct plane_info* plane);
struct block_info* init_block(struct block_info* block);
struct page_info* init_page(struct page_info* page);
struct spare_page_info* init_spare_page(struct spare_page_info* spare);
struct ac_time_characteristics* init_time(struct ac_time_characteristics* time);



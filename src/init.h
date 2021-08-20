#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHANNEL_NUM 5
#define WAY_NUM 5
#define DIE_NUM 5
#define PLANE_NUM 2
#define BLOCK_NUM 32
#define PAGE_NUM 32

// DFTL
#define DATA_BLOCK_NUM 10
#define TRANSLATION_BLOCK_NUM 2

// size
#define SECTOR_SIZE 512
#define PAGE_SIZE 4
#define DRAM_SIZE 10				// MB
#define MP_SIZE 4					// MB
#define CACHE_SIZE 1				// MB

//toggle
#define IDLE 1
#define BUSY 0

//data state
#define VALID 1
#define INVALID 0

struct ssd_info {
    
    //struct dram_info* dram;
    struct channel_info* channel;
    struct dram_info* dram;
    struct parameter_value* parameter;
};

struct channel_info {
    int isBusy;
    
    struct way_info* way;
};

struct way_info {
    int isBusy;
    
    struct die_info* die;
};

struct die_info {
    int isBusy;
    
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
    int state;
    char* data;
    int test;
    
    struct spare_page_info* spare;
};

struct spare_page_info
{
    unsigned int lpn;
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

struct parameter_value {
    unsigned int write_count;
    unsigned int read_count;
    unsigned int erase_count;
    
    unsigned int channel_num;
    unsigned int way_channel;
    unsigned int die_way;
    unsigned int plane_die;
    unsigned int block_plane;
    unsigned int page_block;
    
    unsigned int data_block_num;
    unsigned int translation_block_num;
    unsigned int page_num;
};

struct dram_info {
    unsigned int capacity;
    
    struct mapping_table* pmap;
    struct mapping_table* bmap;
    struct mapping_table* cache;
};

struct mapping_table {
    unsigned int lpn;
    unsigned int ppn;
    
    unsigned int lbn;
    unsigned int pbn;
    
    int state;
};	

struct parameter_value* init_parameter(struct parameter_value* parameter);

struct ssd_info* init_ssd(struct ssd_info* ssd, char choice);
struct channel_info* init_channel(struct channel_info* channel, struct parameter_value* p);
struct way_info* init_way(struct way_info* way, struct parameter_value* p);
struct die_info* init_die(struct die_info* die, struct parameter_value* p);
struct plane_info* init_plane(struct plane_info* plane, struct parameter_value* p);
struct block_info* init_block(struct block_info* block, struct parameter_value* p);
struct page_info* init_page(struct page_info* page);
struct spare_page_info* init_spare_page(struct spare_page_info* spare);

struct ac_time_characteristics* init_time(struct ac_time_characteristics* time);

struct mapping_table* init_mapping_table(struct mapping_table* mp);
struct dram_info* init_cache_mapping(struct dram_info* dram);
struct dram_info* init_block_mapping(struct dram_info* dram);
struct dram_info* init_page_mapping(struct dram_info* dram);
void select_table(struct dram_info* dram, char choice);


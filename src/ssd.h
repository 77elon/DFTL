
void SSD_read(struct ssd_info* ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block, unsigned int I_page);
void SSD_write(struct ssd_info* ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block, unsigned int I_page, char* input);
void SSD_erase(struct ssd_info* ssd, unsigned int I_ch, unsigned int I_chip, unsigned int I_die, unsigned int I_plane, unsigned int I_block);

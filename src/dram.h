
void mapping_update(struct mapping_table* mp, int logical, int physical);

//step 1. lpn -> ppn (translate) --> find Idle location (in dynamic allo),  step 2. ppn location find,,, (multiple ch, chip)
void get_location(struct ssd_info *ssd, unsigned int ppn);


#include "init.h"

void print_mappingTable(struct mapping_table* mp, struct parameter_value* p, char choice) {
    FILE* fp;
    char* temp = malloc(p->page_num);
    
    fp = fopen("test.txt", "wt");
    
    if (fp == NULL) {
        printf("파일열기 실패\n");
        return;
    }
    
    switch (choice) {
        case 'p':
        case 'b':
            for (int i = 0; i < MP_SIZE * 256 * 1024; i++) {
                sprintf(temp, "%d", mp[i].lpn);
                //_itoa(mp[i].lpn, temp, 10);                /* vs 에선 이거 사용 */
                fprintf(fp, "%s", temp);
                
                fprintf(fp, " ");
                
                sprintf(temp, "%d", mp[i].ppn);
                //_itoa(mp[i].ppn, temp, 10);                /* vs 에선 이거 사용 */
                fprintf(fp, "%s", temp);
                
                fprintf(fp, "\n");
            }
            break;
            
        case 'c':
            for (int i = 0; i < CACHE_SIZE * 256 * 1024; i++) {
                sprintf(temp, "%d", mp[i].lpn);
                //_itoa(mp[i].lpn, temp, 10);                /* vs 에선 이거 사용 */
                fprintf(fp, "%s", temp);
                
                fprintf(fp, " ");
                
                sprintf(temp, "%d", mp[i].ppn);
                //_itoa(mp[i].ppn, temp, 10);                /* vs 에선 이거 사용 */
                fprintf(fp, "%s", temp);
                
                fprintf(fp, "\n");
            }
            break;
    }
    
    fclose(fp);
    
    return;
}

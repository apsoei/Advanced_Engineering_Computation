#include <stdint.h>
#include <stdio.h>

bool CPUisLittleEndian(void)
{
	unsigned char input[4]={1,0,0,0};
	uint32_t *intPtr=(unsigned int *)input;
	return (*intPtr==1);
}

int main(void)
{
	printf("%d\n",CPUisLittleEndian());
	return 0;
}

#define XIP_SSI_BASE       0x18000000
#define XIP_SSI_CTRLR0     XIP_SSI_BASE + 0x00
#define XIP_SSI_CTRLR1     XIP_SSI_BASE + 0x04
#define XIP_SSI_SSIENR     XIP_SSI_BASE + 0x08
#define XIP_SSI_BAUDR      XIP_SSI_BASE + 0x14
#define XIP_SSI_SPI_CTRLR0 XIP_SSI_BASE + 0xF4

typedef volatile unsigned int addr;

#define deref(X) (*(addr*)(X))

typedef void (*NoRetFunc)();

static const NoRetFunc main = 0x20000101;

__attribute__( (  noreturn, used, retain, section( ".boot2" ) ) ) void boot2() 
{
	deref(0x00000000) = deref(XIP_SSI_SSIENR);
	deref(0x001F0300) = deref(XIP_SSI_CTRLR0);
	deref(0x00000008) = deref(XIP_SSI_BAUDR);
	deref(0x03000218) = deref(XIP_SSI_SPI_CTRLR0);
	deref(0x00000000) = deref(XIP_SSI_CTRLR1);
	deref(0x00000001) = deref(XIP_SSI_SSIENR);
	
	static addr* src = 0x10000100;
	static addr* dest = 0x20000100;
	
	for(int i = 0; i < 0x1000; ++i)
	{
		*(++dest) = *(++src);
	}
	main();
	while(1)
	{
		
	}
}
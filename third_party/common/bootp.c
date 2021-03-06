#if RASPPI == 1
#define ARM_IO_BASE		0x20000000
#elif RASPPI <= 3
#define ARM_IO_BASE		0x3F000000
#else
#define ARM_IO_BASE		0xFE000000
#endif

#define ARM_PM_BASE		(ARM_IO_BASE + 0x100000)
#define ARM_PM_RSTS   ((volatile unsigned int*)(ARM_PM_BASE +0x20))
#define ARM_PM_PASSWD		(0x5A << 24)

void select_boot_partition(int partition) {
    unsigned long r;
    // unsigned long rsts;

    // rsts = (partition & BIT(0)) | ((partition & BIT(1)) << 1) |
    //     ((partition & BIT(2)) << 2) | ((partition & BIT(3)) << 3) |
    //     ((partition & BIT(4)) << 4) | ((partition & BIT(5)) << 5);

    r = *ARM_PM_RSTS; r &= 0xfffffaaa;
    r |= 0x555;    // partition 63 used to indicate halt
    *ARM_PM_RSTS = ARM_PM_PASSWD | r;
}

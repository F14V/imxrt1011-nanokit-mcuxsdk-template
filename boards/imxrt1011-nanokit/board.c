#include "fsl_common.h"
#include "board.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/* MPU configuration. */
void BOARD_ConfigMPU(void)
{
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$RW_m_ncache$$Base[];
    extern uint32_t Image$$RW_m_ncache_unused$$Base[];
    extern uint32_t Image$$RW_m_ncache_unused$$ZI$$Limit[];
    const uint32_t nonCacheStart = (uint32_t)Image$$RW_m_ncache$$Base;
    const uint32_t size = ((uint32_t)Image$$RW_m_ncache_unused$$Base == nonCacheStart) ? 0U : ((uint32_t)Image$$RW_m_ncache_unused$$ZI$$Limit - nonCacheStart);
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_NCACHE_REGION;
    extern uint32_t __top_NCACHE_REGION;
    const uint32_t nonCacheStart = (uint32_t)(&__base_NCACHE_REGION);
    const uint32_t size = (uint32_t)(&__top_NCACHE_REGION) - nonCacheStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __NCACHE_REGION_START[] __attribute__((weak));
    extern uint32_t __NCACHE_REGION_SIZE[] __attribute__((weak));
    const uint32_t nonCacheStart = (uint32_t)__NCACHE_REGION_START;
    const uint32_t size = (uint32_t)__NCACHE_REGION_SIZE;
#endif
    /* Determine MPU regions count */
    const uint32_t regionCount = (MPU->TYPE & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos;
    assert(regionCount >= 10U);

    /* Disable I cache and D cache */
    if ((SCB->CCR & SCB_CCR_IC_Msk) != 0U)
    {
        SCB_DisableICache();
    }
    if ((SCB->CCR & SCB_CCR_DC_Msk) != 0U)
    {
        SCB_DisableDCache();
    }

    /* Disable MPU */
    ARM_MPU_Disable();

    /*
     * Region 0: Default deny
     * Range:    0x00000000-0xFFFFFFFF (4 GiB)
     * Access:   None, execute never
     * Memory:   Strongly-ordered, inherently shareable, non-cacheable, non-bufferable
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(0U, 0x00000000U),
        ARM_MPU_RASR(1U, ARM_MPU_AP_NONE, 0U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_4GB)
    );

    /*
     * Region 1: ITCM
     * Range:    0x00000000-0x00007FFF (32 KiB)
     * Access:   Read-Only, executable
     * Memory:   Normal, non-shareable, non-cacheable
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(1U, 0x00000000U),
        ARM_MPU_RASR(0U, ARM_MPU_AP_RO, 1U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_32KB)
    );

    /*
     * Region 2: ROMCP
     * Range:    0x00200000-0x0020FFFF (64 KiB)
     * Access:   Read-Only, executable
     * Memory:   Normal, non-shareable, write-back, read-allocate, no-write-allocate
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(2U, 0x00200000U),
        ARM_MPU_RASR(0U, ARM_MPU_AP_RO, 0U, 0U, 1U, 1U, 0U, ARM_MPU_REGION_SIZE_64KB)
    );

    /*
     * Region 3: DTCM
     * Range:    0x20000000-0x20007FFF (32 KiB)
     * Access:   Full, execute never
     * Memory:   Normal, non-shareable, non-cacheable
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(3U, 0x20000000U),
        ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 1U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_32KB)
    );

    /*
     * Region 4: OCRAM
     * Range:    0x20200000-0x2020FFFF (64 KiB)
     * Access:   Full, execute never
     * Memory:   Normal, non-shareable, write-back, read/write-allocate
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(4U, 0x20200000U),
        ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 1U, 0U, 1U, 1U, 0U, ARM_MPU_REGION_SIZE_64KB)
    );

    /*
     * Region 5: AIPS-1 and AIPS-2
     * Range:    0x40000000-0x401FFFFF (2 MiB)
     * Access:   Full, execute never
     * Memory:   Device, non-shareable, non-cacheable, non-bufferable
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(5U, 0x40000000U),
        ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_2MB)
    );

    /*
     * Region 6: GPIO2
     * Range:    0x42000000-0x43FFFFFF (32 MiB)
     * Access:   Full, execute never
     * Memory:   Device, non-shareable, non-cacheable, non-bufferable
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(6U, 0x42000000U),
        ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_32MB)
    );

    /*
     * Region 7: FlexSPI aperture
     * Range:    0x60000000-0x7FFFFFFF (512 MiB)
     * Access:   Full, execute never
     * Memory:   Device, non-shareable, non-cacheable, non-bufferable
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(7U, 0x60000000U),
        ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_512MB)
    );

#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    /*
     * Region 8: XIP flash override
     * Range:    0x60000000-0x60FFFFFF (16 MiB)
     * Access:   Read-Only, executable
     * Memory:   Normal, non-shareable, write-back, read-allocate, no-write-allocate
     */
    ARM_MPU_SetRegion(
        ARM_MPU_RBAR(8U, 0x60000000U),
        ARM_MPU_RASR(0U, ARM_MPU_AP_RO, 0U, 0U, 1U, 1U, 0U, ARM_MPU_REGION_SIZE_16MB)
    );
#else
    ARM_MPU_ClrRegion(8U);
#endif

    if (size != 0U)
    {
        /* Configure the optional linker-defined non-cacheable region.
         * MPU regions must be power-of-two sized, at least 32 bytes, and naturally aligned.
         */
        assert(size >= 32U);
        assert((size & (size - 1U)) == 0U);
        assert((nonCacheStart & (size - 1U)) == 0U);

        uint32_t sizeField = 0U;
        while ((size >> sizeField) > 1U)
        {
            sizeField++;
        }

        /*
         * Region 9: Non-cacheable RAM override
         * Range:    Linker-defined
         * Access:   Full, execute never
         * Memory:   Normal, non-shareable, non-cacheable
         */
        ARM_MPU_SetRegion(
            ARM_MPU_RBAR(9U, nonCacheStart),
            ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 1U, 0U, 0U, 0U, 0U, sizeField - 1U)
        );
    }
    else
    {
        ARM_MPU_ClrRegion(9U);
    }

    /* Clear remaining MPU regions */
    for (uint32_t region = 10U; region < regionCount; region++)
    {
        ARM_MPU_ClrRegion(region);
    }

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk);

    /* Enable I cache and D cache */
    SCB_EnableDCache();
    SCB_EnableICache();
}

#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
/* SystemInitHook */
void SystemInitHook(void)
{
    /* When set this bit, FlexSPI will fetch more data than AHB burst required to meet the alignment requirement. */
    FLEXSPI->AHBCR |= FLEXSPI_AHBCR_READADDROPT_MASK;
}
#endif

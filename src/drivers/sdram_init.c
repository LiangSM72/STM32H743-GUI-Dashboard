/**
 * @file sdram_init.c
 * @brief SDRAM initialization implementation
 */

#include "sdram_init.h"

/**
 * @brief Initialize FMC for SDRAM access
 */
void SDRAM_Init(void)
{
    SDRAM_HandleTypeDef hsdram1;
    FMC_SDRAM_TimingTypeDef SdramTiming = {0};
    
    /* Enable FMC clock */
    __HAL_RCC_FMC_CLK_ENABLE();
    
    /* Configure SDRAM timing parameters */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshTime = 7;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 7;
    SdramTiming.WriteRecoveryTime = 2;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;
    SdramTiming.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    SdramTiming.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
    SdramTiming.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    SdramTiming.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
    SdramTiming.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    SdramTiming.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    SdramTiming.ReadBurstLength = FMC_SDRAM_RBURST_LENGTH_2;
    SdramTiming.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram1.Init.ReadBurstLength = FMC_SDRAM_RBURST_LENGTH_2;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    
    if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
    {
        printf("[ERROR] SDRAM initialization failed!\r\n");
    }
    else
    {
        printf("[OK] SDRAM initialized successfully\r\n");
    }
}

/**
 * @brief Test SDRAM read/write functionality
 */
void SDRAM_Test(void)
{
    uint32_t test_addr = SDRAM_BANK_ADDR;
    uint32_t test_data = 0x12345678;
    uint32_t read_data = 0;
    
    /* Write test data */
    *((uint32_t *)test_addr) = test_data;
    
    /* Read back */
    read_data = *((uint32_t *)test_addr);
    
    if (read_data == test_data)
    {
        printf("[OK] SDRAM test passed\r\n");
    }
    else
    {
        printf("[ERROR] SDRAM test failed (expected 0x%08X, got 0x%08X)\r\n", 
               test_data, read_data);
    }
}

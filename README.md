# STM32H743 GUI Dashboard

完整的 STM32H743XIH6 圖形用戶界面儀表板系統，包含 5" LCD 顯示、按鍵矩陣輸入和 VS Code 開發環境。

## 📋 功能特性

✅ **完整的硬件驅動**
- LTDC LCD 驅動 (800×480, RGB565)
- 256MB SDRAM 初始化
- 4×4 矩陣鍵盤掃描 (消抖)
- PWM 背光控制 (0-100%)
- UART 調試接口 (printf 重定向)
- I2C/SPI 接口預備

✅ **現代化開發環境**
- VS Code + Cortex-Debug
- 完整的 Makefile 編譯系統
- 自動化燒錄和調試
- 代碼補全和智能感知

✅ **模塊化設計**
- 每個外設獨立驅動模塊
- 易於擴展和集成
- 詳細的中文代碼註釋

---

## 🚀 快速開始

### 1. 克隆項目

```bash
git clone https://github.com/LiangSM72/STM32H743-GUI-Dashboard.git
cd STM32H743-GUI-Dashboard
```

### 2. 配置開發環境

按照 `docs/01_開發環境配置.md` 的步驟進行

### 3. 編譯項目

```bash
make clean && make all
```

### 4. 燒錄到開發板

```bash
make flash
```

### 5. 打開串口監視器

連接 USB 轉 UART（波特率 115200）查看調試信息

---

## 📁 項目結構

```
STM32H743-GUI-Dashboard/
├── src/                          # 源代碼
│   ├── main.c                   # 主程序
│   └── drivers/                 # 驅動程序
│       ├── clock.h              # 時鐘配置
│       ├── gpio_init.h/c        # GPIO 初始化
│       ├── sdram_init.h/c       # SDRAM 驅動
│       ├── lcd_driver.h/c       # LCD LTDC 驅動
│       ├── backlight.h/c        # PWM 背光控制
│       ├── keypad.h/c           # 按鍵掃描驅動
│       └── uart_debug.h/c       # UART 調試
├── .vscode/                      # VS Code 配置
│   ├── c_cpp_properties.json    # IntelliSense
│   ├── launch.json              # 調試配置
│   └── tasks.json               # 編譯任務
├── docs/                         # 文檔
│   └── 01_開發環境配置.md
├── build/                        # 編譯輸出 (自動生成)
├── Makefile                      # 編譯配置
└── README.md                     # 項目說明
```

---

## 🛠️ 硬件連接

### LCD 接口
- **HSYNC**: PE3
- **VSYNC**: PE4
- **DE**: PE5
- **CLK**: PE2
- **Data**: PE6, PE7 等 (8080 並行接口)

### 按鍵接口
- **行 (Row)**: PB0-PB3
- **列 (Col)**: PC4-PC7

### 背光控制
- **PWM**: PE8 (TIM8_CH1)

### 調試接口
- **UART1 TX**: PA9
- **UART1 RX**: PA10

---

## 📖 代碼示例

### 初始化所有外設

```c
int main(void)
{
    HAL_Init();
    SystemClock_Config();      // 400MHz 時鐘
    UART_Debug_Init();         // 調試串口
    GPIO_Init();               // GPIO 配置
    SDRAM_Init();              // 256MB SDRAM
    LCD_Init();                // LCD LTDC
    Backlight_Init();          // 背光 PWM
    Keypad_Init();             // 按鍵掃描
    
    printf("System ready!\r\n");
    
    while (1)
    {
        Keypad_Scan();
        uint8_t key = Keypad_Get_Key();
        if (key != 0xFF)
        {
            printf("Key pressed: %d\r\n", key);
        }
    }
}
```

### LCD 繪圖

```c
/* 填充整個屏幕為黑色 */
LCD_Fill_Color(LCD_COLOR_BLACK);

/* 繪製紅色矩形 */
LCD_Draw_Filled_Rectangle(100, 100, 300, 200, LCD_COLOR_RED);

/* 繪製綠色線條 */
LCD_Draw_Line(0, 0, 799, 479, LCD_COLOR_GREEN);

/* 設置背光亮度為 50% */
Backlight_Set_Brightness(50);
```

---

## 🔧 編譯命令

| 命令 | 功能 |
|------|------|
| `make all` | 編譯所有 |
| `make clean` | 清理編譯文件 |
| `make flash` | 燒錄到開發板 |
| `make size` | 顯示二進制大小 |

---

## 📊 系統規格

| 項目 | 規格 |
|------|------|
| **CPU** | STM32H743XIH6 (Cortex-M7, 400MHz) |
| **RAM** | 256MB SDRAM + 384KB 內部 SRAM |
| **LCD** | 5" TFT (800×480, RGB565) |
| **輸入** | 4×4 矩陣鍵盤 |
| **接口** | UART, I2C, SPI, LTDC |
| **存儲** | FRAM + QSPI Flash |

---

## 🎯 下一步計劃

- [ ] LVGL 圖形庫集成
- [ ] 觸摸屏驅動
- [ ] 溫度/濕度傳感器示例
- [ ] QSPI Flash 驅動
- [ ] USB 通信功能

---

## 📞 支持與聯繫

有問題或建議？請提交 GitHub Issue：
https://github.com/LiangSM72/STM32H743-GUI-Dashboard/issues

---

## 📄 許可

MIT License

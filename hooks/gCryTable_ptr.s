
//offset        puntero     tabla
//0x08072104    0848db44    gCryTable_Reverse
.org 0x08072104
    .word gCryTable_Reverse

//0x08072114    0848c914    gCryTable
.org 0x08072114
    .word gCryTable

//0x08072128    0848e144    gCryTable_Reverse + (0x600 * 1)
.org 0x08072128
    .word gCryTable_Reverse + (0x600 * 1)

//0x08072138    0848cf14    gCryTable  + (0x600 * 1)
.org 0x08072138
    .word gCryTable  + (0x600 * 1)

//0x0807214C    0848e744    gCryTable_Reverse + (0x600 * 2)
.org 0x0807214C
    .word gCryTable_Reverse + (0x600 * 2)

//0x0807215C    0848d514    gCryTable  + (0x600 * 2)
.org 0x0807215C
    .word gCryTable  + (0x600 * 2)

//0x08072170    0848ed44    gCryTable_Reverse + (0x600 * 3)
.org 0x08072170
    .word gCryTable_Reverse + (0x600 * 3)

//0x08072198    0848db14    gCryTable + (0x600 * 3)
.org 0x08072198
    .word gCryTable + (0x600 * 3)



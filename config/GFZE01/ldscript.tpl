MEMORY
{
    text : origin = $ORIGIN
}

SECTIONS
{
    GROUP:
    {
        $SECTIONS
        .stack ALIGN(0x100):{}
    } > text

    _stack_end = $LAST_SECTION_SYMBOL + SIZEOF($LAST_SECTION_NAME);
    _stack_addr = (_stack_end + $STACKSIZE + 0x7) & ~0x7;
    _db_stack_addr = (_stack_addr + 0x2000);
    _db_stack_end = _stack_addr;
    __ArenaLo = (_db_stack_addr + 0x1f) & ~0x1f;
    __ArenaHi = $ARENAHI;

    /* Hardware register blocks: retail addresses them through linker-defined absolute symbols
       (lis/addi of the symbol, never a folded literal), as the SDK's own link script did.
       Declare them `extern vu32 __DIRegs[];` (or a register struct) in C. A name here must
       not exist in symbols.txt: GX's __cpReg/__peReg/__piReg/__memReg are .sbss pointer
       variables, not these. */
    __VIRegs = 0xCC002000;
    __PIRegs = 0xCC003000;
    __MEMRegs = 0xCC004000;
    __DSPRegs = 0xCC005000;
    __DIRegs = 0xCC006000;
    __DVDRegs = 0xCC006000;
    __SIRegs = 0xCC006400;
    SIRegs = 0xCC006400;
    __EXIRegs = 0xCC006800;
    EXIRegs = 0xCC006800;
    __AIRegs = 0xCC006C00;
    __GXFifo = 0xCC008000;
}

FORCEACTIVE
{
    $FORCEACTIVE
}

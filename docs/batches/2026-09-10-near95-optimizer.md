# Second deterministic pass over the Luna releases

Starting from the 217 remaining frozen batch candidates, optimizer probes found
seven additional exact candidates. The same proven pragma family found seven
more among 301 other saved bodies above 90%. All 14 were reproduced through the
ordinary `fixup.try_fix` path from their saved C and compiler settings.

The four settings are `peephole`, `opt_propagation`, `opt_common_subs`, and
`opt_lifetimes`, each tried off and reset after the function. Their success
establishes an exact build configuration, not proof of the original source's
pragma spelling. These probes run before declaration and register permutations.

Two further exact candidates:

- `fn_1_133BD8` (484 bytes): recover a real aggregate local from a biased array
  pointer and a fake leading field. Keep the union's array extent, and remove
  the false field and pointer bias together. This fixes all three copy origins
  without changing the already correct field accesses.
- `InitializeProgramEndTrap` (88 bytes): use the existing rename tool to give
  `EndofProgramInstruction$162` a C identifier, then let fixup bind the extern.

Together: 16 candidates, 2,984 bytes; nine from the Luna batch and seven from
the wider saved corpus. No reconstructed C was edited by hand.

The search also had a stopping bug: masked instruction equality could select a
candidate whose relocations were still wrong, hiding a later exact repair.
Every such candidate now passes the full oracle before stopping. The trap
function exercises this path: early optimizer variants preserve the wrong
binding, while the later symbol substitution matches. Sweep submission now
retains the compiler settings used to verify its repaired body.

Negative results: 191 guard variants across 24 functions and 360 accessor
variants across 52 functions closed nothing; neither generator was retained.
Other optimizer axes also found no additional candidates. Local inputs and
results are under `.fzgx/repair-near95/optimizer/`, with the accepted source
manifest in `.fzgx/repair-near95/winners2.json`.
